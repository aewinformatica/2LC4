#pragma once

class CSocket;
class CUserData;
class CPet;
class CPledge;
class CParty;

class User : public CCreature
{
public:

	User();
	~User();

	/* 14F0 */ s32 _dw14F0[1122];
	/* 2670 */ CSocket *Socket;
	/* 2678 */ s32 _dw2678[97];
	/* 27FC */ WCHAR AccountID[16];
	/* 281C */ s32 _dw281C[23];
	/* 2878 */ WCHAR ClanTitle[26];
	/* 28AC */ s32 _dw28AC[257];
	/* 2CB0 */ s32 _dw2CB0[2];
	/* 2CB8 */ s32 _dw2CB8[37];
	/* 2D4C */ s32 _dw2D4C;
	/* 2D50 */ s32 _dw2D50[2];
	/* 2D58 */ WCHAR *pActiveHTMLFileName;
	/* 2D60 */ s32 _dw2D60[6];

	void SendQuestList();
	void SendAcquiredSkillToDB(s32 SkillID, s32 SkillLevel, bool bMayDown);
	void SendDeletedSkillToDB(s32 SkillID);
	bool IsNoblesse();
	bool IsHero();
	void SendUserInfo(bool GMPacket);
	void SendCharInfo(bool GMPacket);
	bool SendCoolTime();
	void SetKarma(s32 nKarma);
	void SendUserHPInfo();
	void SendUserMPInfo();
	void DespawnSummon();
	bool TeleportToLocation(s32 x, s32 y, s32 z);
	bool IsNowTrade();
	void TradeCancel();
	bool HaveSummon();
	void SendETCBuffStatus();
	void Ride(CPet *pPet);
	void SendSkillList();
	s32 GetPledgeClass();
	void IconAction(s32 nID, bool bControl, bool bShift);
	CPledge* GetPledge();
	CObject* GetSummonOrPet();
	void UseItem(CItem *pItem);
	void SetState(s32 nState);
	bool IsMyParty(CCreature *pCreature);
	CParty *GetParty();
	bool InCombat();
	s32 CombatTime();
	s32 GetKarma();
	void SendETCBuffStatusInfo();
	bool DropItem(CItem* pItem, u32 nAmmount, FVector vPos);
	u32 SlotItemEquiped(u32 nItemIndex);
	void Transform(u32 nID);
	void Transform(u32 nID, s32 nDuration);
	bool IsPledgeMaster();
	void ChangeClass(u32 nClass);
	bool CanJoinPledge();
	void ResetWithdrawPenalty();
	void SendSkillAcquireList(u32 nType);
	void Say(WCHAR* pText);
	int GetPrivateStoreTime();
	/*void LeaveWorld();*/
};
