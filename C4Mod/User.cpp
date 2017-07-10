#include "stdafx.h"
#include "Offsets.h"
#include "User.h"

User::User()
{
}

User::~User()
{
}

void User::SendQuestList()
{
	typedef void (__thiscall *_SEND_QUEST_LIST) (User *pUser, bool GMPacket);
	_SEND_QUEST_LIST _SendQuestList = (_SEND_QUEST_LIST)User__SendQuestList;
	_SendQuestList(this, false);
}

void User::SendAcquiredSkillToDB(s32 SkillID, s32 SkillLevel, bool bMayDown)
{
	typedef void (__thiscall *_SASTDB) (User *pUser, s32 SkillID, s32 SkillLevel, bool bMayDown);
	_SASTDB _SendAcquiredSkillToDB = (_SASTDB)User__SendAcquiredSkillToDB;
	_SendAcquiredSkillToDB(this, SkillID, SkillLevel, bMayDown);
}

void User::SendDeletedSkillToDB(s32 SkillID)
{
	typedef void (__thiscall *_SDSTDB) (User *pUser, s32 SkillID);
	_SDSTDB _SendDeletedSkillToDB = (_SDSTDB)User__SendDeletedSkillToDB;
	_SendDeletedSkillToDB(this, SkillID);
}

void User::SendSkillAcquireList(u32 nType)
{
	typedef void (__thiscall*TFunc)(User*, u32);
	TFunc func = (TFunc)User__SendSkillAcquireList;
	func(this, nType);
}

bool User::IsNoblesse()
{
	return (SD->NoblesseType == 1);
}

bool User::IsHero()
{
	return (SD->HeroType == 2);
}

void User::SendUserInfo(bool GMPacket)
{
	typedef void (__thiscall *_SEND_USER_INFO) (User *pUser, bool gmpacket);
	_SEND_USER_INFO _SendUserInfo = (_SEND_USER_INFO)User__SendUserInfo;
	_SendUserInfo(this, GMPacket);
}

void User::SendCharInfo(bool GMPacket)
{
	typedef void (__thiscall *_SEND_CHAR_INFO) (User *pUser, bool gmpacket);
	_SEND_CHAR_INFO _SendCharInfo = (_SEND_CHAR_INFO)User__SendCharInfo;
	_SendCharInfo(this, GMPacket);
}

bool User::SendCoolTime()
{
	typedef bool(*_sc)(User*);
	_sc sc = (_sc)User__SendCoolTime;
	return sc(this);
}

void User::SetKarma(s32 nKarma)
{
	typedef void (__thiscall * __SetKarma)(User*, s32 Karma);
	__SetKarma _SetKarma = (__SetKarma)User__SetKarma;
	_SetKarma(this, nKarma);
}

bool User::IsNowTrade()
{
	typedef bool (*ISNOWTRADE)(User *pUser);
	ISNOWTRADE xIsNowTrade = (ISNOWTRADE)(User__IsNowTrade);
	return xIsNowTrade(this);
}

void User::SendUserHPInfo()
{
	typedef void (__thiscall *_USER_SEND_HP_INFO) (User *);
	_USER_SEND_HP_INFO _SendHPInfo = (_USER_SEND_HP_INFO)User__SendUserHPInfo;
	
	_SendHPInfo(this);
}

void User::SendUserMPInfo()
{
	typedef void (__thiscall *_USER_SEND_MP_INFO) (User *);
	_USER_SEND_MP_INFO _SendMPInfo = (_USER_SEND_MP_INFO)User__SendUserMPInfo;
	
	_SendMPInfo(this);
}

void User::DespawnSummon()
{
	typedef void(__fastcall *_DS)(User*);
	_DS xDS = (_DS)User__DespawnSummon;
	xDS(this);
}

bool User::TeleportToLocation(s32 x, s32 y, s32 z)
{
	typedef bool (__thiscall *_USER_TELEPORT_TO_LOC) (User *, s32, s32, s32);
	_USER_TELEPORT_TO_LOC _TeleportToLocation = (_USER_TELEPORT_TO_LOC)User__TeleportToLocation;

	return _TeleportToLocation(this, x, y, z);
}

void User::TradeCancel()
{
	typedef void (__thiscall *_USER_TRADE_CANCEL) (User *);
	_USER_TRADE_CANCEL _TradeCancel = (_USER_TRADE_CANCEL)User__TradeCancel;
	
	_TradeCancel(this);
}

bool User::HaveSummon()
{
	typedef bool (__thiscall *_HS) (User *);
	_HS xHS = (_HS)User__HaveSummon;
	return xHS(this);
}

void User::SendETCBuffStatus()
{
	typedef void (__fastcall * SendETCBuffStatusS) (User*);
	SendETCBuffStatusS _SendETCBuffStatus = (SendETCBuffStatusS)User__SendETCBuffStatus;
	_SendETCBuffStatus(this);
}

void User::Ride(CPet *pPet)
{
	typedef void(__fastcall *__ODDI)(User*, CPet*);
	__ODDI _ODDI = (__ODDI)User__Ride;
	_ODDI(this, pPet);
}

void User::SendSkillList()
{
	typedef void(__fastcall *_SL)(User*);
	_SL xSL = (_SL)User__SendSkillList;
	xSL(this);
}

void User::IconAction(s32 nID, bool bControl, bool bShift)
{
	typedef void(__fastcall *_IA)(User*,s32,bool,bool);
	_IA xIA = (_IA)User__IconAction;
	xIA(this,nID,bControl,bShift);
}

CPledge* User::GetPledge()
{
	typedef CPledge*(__fastcall *_GET_PLEDGE)(User*);
	_GET_PLEDGE _GetPledge = (_GET_PLEDGE)User__GetPledge;
	return _GetPledge(this);
}


CObject* User::GetSummonOrPet()
{
	typedef CObject *(__fastcall *__gp)(User*);
	__gp _gp = (__gp)User__GetSummonOrPet;
	return _gp(this);
}

void User::UseItem(CItem *pItem)
{
	typedef void (*_USE_ITEM)(User *, CItem *);
	_USE_ITEM xUseItem = (_USE_ITEM)User__UseItem;
	xUseItem(this, pItem);
}

void User::SetState(s32 nState)
{
	*(s32 *)(((u8 *)this)+0x2958) = nState;
}

bool User::IsMyParty(CCreature *pCreature)
{
	typedef bool (*_MY_PARTY)(User *, CCreature *);
	_MY_PARTY isMyParty = (_MY_PARTY)User__IsMyParty;
	return isMyParty(this, pCreature);
}

CParty * User::GetParty()
{
	if(this)
	{
		typedef CParty *(* __GetParty)(User*);
		__GetParty _GetParty = (__GetParty)User__GetParty;
		return _GetParty(this);
	}
	else
		return NULL;
}

bool User::InCombat()
{
	if(this)
	{
		s64 dCombat = (s64)this;
		dCombat += 0xCA5;
		dCombat = *(u8*)dCombat;
		return dCombat ? true : false;
	}
	return 0;
}

s32 User::CombatTime()
{
	if(this)
	{
		s64 dCombat = (s64)this;
		dCombat += 0xCA8;
		dCombat = *(s32*)dCombat;
		return (s32)dCombat;
	}
	return 0;
}

void User::SendETCBuffStatusInfo()
{
	typedef void (__thiscall *_SETC) (User*);
	_SETC xSendETCBuffStatusInfo = (_SETC)User__SendETCBuffStatusInfo;
	xSendETCBuffStatusInfo(this);
}

u32 nUser__SlotItemEquiped = 0;
u32 User::SlotItemEquiped(u32 nItemIndex)
{

	s32* pSlots = &SD->nObjIdUnder;

	u32 nSlot = -1;

	for(u32 i = 0; i < 18; i++)
	{
		if(pSlots[i] == nItemIndex)
		{
			nSlot = i;
			break;
		}
	}

// 	if(nSlot == -1)
// 	{
// 		pSlots = &SD->nObjIdLHair;
// 		for(u32 i = 0; i < 10; i++)
// 		{
// 			if(pSlots[i] == nItemIndex)
// 			{
// 				nSlot = i + 18;
// 				break;
// 			}
// 		}
// 	}
	
	return nSlot;
}

bool User::DropItem( CItem* pItem, u32 nAmmount, FVector vPos )
{
	typedef bool (__fastcall*_TUDI)(User*, CItem*, u32, FVector);
	_TUDI _UDI = (_TUDI)User__DropItem;
	return _UDI(this, pItem, nAmmount, vPos);
}

bool User::IsPledgeMaster()
{
	typedef bool (__fastcall*_TIPM)(User*);
	_TIPM _IPM = (_TIPM)User__IsPledgeMaster;
	return _IPM(this);
}

void User::ChangeClass(u32 nClass)
{
	typedef void (__fastcall*_TCS)(User*, u32);
	_TCS _CS = (_TCS)User__ChangeClass;
	_CS(this, nClass);
}

bool User::CanJoinPledge()
{
	typedef bool (__fastcall*_TCS)(User*);
	_TCS _CS = (_TCS)User__CanJoinPledge;
	return _CS(this);
}

void User::ResetWithdrawPenalty() 
{ 
	typedef void(__fastcall *_Reset)(User*);  
	_Reset Reset = (_Reset)User__ResetWithdrawPenalty; 
	Reset(this); 
}

void User::Say( WCHAR* pText )
{
	typedef void(__fastcall *_FT)(User*, WCHAR*);
	_FT f = (_FT)User__Say;
	f(this, pText);
}

int User::GetPrivateStoreTime()
{
	typedef int (__fastcall *_FT)(User*);  
	_FT f = (_FT)User__GetPrivateStoreTime; 
	return f(this); 
}

/*
void User::LeaveWorld()
{
	typedef void (__fastcall *_FT)(User*);
	_FT f = (_FT)User__LeaveWorld;
	f(this);
}*/
