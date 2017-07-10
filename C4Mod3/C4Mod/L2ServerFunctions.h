#pragma once

class CObject;
class CSetItem;
class CItem;
class CSkillInfo;
class User;

class L2Server
{
public:
	static u32 GetClassIdFromName(const WCHAR* name)
	{
		typedef u32 (__fastcall*TFunc)(LPVOID, const WCHAR*);
		TFunc func = (TFunc)L2Server__GetClassIdFromName;
		return func((LPVOID)L2Server__GetClassIdFromNameObj, name);
	}

	static User *GetObjectByName(WCHAR *cObjectName)
	{
		typedef void (__fastcall *_GET_OBJECT_BY_NAME) (VOID *ClassObject, CHAR *pFound, WCHAR *cObjectName);
		_GET_OBJECT_BY_NAME xGetObjectByName = (_GET_OBJECT_BY_NAME)L2Server__GetObjectByName;
		CHAR pUsrAddr[0x2D78 + 0x08];
		xGetObjectByName((VOID *)L2Server__GetObjectByNameObj, pUsrAddr, cObjectName);
		User *pUser = (User *)pUsrAddr;
		return pUser;
	}

	static void *GetObject(s32 nObjectID)
	{
		typedef void *(__fastcall *_GET_OBJECT) (s32 id);
		_GET_OBJECT xGetObject = (_GET_OBJECT)L2Server__GetObject;
		return xGetObject(nObjectID);
	}

	static CObject *GetObjectByClassId(s32 nClassID)
	{
		typedef CObject *(__fastcall *_GET_OBJECT) (s64, s32);
		_GET_OBJECT xGetObject = (_GET_OBJECT)L2Server__GetObjectByClassId;
		return xGetObject(L2Server__GetClassIdFromNameObj, nClassID);
	}

	static CSetItem *GetSetObject(s32 nSetID)
	{
		typedef CSetItem *(__fastcall *_SET_GET_OBJECT) (VOID *pObjectDB, s32 nsid);
		_SET_GET_OBJECT xSetGetObject = (_SET_GET_OBJECT)L2Server__GetSetObject;
		return xSetGetObject((VOID *)L2Server__GetSetObjectObj, nSetID);
	}

	static void BroadcastToNeighbor(s32 ObjectID, vPosition vPos, CSPacket *pPacket)
	{
		typedef void (__fastcall *_BROADCAST_TO_NEIGHBOR) (VOID *UnkArg1, s32 ObjID, s32 Dist, vPosition Pos, const char *fmt, ...);
		_BROADCAST_TO_NEIGHBOR xBroadcastToNeighbor = (_BROADCAST_TO_NEIGHBOR)L2Server__BroadcastToNeighbor;
		xBroadcastToNeighbor((VOID *)L2Server__BroadcastToNeighborObj, ObjectID, 0x80000, vPos, "b", pPacket->size(), pPacket->buffer(false));
	}

	static void BroadcastToNeighborDist(s32 ObjectID, vPosition vPos, s32 Distance, CSPacket *pPacket)
	{
		typedef void (__fastcall *_BROADCAST_TO_NEIGHBOR_DIST) (VOID *UnkArg1, s32 ObjID, s32 Dist, vPosition Pos, s32 Dist2, const char *fmt, ...);
		_BROADCAST_TO_NEIGHBOR_DIST xBroadcastToNeighborDist = (_BROADCAST_TO_NEIGHBOR_DIST)L2Server__BroadcastToNeighborDist;
		xBroadcastToNeighborDist((VOID *)L2Server__BroadcastToNeighborObj, ObjectID, 0x80000, vPos, Distance, "b", pPacket->size(), pPacket->buffer(false));
	}

	static void BroadcastToNeighborExceptSelf(s32 ObjectID, vPosition vPos, CSPacket *pPacket)
	{
		typedef void (__fastcall *_BROADCAST_TO_NEIGHBOR_EXCEPT_SELF) (VOID *UnkArg1, s32 ObjID, s32 Dist, vPosition Pos, const char *fmt, ...);
		_BROADCAST_TO_NEIGHBOR_EXCEPT_SELF xBroadcastToNeighborExceptSelf = (_BROADCAST_TO_NEIGHBOR_EXCEPT_SELF)L2Server__BroadcastToNeighborExceptSelf;
		xBroadcastToNeighborExceptSelf((VOID *)L2Server__BroadcastToNeighborObj, ObjectID, 0x80000, vPos, "b", pPacket->size(), pPacket->buffer(false));
	}

	static void BroadcastToAllUser(CSPacket *pPacket)
	{
		typedef void (__fastcall *_BROADCAST_TO_ALL_USER) (const char * format, ...);
		_BROADCAST_TO_ALL_USER BroadcastToAllUser = (_BROADCAST_TO_ALL_USER)L2Server__BroadcastToAllUser;
		BroadcastToAllUser("b", pPacket->size(), pPacket->buffer(false));
	}

	static void BroadcastToAllUser(const char* format, ...)
	{
		typedef void (__fastcall *_BROADCAST_TO_ALL_USER) (const char * format, ...);
		_BROADCAST_TO_ALL_USER BroadcastToAllUser = (_BROADCAST_TO_ALL_USER)L2Server__BroadcastToAllUser;
		BroadcastToAllUser(format);
	}

	static void BroadcastSendSystemMessageToAll(char *format, ...)
	{
		typedef void (__fastcall *_BROADCAST_TO_ALL_USER) (const char * format, ...);
		_BROADCAST_TO_ALL_USER xBroadcastToAllUser = (_BROADCAST_TO_ALL_USER)L2Server__BroadcastToAllUser;

		CHAR  BUF1[256];
		WCHAR BUF2[512];

		memset(BUF1, 0x00, 256);
		memset(BUF2, 0x00, 512);

		va_list args;
		va_start(args, format);
		vsprintf(BUF1,format,args);
		va_end(args);

		MultiByteToWideChar(CP_ACP, 0, BUF1, -1, BUF2, 256);

		xBroadcastToAllUser("cdddSdS", 0x64, 614, 2, 0, L"SVR", 0, BUF2);
	}

	static void* New(s32 nSize)
	{
		typedef void*(*_new)(s32);
		_new __new = (_new)L2Server__New ;
		return __new(nSize);
	}
	
	static void Delete(void *pPointer)
	{
		typedef void(*_del)(void*);
		_del __del = (_del)L2Server__Delete ;
		__del(pPointer);
	}

	static void LockCS(VOID *lpCriticalSection, wchar_t *wszFile, s32 nLine)
	{
		typedef void (__fastcall *_Lock)(VOID *, WCHAR *, s32);
		_Lock xLock = (_Lock)L2Server__LockCS ;
		xLock(lpCriticalSection, wszFile, nLine);
	}

	static void UnlockCS(VOID *lpCriticalSection, wchar_t *wszFile, s32 nLine)
	{
		typedef void (__fastcall *_UnLock)(VOID *, WCHAR *, s32);
		_UnLock xUnLock = (_UnLock)L2Server__UnlockCS ;
		xUnLock(lpCriticalSection, wszFile, nLine);
	}

	static CItem* CreateItem(s32 nClassID)
	{
		typedef CItem* (__fastcall*_TODCI)(s64, s32);
		_TODCI _ODCI = (_TODCI)L2Server__CreateItem;
		return _ODCI(L2Server__CreateItemObj, nClassID);
	}

	static CObject* FindItemByIndex(s32 nObjID)
	{
		u64 nRetAddr = 0;
		typedef void (__fastcall*_TGOBOI)(s64, u64*, s32);
		_TGOBOI _GOBOI = (_TGOBOI)L2Server__FindItemByIndex;
		_GOBOI(L2Server__FindItemByIndexObj, &nRetAddr, nObjID);
		return (CObject*)nRetAddr;
	}

	static CSkillInfo *GetSkillInfo(u16 SkillID, u8 SkillLevel)
	{
		typedef CSkillInfo *(*_GETSKILLINFO) (void *CSkillDB, CSkillKey *c);
		_GETSKILLINFO xGetSkillInfo = (_GETSKILLINFO)L2Server__GetSkillInfo;

		CSkillKey c;
		c.nID = SkillID;
		c.nLevel = SkillLevel;

		CSkillInfo *pSI = xGetSkillInfo((void *)L2Server__GetSkillInfoObj, &c);

		if ( !pSI )
			return NULL;
		else
			return pSI;
	}

	static bool MakeReply(u32 nType, User *pAsker, User *pAsked, u32 nTimeout)
	{
		typedef bool (*makereply)(u32, User*, User*, u32);
		makereply _makereply = (makereply)L2Server__MakeReply ;
		return _makereply(nType, pAsker, pAsked, nTimeout);
	}

	static User *GetAsker(User *pUser)
	{
		typedef void (*_GA)(CObjectSP*, User*);
		_GA GA = (_GA)L2Server__GetAsker ;

		CObjectSP userSP;
		GA(&userSP, pUser);
		return (User*)userSP.pObject;
	}

	static void ResetAsker(User *pUser)
	{
		typedef void (*resetasker)(User*);
		resetasker _ra = (resetasker)L2Server__ResetAsker ;
		_ra(pUser);
	}

	static u32 UnicodeToAnsi(WCHAR* unistr, u32 maxunilen, const char* ansistr, u32 maxansilen)
	{
		typedef u32 (*tfunc)(WCHAR*, u32, const char*, u32);
		tfunc _func = (tfunc)L2Server__UnicodeToAnsi ;
		return _func(unistr, maxunilen, ansistr, maxansilen);
	}

	static u32 AnsiToUnicode(const char* ansistr, u32 maxansilen, WCHAR*  unistr, u32 maxunilen)
	{
		typedef u32 (*tfunc)(const char*, u32, WCHAR*, u32);
		tfunc _func = (tfunc)L2Server__AnsiToUnicode ;
		return _func(ansistr, maxansilen, unistr, maxunilen);
	}
};
