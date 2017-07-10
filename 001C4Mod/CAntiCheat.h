#pragma once

class CAntiCheat
{
public:
	static void Install();
	static bool CheckPacket(CSocket *pSocket, u8 *pPacket, u32 nPacketLen);

private:
	// Fixes
	static bool GetItemFromPetPacket(CSocket *pSocket, u8 *packet);
	static bool GiveItemToPetPacket(CSocket *pSocket, u8 *packet);
	static void Ride(User *pUser, CPet *pStrider);
	static CPet *GetPet_in_DespawnPet(User *pUser);
	static bool HtmlCommand(CSocket *pSocket, u8 *packet);
	static bool UseItem(CSocket *pSocket, u8 *packet);
	static bool WarehouseDeposit(CSocket *pSocket, u8 *packet);
};