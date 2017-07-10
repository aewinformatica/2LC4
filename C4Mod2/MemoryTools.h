#pragma once
#pragma warning( disable : 4312 ) 
#pragma warning( disable : 4996 ) 
#pragma warning( disable : 4309 )
#pragma warning( disable : 4311 )

#define ASM_CALL 0xE8
#define ASM_JUMP 0xE9

void WriteInstruction(u64 Address, u64 NewAddress, u64 NopZone, u8 Instruction);
void NOPMemory(s64 Address, s32 len);
void NULLMemory(s32 Address, s32 len);
void HookSwitch(s32 Address, s32 NewAddress);

void WriteMemoryBYTES(s32 Address, VOID *bytes, s32 len);
void WriteMemoryBYTES(s32 Address, s32 len, ...);
void WriteMemoryQWORD(s32 Address, s64 value);
void WriteMemoryFWORD(s32 Address, s64 value);
void WriteMemoryDWORD(s32 Address, s32 value);
void WriteMemoryWORD(s32 Address, s16 value);
void WriteMemoryBYTE(s32 Address, s8 value);

void ReadMemoryBYTES(s32 Address, VOID *bytes, s32 len);
void ReadMemoryQWORD(s32 Address, s64 *Value);
void ReadMemoryDWORD(s32 Address, s32 *Value);
void ReadMemoryWORD(s32 Address, s16 *Value);
void ReadMemoryBYTE(s32 Address, s8 *Value);

// Process Tools
s64 GetModuleAddress(CHAR *pModule);

// Array Tools
u64 WriteRelativeAddress(s64 nOrgAddress, s64 nWriteFrom, VOID *pArray, s64 nOffsetIndex);

inline void bitsetn(s32 & i, unsigned bitposition) { i|= 1<<(bitposition); }
inline s32 readbitn(s32 i, unsigned bitposition) { return (i>>(bitposition))&1; }
