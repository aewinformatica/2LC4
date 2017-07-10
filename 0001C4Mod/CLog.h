#pragma once

enum LogType
{
	BLACK	= 0,
	BLUE	= 1,
	RED		= 2,
};


class CLog
{
public:
	static void AddAnsi(s32 nType, CHAR *format, ...);
	static void AddUnicode(s32 nType, WCHAR *format, ...);
};