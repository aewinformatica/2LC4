#pragma once

class CItem;
class User;
class CPet;

class CInventory
{
public:
	bool CheckAddable(s32 index);

	CItem* GetFirstItemByClassID(s32 nItemID);
	CItem* GetNextItemByClassID(s32 ItemClassID);
	CItem* GetItemByIndex(u32 nIndex);
	CItem* GetByDBID(u32 dbid);
	void SetInventoryChanged(CItem *pItem, s32 inventoryUpdateType);
	bool CheckAddable(u32 nClassId, u32  nAmount);
	u32 GetAdenaAmount();

	void WriteLock(const wchar_t* file, s32 line);
	void WriteUnlock();

	void Push(s32 nIndex);
	bool Pop(s32 itemIndex, bool flag);
	User *GetUser();
	CPet *GetPet();
	u32 GetItemAmmount( u32 nItemID, u32 nUnk);
};
