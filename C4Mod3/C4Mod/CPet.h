#pragma once

class CPet : public CSummon
{
	public:

		void DropItem(CItem* pItem, u32 nAmount);
		bool UseItem(CItem *pItem, s32 nForce);
		static bool CreatePet(User* pUser, s32 nCollarID, s32 nNpcID, s32 nLevel);
};