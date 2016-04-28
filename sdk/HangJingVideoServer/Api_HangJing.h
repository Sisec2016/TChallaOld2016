#ifndef _API_HangJing_H
#define _API_HangJing_H
#include <Windows.h>
namespace HangJing
{
#include "LvrNetSdk.h"
}
// #pragma comment(lib, "dhnetsdk.lib")
typedef DWORD(__stdcall *pLvrNetGetLastError)();
typedef BOOL(__stdcall *pLvrNetStartup)();
typedef void(__stdcall *pLvrNetCleanup)();
typedef LONG(__stdcall *pLvrNetLogin)(CHAR *sServerIP, WORD woServerPort, CHAR *sUserName, CHAR *sUserPassword, HangJing::LPLVR_NET_DEVICE_INFO pDeviceInfo);
typedef BOOL(__stdcall *pLvrNetLogout)(LONG lvrNetHandle);
typedef BOOL(__stdcall *pLvrNetGetConfig)(LONG lvrNetHandle, DWORD dwCommand, LONG lChannel, LPVOID pGetBuffer, DWORD dwBufferSize, LPDWORD pBytesReturned);
typedef LONG(__stdcall *pLvrNetFindFile)(LONG lvrNetHandle, LONG lChannel, DWORD dwFileType, BOOL bPlayback, HangJing::LPLVR_NET_TIME pStart, HangJing::LPLVR_NET_TIME pStop);
typedef LONG(__stdcall *pLvrNetFindNextFile)(LONG lvrFileHandle, HangJing::LPLVR_NET_FILE pLvrFile);
typedef BOOL(__stdcall *pLvrNetFindFileClose)(LONG lvrFileHandle);
typedef LONG(__stdcall *pLvrNetGetFileByName)(LONG lvrNetHandle, CHAR *pGetFile, CHAR *pSaveFile);
typedef LONG(__stdcall *pLvrNetGetFilePos)(LONG lvrGetHandle);
typedef BOOL(__stdcall *pLvrNetStopGetFile)(LONG lvrGetHandle);
typedef LONG(__stdcall *pLvrNetPlayByFile)(LONG lvrNetHandle, CHAR *pFile, HWND hPlayWnd);
typedef BOOL(__stdcall *pLvrNetPlayControl)(LONG lvrPlayHandle, DWORD dwCommand, LPARAM lParam);
typedef BOOL(__stdcall *pLvrNetPlayClose)(LONG lvrPlayHandle);

class Api_HangJing
{
public:
	Api_HangJing();
	virtual ~Api_HangJing();
	static Api_HangJing& Api();

public:
	pLvrNetGetLastError m_pGetLastError;
	pLvrNetStartup m_pInit;
	pLvrNetCleanup m_pUninit;
	pLvrNetLogin m_pLogin;
	pLvrNetLogout m_pLogout;
	pLvrNetGetConfig m_pGetConfig;
	pLvrNetFindFile m_pFindFile;
	pLvrNetFindNextFile m_pFindNext;
	pLvrNetFindFileClose m_pFindClose;
	pLvrNetGetFileByName m_pDownloadByFile;
	pLvrNetGetFilePos m_pGetDownloadPos;
	pLvrNetStopGetFile m_pStopDownload;
	pLvrNetPlayByFile m_pPlayBackByName;
	pLvrNetPlayControl m_pPlayBackControl;
	pLvrNetPlayClose m_pStopPlayBack;

private:
	HMODULE m_hMod;
};
#endif