#ifndef _API_HanBang_H
#define _API_HanBang_H
#include <Windows.h>
namespace HanBang
{
#include "HBSDVRSDK.h"
}
// #pragma comment(lib, "dhnetsdk.lib")
typedef DWORD (__stdcall *pHB_SDVR_GetLastError)();
typedef BOOL (__stdcall *pHB_SDVR_Init)();
typedef BOOL (__stdcall *pHB_SDVR_Cleanup)();
typedef LONG (__stdcall *pHB_SDVR_Login_Ex_Nvs)(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,HanBang::LPHB_SDVR_DEVICEINFO_EX lpDeviceInfo);
typedef BOOL (__stdcall *pHB_SDVR_Logout)(LONG lUserID);
typedef BOOL (__stdcall *pHB_SDVR_GetDVRConfig)(LONG lUserID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer,DWORD dwOutBufferSize,LPDWORD lpBytesReturned,DWORD type);
typedef LONG (__stdcall *pHB_SDVR_FindFile)(LONG lUserID,LONG lChannel,DWORD dwFileType, HanBang::LPHB_SDVR_TIME lpStartTime, HanBang::LPHB_SDVR_TIME lpStopTime);
typedef LONG (__stdcall *pHB_SDVR_FindNextFile)(LONG lFindHandle,HanBang::LPHB_SDVR_FIND_DATA lpFindData);
typedef BOOL (__stdcall *pHB_SDVR_FindClose)(LONG lFindHandle);
typedef LONG (__stdcall *pHB_SDVR_GetFileByName)(LONG lUserID,char *sDVRFileName,char *sSavedFileName);
typedef DWORD (__stdcall *pHB_SDVR_GetDownloadTotalSize)(LONG lFileHandle);
typedef int (__stdcall *pHB_SDVR_GetDownloadPos)(LONG lFileHandle);
typedef BOOL (__stdcall *pHB_SDVR_StopGetFile)(LONG lFileHandle);
typedef LONG (__stdcall *pHB_SDVR_PlayBackByName)(LONG lUserID, char *sPlayBackFileName, HWND hWnd);
typedef LONG (__stdcall *pHB_SDVR_PlayBackByTime)(LONG lUserID,LONG lChannel, HanBang::LPHB_SDVR_TIME lpStartTime, HanBang::LPHB_SDVR_TIME lpStopTime, HWND hWnd);
typedef LONG (__stdcall *pHB_SDVR_PlayBackByTimeWithChl_ex)(LONG lUserID, LONG lChannel, HanBang::LPHB_SDVR_TIME lpStartTime, HanBang::LPHB_SDVR_TIME lpStopTime, HWND hWnd);
typedef BOOL (__stdcall *pHB_SDVR_PlayBackControl)(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *lpOutValue);
typedef BOOL (__stdcall *pHB_SDVR_StopPlayBack)(LONG lPlayHandle);

typedef double (__stdcall *pHB_SDVR_GetDownloadBytesSize)(LONG  lFileHandle);

class Api_HanBang
{
public:
	Api_HanBang();
	virtual ~Api_HanBang();
	static Api_HanBang& Api();

public:
	pHB_SDVR_GetLastError m_pGetLastError;
	pHB_SDVR_Init m_pInit;
	pHB_SDVR_Cleanup m_pUninit;
	pHB_SDVR_Login_Ex_Nvs m_pLogin;
	pHB_SDVR_Logout m_pLogout;
	pHB_SDVR_GetDVRConfig m_pGetConfig;
	pHB_SDVR_FindFile m_pFindFile;
	pHB_SDVR_FindNextFile m_pFindNext;
	pHB_SDVR_FindClose m_pFindClose;
	pHB_SDVR_GetFileByName m_pDownloadByFile;
	pHB_SDVR_GetDownloadTotalSize m_pGetDownloadTotal;
	pHB_SDVR_GetDownloadPos m_pGetDownloadPos;
	pHB_SDVR_StopGetFile m_pStopDownload;
	pHB_SDVR_PlayBackByName m_pPlayBackByName;
	pHB_SDVR_PlayBackByTime m_pPlayBackByTime;
	pHB_SDVR_PlayBackByTimeWithChl_ex m_pPlayBackByTimeEx;
	pHB_SDVR_PlayBackControl m_pPlayBackControl;
	pHB_SDVR_StopPlayBack m_pStopPlayBack;

	pHB_SDVR_GetDownloadBytesSize m_pGetDownloadBytesSize;

private:
	HMODULE m_hMod;
};
#endif