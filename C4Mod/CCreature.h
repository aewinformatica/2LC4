#pragma once

struct CBuffInfo
{
	CSkillInfo *pSkillInfo;
	s32 nSelfCasted;
	s32 nCastTime;
	s32 nCasterID;
	s32 nSomething;
};

typedef vector<CBuffInfo> BuffVector;

typedef struct
{
	d64 X;
	d64 Y;
	d64 Z;
} FVector;

typedef struct
{
	s32 X;
	s32 Y;
	s32 Z;
} FIVector;

typedef struct
{
	d64 X;
	d64 Y;
	d64 MinZ;
	d64 MaxZ;
} FVector2;

#pragma pack( push, 1 )

class CCreature : public CObject
{
	public:

	//Constructor
	CCreature();

	void AcquireSkill(u32 skillID, u32 level, u32 nUnk1, bool bUnk2)
	{
		typedef void (__thiscall *_ACQUIRE_SKILL) (CCreature *, u32, u32, u32, bool);
		_ACQUIRE_SKILL _AcquireSkill = (_ACQUIRE_SKILL)CCreature__AcquireSkill;
		_AcquireSkill(this, skillID, level, nUnk1, bUnk2);
	}

	void DeleteAcquiredSkill(s32 skillID)
	{
		typedef void (__thiscall *_DELETE_ACQUIRE_SKILL) (CCreature *, s32);
		_DELETE_ACQUIRE_SKILL _DeleteAcquireSkill = (_DELETE_ACQUIRE_SKILL)CCreature__DeleteAcquiredSkill;
		_DeleteAcquireSkill(this, skillID);
	}

	bool HaveSkill(s32 skillID, s32 level)
	{
		typedef bool (__thiscall *_HAVE_SKILL) (CCreature *, s32, s32);
		_HAVE_SKILL _HaveSkill = (_HAVE_SKILL)CCreature__HaveSkill;
		return ( _HaveSkill(this, skillID, level) );
	}

	void ModifyAcquireSkill(s32 skillID, s32 level)
	{
		typedef void (__thiscall *_MODIFY_ACQUIRE_SKILL) (CCreature *, s32, s32);
		_MODIFY_ACQUIRE_SKILL _ModifyAcquireSkill = (_MODIFY_ACQUIRE_SKILL)CCreature__ModifyAcquireSkill;
		_ModifyAcquireSkill(this, skillID, level);
	}

	void ValidateParameters()
	{
		typedef void (__thiscall *_VALIDATE_PARAMETERS) (CCreature *);
		_VALIDATE_PARAMETERS _ValidateParameters = (_VALIDATE_PARAMETERS)CCreature__ValidateParameters;
		_ValidateParameters(this);
	}

	void ValidateSkillMod()
	{
		typedef void (__thiscall *_VALIDATE_SKILLMOD) (CCreature *pCreature);
		_VALIDATE_SKILLMOD xValidateSkillMod = (_VALIDATE_SKILLMOD)CCreature__ValidateSkillMod;
		xValidateSkillMod(this);
	}

	void ValidateAllOnSIM()
	{
		typedef void (__thiscall *_VAS) (CCreature *pCreature);
		_VAS xVas = (_VAS)CCreature__ValidateAllOnSIM;
		xVas(this);
	}

	void ValidateSkillList()
	{
		typedef void (__thiscall *_VALIDATE_SKILL_LIST) (CCreature *);
		_VALIDATE_SKILL_LIST _ValidateSkillList = (_VALIDATE_SKILL_LIST)CCreature__ValidateSkillList;
		_ValidateSkillList(this);
	}

	void ValidateAttachedSkills()
	{
		typedef void (__thiscall *_VALIDATE_ATTACHED_SKILLS) (CCreature *pCreature);
		_VALIDATE_ATTACHED_SKILLS xValidateAttachedSkills = (_VALIDATE_ATTACHED_SKILLS)CCreature__ValidateAttachedSkills;
		xValidateAttachedSkills(this);
	}

	bool InfectedSkillBy(CCreature *pSource, void *pSkillInfo)
	{
		typedef bool (*_INFECTSKILLBY) (CCreature *pMyself, CCreature *pSource, void *SkillInfo);
		_INFECTSKILLBY _InfectedSkillBy = (_INFECTSKILLBY)CCreature__InfectedSkillBy;
		return _InfectedSkillBy(this, pSource, pSkillInfo);
	}

	void CreatureUseItem(void *pItem)
	{
		typedef void (*_CUI)(CCreature *pCreature, void *pItem, u32 unknown);
		_CUI _CreatureUseItem = (_CUI)(CCreature__CreatureUseItem);
		_CreatureUseItem(this, pItem, 0);
	}

	u32 GetResurrectExp(CCreature* pSpeller, u32 restorerate)
	{
		typedef u32 (*_CGRE)(CCreature*, CCreature*, u32);
		_CGRE _GetRessurectExp = (_CGRE)CCreature__GetResurrectExp;
		return _GetRessurectExp(this, pSpeller, restorerate);
	}

	bool ResurrectedBy(s32 nExpToRestore)
	{
		typedef bool (__fastcall*_TRB)(CCreature*, s64, s32);
		_TRB _RB = (_TRB)CCreature__ResurrectedBy;
		return _RB(this, 0, nExpToRestore);
	}

	bool DeleteAbnormalStatus(s32 nAbnormalStatusSlotType)
	{
		typedef bool (__fastcall*_TRB)(LPVOID, s32);
		_TRB _RB = (_TRB)CCreature__DeleteAbnormalStatus;
		return _RB(this->SD, nAbnormalStatusSlotType);
	}
	

    bool IsValidSD()
    {
        if(this)
		{
            __try
			{ 
				if(this->SD && this->SD > (CSharedData *)rDataEnd) { d64 A = this->SD->x; return true; }
			}
            __except(EXCEPTION_EXECUTE_HANDLER)
			{ 
				/* Invalid pointer */
				/* Preventing Crash ;) */
			}
        }

		return false;
    }

	bool IsValidCreature()
	{
		if( IsValidObject(VMT_CCreature)
			|| IsValidObject(VMT_CNPC)
			|| IsValidObject(VMT_CSummon)
			|| IsValidObject(VMT_CBoss)
			|| IsValidObject(VMT_CZzoldagu)
			|| IsValidObject(VMT_User)
			|| IsValidObject(VMT_CPet)
			|| IsValidObject(VMT_CMerchant) )
		{
			if(IsValidSD())
			{
				return true;
			}
		}

		return false;
	}

	bool IsValidUser()
	{
		if( IsValidObject(VMT_User) && IsValidSD())
			return true;
		else
			return false;
	}

	bool IsBoss() { return IsValidObject(VMT_CBoss); }
	bool IsZZoldagu() { return IsValidObject(VMT_CZzoldagu); }

	bool IsPlayer()
	{
		if ( SD->nIsPlayer == 1 )
			return true;
		else
			return false;
	}

	bool IsAlive()
	{
		if ( SD->nIsAlive == 1 )
			return true;
		else
			return false;
	}

	s32 GetAcquiredSkillLevel(s32 SkillID)
	{
		typedef s32 (*_GASL)(CCreature *pCreature, s32 SkillID);
		_GASL _GetAcquiredSkillLevel = (_GASL)(CCreature__GetAcquiredSkillLevel);
		return _GetAcquiredSkillLevel(this, SkillID);
	}

	bool DeleteItemInInventory(s32 nItemID, s32 nAmount)
	{
 		typedef bool (__fastcall * __DeleteItemInInventory)(CCreature*, s32 ItemID, s32 Amount);
 		__DeleteItemInInventory _DeleteItemInInventory = (__DeleteItemInInventory)CCreature__DeleteItemInInventory;
 		return _DeleteItemInInventory(this, nItemID, nAmount);
	}

	bool AddItemToInventory(s32 nItemID, s32 nAmount)
	{
		typedef bool (__fastcall * __AddItemToInventory)(CCreature *Creature, s32 ItemID, s32 Amount, bool bIsPick, s32 nEnchanted, s32 nBless, s32 nEroded);
		__AddItemToInventory xAddItemToInventory = (__AddItemToInventory)CCreature__AddItemToInventory;
		
		return xAddItemToInventory(this, nItemID, nAmount, 0, 0, 0, 0);
	}

	bool AddItemToInventory(CItem * pItem)
	{
		typedef bool (__fastcall * __AddItemToInventory)(CCreature*, CItem*);
		__AddItemToInventory xAddItemToInventory = (__AddItemToInventory)CCreature__AddItemToInventory2;

		return xAddItemToInventory(this, pItem);
	}

	bool AddItemToInventory(s32 nItemClassID, s32 nCount, bool bIsPick, s32 nEnchanted, s32 nBless, s32 nEroded)
	{
		typedef bool (__fastcall*_TCAITI)(CCreature*, s32, s32, bool, s32, s32, s32);
		_TCAITI _CAITI = (_TCAITI)CCreature__AddItemToInventory3;
		return _CAITI(this, nItemClassID, nCount, bIsPick, nEnchanted, nBless, nEroded);
	}

	void ChangeTarget(CObject * pTarget, bool bByUser)
	{
		typedef void (__thiscall *_CHANGE_TARGET) (CCreature *, CObject *, bool);
		_CHANGE_TARGET _ChangeTarget = (_CHANGE_TARGET)CCreature__ChangeTarget;

		_ChangeTarget(this, pTarget, bByUser);
	}

	void SetMaxMagicLevel()
	{
		typedef void (__thiscall *_SMML) (CCreature *pCreature);
		_SMML xSetMaxMagicLevel = (_SMML)CCreature__SetMaxMagicLevel;
		xSetMaxMagicLevel(this);
	}

	bool Die(CCreature *pEnemy)
	{
		typedef bool (__thiscall *_DIE) (CCreature *MySelf, CCreature *Enemy);
		_DIE xDie = (_DIE)CCreature__Die;
		return ( xDie(this, pEnemy) );
	}

	void DispelAllByGM()
	{
		typedef bool (__thiscall *_DAGM) (CCreature *pMySelf);
		_DAGM xDispelAllByGM = (_DAGM)CCreature__DispelAllByGM;
		xDispelAllByGM(this);
	}

	bool ValidateBaseCP()
	{
		typedef bool (__fastcall * ValidateBCPS) (CCreature*);
		ValidateBCPS _ValidateBCPS = (ValidateBCPS)CCreature__ValidateBaseCP;
		return _ValidateBCPS(this);
	}
	 
	bool ValidateAllOnWeapon()
	{
		typedef bool (__fastcall * __ValidateAllOnWeapon) (CCreature*);
		__ValidateAllOnWeapon _ValidateAllOnWeapon = (__ValidateAllOnWeapon) CCreature__ValidateAllOnWeapon;
		return _ValidateAllOnWeapon(this);
	}

	bool ValidateCPRegen()
	{
		typedef bool (__fastcall * _VLREGEN) (CCreature*);
		_VLREGEN xVlRegen = (_VLREGEN)CCreature__ValidateCPRegen ;
		return xVlRegen(this);
	}

	bool ValidateHPRegen()
	{
		typedef bool (__fastcall * _VLREGEN) (CCreature*);
		_VLREGEN xVlRegen = (_VLREGEN)CCreature__ValidateHPRegen ;
		return xVlRegen(this);
	}

	bool ValidateMPRegen()
	{
		typedef bool (__fastcall * _VLREGEN) (CCreature*);
		_VLREGEN xVlRegen = (_VLREGEN)CCreature__ValidateMPRegen ;
		return xVlRegen(this);
	}

	bool IsValidSummon()
	{
		return IsValidObject(VMT_CSummon);
	}

	bool IsValidPet()
	{
		return IsValidObject(VMT_CPet);
	}

	bool IsValidNPC()
	{
		return IsValidObject(VMT_CNPC);
	}
	
	bool IsValidMerchant()
	{
		return IsValidObject(VMT_CMerchant);
	}

	void Action(CCreature *pCreature, s32 dOption1, s32 dOption2)
	{
		typedef void(__fastcall *__ct)(CCreature*, CCreature *, s32 dOption1, s32 dOption2);
		__ct _ct = (__ct) CCreature__Action;
		if(this->IsValidCreature())
		{
			if(pCreature->IsValidCreature())
			{
				_ct(this, pCreature, dOption1, dOption2);
			}
		}
	}

	s32 UnequipItem(s32 slotId)
	{
		typedef s32 (*t)(CCreature*, s32 slotId);
		t f = (t)CCreature__UnequipItem;
		return f(this,slotId);
	}
	CSharedItemData* GetEquipedWeapon()
	{
		typedef CSharedItemData* (*t)(CCreature*);
		t f = (t)CCreature__GetEquipedWeapon;
		return f(this);
	}

	d64 Distance(d64 x1, d64 y1, d64 z1);

	void BuffCreature(s32 nSkillClassID);
	
	//Destructor
	~CCreature();

	void Lock(WCHAR* file, s32 line);
	void Unlock();
	void LockBuffs(WCHAR* file, s32 line);
	void UnlockBuffs(WCHAR* file, s32 line);

	CInventory *GetInventory();

    /* 0030 */      s32 _dw0000[342];
    /* 0588 */      CSharedData *SD;
    /* 0590 */      s32 _dw0590[2];
    /* 0598 */      s32 _dw0598[2];
    /* 05A0 */      void *nInventory;
    /* 05A8 */      s32 _dw05A8[2];
    /* 05B0 */      s32 _dw05B8[22];
    /* 0608 */      s32 nCurrentSetID;
    /* 060C */      s32 _dw060C;
    /* 0610 */      s32 _dw0610[2];
    /* 0614 */      s32 _dw0614[74];
    /* 0740 */      s32 _dw0740[2];
    /* 0748 */      s32 _dw0748[2];
    /* 0750 */      s32 _dw0750[4];
    /* 0760 */      d64 dCritRateMul;
    /* 0768 */      d64 dCritRateAdd;
    /* 0770 */      s32 _dw0770[2];
    /* 0778 */      s32 _dw0778[2];
    /* 0780 */      s32 _dw0780;
	/* 0784 */		u8 _b0784[2];
	/* 0786 */		u8 bPreserveAbnormal;
	/* 0787 */		u8 _b0787;
	/* 0788 */      s32 _dw0788[20];
    /* 07D8 */      s32 _dw07D8[2];
    /* 07E0 */      s32 _dw07E0[2];
    /* 07E8 */      d64 dCritDmgAdd;
    /* 07F0 */      d64 dCritDmgMul;
    /* 07F8 */      s32 _dw07F8[158];
    /* 0A70 */      s32 _dw0A70[2];
    /* 0A78 */      s32 _dw0A78[12];
    /* 0AA8 */      d64 dResistDispelByCategory_SlotBuff;
    /* 0AB0 */      d64 dResistDispelByCategory_SlotDebuff;
    /* 0AB8 */      s32 _dw0AB8[34];
    /* 0B40 */      u8 _b0B40;
    /* 0B41 */      bool bOnBattlefield;
    /* 0B42 */      u8 _b0B42;
    /* 0B43 */      u8 _b0B43;
    /* 0B44 */      s32 _dw0B44[26];
	/* 0BAC */		u32 nCharges;
	/* 0BB0 */		s32 _dw[61];
    /* 0CA4 */      u8 _b0CA4;
    /* 0CA5 */      bool bCombatMode;
    /* 0CA6 */      u8 _b0CA6;
    /* 0CA7 */      u8 _b0CA7;
    /* 0CA8 */      s32 _dw0CA8[8];
	/* 0CC8 */		s32 nLastTalkedNpcObjID;
	/* 0CCC */		s32 _dw0CCC[3];
    /* 0CD8 */		void *pCCreatureController;
    /* 0CE0 */      s32 _dw0CDC[64];
    /* 0DE0 */      VOID *pLock1;
    /* 0DE8 */      s32 _dw0DE8[22];
    /* 0E40 */      BuffVector vBuff;
    /* 0E60 */      s32 _dw0E60[232];//
	/* 1200 */		bool bAtkAttribute[34];
	/* 1222 */		s16 _w1222;
	/* 1224 */		s32 _dw1224;
	/* 1228 */		d64 dDefAttribute[34];
	/* 1338 */		s32 _dw1330[108];
};

#pragma pack( pop )
