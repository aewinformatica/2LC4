#pragma once

u64 Assemble(u8 *buf, s32 bufLen, const char *format, ...);
char *StrNChr(char *str, char c, s32 len);
s32 WcsNLen(char *str, s32 len);
u8 *Disassemble(u8* packet, const char* format, ...);
void DisassembleVA(const char* format, va_list sourceva, ...);
u64 VAssemble(u8* buf, s32 bufLen, const char* format, va_list ap);
u16 GETPACKETLENGHT(char *pPacket);
string GetServerTime();
bool CopyVMT(LPVOID *dst, LPVOID *src, size_t num);
vector <string> Split( string _separator, string _string );
BOOL FileExists(const TCHAR *fileName);
