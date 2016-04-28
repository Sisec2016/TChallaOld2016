#ifndef _API_XingWang_H
#define _API_XingWang_H
#include <Windows.h>
#include <time.h>
#include <climits>
#include <cfloat>
namespace XingWang
{
#include "SN_DVR_Interface.h"
#include "SnplayEx.hpp"
#include "SnplayExDef.hpp"
// #include "TLPlay.h"
}
// #pragma comment(lib, "dhnetsdk.lib")
typedef DWORD (/*__stdcall*/ *pSN_DVR_GetLastError)();
typedef LONG (/*__stdcall*/ *pSN_DVR_SDKInit)();
typedef LONG (/*__stdcall*/ *pSN_DVR_SDKUninit)();
typedef LONG (/*__stdcall*/ *pSN_DVR_UserLogon)(char *strDeviceIP,
	WORD Port,
	char *UserName,
	char *Passwd,
	XingWang::LPSN_DEVICEINFO lpDeviceInfo);
typedef BOOL (/*__stdcall*/ *pSN_DVR_UserLogoff)(LONG SessionID);
typedef LONG(/*__stdcall*/ *pSN_DVR_FindFirstFile)(XingWang::LPSN_DVR_FILECONDITION lpFileCondition, XingWang::LPSN_DVR_FILEDATA lpFileData);
typedef BOOL(/*__stdcall*/ *pSN_DVR_FindNextFile)(LONG lFindHandle, XingWang::LPSN_DVR_FILEDATA lpFileData);
typedef BOOL (/*__stdcall*/ *pSN_DVR_FindClose)(LONG lFindHandle);
typedef LONG (/*__stdcall*/ *pSN_DVR_DownloadFileByName)(LONG lSessionID,
	char *sDVRFileName,
	char *sSavedFileName);
typedef int (/*__stdcall*/ *pSN_DVR_GetDownloadPos)(LONG lDownloadHandle);
typedef BOOL (/*__stdcall*/ *pSN_DVR_StopDownloadFile)(LONG lDownloadHandle);
typedef LONG(/*__stdcall*/ *pSN_DVR_PlayBackByFileName)(LONG lSessionID,
	char *sPlayBackFileName,
	HWND hWnd,
	XingWang::PFN_NVRDISPLAYCALLBACK pfnCallBack,
	void *pContext);
typedef BOOL (/*__stdcall*/ *pSN_DVR_PlayBackControl)(LONG  lPlayHandle,
	DWORD dwControlCode,
	DWORD dwInValue,
	DWORD *lpOutValue);
typedef BOOL (/*__stdcall*/ *pSN_DVR_StopPlayBack)(LONG lPlayHandle);

typedef BOOL(*pSnPlay_Init)();
typedef BOOL(*pSnPlay_GetPort)(LONG* nPort);
typedef BOOL(*pSnPlay_FreePort)(LONG nPort);
typedef BOOL(*pSnPlay_SetStreamOpenMode)(LONG nPort, DWORD nMode);
typedef BOOL(*pSnPlay_Play)(LONG nPort, HWND hWnd);
typedef BOOL(*pSnPlay_Stop)(LONG nPort);
typedef BOOL(*pSnPlay_InputData)(LONG nPort, PBYTE pBuf, DWORD nSize);

// typedef BOOL(__stdcall *pTLPlay_GetPort)(LONG* pnPort);
// typedef BOOL(__stdcall *pTLPlay_FreePort)(LONG nPort);
// typedef BOOL(__stdcall *pTLPlay_SetPlayMode)(LONG nPort, XingWang::TLPLAYMODE mode);
// typedef BOOL(__stdcall *pTLPlay_OpenStream)(LONG nPort, DWORD dwPoolsize);
// typedef BOOL(__stdcall *pTLPlay_SetDelayTime)(LONG nPort, int nSeconds, int nFrames);
// typedef BOOL(__stdcall *pTLPlay_Close)(LONG nPort);
// typedef BOOL(__stdcall *pTLPlay_Play)(LONG nPort, HWND hWnd);
// typedef BOOL(__stdcall *pTLPlay_Stop)(LONG nPort);
// typedef BOOL(__stdcall *pTLPlay_InputVideoData)(LONG nPort, PBYTE pBuf, DWORD nSize);
// typedef BOOL(__stdcall *pTLPlay_InputAudioData)(LONG nPort, PBYTE pBuf, DWORD nSize);

class Api_XingWang
{
public:
	Api_XingWang();
	virtual ~Api_XingWang();
	static Api_XingWang& Api();

	void ReloadPlayLib();
public:
	pSN_DVR_GetLastError m_pGetLastError;
	pSN_DVR_SDKInit m_pInit;
	pSN_DVR_SDKUninit m_pUninit;
	pSN_DVR_UserLogon m_pLogin;
	pSN_DVR_UserLogoff m_pLogout;
	pSN_DVR_FindFirstFile m_pFindFile;
	pSN_DVR_FindNextFile m_pFindNext;
	pSN_DVR_FindClose m_pFindClose;
	pSN_DVR_DownloadFileByName m_pDownloadByFile;
	pSN_DVR_GetDownloadPos m_pGetDownloadPos;
	pSN_DVR_StopDownloadFile m_pStopDownload;
	pSN_DVR_PlayBackByFileName m_pPlayBackByName;
	pSN_DVR_PlayBackControl m_pPlayBackControl;
	pSN_DVR_StopPlayBack m_pStopPlayBack;

	pSnPlay_Init m_pPlayInit;
	pSnPlay_GetPort m_pPlayGetPort;
	pSnPlay_FreePort m_pPlayFreePort;
	pSnPlay_SetStreamOpenMode m_pPlaySetMode;
	pSnPlay_Play m_pPlayPlay;
	pSnPlay_Stop m_pPlayStop;
	pSnPlay_InputData m_pPlayInputV;

// 	pTLPlay_GetPort m_pPlayGetPort;
// 	pTLPlay_FreePort m_pPlayFreePort;
// 	pTLPlay_SetPlayMode m_pPlaySetMode;
// 	pTLPlay_OpenStream m_pPlayOpenStream;
// 	pTLPlay_SetDelayTime m_pPlaySetDelay;
// 	pTLPlay_Close m_pPlayClose;
// 	pTLPlay_Play m_pPlayPlay;
// 	pTLPlay_Stop m_pPlayStop;
// 	pTLPlay_InputVideoData m_pPlayInputV;
// 	pTLPlay_InputAudioData m_pPlayInputA;

private:
	HMODULE m_hMod;
	HMODULE m_hModPlay;
};
#endif