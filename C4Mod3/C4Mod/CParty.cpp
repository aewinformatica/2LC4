#include "stdafx.h"
#include "Offsets.h"

void CParty::WithDraw(User *pUser)
{
	typedef void (__thiscall *_WITHDRAW) (CParty *, User *);
	_WITHDRAW xWithdraw = (_WITHDRAW)CParty__WithDraw;
	xWithdraw(this, pUser);
}

s32 CParty::GetPartyRoutingType()
{
	typedef s32 (__thiscall *_GPRT) (CParty *);
	_GPRT xGPRT = (_GPRT)CParty__GetPartyRoutingType;
	return xGPRT(this);
}

bool CParty::IsValidParty()
{
	if(this > (CParty*)rDataEnd)
		if(*(s64*)this == CParty__VMT)
			return true;
	return false;
}

void CParty::RouteItem(CItem *pItem, User *pPicker) 
{
	typedef void (__thiscall*_TPRI)(CParty*, CItem*, User*);
	_TPRI _PRI = (_TPRI)CParty__RouteItem;
	_PRI(this, pItem, pPicker);
}

void CParty::DistributeAdena(s32 nAmount, u32 nTraceChar, s32 nItemDBID, CItem* pItem) 
{
	typedef void (__thiscall*_TPRI)(CParty*, s32, u32, s32, CItem*);
	_TPRI _PRI = (_TPRI)CParty__DistributeAdena;
	_PRI(this, nAmount, nTraceChar, nItemDBID, pItem);
}
