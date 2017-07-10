#pragma once

class User;
class CAmpedX64Socket;

#pragma pack( push, 1 )

class CIOBuffer
{
public:
	/* 0000 */ u8 bUnknownBlock[0x2010];
	/* 2010 */ s32 nWriteCount;
	/* 2014 */ s32 _dw2014;
	/* 2018 */ s32 _dw2018;
};

struct LastPacketData
{
	/* 000 */ u8 _unk000[0x10];
	/* 010 */ u16 nPacketSize;
	/* 012 */ u8 pPacket[0x2000];
};

class CSocket
{
public:
	/* Constructor / Destructor */

	CSocket() { };
	~CSocket() { };

	/* Hooked Functions */
	void Send(const char * format, ...);
	void Send(CSPacket *buf);
	void Close();
	void SendSystemMessage(s32 nMessageID);
	void SendSystemMessage(char *format, ...);
	void SendSystemMessage(wchar_t *wszSender, wchar_t *wszMessage);
	void SendSystemMessage(WCHAR *wsMsg, ...);
	void Lock();
	void Unlock();
	void CUserSocket__SendSystemMessage(char *BUF2); //(WCHAR *wMessagePrefix, WCHAR *wMessageContents);
	//void SetUser(User* pUser);

	bool IsValidUserSocket()
	{
        if(this)
		{
            __try
			{ 
				if(*(s32*)this == CSocket__VMT) return true; 
			}
            __except(EXCEPTION_EXECUTE_HANDLER)
			{ 
				/* Invalid pointer */
				/* Preventing Crash ;) */
			}
        }

		return false;
	}

	/* Class Extending Functions */
	/* 0000 */ s32 _dw0000[6];
	/* 0018 */ SOCKET s;
	/* 0020 */ s32 _dw0020[20];
	/* 0070 */ void *pWSAOverlapped;
	/* 0078 */ s32 _dw0078[6];
	/* 0090 */ LastPacketData* pPacketData;
	/* 0098 */ CIOBuffer *pCIOBuffer;
	/* 00A0 */ s32 _dw00A0[32];
	/* 0120 */ u8 *pDecryptKey;
	/* 0128 */ u8 *pEncryptKey;
	/* 0130 */ s32 _dw0130[10];
	/* 0158 */ User *user;
	/* 0160 */ s32 _dw0160[15];
	/* 0198 */ s32 nSocketStatus;
	/* 019C */ s32 _dw019C[4];
	/* 01B0 */ void *pLock;
	/* 01B8 */ s32 _dw01B8[0x94];
	/* 0408 */ __time32_t stardDisconnect;
	/* 040C */ s32 _dw040C[0x11];
	/* 0450 */ s32 nAccountID;
	/* 0454 */ s32 _dw0454;
	/* 0458 */ s32 _dw0458;
	/* 045C */ s32 _dw045C;
	/* 0460 */ s32 _dw0460;
	/* 0464 */ s32 _dw0464;
	/* 0468 */ s32 _dw0468;
	/* 046C */ s32 _dw046C;
#ifdef _AMPED64_
	/* Extended Area (AmpedX64) [0x470+] */
	/* 0470 */ CAmpedX64Socket *pAmpedSocket;
	/* 0478 */ s32 _dw0478;
#endif
};

#pragma pack( pop )
