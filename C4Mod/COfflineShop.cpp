#include "stdafx.h"
#include "COfflineShop.h"

OfflineSocketMap COfflineShop::offlineShops;
map<u32, u32> COfflineShop::requirements;
CRITICAL_SECTION COfflineShop::cs;
u64 COfflineShop::UserSayOriginal = 0;
u64 COfflineShop::UserLeaveWorldOriginal = 0;

#ifdef DVAMP
	#define VMT_USER_SAY			OCrypt(K0, N0, 0x00A87E08L)
	#define CALL_CLOSE_IO_SOCKET_1	OCrypt(K1, N1, 0x008789C5L)
	#define CALL_CLOSE_IO_SOCKET_2	OCrypt(K2, N2, 0x00878999L)
	#define CALL_WSASEND			OCrypt(K3, N3, 0x007D6509L)
	#define CALL_WSARECV			OCrypt(K4, N4, 0x00621068L)
	#define CALL_WSPRINTF_STATS		OCrypt(K5, N5, 0x00448712L)
	#define CALL_USER_INFO_SELL		OCrypt(K6, N6, 0x008059CEL)
	#define CALL_USER_INFO_BUY		OCrypt(K7, N7, 0x00806AFEL)
	#define CALL_USER_INFO_RECIPE	OCrypt(K0, N0, 0x008080A0L)
	#define CALL_WSASEND2			OCrypt(K1, N1, 0x00621346L)
	#define OFFSET_CAN_SELL_ITEM	OCrypt(K3, N3, 0x0082AC7BL)
	#define CALL_ON_READ			OCrypt(K3, N3, 0x007D61AEL)
	#define CALL_CLOSE_SOCKET2		OCrypt(K3, N3, 0x0062316FL)
	#define SOCKET_READ_IO			OCrypt(K3, N3, 0x006211F0L)
#else
	#define VMT_USER_SAY			OCrypt(K2, N2, 0x00A87498L)
	#define CALL_CLOSE_IO_SOCKET_1	OCrypt(K3, N3, 0x00877C95L)
	#define CALL_CLOSE_IO_SOCKET_2	OCrypt(K4, N4, 0x00877C69L)
	#define CALL_WSASEND			OCrypt(K5, N5, 0x007D5959L)
	#define CALL_WSARECV			OCrypt(K6, N6, 0x006208B8L)
	#define CALL_WSPRINTF_STATS		OCrypt(K7, N7, 0x004480D2L)
	#define CALL_USER_INFO_SELL		OCrypt(K0, N0, 0x008047DEL)
	#define CALL_USER_INFO_BUY		OCrypt(K1, N1, 0x0080590EL)
	#define CALL_USER_INFO_RECIPE	OCrypt(K2, N2, 0x00806EB0L)
	#define CALL_WSASEND2			OCrypt(K3, N3, 0x00620B96L)
	#define OFFSET_CAN_SELL_ITEM	OCrypt(K3, N3, 0x00829A8BL)
	#define CALL_ON_READ			OCrypt(K3, N3, 0x007D55FEL)
	#define CALL_CLOSE_SOCKET2		OCrypt(K3, N3, 0x006229BFL)
	#define SOCKET_READ_IO			OCrypt(K3, N3, 0x00620A40L)
#endif

extern "C" void ManagePrivateStoreFilterHook();

void COfflineShop::Install()
{
	InitializeCriticalSection(&cs);

//	VIRTUALIZE3;
	UserSayOriginal = *(u64*)VMT_USER_SAY;
	WriteMemoryDWORD(VMT_USER_SAY,			(s32)&COfflineShop::OnUserSay);
	WriteInstruction(CALL_ON_READ,			(u64)&COfflineShop::OnSocketRead,		0, ASM_CALL);
	WriteInstruction(CALL_CLOSE_IO_SOCKET_1,(u64)&COfflineShop::OnCloseSocket,		0, ASM_CALL);
	WriteInstruction(CALL_CLOSE_IO_SOCKET_2,(u64)&COfflineShop::OnCloseSocket,		0, ASM_CALL);
	WriteInstruction(CALL_CLOSE_SOCKET2,	(u64)&COfflineShop::OnCloseSocket2,		0, ASM_CALL);
	WriteInstruction(CALL_WSPRINTF_STATS,	(u64)&COfflineShop::OnWho,				1, ASM_CALL);
	WriteInstruction(CALL_USER_INFO_SELL,	(u64)&COfflineShop::OnShopQuit,			4, ASM_CALL);
	WriteInstruction(CALL_USER_INFO_BUY,	(u64)&COfflineShop::OnShopQuit,			4, ASM_CALL);
	WriteInstruction(CALL_USER_INFO_RECIPE,	(u64)&COfflineShop::OnShopQuit,			4, ASM_CALL);
	WriteInstruction(OFFSET_CAN_SELL_ITEM,	(u64)&ManagePrivateStoreFilterHook,		3, ASM_CALL);
//	UNVIRTUALIZE;

	CIniFile ini;
	if(ini.GetIntValue("Enabled", "OfflineShop", "L2Server.ini"))
	{
		u32 nReqCount = ini.GetIntValue("RequirementCount", "OfflineShop", "L2Server.ini");

		for (u32 i = 0; i < nReqCount; i++)
		{
			char ID[20];
			char count[20];

			sprintf_s(ID, sizeof(ID), "ItemID_%d", i);
			sprintf_s(count, sizeof(count), "Quantity_%d", i);

			requirements[ini.GetIntValue(ID, "OfflineShop", "L2Server.ini")] = ini.GetIntValue(count, "OfflineShop", "L2Server.ini");
		}
	}
}

void COfflineShop::OnUserSay( User* pUser, WCHAR* pText )
{
	if(pUser->IsValidUser() && pUser->Socket->IsValidUserSocket())
	{
		if(!wcscmp(pText, L".offline"))
		{
			bool canShop = true;

			if(pUser->GetParty())
			{
				pUser->Socket->SendSystemMessage("You are not allowed to use offline shop while in party.");
				canShop = false;
			}

			if(pUser->GetSummonOrPet())
			{
				pUser->Socket->SendSystemMessage("You are not allowed to use offline shop while pet or summon is summoned.");
				canShop = false;
			}

			if(!pUser->GetPrivateStoreTime())
			{
				pUser->Socket->SendSystemMessage("You have to set up private store first.");
				canShop = false;
			}

			EnterCriticalSection(&cs);
			CInventory* pInventory = pUser->GetInventory();
			pInventory->WriteLock(__WFILE__, __LINE__);
			for (map<u32, u32>::iterator i = requirements.begin(); i != requirements.end(); i++)
			{
				if(pInventory->GetItemAmmount(i->first, 0) < i->second)
				{
					pUser->Socket->SendSystemMessage("You don't have required items to setup offline shop.");
					canShop = false;
					break;
				}
			}

			if(canShop)
			{
				for (map<u32, u32>::iterator i = requirements.begin(); i != requirements.end(); i++)	// Take requirements
					pUser->DeleteItemInInventory(i->first, i->second);
				pUser->Socket->Send("c", /*0x7e*/0x26);													// Disconnect client
				offlineShops[pUser->Socket] = pUser->Socket->s;											// Mark socket as offline
				pUser->Socket->nSocketStatus = 2;
				pUser->Socket->s = -1;
			}
			pInventory->WriteUnlock();
			LeaveCriticalSection(&cs);
		}
		else
		{
			typedef void (__fastcall*_FT)(User*, WCHAR*);
			_FT f = (_FT)UserSayOriginal;
			f(pUser, pText);
		}
	}
}

void COfflineShop::OnCloseSocket( CSocket* pSocket )
{
	if(pSocket->IsValidUserSocket())
	{
		EnterCriticalSection(&cs);
		OfflineSocketMap::iterator i = offlineShops.find(pSocket);
		if(i != offlineShops.end())
		{
			pSocket->s = i->second;
			offlineShops.erase(pSocket);							// Player goes offline, no more socket filtering.
		}
		LeaveCriticalSection(&cs);
	}
	pSocket->Close();
}

void COfflineShop::OnCloseSocket2( CSocket* pSocket )
{
	if(pSocket->IsValidUserSocket())
	{
		EnterCriticalSection(&cs);
		OfflineSocketMap::iterator i = offlineShops.find(pSocket);
		if(i == offlineShops.end())
			pSocket->Close();
		LeaveCriticalSection(&cs);
	}
}

void COfflineShop::OnSocketRead( CSocket* pSocket, LPVOID p2 )
{
	typedef void (__fastcall*_FT)(CSocket*, LPVOID);
	_FT f = (_FT)SOCKET_READ_IO;
	
	bool canRecv = true;
	EnterCriticalSection(&cs);
	OfflineSocketMap::iterator i = offlineShops.find(pSocket);
	if(i != offlineShops.end())
		canRecv = false;
	LeaveCriticalSection(&cs);

	if(canRecv)
		f(pSocket, p2);
}

void COfflineShop::OnWho( LPWSTR wcsBuffer, LPCWSTR wcsFormat, ... )
{
	va_list ap;
	va_start(ap, wcsFormat);
	int current = va_arg(ap, int);
	int playing = va_arg(ap, int);
	int store = va_arg(ap, int);
	int max = va_arg(ap, int);
	EnterCriticalSection(&cs);
	int offline = (int)offlineShops.size();
	LeaveCriticalSection(&cs);
	int total = store;
	store -= offline;

	wsprintfW(wcsBuffer, L"current(%d), playing(%d), private store online(%d), private store offline(%d), private store total(%d), max(%d)", current, playing, store, offline, total, max);
}

void COfflineShop::OnShopQuit( User* pUser )
{
	if(pUser->IsValidUser())
	{
		pUser->SendUserInfo(false);				// overwritten call

		EnterCriticalSection(&cs);
		OfflineSocketMap::iterator i = offlineShops.find(pUser->Socket);
		if(i != offlineShops.end())
			pUser->Socket->stardDisconnect = _time32(NULL);
		LeaveCriticalSection(&cs);
	}
}

bool COfflineShop::CanSellItem( CItem* pItem )
{
	bool ret = true;
	if(pItem->IsValidItem())
	{
		EnterCriticalSection(&cs);
		if(requirements.find(pItem->SD->nClassID) != requirements.end())
			ret = false;
		LeaveCriticalSection(&cs);
	}
	return ret;
}
