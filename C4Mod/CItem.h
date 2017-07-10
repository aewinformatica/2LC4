#pragma once

#pragma pack( push, 1 )

class CItemInfo 
{
	public:
 
	/* 0008 */	s32   dw08; // 2 for weapon/armor
	/* 000C */	s32   dw0C;
	/* 0010 */	s32	EtcItemType; // slot? used in User::EquipItem
	/* 0014 */	s32	weight;
	/* 0018 */	s32	dw18;
	/* 001C */	s32	default_price;
	/* 0020 */	s16	item_skill_id;
	/* 0022 */	s16	item_skill_lvl;
	/* 0024 */	s16	critical_attack_skill_id;
	/* 0026 */	s16	critical_attack_skill_lvl;
	/* 0028 */	s16	attack_skill_id;
	/* 002A */	s16	attack_skill_lvl;
	/* 002C */	s16	magic_skill_id;
	/* 002E */	s16	magic_skill_lvl;
	/* 0030 */	s16	item_skill_enchanted_four_id;
	/* 0032 */	s16	item_skill_enchanted_four_lvl;
	/* 0034 */	s32	prob;
	/* 0038 */	s32		armorType;
	/* 003c */	s32	dw3C;
	/* 0040 */	__int64	i40;
	/* 0048 */	s32		dw48;
	/* 004C */	s32		dw4C;
	/* 0050 */	__int64	i50;
	/* 0058 */	s32	dw58;
	/* 005C */	s32	crystalType;
	/* 0060 */	s32	dw60;
	/* 0064 */	s32	dw64;
	/* 0068 */	s32	dw68;
	/* 006c */	s32	dw6C;
	/* 0070 */	s32	dw70;
	/* 0074 */	bool	is_trade; 
				bool    is_drop;
				bool    is_destruct;
				bool    b77;
	/* 0078 */	s32	slot;
	/* 0078 */	s32	dw78;
	/* 0080 */	s32		consume_type; //0=normal, 1=charge, 2=stackable, 3=asset
	/* 0084 */	s32		weapon_type;  // 6: weapon_type=bow? used in User::EquipItem
	/* 0088 */	s32		dw88; //
	/* 008c */	s32		dw8C;
	/* 00F0 */	s32		equip_pet;
};
 
class CSharedItemData 
{
	public:

	/* 0000 */ s32 _dw0000;
	/* 0004 */ s32 _dw0001;
	/* 0008 */	d64	x;		
	/* 0010 */	d64	y;
	/* 0018 */	d64	z;
	/* 0020 */	s32		dw20;	// /* 0B0h : 0408D10h */    virtual void func_0B0() {};
	/* 0024 */	s32		sid;    // item_id; sid in ItemList packet
	/* 0028 */	s32		itemIndex;
	/* 002C */	s32		containerIndex;
	/* 0030 */	s32		item_type; // used in CSharedItemData_GetInfo_78DE20
	/* 0034 */	s32		VehicleIndex;
	/* 0038 */  __int64 i38;
	/* 0040 */  __int64 i40;
	/* 0048 */  __int64 i48;
	/* 0050 */ 	s32	isLoot; // used in CWorld::PickItem, Amped CItem::TimerExpired hook
	/* 0054 */	s32	prevItemIndex;
	/* 0058 */	s32	nextItemIndex;
	/* 005C */	s32	dw5C;
	/* 0060 */	s32	dw60;
	/* 0064 */	s32	state; // =1 in AtomicDropItem2::Do();
	/* 0068 */	s32	amount;
	/* 006C */	s32	dbid;
	/* 0070 */	s32	nClassID;
	/* 0074 */	s32	nSlot; // itemType2  0-weapon  1-shield/armor  2-ring/earring/necklace  3-questitem  4-adena  5-item
	/* 0078 */	s32	bodyPart;
	/* 007C */	s32	bless;
	/* 0080 */	s32	consume_type;
	/* 0084 */	s32	damaged;
	/* 0088 */	s32	nEnchantLV;
	/* 008C */	s32	dw8C;
	/* 0090 */	s32	timerIndex;
};

class CItem : public CObject
{
	public:
	
	/* 0030 */	CSharedItemData *SD;
	/* 0038 */	CItemInfo* II;
	/* 0040 */	s64 nUnk40[4];

	wchar_t *GetName();
	bool IsValidItem();
	bool IsHerbItem();
	void WriteLock(WCHAR* pFile, s32 nLine);
	void WriteUnlock();
	CObject* Copy();
	void BroadcastDelete();
};

#pragma pack( pop )