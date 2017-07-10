#include "stdafx.h"
#include "Offsets.h"
#include "CSocket.h"

void CSocket::Send(CSPacket *buf)
{
	this->Send("b", buf->size(), buf->buffer(false));
}

void CSocket::Send(const char * format, ...)
{
	// Performing Normal Send
	typedef void (__fastcall *_SENDV) (CSocket * pSocket, const char * format, ...);
	_SENDV SendV = (_SENDV)CSocket__Send;
	va_list vl;
	va_start(vl, format);
	SendV(this, format, vl);
	va_end(vl);
}

void CSocket::SendSystemMessage(char *format, ...)
{
	if(this->IsValidUserSocket())
	{
		CHAR  BUF1[512];
		WCHAR BUF2[512];

		memset(BUF1, 0x00, 256);
		memset(BUF2, 0x00, 512);

		va_list args;
		va_start(args, format);
		vsprintf(BUF1,format,args);
		va_end(args);

		MultiByteToWideChar(CP_ACP, 0, BUF1, -1, BUF2, 256);

		Send("cdddS", 0x64, 1326/*1983*/, 1, 0, BUF2);
	}
}

void CSocket::SendSystemMessage(WCHAR *format, ...)
{
	if(this->IsValidUserSocket())
	{
		WCHAR buf[512];
		va_list ap;
		va_start(ap, format);
		wvsprintfW(buf, format, ap);
		va_end(ap);
		Send("cdddS", 0x64, 1983, 1, 0, buf);
	}
}

void CSocket::Close()
{
	typedef void (__thiscall *_CLOSE) (void * pIOSocket);
	_CLOSE _Close = (_CLOSE)CSocket__Close;
	this->nSocketStatus = 2;
	_Close(this);
}

void CSocket::SendSystemMessage(s32 nMessageID)
{
	typedef void (__thiscall *_SSM) (CSocket *, s32);
	_SSM xSendSystemMessage = (_SSM)CSocket__SendSystemMessage;

	xSendSystemMessage(this, nMessageID);
}

void CSocket::SendSystemMessage(wchar_t *wszSender, wchar_t *wszMessage)
{
	typedef void (*__SSM)(CSocket *, wchar_t *, wchar_t *);
	__SSM _SSM = (__SSM)CSocket__SendSystemMessage2;

	_SSM(this, wszSender, wszMessage);
}

void CSocket::Lock()
{
	typedef void (__fastcall *_LOCK) (void *, wchar_t *, s32);
	_LOCK xLock = (_LOCK)CSocket__Lock;
	xLock(&this->pLock, __WFILE__, __LINE__);
}

void CSocket::Unlock()
{
	typedef void (__fastcall *_UNLOCK) (void *, wchar_t *, s32);
	_UNLOCK xUnlock = (_UNLOCK)CSocket__Unlock;
	xUnlock(&this->pLock, __WFILE__, __LINE__);
}

/*
void CSocket::SetUser( User* pUser )
{
	typedef void (__fastcall*_FT)(CSocket*, User*);
	_FT f = (_FT)(CSocket__SetUser);
	f(this, pUser);
}*/
