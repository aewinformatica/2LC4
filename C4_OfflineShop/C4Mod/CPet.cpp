#include "stdafx.h"
#include "Offsets.h"

void CPet::DropItem(CItem* pItem, u32 nAmount)
{
	typedef void (__thiscall * __DropItem)(CPet *, CItem *, s32, vPosition *);
	__DropItem _DropItem = (__DropItem)CPet__DropItem;
	_DropItem(this, pItem, nAmount, (vPosition *)(this->SD+0x08));
}

bool CPet::UseItem(CItem *pItem, s32 nForce)
{
	typedef bool (*_USE_ITEM)(CPet *, CItem *, s32 nForce);
	_USE_ITEM xUseItem = (_USE_ITEM)CPet__UseItem;
	return xUseItem(this, pItem, nForce);
}

bool CPet::CreatePet(User* pUser, s32 nCollarID, s32 nNpcID, s32 nLevel)
{
	typedef bool (__fastcall*_TCP)(User*, s32, s32, s32);
	_TCP _CP = (_TCP)CPet__CreatePet;
	return _CP(pUser, nCollarID, nNpcID, nLevel);
}