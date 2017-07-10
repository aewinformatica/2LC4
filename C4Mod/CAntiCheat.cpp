#include "stdafx.h"
#include "CAntiCheat.h"

#ifdef DVAMP
#else
	#define CALL_RIDE1		0x0083829BL
	#define CALL_RIDE2		0x0088FCDEL
	#define CALL_GET_PET	0x00816CF6L
#endif

void CAntiCheat::Install()
{
	// Cancel Trade When Rideing a Pet...
// 	WriteInstruction(CALL_RIDE1, (s32)CAntiCheat::Ride, 0, ASM_CALL);
// 	WriteInstruction(CALL_RIDE2, (s32)CAntiCheat::Ride, 0, ASM_CALL);
//  
// 	// Cancel Trade, When Despawning a Pet...
// 	WriteInstruction(CALL_GET_PET, (s32)CAntiCheat::GetPet_in_DespawnPet, 0, ASM_CALL);
}

s32 nIncommingPackets = 0;
bool CAntiCheat::CheckPacket(CSocket *pSocket, u8 *pPacket, u32 nPacketLen)
{
	bool bResult = true;

	if ( pSocket->user->IsValidUser() )
	{
		// In-Game Exploits
		switch ( pPacket[0] )
		{
			case 0x21:
				bResult = HtmlCommand(pSocket, &pPacket[1]);
				break;
			
			case 0x8C:
				bResult = GetItemFromPetPacket(pSocket, &pPacket[1]);
				break;

			case 0x8B:
				bResult = GiveItemToPetPacket(pSocket, &pPacket[1]);
				break;

			case 0x14:
				bResult = UseItem(pSocket, &pPacket[1]);
				break;

			case 0x31:
				bResult = WarehouseDeposit(pSocket,  &pPacket[1]);
				break;

			default:
				bResult = true;
				break;
		}
	}

	if ( !bResult )
		CLog::AddAnsi(2,"An exploit attempt detected. Incoming packet Opcode=[0x%02X] Length=[%d] blocked.", pPacket[0], nPacketLen);

	return bResult;
}

s32 nGetItemFromPetPacket = 0;
bool CAntiCheat::GetItemFromPetPacket(CSocket *pSocket, u8 *packet)
{
	User *pUser = pSocket->user;
	
	if (pUser->IsNowTrade())
	{
		pUser->TradeCancel();
		return false;
	}
 
	s32 nObjectID, nCount;
	
	Disassemble(packet, "dd", &nObjectID, &nCount);
	
	if (nCount < 0)
		return false;

	if (nCount > 2000000000)
	{
		pSocket->SendSystemMessage(1338);	// Message: You have exceeded the maximum amount that may be transferred at one time.
		return false;
	}
 
	return true;
}
 
s32 nGiveItemToPetPacket = 0;
bool CAntiCheat::GiveItemToPetPacket(CSocket *pSocket, u8 *packet)
{
	User *pUser = pSocket->user;

	if (pUser->IsNowTrade())
	{
		pUser->TradeCancel();
		return false;
	}
 
	s32 nObjectID, nCount;
	
	Disassemble(packet, "dd", &nObjectID, &nCount);
	
	if (nCount < 0)
	{
		return false;
	}
	
	if (nCount > 2000000000)
	{
		pSocket->SendSystemMessage(1338);	// Message: You have exceeded the maximum amount that may be transferred at one time.
		return false;
	}
 
	return true;
}
 
s32 nRide = 0;
void CAntiCheat::Ride(User *pUser, CPet *pStrider)
{
	typedef void (*_Ride)(User *pUser, CPet *pStrider);
	_Ride Ride = (_Ride)0x00834AD0;
 
	if (!pUser->IsValidUser() || pStrider == NULL)
		return;
 
	if (pUser->IsNowTrade())
	{
		pUser->TradeCancel();
		return;
	}
 
	Ride(pUser, pStrider);
}
 
s32 nGetPet_in_DespawnPet = 0;
CPet *CAntiCheat::GetPet_in_DespawnPet(User *pUser)
{
	if (pUser->IsValidUser())
		if (pUser->IsNowTrade())
			pUser->TradeCancel();
 
	CPet *ret = (CPet *)pUser->GetSummonOrPet();
	return ret;
}
 
s32 nHtmlCommand = 0;
bool CAntiCheat::HtmlCommand(CSocket *pSocket, u8 *packet)
{
	User *pUser = pSocket->user;

	if (pUser->IsNowTrade())
	{
		pUser->TradeCancel();
		return false;
	}
 
	if (pUser->SD->nStopType == 2)
	{
		pSocket->SendSystemMessage(556);	// Message: You cannot move in this state
		return false;
	}

	CSPacket reply;
	reply.set(5);
	reply << (u8)0x81;		// EnchantResult
	reply << (s32)2;

	pSocket->Send(&reply);

	return true;
}

s32 nCAntiExploits__RequestEnchantItem = 0;
bool CAntiCheat::UseItem(CSocket *pSocket, u8 *packet)
{
	User* pUser = pSocket->user;

	s32 nObjID = *(s32*)(packet);

	CItem* pItem = (CItem*)L2Server::GetObjectA(nObjID);

	if(pItem->IsValidItem())
	{
		s32 nClassID = pItem->SD->nClassID;
		if((nClassID >= 729 && nClassID <= 732) || (nClassID >= 947 && nClassID <= 962))
		{
			if (pUser->IsNowTrade())
			{
				pUser->TradeCancel();
				return false;
			}

			CSPacket clAugWind;
			clAugWind.set(11);
			clAugWind << 0xFE;
			clAugWind << 0x58;
			clAugWind << 1;
			clAugWind << 0;

			pSocket->Send(&clAugWind);
		}
	}

	return true;
}

bool CAntiCheat::WarehouseDeposit( CSocket *pSocket, u8 *packet )
{
	if(pSocket->IsValidUserSocket())
	{
		u32 nCount = *(u32*)packet;
		u32* pData = (u32*)&packet[4];

		for (u32 i = 0; i < nCount; i++)
		{
			u32 nObjID = pData[i * 2];

			for(u32 j = 0; j < nCount; j++)
			{
				if( i != j )
				{
					u32 nObjID2 = pData[j * 2];
					if(nObjID == nObjID2)
						return false;				// dublicate id found
				}
			}
		}
	}

	return true;
}