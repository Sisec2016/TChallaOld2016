#ifndef _API_DaLi_DM_H
#define _API_DaLi_DM_H
// #define WIN32_LEAN_AND_MEAN
#include <Windows.h>
// namespace DaLi_DM
// {
#include "NetSDK.h"
// }
// #pragma comment(lib, "dhnetsdk.lib")
typedef DWORD (__stdcall *pNET_DLDVR_GetLastError)();
typedef BOOL (__stdcall *pNET_DLDVR_Init)();
typedef BOOL (__stdcall *pNET_DLDVR_Cleanup)();
typedef LONG (__stdcall *pNET_DLDVR_Login)(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_DLDVR_DEVICEINFO lpDeviceInfo);
typedef BOOL (__stdcall *pNET_DLDVR_Logout)(LONG lUserID);
typedef INT (__stdcall *pNET_DLDVR_OnlineHearBeat)(CHAR *sDVRIP, WORD port, LONG lUserID);
typedef BOOL (__stdcall *pNET_DLDVR_GetDVRConfig)(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer,DWORD dwOutBufferSize,LPDWORD lpBytesReturned);
typedef LONG (__stdcall *pNET_DLDVR_FindFile)(LONG lUserID,LONG lChannel,DWORD dwFileType, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime);
typedef LONG (__stdcall *pNET_DLDVR_FindNextFile)(LONG lFindHandle,LPNET_DLDVR_FIND_DATA lpFindData);
typedef BOOL (__stdcall *pNET_DLDVR_FindClose)(LONG lFindHandle);
typedef LONG (__stdcall *pNET_DLDVR_GetFileByName)(LONG lUserID,char *sDVRFileName,char *sSavedFileName);
typedef int (__stdcall *pNET_DLDVR_GetDownloadPos)(LONG lFileHandle);
typedef BOOL (__stdcall *pNET_DLDVR_StopGetFile)(LONG lFileHandle);
typedef LONG (__stdcall *pNET_DLDVR_PlayBackByName)(LONG lUserID, CHAR *sPlayBackFileName, HWND hWnd);
typedef LONG (__stdcall *pNET_DLDVR_PlayBackByTime)(LONG lUserID,LONG lChannel, LPNET_DLDVR_TIME lpStartTime, LPNET_DLDVR_TIME lpStopTime, HWND hWnd);
typedef BOOL (__stdcall *pNET_DLDVR_PlayBackControl)(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *lpOutValue);
typedef BOOL (__stdcall *pNET_DLDVR_StopPlayBack)(LONG lPlayHandle);

class Api_DaLi_DM
{
public:
	Api_DaLi_DM();
	virtual ~Api_DaLi_DM();
	static Api_DaLi_DM& Api();

public:
	pNET_DLDVR_GetLastError m_pGetLastError;
	pNET_DLDVR_Init m_pInit;
	pNET_DLDVR_Cleanup m_pUninit;
	pNET_DLDVR_Login m_pLogin;
	pNET_DLDVR_Logout m_pLogout;
	pNET_DLDVR_OnlineHearBeat m_pHeartBeat;
	pNET_DLDVR_GetDVRConfig m_pGetConfig;
	pNET_DLDVR_FindFile m_pFindFile;
	pNET_DLDVR_FindNextFile m_pFindNext;
	pNET_DLDVR_FindClose m_pFindClose;
	pNET_DLDVR_GetFileByName m_pDownloadByFile;
	pNET_DLDVR_GetDownloadPos m_pGetDownloadPos;
	pNET_DLDVR_StopGetFile m_pStopDownload;
	pNET_DLDVR_PlayBackByName m_pPlayBackByName;
	pNET_DLDVR_PlayBackByTime m_pPlayBackByTime;
	pNET_DLDVR_PlayBackControl m_pPlayBackControl;
	pNET_DLDVR_StopPlayBack m_pStopPlayBack;

private:
	HMODULE m_hMod;
};
#endif