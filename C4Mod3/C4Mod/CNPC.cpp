#include "stdafx.h"
#include "Offsets.h"

void CNPC::AddItemToInventory2(CItem *pItem)
{
	typedef void (__thiscall *_ADD_ITEM_TO_INVENTORY) (CNPC *pNPC, CItem *Item);
	_ADD_ITEM_TO_INVENTORY xAddItemToInventory = (_ADD_ITEM_TO_INVENTORY)CNPC__AddItemToInventory2;
	xAddItemToInventory(this, pItem);
}
