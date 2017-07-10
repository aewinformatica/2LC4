#pragma once

class User;
class CItem;

class CParty
{
	public:

		void WithDraw(User *pUser);
		s32 GetPartyRoutingType();
		bool IsValidParty();
		void RouteItem(CItem *pItem, User *pPicker);
		void DistributeAdena(s32 nAmount, u32 nTraceChar, s32 nItemDBID, CItem* pItem);
};