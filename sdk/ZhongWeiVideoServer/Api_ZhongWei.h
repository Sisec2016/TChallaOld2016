#ifndef _API_DH_H
#define _API_DH_H
#include <Windows.h>
namespace ZhongWei
{
	//#include "ZhongWei/JCSDK.h"
#include "JCSDK.h"
}
// #pragma comment(lib, "dhnetsdk.lib")
typedef void (JCSDK_CALLTYPE *pJCSDK_RegisterCallback)(
	ZhongWei::JCEventCallback_t funEventCallback,
	ZhongWei::JCDataCallback_t funDataCallback,
	ZhongWei::JCRawDataCallback_t funRawDataCallback,
	ZhongWei::JCLanSearchDeviceCallback_t funLanSearchDeviceCallback);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_InitSDK)(int nLocStartPort);
typedef void (JCSDK_CALLTYPE *pJCSDK_ReleaseSDK)();
typedef ZhongWei::JCLink_t (JCSDK_CALLTYPE *pJCSDK_Connect)(char *szServer, int nPort, int nChannel,
	char *szNetUser, char *szPwd, BOOL bNumOrIP, LPVOID pUserData);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_EnableDecoder)(ZhongWei::JCLink_t nLinkID, BOOL bEnable);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_SetVideoPreview)(ZhongWei::JCLink_t nLinkID, HWND hWnd, LPRECT pRect);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_Disconnect)(ZhongWei::JCLink_t nLinkID);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_GetRemoteRecFileList)(ZhongWei::JCLink_t nLinkID, ZhongWei::PJCDateBlock pDate);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_DownloadRemoteFile)(ZhongWei::JCLink_t nLinkID, int nFileID);
typedef BOOL (JCSDK_CALLTYPE *pJCSDK_RemotePlay)(ZhongWei::JCLink_t nLinkID, int nFileID);
typedef BOOL(JCSDK_CALLTYPE *pJCSDK_RemotePlayControl)(ZhongWei::JCLink_t nLinkID, ZhongWei::JCRemotePlayCommand nCmd);

class Api_ZhongWei
{
public:
	Api_ZhongWei();
	virtual ~Api_ZhongWei();
	static Api_ZhongWei& Api();

public:
	pJCSDK_RegisterCallback m_pSetCallback;
	pJCSDK_InitSDK m_pInit;
	pJCSDK_ReleaseSDK m_pUninit;
	pJCSDK_Connect m_pLogin;
	pJCSDK_EnableDecoder m_pEnableDecoder;
	pJCSDK_SetVideoPreview m_pSetVPreview;
	pJCSDK_Disconnect m_pLogout;
	pJCSDK_GetRemoteRecFileList m_pSearchFileByTime;
	pJCSDK_DownloadRemoteFile m_pDownloadByFile;
	pJCSDK_RemotePlay m_pPlayBackByFile;
	pJCSDK_RemotePlayControl m_pPlayBackControl;

private:
	HMODULE m_hMod;
};
#endif