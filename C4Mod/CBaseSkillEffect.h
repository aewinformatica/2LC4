#pragma once

class CObject;
class CCreature;
class CSkillInfo;
class CSkillAction2;

class CBaseSkillEffect
{
	protected:
		__int64 i08;

	public:
/* 00h */ virtual void CalcSuccess(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction) = 0; //pure
/* 08h */ virtual void Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance) = 0; // pure
/* 10h */ virtual void Unk() = 0; // pure
/* 18h */ virtual void Tick() = 0; // pure
/* 20h */ virtual double Unk2() = 0; // pure
/* 28h */ virtual bool CheckPumpCondition(CObject* pTarget) = 0; // pure
/* 30h */ virtual void Pump(CObject* pTarget, CSkillInfo* pSkillInfo) = 0; // pure
/* 38h */ virtual bool Consume(CCreature *pCreature, double param2) = 0; // pure
/* 40h */ virtual bool CheckResisted() = 0; // pure
};

// Macros
#define CSKILL_EFFECT_INSTALL_VMT(Klasse) \
	Klasse::Klasse(bool bInstallVMT) \
	{ \
	static bool _init_done = false; \
	if (!_init_done) { \
	_init_done = true; \
	LPVOID* my_vmt = *(LPVOID**)this; \
	LPVOID check_resited = (LPVOID)CSkill_CheckResisted; \
	CopyVMT(&my_vmt[8], &check_resited, 1); \
	} \
	}\
	static Klasse e(true);

