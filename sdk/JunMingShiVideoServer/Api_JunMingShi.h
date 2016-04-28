#ifndef _API_JunMingShi_H
#define _API_JunMingShi_H
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
namespace JunMingShi
{
#include "netdvr.h"
#include "TLPlay.h"
}
// #pragma comment(lib, "dhnetsdk.lib")

typedef int (__stdcall *pNETDVR_startup)(void);
typedef int (__stdcall *pNETDVR_cleanup)(void);
typedef int (__stdcall *pNETDVR_createDVR)(int *p_handle, unsigned int serverip, unsigned short serverport);
typedef int (__stdcall *pNETDVR_destroyDVR)(int Handle);
typedef int (__stdcall *pNETDVR_loginServer)(int Handle, const JunMingShi::NETDVR_loginInfo_t *p_para);
typedef int (__stdcall *pNETDVR_logoutServer)(int Handle);
typedef int(__stdcall *pNETDVR_GetDeviceInfo)(int Handle, JunMingShi::NETDVR_DeviceInfo_t *pDeviceInfo);
typedef int (__stdcall *pNETDVR_recFilesSearch)(int Handle, const JunMingShi::NETDVR_fileSearchCondition_t *prfs, JunMingShi::NETDVR_recFileSearchResult_t *pdesc);
typedef int (__stdcall *pNETDVR_recFilesSearchClean)(JunMingShi::NETDVR_recFileSearchResult_t *pdesc);
typedef int(__stdcall *pNETDVR_regCBFileRecieverProgress)(int Handle, JunMingShi::PFUN_PROGRESS_T p_cb_progress, unsigned int dwContent);
typedef int (__stdcall *pNETDVR_regCBFileRecieverError)(int Handle, JunMingShi::PFUN_ERROR_T p_cb_err, unsigned int dwContent);
typedef int (__stdcall *pNETDVR_startFileDownload)(int Handle,  char *s_save_dir, char *s_save_filename, const JunMingShi::NETDVR_recFileInfo_t *pFileInfo);
typedef int (__stdcall *pNETDVR_regCBFileRecieverProgress)(int Handle, JunMingShi::PFUN_PROGRESS_T p_cb_progress, unsigned int dwContent);
typedef int (__stdcall *pNETDVR_stopFileDownload)(int Handle);
typedef int (__stdcall *pNETDVR_startPlayByFile)(int Handle,  const JunMingShi::NETDVR_recFileInfo_t *pFileInfo, const JunMingShi::PlayBackClientInfo_t* pClientInfo, int* pPlayHandle);
typedef int (__stdcall *pNETDVR_playSeek)(int nPlayBackHandle, unsigned int new_time);
typedef int (__stdcall *pNETDVR_pausePlay)(int nPlayBackHandle);
typedef int (__stdcall *pNETDVR_stopPlayBack)(int nPlayBackHandle);

typedef BOOL (__stdcall *pTLPlay_GetPort)(LONG* pnPort);
typedef BOOL (__stdcall *pTLPlay_FreePort)(LONG nPort);
typedef BOOL (__stdcall *pTLPlay_SetPlayMode)(LONG nPort, JunMingShi::TLPLAYMODE mode);
typedef BOOL (__stdcall *pTLPlay_OpenStream)(LONG nPort, DWORD dwPoolsize);
typedef BOOL (__stdcall *pTLPlay_SetDelayTime)(LONG nPort, int nSeconds, int nFrames);
typedef BOOL (__stdcall *pTLPlay_Close)(LONG nPort);
typedef BOOL (__stdcall *pTLPlay_Play)(LONG nPort, HWND hWnd);
typedef BOOL (__stdcall *pTLPlay_Stop)(LONG nPort);
typedef BOOL (__stdcall *pTLPlay_InputVideoData)(LONG nPort, PBYTE pBuf,DWORD nSize);
typedef BOOL (__stdcall *pTLPlay_InputAudioData)(LONG nPort, PBYTE pBuf,DWORD nSize);

class Api_JunMingShi
{
public:
	Api_JunMingShi();
	virtual ~Api_JunMingShi();
	static Api_JunMingShi& Api();

public:
	pNETDVR_startup m_pInit;
	pNETDVR_cleanup m_pUninit;
	pNETDVR_createDVR m_pCreateDvr;
	pNETDVR_destroyDVR m_pDestroyDvr;
	pNETDVR_loginServer m_pLogin;
	pNETDVR_logoutServer m_pLogout;
	pNETDVR_GetDeviceInfo m_pGetDeviceInfo;
	pNETDVR_recFilesSearch m_pSearchFileByTime;
	pNETDVR_recFilesSearchClean m_pSearchFileByTimeClean;
	pNETDVR_regCBFileRecieverProgress m_pSetDownPosCallback;
	pNETDVR_regCBFileRecieverError m_pSetDownErrCallback;
	pNETDVR_startFileDownload m_pDownloadByFile;
	pNETDVR_regCBFileRecieverProgress m_pSetCb;
	pNETDVR_stopFileDownload m_pStopDownload;
	pNETDVR_startPlayByFile m_pPlayBackByFile;
	pNETDVR_playSeek m_pSeekPlayBack;
	pNETDVR_pausePlay m_pPausePlayBack;
	pNETDVR_stopPlayBack m_pStopPlayBack;

	pTLPlay_GetPort m_pPlayGetPort;
	pTLPlay_FreePort m_pPlayFreePort;
	pTLPlay_SetPlayMode m_pPlaySetMode;
	pTLPlay_OpenStream m_pPlayOpenStream;
	pTLPlay_SetDelayTime m_pPlaySetDelay;
	pTLPlay_Close m_pPlayClose;
	pTLPlay_Play m_pPlayPlay;
	pTLPlay_Stop m_pPlayStop;
	pTLPlay_InputVideoData m_pPlayInputV;
	pTLPlay_InputAudioData m_pPlayInputA;

private:
	HMODULE m_hMod;
	HMODULE m_hModPlay;
};
#endif