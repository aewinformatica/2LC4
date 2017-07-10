#include "stdafx.h"
#include "MemoryTools.h"

void WriteInstruction( u64 Address, u64 NewAddress, u64 NopZone, u8 Instruction )
{
	s32 OLDPROTECT;
	SIZE_T BytesWritten;
	CHAR *MyAddress = (CHAR *)Address;
	u64 JAddress = NewAddress - (Address+5);
	
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());

	if ( Server )
	{
		// Unlocking the current address space in order to create the new jump.
		VirtualProtectEx(Server, (VOID *)Address, 5+NopZone, PAGE_WRITECOPY, (DWORD*)&OLDPROTECT);

		WriteProcessMemory(Server,MyAddress,(CHAR *)&Instruction,1,&BytesWritten);
		WriteProcessMemory(Server,MyAddress+1,(CHAR *)&JAddress,4,&BytesWritten);
													 // COPYING THE ADDRESS TO THE ADDRESS SPACE.
		NOPMemory((s64)MyAddress+5, (s32)NopZone);	         // NOPING THE REST OF THE ZONE YOU WANTED PATCHED.
		VirtualProtectEx(Server, (VOID *)Address, 5+NopZone, OLDPROTECT, (DWORD*)&OLDPROTECT);
	}

	CloseHandle(Server);
}

void NOPMemory( s64 Address, s32 len )
{
	u8 Byte = 0x90;
	s32 OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		for ( s32 i = 0 ; i < len ; i++ )
		{
			s32 ADDR = (s32)(Address+i);
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, PAGE_WRITECOPY, (DWORD*)&OLDPROTECT);
			WriteProcessMemory(Server,(LPVOID)ADDR,&Byte,1,&BW);
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, OLDPROTECT, (DWORD*)&OLDPROTECT);
		}
	}
	CloseHandle(Server);
}

void NULLMemory(s32 Address, s32 len)
{
	s32 OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		for ( s32 i = 0 ; i < len ; i++ )
		{
			s32 ADDR = Address+i;
			CHAR Byte = 0x00;
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, PAGE_WRITECOPY, (DWORD*)&OLDPROTECT);
			WriteProcessMemory(Server,(LPVOID)ADDR,&Byte,1,&BW);
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, OLDPROTECT, (DWORD*)&OLDPROTECT);
		}
	}
	CloseHandle(Server);
}

void WriteMemoryBYTES(s32 Address, VOID *bytes, s32 len)
{
	s32 OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		VirtualProtectEx(Server, (LPVOID)Address, len, PAGE_WRITECOPY, (DWORD*)&OLDPROTECT);
		WriteProcessMemory(Server,(LPVOID)Address,bytes,len,&BW);
		VirtualProtectEx(Server, (LPVOID)Address, len, OLDPROTECT, (DWORD*)&OLDPROTECT);
	}
	CloseHandle(Server);
}

void WriteMemoryBYTES(s32 Address, s32 len, ...)
{
	char *memory = new char[len];
	va_list vl;
	va_start(vl, len);

	for (s32 i = 0; i < len; i++)
		memory[i] = va_arg(vl, char);

	va_end(vl);
	WriteMemoryBYTES(Address, memory, len);

	delete[] memory;
}

void WriteMemoryQWORD(s32 Address, s64 value)     { WriteMemoryBYTES(Address, &value, 8); }
void WriteMemoryFWORD(s32 Address, s64 value)     { WriteMemoryBYTES(Address, &value, 6); }
void WriteMemoryDWORD(s32 Address, s32 value)     { WriteMemoryBYTES(Address, &value, 4); }
void WriteMemoryWORD(s32 Address, s16 value)      { WriteMemoryBYTES(Address, &value, 2); }
void WriteMemoryBYTE(s32 Address, s8 value)       { WriteMemoryBYTES(Address, &value, 1); }

u64 WriteRelativeAddress(s64 nOrgAddress, s64 nWriteFrom, VOID *pArray, s64 nOffsetIndex) 
{ 
	u64 nAddressToPatch  = nOrgAddress+nWriteFrom;
	u64 nRIPAddress      = nOrgAddress+nWriteFrom+4;
	u64 nPointerAddress  = (u64)pArray;
	u64 nRelativeAddress = ((nPointerAddress + nOffsetIndex) - nRIPAddress);

	//char MyBigBuffer[256];
	//sprintf(MyBigBuffer, "IDA Address : 0x%04X\nRIP Address : 0x%04X\nDB Address : 0x%04X\nRelative Address 0x%04X", nOrgAddress, nRIPAddress, nPointerAddress, nRelativeAddress);
	//MessageBox( NULL, MyBigBuffer, "", 0 );

	WriteMemoryDWORD((s32)nAddressToPatch, (s32)nRelativeAddress);

	return nRelativeAddress;
}

void ReadMemoryBYTES(s32 Address, VOID *bytes, s32 len)
{
	SIZE_T BR;
	HANDLE Client = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Client )
		ReadProcessMemory(Client,(LPVOID)Address,bytes,len,&BR);
	CloseHandle(Client);
}

void ReadMemoryQWORD(s32 Address, s64 *Value) {	ReadMemoryBYTES(Address, Value, 8); }
void ReadMemoryDWORD(s32 Address, s32 *Value) {	ReadMemoryBYTES(Address, Value, 4); }
void ReadMemoryWORD(s32 Address, s16 *Value)  {	ReadMemoryBYTES(Address, Value, 2); }
void ReadMemoryBYTE(s32 Address, s8 *Value)   {	ReadMemoryBYTES(Address, Value, 1); }

s64 GetModuleAddress(CHAR *pModule)
{
	s64 nAddress = (s64)GetModuleHandle(pModule);
	return nAddress;
}

void HookSwitch(s32 Address, s32 NewAddress)
{
	WriteMemoryDWORD(Address, (NewAddress - 0x400000));
}