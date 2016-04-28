#ifndef _Api_WSD_H
#define _Api_WSD_H
#include <Windows.h>
namespace WSD
{
#include "zlnetsdk.h"
}

typedef DWORD (CALLBACK *pZLNET_GetLastError)(void);
typedef BOOL (CALLBACK *pZLNET_GetDevConfig)
(
	LONG     lLoginID,
	DWORD    dwCommand,
	LONG     lChannel,
	LPVOID   lpOutBuffer,
	DWORD    dwOutBufferSize,
	LPDWORD  lpBytesReturned,
	int      waittime
);
typedef BOOL (CALLBACK *pZLNET_Init)(WSD::fZLDisConnect cbDisConnect, DWORD dwUser);
typedef void (CALLBACK *pZLNET_Cleanup)();
typedef LONG (CALLBACK *pZLNET_Login)(
	char               *pchDVRIP,
	WORD               wDVRPort,
	char               *pchUserName,
	char               *pchPassword,
	WSD::LPZLNET_DEVICEINFO lpDeviceInfo,
	int                *error
	);
typedef BOOL (CALLBACK *pZLNET_Logout)(LONG lLoginID);
typedef BOOL (CALLBACK *pZLNET_QueryRecordFile)(
	LONG                          lLoginID,
	int                           nChannelId,
	int                           nRecordFileType,
	WSD::LPZLNET_TIME             tmStart,
	WSD::LPZLNET_TIME             tmEnd,
	char                          *pchCardid,
	WSD::LPZLNET_RECORDFILE_INFO  nriFileinfo,
	int                           maxlen,
	int                           *filecount,
	int                           waittime,
	bool                          bTime
);
typedef LONG (CALLBACK *pZLNET_DownloadByRecordFile)(
	LONG                          lLoginID,
	WSD::LPZLNET_RECORDFILE_INFO  lpRecordFile,
	char                          *sSavedFileName,
	WSD::fZLDownLoadPosCallBack   cbDownLoadPos,
	DWORD                         dwUserData
);
typedef LONG (CALLBACK *pZLNET_DownloadByTime)(
	LONG							lLoginID,
	int								nChannelId,
	int								nRecordFileType,
	WSD::LPZLNET_TIME               tmStart,
	WSD::LPZLNET_TIME               tmEnd,
	char                            *sSavedFileName,
	WSD::fZLTimeDownLoadPosCallBack cbTimeDownLoadPos,
	DWORD							dwUserData
);
typedef BOOL (CALLBACK *pZLNET_GetDownloadPos)(LONG lFileHandle, int  *nTotalSize, int  *nDownLoadSize);
typedef BOOL (CALLBACK *pZLNET_StopDownload)(LONG lFileHandle);
typedef LONG (CALLBACK *pZLNET_PlayBackByRecordFile)(
	LONG                            lLoginID,
	WSD::LPZLNET_RECORDFILE_INFO    lpRecordFile,
	HWND                            hWnd,
	WSD::fZLDownLoadPosCallBack     cbDownLoadPos,
	DWORD                           dwUserData
);
typedef BOOL (CALLBACK *pZLNET_StopPlayBack)(LONG lPlayHandle);

typedef BOOL (CALLBACK *pZLNET_FindFile)(
	LONG			  lLoginID,
	int				  nChannelId,
	int				  nRecordFileType,
	char			  *cardid,
	WSD::LPZLNET_TIME time_start,
	WSD::LPZLNET_TIME time_end,
	bool              bTime,
	int               waittime
);

typedef int (CALLBACK *pZLNET_FindNextFile)(LONG lFindHandle, WSD::LPZLNET_RECORDFILE_INFO lpFindData);
typedef BOOL (CALLBACK *pZLNET_FindClose)(LONG lFindHandle);

class Api_WSD
{
public:
	Api_WSD();
	virtual ~Api_WSD();
	static Api_WSD& Api();

public:
	pZLNET_GetLastError ZLNET_GetLastError;
	pZLNET_GetDevConfig ZLNET_GetDevConfig;
	pZLNET_Init ZLNET_Init;
	pZLNET_Cleanup ZLNET_Cleanup;
	pZLNET_Login ZLNET_Login;
	pZLNET_Logout ZLNET_Logout;
	pZLNET_QueryRecordFile ZLNET_QueryRecordFile;
	pZLNET_DownloadByRecordFile ZLNET_DownloadByRecordFile;
	pZLNET_DownloadByTime ZLNET_DownloadByTime;
	pZLNET_GetDownloadPos ZLNET_GetDownloadPos;
	pZLNET_StopDownload ZLNET_StopDownload;
	pZLNET_PlayBackByRecordFile ZLNET_PlayBackByRecordFile;
	pZLNET_StopPlayBack ZLNET_StopPlayBack;

	pZLNET_FindFile ZLNET_FindFile;
	pZLNET_FindNextFile ZLNET_FindNextFile;
	pZLNET_FindClose ZLNET_FindClose;

private:
	HMODULE m_hMod;
};


#if 0
typedef long (CALL_METHOD *pH264_DVR_GetLastError)();
typedef long (CALL_METHOD *pH264_DVR_GetDevConfig)(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime);
typedef long (CALL_METHOD *pH264_DVR_Init)(WSD::fDisConnect cbDisConnect, unsigned long dwUser);
typedef bool (CALL_METHOD *pH264_DVR_Cleanup)();
typedef long (CALL_METHOD *pH264_DVR_Login)(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
	WSD::LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error, int socketType);
typedef long (CALL_METHOD *pH264_DVR_Logout)(long lLoginID);
typedef long (CALL_METHOD *pH264_DVR_FindFile)(long lLoginID, WSD::H264_DVR_FINDINFO* lpFindInfo, WSD::H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime);
typedef long (CALL_METHOD *pH264_DVR_GetFileByName)(long lLoginID, WSD::H264_DVR_FILE_DATA *sPlayBackFile, char *sSavedFileName,
	WSD::fDownLoadPosCallBack cbDownLoadPos, long dwDataUser, WSD::fRealDataCallBack fDownLoadDataCallBack);
typedef long (CALL_METHOD *pH264_DVR_GetFileByTime)(long WSD, WSD::H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge,
	WSD::fDownLoadPosCallBack cbDownLoadPos, long dwDataUser, WSD::fRealDataCallBack fDownLoadDataCallBack);
typedef int (CALL_METHOD *pH264_DVR_GetDownloadPos)(long lFileHandle);
typedef bool (CALL_METHOD *pH264_DVR_StopGetFile)(long lFileHandle);
typedef long (CALL_METHOD *pH264_DVR_PlayBackByName)(long lLoginID, WSD::H264_DVR_FILE_DATA *sPlayBackFile, WSD::fDownLoadPosCallBack cbDownLoadPos, WSD::fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);
typedef bool (CALL_METHOD *pH264_DVR_PlayBackControl)(long lPlayHandle, long lControlCode,long lCtrlValue);
typedef bool (CALL_METHOD *pH264_DVR_StopPlayBack)(long lPlayHandle);

class Api_WSD
{
public:
	Api_WSD();
	virtual ~Api_WSD();
	static Api_WSD& Api();

public:
	pH264_DVR_GetLastError m_pGetLastError;
	pH264_DVR_GetDevConfig m_pGetConfig;
	pH264_DVR_Init m_pInit;
	pH264_DVR_Cleanup m_pUninit;
	pH264_DVR_Login m_pLogin;
	pH264_DVR_Logout m_pLogout;
	pH264_DVR_FindFile m_pSearchFileByTime;
	pH264_DVR_GetFileByName m_pDownloadByFile;
	pH264_DVR_GetFileByTime m_pDownloadByTime;
	pH264_DVR_GetDownloadPos m_pGetDownloadPos;
	pH264_DVR_StopGetFile m_pStopDownload;
	pH264_DVR_PlayBackByName m_pPlayBackByFile;
	pH264_DVR_PlayBackControl m_pPlayBackControl;
	pH264_DVR_StopPlayBack m_pStopPlayBack;

private:
	HMODULE m_hMod;
};
#endif
#endif