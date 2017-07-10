#include "stdafx.h"
#include "Utils.h"

u64 Assemble(u8 *buf, s32 bufLen, const char *format, ...)
{
	//guard(s32 Assemble(char *buf, s32 bufLen, const char *format, ...));

	va_list ap;
	va_start(ap, format);
	u64 len = VAssemble(buf, bufLen, format, ap);
	va_end(ap);
	return len;

	//unguard;
}

char *StrNChr(char *str, char c, s32 len)
{
	//guard(const char *StrNChr(const char *str, char c, s32 len));

	while (len > 0)
	{
		if (*str == c)
			return str;
		str++;
		len--;
	}
	return str;

	//unguard;
}

s32 WcsNLen(char *str, s32 len)
{
//	guard(s32 WcsNLen(const u8 *str, s32 len));

	s32 i;
	for (i = 0; i < len; i++)
	{
		if (!str[0] && !str[1])
			break;
		str += 2;
	}
	return i;

//	unguard;
}



u8 *Disassemble(u8* packet, const char* format, ...)
{
//	guard(const u8 *Disassemble(const u8* packet, const char* format, ...));

	char* f = (char*)format;
	va_list ap;
	s32 t;
	va_start(ap, format);
	while ((t = *format++))
	{
		switch (t)
		{
		case 'c':
			{
				char* cp = va_arg(ap, char*);
				*cp = *packet++;
			}
			break;
		case 'h':
			{
				s16* hp = va_arg(ap, s16*);
#ifdef _WIN32
				*hp = ((s16 *)packet)[0];
#else
				*hp = packet[0] + (packet[1] << 8);
#endif
				packet += 2;
			}
			break;
		case 'd':
			{
				s32* dp = va_arg(ap, s32*);

#ifdef _WIN32           // CPU specific optimization.
				*dp = ((s32 *)packet)[0];
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24);
#endif
				packet += 4;
			}
			break;

		case 'f':
			{
				d64* dp = va_arg(ap, d64*);

#ifdef _WIN32           // CPU specific optimization.
				CopyMemory(dp, packet, 8);
				/*
				s32 i1 = *(s32*)packet;
				s32 i2 = *(((s32*)packet)+1);
				*(((s32*)dp)+0) = i2;
				*(((s32*)dp)+1) = i1;
				*/
				/*
				*dp = ((d64 *)packet)[0];
				*/
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24)
					+ (packet[4] << 32) + (packet[5] << 40) + (packet[6] << 48) + (packet[7] << 56)
#endif
				packet += 8;
			}
			break;

		case 's':
			{
				s32 dstLen = va_arg(ap, s32);
				char* dst = va_arg(ap, char*);
				strncpy(dst, (char*)packet, dstLen);
				dst[dstLen - 1] = 0;
				u8* end = (u8*)StrNChr((char*)packet, '\0', dstLen) + 1;
//		if (end - packet > dstLen) {
//		    log.Add(LOG_ERROR, "too s32 string in %s", f);
//		}
				packet = end;
			}
			break;
		case 'S':
			{
				s32 len = va_arg(ap, s32) / sizeof(wchar_t);
				len = WcsNLen((char*)packet, len-1);
				wchar_t* dst = va_arg(ap, wchar_t*);
				memcpy(dst, packet, len * sizeof(wchar_t));
				dst[len] = 0;
				packet += (len + 1) * sizeof(wchar_t);
			}
			break;
#ifdef _DEBUG
		default:
			printf("Disassemble: unknown type %c in %s", t, f);
#endif
		}
	}
	va_end(ap);
	return packet;

//	unguard;
}

void DisassembleVA(const char* format, va_list sourceva, ...)
{
	const char* f = format;
	va_list ap;
	s32 t;
	va_start(ap, format);
	while ((t = *format++))
	{
		switch (t)
		{
		case 'c':
			{
				char* cp = va_arg(ap, char*);
				*cp = va_arg(sourceva, char);
			}
			break;
		case 'h':
			{
				s16* hp = va_arg(ap, s16*);
				*hp = va_arg(sourceva, s16);
			}
			break;
		case 'd':
			{
				s32* dp = va_arg(ap, s32*);
				*dp = va_arg(sourceva, s32);
			}
			break;

		case 'f':
			{
				d64* dp = va_arg(ap, d64*);
				*dp = va_arg(sourceva, d64);
			}
			break;

		case 's':
			{
				va_arg(ap, char*) = va_arg(sourceva, char*);
			}
			break;
		case 'S':
			{
				va_arg(ap, char*) = va_arg(sourceva, char*);
			}
			break;
		}
	}
	va_end(ap);
}

u64 VAssemble( u8* buf, s32 bufLen, const char* format, va_list ap )
{
	//guard(s32 VAssemble(char* buf, s32 bufLen, const char* format, va_list ap));

	char* f = (char*)format;
	u8* start = buf;
	u8* end = buf + bufLen;
	s32 t;
	char* p;
	size_t len;
	s32 i;

	d64 d;

	while ((t = *format++))
	{
		switch (t)
		{
		case 's':
			p = va_arg(ap, char*);
			if (p)
			{
				len = strlen(p);
				if (buf + len + 1 > end)
				{
					goto overflow;
				}
				strcpy((char*)buf, p);
				buf += len + 1;
			}
			else
			{
				// p is null. Is it correct?
				if (buf + 1 > end)
				{
					goto overflow;
				}
				*buf++ = 0;
			}
			break;
		case 'S': 
			{
				wchar_t* p = va_arg(ap, wchar_t*);
				if (p)
				{
					len = (wcslen(p) + 1)* sizeof(wchar_t);
					if (buf + len > end)
					{
						goto overflow;
					}
					memcpy(buf, p, len);
					buf += len;
				}
				else
				{
					// p is null. Is it correct?
					if (buf + 2 > end)
					{
						goto overflow;
					}
					*buf++ = 0;
					*buf++ = 0;
				}
			}
			break;
		case 'b':	    // blind copy
			len = va_arg(ap, s32);
			p = va_arg(ap, char*);
			if (buf + len > end)
			{
				goto overflow;
			}
			memcpy(buf, p, len);
			buf += len;
			break;
		case 'c':
			i = va_arg(ap, s32);
			if (buf + 1 > end)
			{
				goto overflow;
			}
			*buf++ = (u8)i;
			break;
		case 'h':
			i = va_arg(ap, s32);
			if (buf + 2 > end)
			{
				goto overflow;
			}
#ifdef _WIN32
			*((s16 *)buf) = (s16)i;
			buf += 2;
#else
			*buf++ = i;
			*buf++ = i >> 8;
#endif
			break;
		case 'd':
			i = va_arg(ap, s32);
			if (buf + 4 > end)
			{
				goto overflow;
			}
#ifdef _WIN32
			*((s32 *)buf) = i;
			buf += 4;
#else
			*buf++ = i;
			*buf++ = i >> 8;
			*buf++ = i >> 16;
			*buf++ = i >> 24;
#endif
			break;

		case 'f':
			d = va_arg(ap, d64);
			if (buf + 8 > end)
			{
				goto overflow;
			}
#ifdef _WIN32
			CopyMemory(buf, &d, 8);
			/*
			*(((s32*)buf)+0) = *(((s32*)&d)+0);
			*(((s32*)buf)+1) = *(((s32*)&d)+1);
			*/
			/*
			*((d64 *)buf) = d;
			*/
			buf += 8;
#else
			*buf++ = d;
			*buf++ = d >> 8;
			*buf++ = d >> 16;
			*buf++ = d >> 24;
			*buf++ = d >> 32
			*buf++ = d >> 40;
			*buf++ = d >> 48;
			*buf++ = d >> 56;
#endif
			break;

		}
	}
	return (buf - start);
overflow:
#ifdef _DEBUG
	printf("Buffer overflow in Assemble");
#endif
	return 0;

	//unguard;
}

u16 GETPACKETLENGHT(char *pPacket)
{
 	u8 *temp = (u8*)pPacket;
 	temp-=2;
 	s16 packetlen = *temp  << 8;
 	temp--;
 	packetlen += *temp;
 	return packetlen-3;  //1=u8 packetno + 2=s16 packetlen
}

string GetServerTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	stringstream ss;
	ss << setw(2) << setfill('0') << timeinfo->tm_hour;
	ss << ":" << setw(2) << setfill('0') << timeinfo->tm_min;
	ss << ":" << setw(2) << setfill('0') << timeinfo->tm_sec;
	return ss.str();
}

bool CopyVMT(LPVOID *dst, LPVOID *src, size_t num)
{
	s32 oldProtect = NULL;
	size_t size = num * sizeof(LPVOID);

	if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, (DWORD*)&oldProtect)!=0)
	{
		memcpy_s(dst, size, src, size);
		VirtualProtect(dst, size, oldProtect, (DWORD*)&oldProtect);
		return true;
	}
	else
	{
		MessageBox(NULL, "CopyVMT() failed!", "(Error) L2Server_addon", MB_OK);
		return false;
	}
}

std::vector <std::string> Split( std::string _separator, std::string _string )
{

        std::vector <std::string> array;

        size_t position;
        
        // we will find the position of first of the separators
        position = _string.find_first_of( _separator );
        
        // We will loop true this until there are no separators left
        // in _string
        while ( position != _string.npos )
        {
        
                // This thing here checks that we dont push empty strings
                // to the array
                if ( position != 0 )
                        array.push_back( _string.substr( 0, position ) );

                // When the cutted part is pushed into the array we
                // remove it and the separator from the _string
                _string.erase( 0, position + _separator.length() );

                // And the we look for a new place for the _separator
                position = _string.find_first_of( _separator );
        }

        // We will push the rest of the stuff in to the array
        if ( _string.empty() == false )
                array.push_back( _string );

        // Then we'll just return the array
        return array;
}

BOOL FileExists(const TCHAR *fileName)
{
	s32       fileAttr;

	fileAttr = GetFileAttributes(fileName);
	if (-1 == fileAttr)
		return FALSE;
	return TRUE;
}
