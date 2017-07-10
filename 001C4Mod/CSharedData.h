#pragma once

class CObjectEx;

#pragma pack( push, 1 )

struct AbnormalInfo
{
	s32 nAbnormalType;
	s32 nLevel;
};

struct QuestData
{
	s32		questId;
	s32		questState;
	s32		questJournal;
	s32		unk4;
};

class CSharedData
{
	public:

		/* Functions */

		void DeleteAbnormalStatus(s32 nAbnormalType)
		{
			typedef void (*das)(CSharedData*, s32);
			das _das = (das)CSharedData__DeleteAbnormalStatus ;
			_das(this, nAbnormalType);
		}

		void AddAbnormalStatus(s32 nAbnormalType, s32 nLevel)
		{
			typedef void(*aas)(CSharedData*, s32, s32);
			aas _aas = (aas)CSharedData__AddAbnormalStatus ;
			_aas(this, nAbnormalType, nLevel);
		}

		/* Variables */

		/* 0000 */ s32	_dw0000;
		/* 0004 */ s32	_dw0004;
		/* 0008 */ d64	x;
		/* 0010 */ d64	y;
		/* 0018 */ d64	z;

		/* 0020 */ s32	nHeading;
		/* 0024 */ s32	nObjectID;
		/* 0028 */ s32	_dw0028;	//0x06
		/* 002C */ s32	nNPCIndex;	//0x5279

		/* 0030 */ s32	_dw0030;
		/* 0034 */ s32	_dw0034;
		/* 0038 */ s32	_dw0038;
		/* 003C */ s32	_dw003C;

		/* 0040 */ s32	_dw0040;
		/* 0044 */ s32	_dw0044;
		/* 0048 */ s32	_dw0048;
		/* 004C */ s32	_dw004C;

		/* 0050 */ u8	nIsActive;
		/* 0051 */ u8	_b0051;
		/* 0052 */ u8	_b0052;
		/* 0053 */ u8	_b0053;
		/* 0054 */ s32	_dw0054;	//-2
		/* 0058 */ s32	_dw0058;	//-1
		/* 005C */ s32	_dw005C;	//0

		/* 0060 */ s32	_dw0060;	//0
		/* 0064 */ s32	nIsPlayer;
		/* 0068 */ s32	nIsAlive;
		/* 006C */ s32	nAge;

		/* 0070 */ s32	_dw0070;
		/* 0074 */ s32	_dw0074;
		/* 0078 */ s32	_dw0078;
		/* 007C */ s32	_dw007C;

		/* 0080 */ s32	_dw0080;
		/* 0084 */ s32	_dw0084;
		/* 0088 */ s32	_dw0088;
		/* 008C */ s32	_dw008C;
		
		/* 0090 */ s32	_dw0090;
		/* 0094 */ s32	_dw0094;
		/* 0098 */ s32	SubClassID;
		/* 009C */ s32	NoblesseType;
		
		/* 00A0 */ s32	HeroType;
		/* 00A4 */ s32	_dw00A4;
		/* 00A8 */ s32	_dw00A8;
		/* 00AC */ s32	SubJob0;
		
		/* 00B0 */ s32	SubJob1;
		/* 00B4 */ s32	SubJob2;
		/* 00B8 */ s32	SubJob3;
		/* 00BC */ s32	nRace;
		
		/* 00C0 */ s32	nClass;
		/* 00C4 */ s32	nSex;
		/* 00C8 */ WCHAR wszName[25];

		/* 00FA */ bool	bUndying;
		/* 00FB */ bool	bCanBeAttacked;
		/* 00FC */ bool	bHide;
		/* 00FD */ bool	_b00FD;
		/* 00FE */ s16 _w00FE;

		/* 0100 */ d64 nCollisionRadius;
		/* 0108 */ d64 nCollisionHeight;

		/* 0110 */ s32	nHairShape;
		/* 0114 */ s32	nHairColor;
		/* 0118 */ s32	nFaceIndex;
		/* 011C */ s32	nExp;
		/* 0120 */ s32	nSp;

		/* 0124 */ s32	nObjIdAdena;
		
		/* 0128 */ s32	nObjIdUnder;						/* Slot Type Array Start */
		/* 012C */ s32	nObjIdLEar;

		/* 0130 */ s32	nObjIdREar;
		/* 0134 */ s32	nObjIdNeck;
		/* 0138 */ s32	nObjIdLRing;
		/* 013C */ s32	nObjIdRRing;

		/* 0140 */ s32	nObjIdHead;
		/* 0144 */ s32	nObjIdLHand;
		/* 0148 */ s32	nObjIdRHand;
		/* 014C */ s32	nObjIdGloves;

		/* 0150 */ s32	nObjIdChest;
		/* 0154 */ s32	nObjIdLegs;
		/* 0158 */ s32	nObjIdFeet;
		/* 015C */ s32	nObjIdBack;

		/* 0160 */ s32	nObjId2Hand;
		/* 0164 */ s32	nObjIdOnePiece;
		/* 0168 */ s32	nObjIdHair;
		/* 016C */ s32	nObjIdDress;
		
		/* 0170 */ s32	nDefaultINT;
		/* 0174 */ s32	nDefaultSTR;
		/* 0178 */ s32	nDefaultCON;
		/* 017C */ s32	nDefaultMEN;
		/* 0180 */ s32	nDefaultDEX;
		/* 0184 */ s32	nDefaultWIT;
		
		/* 0188 */ d64	fHP;
		/* 0190 */ d64	fMP;
		/* 0198 */ d64	fCP;
		
		/* 01A0 */ s32 _n1A0;
		/* 01A4 */ s32 nMoveType;
		/* 01A8 */ s32 nStopType;
		/* 01AC */ s32 _n1AC;

		/* 01B0 */ s32 _n1B0;
		/* 01B4 */ s32 _n1B8;
		/* 01B8 */ s32 nTargetIndex;
		/* 01BC */ s32 nTargetObjId;

		/* 01C0 */ s32 _n1C0;
		/* 01C4 */ bool bUnkn1c4;
		/* 01C5 */ bool bIsFreezed;
		/* 01C6 */ bool bUnkn1c6;
		/* 01C7 */ bool bUnkn1c7;
		/* 01C8 */ s32 nPvPScore;
		/* 01CC */ s32 nPKScore;

		/* 01D0 */ s32 _n1D0;
		/* 01D4 */ s32 nKarma;
		/* 01D8 */ s32 nRecommendationsLeft;
		/* 01DC */ s32 nEvalScore;
		
		/* 01E0 */ s32 _n1E0;

		/* 01E4 */ QuestData OldQuests[16];

		/* 02E4 */ s32 _dw224[8];

		/* 0304 */ s32 nQuestLastRewardTime;
		/* 0308 */ s32 nLastAttackerIndex;
		/* 030C */ s32 _n30C;

		/* 0310 */ s32 _n310;
		/* 0314 */ s32 _n314;
		/* 0318 */ s32 nPledgeId;
		/* 031C */ s32 _n31C;

		/* 0320 */ s32 nIsPledgeLeader;
		/* 0324 */ s32 _n324;
		/* 0328 */ s32 _n328;
		/* 032C */ s32 _n32C;

		/* 0330 */ s32 _n330;
		/* 0334 */ s32 _n334;
		/* 0338 */ s32 nResidenceID;
		/* 033C */ s32 _n33C;

		/* 0340 */ s32 _n340;
		/* 0344 */ s32 nMountType;				// None = 0, Strider = 1, Wyvern = 2, Wolf = 3, Horse = 4
		/* 0348 */ s32 nMountClassID;
		/* 034C */ s32 nStoreMode;

		/* 0350 */ s32 _n350;
		/* 0354 */ s32 _n354;
		/* 0358 */ s32 _n358;
		/* 035C */ s32 nIsSoulshot; //6- S 5-A 4-B 3-C 2-D 1-NG

		/* 0360 */ s32 _n360;
		/* 0364 */ s32 _n364;
		/* 0368 */ s32 nIsSpiritshot; //Spiritshot /Blessed spiritshot = 1
		/* 036C */ s32 bIsRiding;
		
		/* 0370 */ d64 SpiritShotMulti;
		/* 0378 */ s32 _n378;
		/* 037C */ bool bSoulShot;
		/* 037D */ bool _b37D;
		/* 037E */ s16 _w37E;
		
		/* 0380 */ d64 fSoulShotPower;
		/* 0388 */ bool bSpiritShot;
		/* 0389 */ bool _b389;
		/* 038A */ s16 _w38A;
		/* 038C */ s32 _n38C;

		/* 0390 */ d64 fSpiritShotPower;
		/* 0398 */ s32 _n398;
		/* 039C */ s32 _n39C;

		/* 03A0 */ s32 _n3A0;
		/* 03A4 */ s32 _n3A4;
		/* 03A8 */ s32 _n3A8;
		/* 03AC */ s32 _n3AC;

		/* 03B0 */ s32 _n3B0;
		/* 03B4 */ s32 _n3B4;
		/* 03B8 */ s32 _n3B8;
		/* 03BC */ s32 _n3BC;

		/* 03C0 */ s32 _n3C0;
		/* 03C4 */ s32 _n3C4;
		/* 03C8 */ s32 _n3C8;
		/* 03CC */ s32 _n3CC;

		/* 03D0 */ s32 _n3D0;
		/* 03D4 */ s32 _n3D4;
		/* 03D8 */ s32 nIsNewbieC4;
		/* 03DC */ s32 nCharId;

		/* 03E0 */ s32 _n3E0;
		/* 03E4 */ s32 _n3E4;
		/* 03E8 */ s32 _n3E8;
		/* 03EC */ s32 _n3EC;

		/* 03F0 */ s32 _n3F0;
		/* 03F4 */ s32 _n3F4;
		/* 03F8 */ s32 _n3F8;
		/* 03FC */ s32 _n3FC;

		/* 0400 */ s32 _n400;
		/* 0404 */ s32 _n404;
		/* 0408 */ s32 _n408;
		/* 040C */ s32 _n40C;

		/* 0410 */ s32 _n410;
		/* 0414 */ s32 nBaseAttackSpeed;
		/* 0418 */ s32 nBaseCritical;

		/* 041C */ s32 nINT;
		/* 0420 */ s32 nSTR;
		/* 0424 */ s32 nCON;
		/* 0428 */ s32 nMEN;
		/* 042C */ s32 nDEX;
		/* 0430 */ s32 nWIT;
		
		/* 0434 */ s32 _n434;
		/* 0438 */ s32 _n438;
		/* 043C */ s32 _n43C;
		/* 0440 */ s32 _n440;

		//=====================//

		/* 0444 */ s32 nLevel;
		/* 0448 */ s32 _n448;
		/* 044C */ s32 _n44C;
		/* 0450 */ s32 _n450;
		/* 0454 */ s32 _n454;
		/* 0458 */ s32 _n458;
		/* 045C */ s32 _n45C;
		/* 0460 */ s32 _n460;
		/* 0464 */ s32 _n464;
		/* 0468 */ s32 _n468;
		/* 046C */ s32 _n46C;
		/* 0470 */ s32 _n470;
		/* 0474 */ s32 _n474;
		/* 0478 */ s32 _n478;
		/* 047C */ s32 _n47C;
		/* 0480 */ s32 _n480;
		/* 0484 */ s32 _n484;
		/* 0488 */ s32 _n488;
		/* 048C */ s32 _n48C;

		/* 0490 */ s32 nMaxSlot;
		/* 0494 */ s32 nCurrSlot;
		/* 0498 */ s32 nCurrWeight;
		/* 049C */ s32 _n49C;

		/* 04A0 */ d64 fMaxLoad;
		/* 04A8 */ d64 fOrgHP;
		/* 04B0 */ d64 fOrgMP;
		/* 04B8 */ d64 fOrgCP;
		/* 04C0 */ d64 fMaxHP;
		/* 04C8 */ d64 fMaxMP;
		/* 04D0 */ d64 fMaxCP;
		/* 04D8 */ d64 _fHpRegen;
		/* 04E0 */ d64 _fMpRegen;
		/* 04E8 */ d64 fOrgSpeed;
		/* 04F0 */ d64 fSpeed;
		/* 04F8 */ d64 _f4F8;
		/* 0500 */ d64 _f500;
		/* 0508 */ d64 _f508;
		/* 0510 */ d64 fCurrentSpeed;	//fNoise;
		/* 0518 */ d64 fHit;
		/* 0520 */ d64 fAvoid;
		/* 0528 */ d64 _f528;
		/* 0530 */ d64 _f530;
		/* 0538 */ d64 fAccuracy;
		/* 0540 */ d64 fEvasion;
		/* 0548 */ d64 _f548;

		/* 0550 */ s32 _n550;
		/* 0554 */ s32 _n554;
		/* 0558 */ s32 _n558;
		/* 055C */ s32 _n55C;
		/* 0560 */ s32 _n560;
		/* 0564 */ s32 _n564;
		
		/* 0568 */ s32 nWeaponID;
		/* 056C */ s32 nWeaponType;
		
		/* 0570 */ s32 _n570;
		/* 0574 */ s32 _n574;
		/* 0578 */ s32 _n578;
		/* 057C */ s32 nWeaponRange;

		/* 0580 */ s32 _n580;
		/* 0584 */ s32 _n584;
		/* 0588 */ s32 _n588;
		/* 058C */ s32 _n58C;
		/* 0590 */ s32 nWeaponRandomDmg;
		/* 0594 */ s32 nWeaponPhysDmg;
		/* 0598 */ s32 _n598;
		/* 059C */ s32 nWeaponAtkSpeed;
		/* 05A0 */ s32 _n5A0;
		/* 05A4 */ s32 nWeaponMagicDmg;
		/* 05A8 */ s32 _n5A8;
		/* 05AC */ s32 _n5AC;

		/* 05B0 */ d64 fPAtk;
		/* 05B8 */ d64 fMAtk;
		/* 05C0 */ d64 fPDef;
		/* 05C8 */ d64 fMDef;
		/* 05D0 */ d64 fAtkSpeed;
		/* 05D8 */ d64 fBaseCritical;
		/* 05E0 */ d64 fBaseAtkSpeed;
		/* 05E8 */ d64 fBaseCastSpeed;

		/* 05F0 */ s32 _n5F0;
		/* 05F4 */ s32 _n5F4;
		/* 05F8 */ s32 _n5F8;
		/* 05FC */ s32 _n5FC;

		/* 0600 */ s32 _n600;
		/* 0604 */ s32 _n604;
		/* 0608 */ s32 _n608;
		/* 060C */ s32 _n60C;
		/* 0610 */ s32 _n610;
		/* 0614 */ s32 _n614;

		/* 0618 */ s32 nBuilderLevel;

		/* 061C */ s32 _n61C;
		/* 0620 */ s32 _n620;
		/* 0624 */ s32 _n624;
		/* 0628 */ s32 _n628;
		/* 062C */ s32 nLastBlowWeaponClassID;
		/* 0630 */ s32 nSSQRoundNumber;
		/* 0634 */ s32 nSSQPart;
		/* 0638 */ s32 _n638;
		/* 063C */ s32 nSealSelectionNo;
		/* 0640 */ s32 _n640;
		/* 0644 */ s32 _n644;
		/* 0648 */ s32 _n648;
		/* 064C */ s32 _n64C;
		/* 0650 */ s32 _n650;
		/* 0654 */ s32 _n654;
		/* 0658 */ s32 _n658;
		/* 065C */ s32 _n65C;
		/* 0660 */ s32 nSSQDawnRound;
		/* 0664 */ s32 nInPeaceZone;
		/* 0668 */ s32 nInBattleField;
		/* 066C */ wchar_t wszAI[64];
		/* 06EC */ s32 _n6EC;
		/* 06F0 */ s32 _n6F0;
		/* 06F4 */ s32 _n6F4;
		/* 06F8 */ s32 _n6F8;
		/* 06FC */ s32 _n6FC;

		/* 0700 */ s32 _n0700;
		/* 0704 */ s32 _n0704;
		/* 0708 */ s32 _n0708;
		/* 070C */ s32 _n070C;
		/* 0710 */ s32 _n0710;
		/* 0714 */ s32 _n0714;
		/* 0718 */ s32 _n0718;
		/* 071C */ s32 _n071C;
		/* 0720 */ s32 _n0720;
		/* 0724 */ s32 _n0724;
		/* 0728 */ s32 _n0728;
		/* 072C */ s32 _n072C;
		/* 0730 */ s32 _n0730;
		/* 0734 */ s32 _n0734;
		/* 0738 */ s32 _n0738;
		/* 073C */ s32 _n073C;
		/* 0740 */ s32 _n0740;
		/* 0744 */ s32 _n0744;
		/* 0748 */ s32 _n0748;
		/* 074C */ s32 _n074C;
		/* 0750 */ s32 _n0750;
		/* 0754 */ s32 _n0754;
		/* 0758 */ s32 _n0758;
		/* 075C */ s32 _n075C;
		/* 0760 */ s32 _n0760;
		/* 0764 */ s32 _n0764;
		/* 0768 */ s32 _n0768;
		/* 076C */ s32 _n076C;
		/* 0770 */ s32 _n0770;
		/* 0774 */ s32 _n0774;
		/* 0778 */ s32 nSummonType;
		/* 077C */ s32 _n077C;
		/* 0780 */ s32 nMasterID;
		/* 0784 */ s32 _n0784;
		/* 0788 */ s32 NPC_CLASS_ID;
		/* 078C */ s32 nWeightPoint;
		/* 0790 */ s32 nRespawnTime;
		/* 0794 */ s32 _n0794;
		/* 0798 */ s32 _n0798;
		/* 079C */ s32 _n079C;
		/* 07A0 */ s32 _n07A0;
		/* 07A4 */ s32 _n07A4;
		/* 07A8 */ s32 _n07A8;
		/* 07AC */ s32 _n07AC;
		/* 07B0 */ s32 nClanHelpRange;
		/* 07B4 */ s32 _n07B4;
		/* 07B8 */ s32 _n07B8;
		/* 07BC */ s32 _n07BC;
		/* 07C0 */ s32 nPState;
		/* 07C4 */ s32 _n07C4;
		/* 07C8 */ s32 _n07C8;
		/* 07CC */ s32 _n07CC;
		/* 07D0 */ s32 _n07D0;
		/* 07D4 */ s32 _n07D4;
		/* 07D8 */ CSharedData *pMasterSD;
		/* 07E0 */ s32 nAction;
		/* 07E4 */ s32 _n07E4;
		/* 07E8 */ s32 _n07E8;
		/* 07EC */ s32 _n07EC;
		/* 07F0 */ s32 _n07F0;
		/* 07F4 */ s32 _n07F4;
		/* 07F8 */ s32 _n07F8;
		/* 07FC */ s32 _n07FC;

		/* 0800 */ s32 _n0800;
		/* 0804 */ s32 _n0804;
		/* 0808 */ s32 _n0808;
		/* 080C */ s32 _n080C;
		/* 0810 */ s32 nFlag;
		/* 0814 */ s32 nCurrentFeed;
		/* 0818 */ s32 nMaxFeed;
		/* 081C */ s32 nPetDBID;
		/* 0820 */ s32 nStriderLevel;
		/* 0824 */ s32 _n0824;
		/* 0828 */ s32 nMaxMagicLevel;
		/* 082C */ s32 OldAbnormalTable[20][2]; //NotUsed
		/* 08CC */ s32 nDBValue; 
		/* 08D0 */ s32 nDualGara1;
		/* 08D4 */ s32 nDualGara2;
		/* 08D8 */ s32 nTradeSkillLevel;
		/* 08DC */ s32 nMakerParam1;
		/* 08E0 */ s32 nMakerParam2;
		/* 08E4 */ s32 nMakerParam3;
		/* 08E8 */ u64 PledgePower1;				// Chronicle 4 Pledge Powers Are Stored Here
		/* 08F0 */ u64 PledgePower2;				// Never Used / Unknown
		/* 08F8 */ u64 PledgePower3;				// Never Used / Unknown
		/* 0900 */ u64 PledgePower4;				// Never Used / Unknown
		/* 0908 */ s32 nLang;						// Korea=0, USA=1, Japan=2, Taiwan=3, China=4, Thailand=5
		/* 090C */ s32 _n90C;						// End of the Original Shared Data
// 		/* 0910 */ AbnormalInfo AbnormalTable[36];	// New Abnormal Table
// 		/* 0A30 */ s32 nPledgeType;
// 		/* 0A34 */ CObjectEx *pObjectEx;
// 		/* 0A3C */ QuestData Quests[26];
// 		/* 0BDC */ s32 nObjIdLHair;
// 		/* 0BE0 */ s32 nObjIdRHair;
// 		/* 0BE4 */ s32 nObjIdBracelet;
// 		/* 0BE8 */ s32 nObjIdTalisman;
// 		/* 0BEC */ s32 nObjIdDeco1;
// 		/* 0BF0 */ s32 nObjIdDeco2;
// 		/* 0BF4 */ s32 nObjIdDeco3;
// 		/* 0BF8 */ s32 nObjIdDeco4;
// 		/* 0BFC */ s32 nObjIdDeco5;
// 		/* 0C00 */ s32 nObjIdDeco6;
};

#pragma pack( pop )
