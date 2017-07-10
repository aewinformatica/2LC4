#include "stdafx.h"
#include "Offsets.h"

wchar_t *CItem::GetName()
{
    typedef wchar_t * (__thiscall *_CITEM_GETNAME) (CItem *pObject);
    _CITEM_GETNAME xGetName = (_CITEM_GETNAME)CItem__GetName;

    return xGetName(this);
}

bool CItem::IsValidItem()
{
	if(this)
	{
        __try
		{ 
			if(    *(__int64*)this == CItemVMT1 
				|| *(__int64*)this == CItemVMT2 
				|| *(__int64*)this == CItemVMT3 
				|| *(__int64*)this == CItemVMT4
				|| *(__int64*)this == CItemVMT5
				|| *(__int64*)this == CItemVMT6
				|| *(__int64*)this == CItemVMT7 )
			{
				return true;
			}
		}
        __except(EXCEPTION_EXECUTE_HANDLER)
		{ 
			/* Invalid pointer */
			/* Preventing Crash ;) */
		}
	}

	return false;
}

bool CItem::IsHerbItem()
{
	if (
			this->nObjectType >= 8154 && this->nObjectType <= 8157 || 
			this->nObjectType >= 8600 && this->nObjectType <= 8614
		)
	{ return true; }
	
	return false;
}

void CItem::WriteLock(WCHAR* pFile, s32 nLine)
{
	typedef void (__fastcall*_TIL)(CItem*, WCHAR*, s32);
	_TIL _IL = (_TIL)0x429730;
	_IL(this, pFile, nLine);
}

void CItem::WriteUnlock()
{
	typedef void (__fastcall*_TIUL)(CItem*);
	_TIUL _IUL = (_TIUL)0x4319D0;
	_IUL(this);
}

CObject* CItem::Copy()
{
	typedef CObject* (__fastcall*_TIC)(CItem*);
	_TIC _IC = (_TIC)0x62B860;
	return _IC(this);
}

void CItem::BroadcastDelete()
{
	CSPacket packet;
	packet.set(9);
	packet << (u8)0x12;
	packet << nObjectID;
	packet << 0x00;

	vPosition vPos;
	vPos.x = SD->x;
	vPos.y = SD->y;
	vPos.z = SD->z;

	L2Server::BroadcastToNeighbor(nObjectID, vPos, &packet);
}