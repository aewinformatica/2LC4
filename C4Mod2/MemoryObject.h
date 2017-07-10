#pragma once

class MemoryObject
{
	public:
/* 0x000 */		u32 *pFunctionVFTable;
/* 0x008 */     s32	nRefCount;
/* 0x00C */     s32	nIdentity; 
/* 0x010 */     s32	nInTimer;
/* 0x014 */     s32	nDeleteCount;
};
