#include "stdafx.h"
#include "COfflineShop.h"
#include "PacketFilter.h"
#include "CHeroSystem.h"

u64* pHwID = 0;

#ifdef DVAMP

#define FUNC_FISHDB_LOAD	OCrypt(K0, N0, 0x005C2980L)
#define CALL_FISHDB_LOAD	OCrypt(K1, N1, 0x00643A96L)
#define NT6_FIX1			OCrypt(K2, N2, 0x00643AA6L)
#define NT6_FIX2			OCrypt(K3, N3, 0x00643AB7L)
#define ADDR_DEADLOCK		OCrypt(K4, N4, 0x0062462BL)

#else

#define FUNC_FISHDB_LOAD	OCrypt(K0, N0, 0x005C20A0L)
#define CALL_FISHDB_LOAD	OCrypt(K1, N1, 0x006432E6L)
#define NT6_FIX1			OCrypt(K2, N2, 0x006432F6L)
#define NT6_FIX2			OCrypt(K3, N3, 0x00643307L)
#define ADDR_DEADLOCK		OCrypt(K4, N4, 0x00623E7BL)

#endif

void PostLoad(u64 pArg)
{
	typedef void (__fastcall*TFishDB)(u64);
	TFishDB FishDB = (TFishDB)FUNC_FISHDB_LOAD;
	FishDB(pArg);

	//CHeroSystem::Install();
	COfflineShop::Install();
	//CPacketFilter::Install();
}

void wmit(LPVOID param)
{
	// Checking the Size of the Classes to make sure everything is Correct...
	if ( sizeof(CCreature) != 0x14E8 ) { MessageBox(NULL, "Bad CCreature Size...", 0, 0); ExitProcess(1); }

//	VIRTUALIZE3;
// 	pHwID = (u64*)((size_t)param + 0x80);
// #ifdef __DEBUG
// 	bool hwidOk = true;
// #else
// 	bool hwidOk = HwLock::CheckLock((u8*)pHwID);
// #endif
//	UNVIRTUALIZE;

// 	if(!hwidOk)
// 	{
// 		CRASH;
// 	}
// 	else
// 	{
		//VIRTUALIZE3;
		WriteInstruction(CALL_FISHDB_LOAD, (s32)PostLoad, 0, ASM_CALL);
		//NOPMemory(0x643140, 5);
		// Vista 64 / Windows 2008 Server (Incompatibility) [Fixes the Crash During the loading of L2Server]
		WriteInstruction(NT6_FIX1, NT6_FIX2, 2, ASM_JUMP);				// Forced Jump
#ifdef ADDR_DEADLOCK
		// DeadLock
		WriteMemoryDWORD(ADDR_DEADLOCK, 60000000);
#endif
		//onread hook at A8EF38
		//UNVIRTUALIZE;
// 	}
}

__declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule,
											DWORD ul_reason_for_call,
											LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)wmit, hModule, 0, 0);
			break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

