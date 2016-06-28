#ifndef _API_DH_H
#define _API_DH_H
#include <Windows.h>
namespace DH
{
#include "dhnetsdk.h"
}
// #pragma comment(lib, "dhnetsdk.lib")
typedef DWORD (CALL_METHOD *pCLIENT_GetLastError)(void);
typedef BOOL (CALL_METHOD *pCLIENT_QueryChannelName)(LLONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime);
typedef BOOL (CALL_METHOD*pCLIENT_Init)(DH::fDisConnect cbDisConnect, LDWORD dwUser);
typedef void (CALL_METHOD*pCLIENT_Cleanup)();
typedef LLONG (CALL_METHOD*pCLIENT_Login)(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, DH::LPNET_DEVICEINFO lpDeviceInfo, int *error);
typedef BOOL (CALL_METHOD*pCLIENT_Logout)(LLONG lLoginID);
typedef BOOL (CALL_METHOD*pCLIENT_QueryRecordFile)(LLONG lLoginID, int nChannelId, int nRecordFileType, DH::LPNET_TIME tmStart, DH::LPNET_TIME tmEnd, char* pchCardid, DH::LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime, BOOL bTime);
typedef LLONG (CALL_METHOD*pCLIENT_DownloadByRecordFile)(LLONG lLoginID,DH::LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, DH::fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData);
typedef LLONG (CALL_METHOD*pCLIENT_DownloadByTime)(LLONG lLoginID, int nChannelId, int nRecordFileType, DH::LPNET_TIME tmStart, DH::LPNET_TIME tmEnd, char *sSavedFileName, DH::fTimeDownLoadPosCallBack cbTimeDownLoadPos, LDWORD dwUserData);
typedef BOOL (CALL_METHOD *pCLIENT_GetDownloadPos)(LLONG lFileHandle, int *nTotalSize, int *nDownLoadSize);
typedef BOOL (CALL_METHOD*pCLIENT_StopDownload)(LLONG lFileHandle);
typedef LLONG (CALL_METHOD *pCLIENT_PlayBackByRecordFile)(LLONG lLoginID, DH::LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, DH::fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData);
typedef BOOL (CALL_METHOD *pCLIENT_SeekPlayBack)(LLONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);
typedef BOOL (CALL_METHOD *pCLIENT_PausePlayBack)(LLONG lPlayHandle, BOOL bPause);
typedef BOOL (CALL_METHOD *pCLIENT_StopPlayBack)(LLONG lPlayHandle);
typedef BOOL(CALL_METHOD *pCLIENT_SearchDevices)(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime, char* szLocalIp);
//<<<<<<<<<add by zhangyaofa 2016/06/15
typedef BOOL (CALL_METHOD *pCLIENT_QueryDevState)(LLONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime);
//>>>>>>>>>add end
class Api_DH
{
public:
	Api_DH();
	virtual ~Api_DH();
	static Api_DH& Api();

public:
	pCLIENT_GetLastError m_pGetLastError;
	pCLIENT_QueryChannelName m_pGetChannel;
	pCLIENT_Init m_pInit;
	pCLIENT_Cleanup m_pUninit;
	pCLIENT_Login m_pLogin;
	pCLIENT_Logout m_pLogout;
	pCLIENT_QueryRecordFile m_pSearchFileByTime;
	pCLIENT_DownloadByRecordFile m_pDownloadByFile;
	pCLIENT_DownloadByTime m_pDownloadByTime;
	pCLIENT_GetDownloadPos m_pGetDownloadPos;
	pCLIENT_StopDownload m_pStopDownload;
	pCLIENT_PlayBackByRecordFile m_pPlayBackByFile;
	pCLIENT_SeekPlayBack m_pSeekPlayBack;
	pCLIENT_PausePlayBack m_pPausePlayBack;
	pCLIENT_StopPlayBack m_pStopPlayBack;
    pCLIENT_SearchDevices m_pSearchDevices;
	//<<<<<<<<<<<<<<<add by zhangyaofa 2016/6/15
	pCLIENT_QueryDevState m_pQueryDevState;
	//>>>>>>>>>>>>>>add end
private:
	HMODULE m_hMod;
};
#endif