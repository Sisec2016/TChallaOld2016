#ifndef _Api_DiZhiPu_H
#define _Api_DiZhiPu_H
#include <Windows.h>
namespace DiZhiPu
{
#include "netsdk.h"
}

typedef long (CALL_METHOD *pH264_DVR_GetLastError)();
typedef long (CALL_METHOD *pH264_DVR_GetDevConfig)(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime);
typedef long (CALL_METHOD *pH264_DVR_Init)(DiZhiPu::fDisConnect cbDisConnect, unsigned long dwUser);
typedef bool (CALL_METHOD *pH264_DVR_Cleanup)();
typedef long (CALL_METHOD *pH264_DVR_Login)(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
	DiZhiPu::LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,int socketType);
typedef long (CALL_METHOD *pH264_DVR_Logout)(long lLoginID);
typedef long (CALL_METHOD *pH264_DVR_FindFile)(long lLoginID, DiZhiPu::H264_DVR_FINDINFO* lpFindInfo, DiZhiPu::H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime);
typedef long (CALL_METHOD *pH264_DVR_GetFileByName)(long lLoginID,DiZhiPu::H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName, 
	DiZhiPu::fDownLoadPosCallBack cbDownLoadPos, long dwDataUser,DiZhiPu::fRealDataCallBack fDownLoadDataCallBack);
typedef long (CALL_METHOD *pH264_DVR_GetFileByTime)(long lLoginID, DiZhiPu::H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge,
	DiZhiPu::fDownLoadPosCallBack cbDownLoadPos, long dwDataUser ,DiZhiPu::fRealDataCallBack fDownLoadDataCallBack );
typedef int (CALL_METHOD *pH264_DVR_GetDownloadPos)(long lFileHandle);
typedef bool (CALL_METHOD *pH264_DVR_StopGetFile)(long lFileHandle);
typedef long (CALL_METHOD *pH264_DVR_PlayBackByName)(long lLoginID, DiZhiPu::H264_DVR_FILE_DATA *sPlayBackFile, DiZhiPu::fDownLoadPosCallBack cbDownLoadPos, DiZhiPu::fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);
typedef bool (CALL_METHOD *pH264_DVR_PlayBackControl)(long lPlayHandle, long lControlCode,long lCtrlValue);
typedef bool (CALL_METHOD *pH264_DVR_StopPlayBack)(long lPlayHandle);

class Api_DiZhiPu
{
public:
	Api_DiZhiPu();
	virtual ~Api_DiZhiPu();
	static Api_DiZhiPu& Api();

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