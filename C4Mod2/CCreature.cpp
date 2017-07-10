#include "stdafx.h"
#include "Offsets.h"

CCreature::CCreature()
{
}

CCreature::~CCreature()
{
}

void CCreature::Lock(WCHAR* file, s32 line)
{
    typedef void (*t)(CCreature*, WCHAR* , s32 );
    t f = (t)CCreature__Lock;
    f(this, file, line);
}

void CCreature::Unlock()
{
    typedef void (*t)(CCreature*);
    t f = (t)CCreature__Unlock;
    f(this);
}

void CCreature::LockBuffs(WCHAR* file, s32 line)
{
	L2Server::LockCS(&this->pLock1, file, line);
}

void CCreature::UnlockBuffs(WCHAR* file, s32 line)
{
	L2Server::UnlockCS(&this->pLock1, file, line);
}

CInventory * CCreature::GetInventory()
{
	if(this)
	{
		s64 dInventory = (s64)this;
		dInventory+=0x5A0;
		return (CInventory *) dInventory;
	}else
		return NULL;
}

d64 CCreature::Distance(d64 x1, d64 y1, d64 z1)
{
	d64 x2 = this->SD->x;
	d64 y2 = this->SD->y;
	d64 z2 = this->SD->z;

	return sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
}

void CCreature::BuffCreature(s32 nSkillClassID)
{
	if(this->IsValidCreature() && nSkillClassID)
	{
		CSkillInfo* pSI = CSkillInfo::GetSkillInfo(nSkillClassID);
		if(pSI)
		{
			pSI->ActivateSkill(this, this, 0, 0);
		}
	}
}