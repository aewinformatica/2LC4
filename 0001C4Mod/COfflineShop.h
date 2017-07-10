#pragma once

typedef map<CSocket*, SOCKET> OfflineSocketMap;

class COfflineShop
{
public:
	static void Install();
	static BOOL OnWSASend(	__in   CSocket* pSocket,
							__in   LPWSABUF lpBuffers,
							__in   DWORD dwBufferCount,
							__out  LPDWORD lpNumberOfBytesSent,
							__in   DWORD dwFlags,
							__in   LPWSAOVERLAPPED lpOverlapped,
							__in   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
	static BOOL OnWSARecv(	__in     CSocket* pSocket,
							__inout  LPWSABUF lpBuffers,
							__in     DWORD dwBufferCount,
							__out    LPDWORD lpNumberOfBytesRecvd,
							__inout  LPDWORD lpFlags,
							__in     LPWSAOVERLAPPED lpOverlapped,
							__in     LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
	static void OnUserSay(User* pUser, WCHAR* pText);
	static void OnCloseSocket(CSocket* pSocket);
	static void OnShopQuit(User* pUser);
	static void OnWho(LPWSTR wcsBuffer, LPCWSTR wcsFormat, ...);
	static bool CanSellItem(CItem* pItem);
	static void OnSocketRead( CSocket* pSocket, LPVOID p2 );
	static void OnCloseSocket2( CSocket* pSocket );
	static OfflineSocketMap offlineShops;
	static map<u32, u32> requirements;
	static CRITICAL_SECTION cs;

	static u64 UserSayOriginal;
	static u64 UserLeaveWorldOriginal;
};
