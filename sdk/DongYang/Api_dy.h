#ifndef _Api_DONGYANG_H
#define _Api_DONGYANG_H
#include <Windows.h>
namespace DONGYANG
{
#include "hsx_cfgdefine.h"
#include "hsx_netclient.h"
}

typedef int (__stdcall *pDyNetwork_ClientInit)();
typedef int (__stdcall *pDyNetwork_ClientUnInit)();
typedef int (__stdcall *pDyNetwork_ClientLogin)(OUT HDEVICE *pDev, char *pSeverAddr, DWORD dwCmdPort, char *pUserName, char *pPassword);
typedef int (__stdcall *pDyNetwork_ClientGetDeviceConfig)(HDEVICE hDev, DWORD dwCommand, DWORD dwChannelMask, BYTE *pCfgBuf, DWORD dwBufLen);
typedef int (__stdcall *pDyNetwork_ClientLogout)(HDEVICE hDev);
typedef int (__stdcall *pDyNetwork_ClientStartFileQuery)(OUT HQUERY *pFileQuery, HANDLE hDev, DWORD dwChannel, DWORD dwFileType, DONGYANG::TimeInfo *pBeginTime, DONGYANG::TimeInfo *pEndTime);
typedef int (__stdcall *pDyNetwork_ClientGetFileQueryResult)(IN HQUERY hFileQuery, INOUT DWORD &dwFileCnt, OUT BYTE *pFileBuf, IN DWORD dwBufLen);
typedef int (__stdcall *pDyNetwork_ClientStopFileQuery)(HQUERY hFileQuery);
typedef int (__stdcall *pDyNetwork_ClientStartDownload)(OUT HDOWNLOAD *pDownload, HANDLE hDev, char *pDevFileName, char *pSavedFileName, DONGYANG::TimeInfo *pBeginTime, DONGYANG::TimeInfo *pEndTime);
typedef int (__stdcall *pDyNetwork_ClientStartPlayback)(OUT HPLAYBACK *pPlayback, HANDLE hDev, DWORD dwChannel, DWORD dwFileType, DONGYANG::TimeInfo *pBeginTime, DONGYANG::TimeInfo *pEndTime, HWND hWnd);
typedef int (__stdcall *pDyNetwork_ClientPlaybackControl)(IN HPLAYBACK hPlayback, DONGYANG::ePlaybackCtrlCode dwControlCode, void *pParam);
typedef int (__stdcall *pDyNetwork_ClientStopPlayback)(IN HPLAYBACK hPlayback);
typedef int (__stdcall *pDyNetwork_ClientStopDownload)(HDOWNLOAD hDownload);
typedef int (__stdcall *pDyNetwork_ClientGetDownloadStatus)(IN HDOWNLOAD hDownload, DWORD &dwProgress);

class Api_DY
{
public:
	Api_DY();
	virtual ~Api_DY();
	static Api_DY& Api();

public:
	pDyNetwork_ClientInit m_pDyNetwork_ClientInit;
	pDyNetwork_ClientUnInit m_pDyNetwork_ClientUnInit;
	pDyNetwork_ClientLogin m_pDyNetwork_ClientLogin;
	pDyNetwork_ClientGetDeviceConfig m_pDyNetwork_ClientGetDeviceConfig;
	pDyNetwork_ClientLogout m_pDyNetwork_ClientLogout;
	pDyNetwork_ClientStartFileQuery m_pDyNetwork_ClientStartFileQuery;
	pDyNetwork_ClientGetFileQueryResult m_pDyNetwork_ClientGetFileQueryResult;
	pDyNetwork_ClientStopFileQuery m_pDyNetwork_ClientStopFileQuery;
	pDyNetwork_ClientStartDownload m_pDyNetwork_ClientStartDownload;
	pDyNetwork_ClientStartPlayback m_pDyNetwork_ClientStartPlayback;
	pDyNetwork_ClientPlaybackControl m_pDyNetwork_ClientPlaybackControl;
	pDyNetwork_ClientStopPlayback m_pDyNetwork_ClientStopPlayback;
	pDyNetwork_ClientStopDownload m_pDyNetwork_ClientStopDownload;
	pDyNetwork_ClientGetDownloadStatus m_pDyNetwork_ClientGetDownloadStatus;

private:
	HMODULE m_hMod;
};
#endif