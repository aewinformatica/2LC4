#include "StdAfx.h"
#include "PacketFilter.h"
#include "CAntiCheat.h"

extern "C"
{
	void PacketInHook();
};

#ifdef DVAMP
	#define CALL_PACKET_IN		OCrypt(K0, N0, 0x00877EFAL)
	#define RET_BLOCK_PACKET	OCrypt(K1, N1, 0x00878065L)
#else
	#define CALL_PACKET_IN		OCrypt(K2, N2, 0x008771CAL)
	#define RET_BLOCK_PACKET	OCrypt(K3, N3, 0x00877335L)
#endif

void CPacketFilter::Install()
{
	WriteInstruction(CALL_PACKET_IN, (u64)&PacketInHook, 3, ASM_CALL);
}

u64 CPacketFilter::PacketIn( CSocket* pSocket, u8* pBuffer, u32 nSize )
{
	if(!pSocket->IsValidUserSocket() || !pSocket->user->IsValidUser())
		return 0;

	if(CAntiCheat::CheckPacket(pSocket, pBuffer, nSize))
	{

	}
	else
		return RET_BLOCK_PACKET;

	return 0;
}
