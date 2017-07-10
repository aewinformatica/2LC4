#pragma once

class CCreature;
class CBaseSkillEffect;
class CBaseOperateCondition;
class CSkillInfo;

typedef vector<CBaseSkillEffect *> CSkillInfoList;
typedef vector<CBaseOperateCondition *> CSkillOpCondList;
 
enum SkillOpType
{
        SKILL_OP_TYPE_A1 = 0,
        SKILL_OP_TYPE_A2 = 1,
        SKILL_OP_TYPE_A3 = 2,
        SKILL_OP_TYPE_A4 = 3,
        SKILL_OP_TYPE_P = 4,
        SKILL_OP_TYPE_T = 5,
        SKILL_OP_TYPE_PP = 6
};
 
enum SkillBasePropery
{
        SKILL_BASE_PROP_STR = 1,
        SKILL_BASE_PROP_DEX = 2,
        SKILL_BASE_PROP_CON = 3,
        SKILL_BASE_PROP_INT = 4,
        SKILL_BASE_PROP_MEN = 5,
        SKILL_BASE_PROP_WIT = 6,
        SKILL_BASE_PROP_NONE = 26
};
 
struct CItemContainer
{
	__int64 ary[4];
	__int64 strlen;
};

class CSkillKey
{
public:
	u16 nID;
	u8 nLevel;
};

class SkillAcquireInfo
{
public:
	/* 000 */ u8 _b000[0x58];
	/* 058 */ u32 nSP;
	/* ... */ // add missing
};

class CSkillInfo 
{
	public:

		wchar_t*			skill_name;		// 00h
		s32					skill_id;	// 08h
		s32					level;		// 0Ch
		s32					magic_level;	// 10h
		s32					is_magic;		// 14h - case 8, values: 0,1,2
		s32					has_i_energy_attack;		// 18h
		SkillOpType			op_type;	// 1Ch
		s32					dw20;
		s32					mp_consume2;	// 24h, case 13
		s32					dw28;			// 28h, case 14
		s32					dw2c;			// 2Ch,
		CItemContainer		item_consume;	// 30h, case 15, sizeof = 0x28.
		s32					dw58;	// 58h, case ???
		s32					item_consume_count;	// 5Ch, case 15, item consume?
		s32					cast_range;		// 60h
		s32					effective_range;	// 64h
		s32					ary_dw_68[4];		// 68h, 6Ch, 70h, 74h - case 5
		d64				skill_hit_time;	// 78h
		d64				skill_cool_time; // 80h
		d64				skill_hit_cancel_time; // 88h 
		d64				reuse_delay; // 90h, sec*1000
		CSkillOpCondList	operate_cond_list; // 98h
		d64				lv_bonus_rate; // B8h, case 25
		s32					activate_rate; // C0h
		SkillBasePropery	basic_property; // C4h, case 26
		s32					abnormal_time;	// C8h
		s32					abnormal_lv;	// CCh
		s32					abnormal_type;  // D0h
		s32					abnormal_visual_effect; // D4h
		s32					attribute;		// D8h, attr_earth=9 and so on...
		s32					effect_point;	// DCh;
		s32					debuff;			// E0h, (1,2)
		s32					next_action;	//E4h;
		s32					next_action_is_fake_death; // E8h, bool 
		s32					ride_state;		// ECh, bitfield
		CBaseSkillEffect*	consume_effect; // F0h, not list!
		CBaseSkillEffect*	tick_effect;	// F8h, not list!
		CSkillInfoList		pump_effect_list; // 100h
		CSkillInfoList		instant_effect_list; // 120h
		s32					target_type;	 // 140h
		s32					affect_scope;	 // 144h, affect_scope_stru item1
		s32					dw148;			 // 148h, case 43
		s32					dw14C;			 // 14Ch, eq -1 if affect_scope==single (0)
		s32					ary_dw150[2];	 // 150h, case 40,
		s32					dw158;			 // case 42
		s32					affect_limit[2]; // 15Ch, 160h 
		s32					dw164; // 164h

		/* EXTENDED FUNCTIONS */

		void AddInstantEffect(VOID *pSkillEffect)
		{
			typedef void (__thiscall *_PUSHBACK) (VOID *, VOID *); _PUSHBACK xPush_Back = (_PUSHBACK)CSkillInfo__AddEffect;
			xPush_Back(&this->instant_effect_list, &pSkillEffect);
		}

		void AddPumptEffect(VOID *pSkillEffect)
		{
			typedef void (__thiscall *_PUSHBACK) (VOID *, VOID *); _PUSHBACK xPush_Back = (_PUSHBACK)CSkillInfo__AddEffect;
			xPush_Back(&this->pump_effect_list, &pSkillEffect);
		}

		void AddOPCondition(VOID *pOpCondition)
		{
			typedef void (__thiscall *_PUSHBACK) (VOID *, VOID *); _PUSHBACK xPush_Back = (_PUSHBACK)CSkillInfo__AddOPCondition;
			xPush_Back(&this->operate_cond_list, &pOpCondition);
		}

		static CSkillInfo *GetSkillInfo(s32 nSkillID, s32 nLevel)
		{
			typedef CSkillInfo*(__fastcall *__GS)(void*, CSkillKey*);
			__GS _GS = (__GS)CSkillInfo__GetSkillInfo ;

			CSkillKey c;
			c.nID = (u16)nSkillID;
			c.nLevel = (u8)nLevel;

			CSkillInfo *pSI = _GS((void*)CSkillInfo__GetSkillInfoObj, &c);
			return pSI;
		}
		static CSkillInfo *GetSkillInfo(int nSkillClassID)
		{
			typedef CSkillInfo*(__fastcall *__GS)(void*, CSkillKey*);
			__GS _GS = (__GS) CSkillInfo__GetSkillInfo;

			CSkillKey c;
			c.nID = nSkillClassID >> 8;
			c.nLevel = nSkillClassID - (c.nID << 8);

			CSkillInfo *pSI = _GS((void*)CSkillInfo__GetSkillInfoObj, &c);
			return pSI;
		}

		static CSkillInfo* GetSkillInfo(WCHAR* name)
		{
			u32 nSkillID = 0, nSkillLvl = 0;
			GetSkillIdLevelByName(name, &nSkillID, &nSkillLvl);
			return GetSkillInfo(nSkillID, nSkillLvl);
		}

		static bool GetSkillIdLevelByName(WCHAR* pszName, u32* id, u32* lvl)
		{
			typedef bool (__fastcall*TFunc)(LPVOID, WCHAR*, u32*, u32*);
			TFunc func = (TFunc)CSkillInfo__GetSkillIdLevelByName;
			return func((LPVOID)CSkillInfo__GetSkillInfoObj, pszName, id, lvl);
		}
		
		void ActivateSkill(CCreature* pCreature, CObject* pTarget, d64 dUnkn, s64 nUnkn)
		{
			typedef void (__thiscall *_as)(CSkillInfo*, CCreature*, CObject*, d64, s64);
			_as as = (_as)CSkillInfo__ActivateSkill ;
			as(this, pCreature, pTarget, dUnkn, nUnkn);
		}

		static SkillAcquireInfo* GetSkillAcquireInfo(u32 nSkillID, u32 nSkillLvl)
		{
			typedef SkillAcquireInfo* (__thiscall *_as)(u64, u32, u32);
			_as as = (_as)CSkillInfo__GetSkillAcquireInfo ;
			return as(CSkillInfo__GetSkillAcquireInfoObj, nSkillID, nSkillLvl);
		}
};