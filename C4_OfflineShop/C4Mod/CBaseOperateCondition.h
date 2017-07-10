#pragma once

class CObject;
class CCreature;
class CSkillInfo;
class CSkillAction2;

class CBaseOperateCondition
{
	protected:
		__int64 i08;		

	public:

        virtual bool CanUse(CCreature *pSkillUser, CObject *pTargetObject) = 0; // pure
		virtual void Unknown1() = 0;											// pure
		virtual void Unknown2() = 0;											// pure
};

// Macros
#define CSKILL_OPCOND_INSTALL_VMT(Klasse) \
	Klasse::Klasse() \
	{ \
	static bool _init_done = false; \
	if (!_init_done) { \
	_init_done = true; \
	LPVOID* my_vmt = *(LPVOID**)this; \
	LPVOID pUnknownFunction = (LPVOID)CSkill_UnknownFunc; \
	CopyVMT(&my_vmt[2], &pUnknownFunction, 1); \
	} \
	}\
	static Klasse e();