#include "stdafx.h"
#include "Offsets.h"

void CLog::AddAnsi(s32 nType, CHAR *format, ...)
{
	CHAR output[1024];
	memset(output,0x00,sizeof(output));
	va_list args;
	va_start(args, format);
	vsprintf(output,format,args);
	va_end(args);
	typedef void (*LADD1)(VOID *CLog, s32 Color, CHAR *Format, ...); 
	LADD1 xAddAnsiLog = (LADD1)(CLog__AddAnsi);
	xAddAnsiLog((VOID *)CLogObj, nType, output);
}

void CLog::AddUnicode(s32 nType, WCHAR *format, ...)
{
	WCHAR output[1024];
	memset(output,0x00,sizeof(output));
	va_list args;
	va_start(args, format);
	wvsprintfW(output,format,args);
	va_end(args);
	typedef void (*LADD2)(VOID *CLog, s32 Color, WCHAR *Format, ...); 
	LADD2 xAddUnicodeLog = (LADD2)(CLog__AddUnicode);
	xAddUnicodeLog((VOID *)CLogObj, nType, output);
}
