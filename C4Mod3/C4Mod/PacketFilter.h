#pragma once

class CPacketFilter
{
public:
	static void Install();
	static u64 PacketIn(CSocket* pSocket, u8* pBuffer, u32 nSize);
};
