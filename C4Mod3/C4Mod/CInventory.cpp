#include "stdafx.h"
#include "Offsets.h"

bool CInventory::CheckAddable(s32 index) 
{
        typedef bool (*t)(CInventory*, s32);
        t f = (t)CInventory__CheckAddable;
        return f(this, index);
};

CItem * CInventory::GetFirstItemByClassID(s32 nItemClassID)
{
	typedef CItem* (*t)(CInventory*,s32);
	t f = (t) CInventory__GetFirstItemByClassID;
	return f(this, nItemClassID);
}

CItem* CInventory::GetNextItemByClassID(s32 ItemClassID)
{
        typedef CItem* (*t)(CInventory*, s32);
        t f = (t)CInventory__GetNextItemByClassID;
        return f(this, ItemClassID);
};

CItem* CInventory::GetItemByIndex(u32 nIndex)
{
	typedef CItem* (*t)(CInventory*, s32);
	t f = (t)CInventory__GetItemByIndex; //byIndex

	if(nIndex != NULL)
		return f(this, nIndex);
	else
		return NULL;
}

void CInventory::SetInventoryChanged(CItem *pItem, s32 inventoryUpdateType)
{
	typedef void (*t)(CInventory*, CItem*, s32);
	t f = (t)CInventory__SetInventoryChanged;
	f(this, pItem, inventoryUpdateType);
}

void CInventory::WriteLock(const wchar_t* file = NULL, s32 line = 0)
{
	typedef void (*t)(CInventory*, const wchar_t* , s32 );
	t f = (t)CInventory__WriteLock;
	f(this, file, line);
};

void CInventory::WriteUnlock()
{
	typedef void (*t)(CInventory*);
	t f = (t)CInventory__WriteUnlock;
	f(this);
};

void CInventory::Push(s32 nIndex)
{
	typedef void (__thiscall * __PUSH)(CInventory *pInventory, s32 Index);
	__PUSH xPush = (__PUSH)CInventory__Push;
	xPush(this, nIndex);
}

bool CInventory::Pop(s32 itemIndex, bool flag)
{
	typedef bool (*t)(CInventory* pInventory, s32 itemIndex, bool flag);
	t f = (t)CInventory__Pop;
	return f(this, itemIndex, flag);
};

s32 nGetUser = 0;
User *CInventory::GetUser()
{

	s64 nUserPTR = (s64)this;
	nUserPTR -= 0x5A0;
	User *pUser = (User *)nUserPTR;

	if ( pUser->IsValidUser() )
	{
		return pUser;
	}

	return NULL;
}

s32 nGetPet = 0;
CPet *CInventory::GetPet()
{

	s64 nPetPTR = (s64)this;
	nPetPTR -= 0x5A0;
	CPet *pPet = (CPet *)nPetPTR;

	if ( pPet->IsValidPet() )
	{
		return pPet;
	}

	return NULL;
}

bool CInventory::CheckAddable(u32 nClassId, u32  nAmount)
{
	typedef bool (__thiscall*_TICA)(CInventory*, u32, u32);
	_TICA _ICA = (_TICA)CInventory__CheckAddable2;
	return _ICA(this, nClassId, nAmount);
}

CItem* CInventory::GetByDBID(u32 dbid)
{
	typedef CItem* (__fastcall*_TIUL)(CInventory*, u32);
	_TIUL _IUL = (_TIUL)CInventory__GetByDBID;
	return _IUL(this, dbid);
}

u32 CInventory::GetAdenaAmount()
{
	typedef u32 (__fastcall*_TGAA)(CInventory*);
	_TGAA _GAA = (_TGAA)CInventory__GetAdenaAmount;
	return _GAA(this);
}

u32 CInventory::GetItemAmmount( u32 nItemID, u32 nUnk)
{
	typedef u32 (__fastcall*_TGAA)(CInventory*, u32, u32);
	_TGAA _GAA = (_TGAA)CInventory__GetItemAmmount;
	return _GAA(this, nItemID, nUnk);
}