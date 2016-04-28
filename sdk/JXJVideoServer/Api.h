#ifndef _API__H
#define _API__H
#include <windows.h>
#include "JNetSDK.h"
#include "AVPlayer.h"
#include <memory>
// #pragma comment(lib, "dhnetsdk.lib")
typedef int (__stdcall *pFunJNetInit)(const char* lpszLogName);
typedef int (__stdcall *pFunAVP_Init)();
typedef int (__stdcall *pFunAVP_InitRecMng)(int iCount, int iBufMBs);
typedef int(__stdcall *pFunAVP_Cleanup)();
typedef int(__stdcall *pFunJNetCleanup)();
typedef long(__stdcall *pFunJNetLogin)(const char*  lpszIP, int iDevPort, const char*  lpszUser, const char*  lpszPassword, int iTimeOut, fcbJEvent* pfcbEvent, void* pUserParam, DWORD dwProtocol, long& lLogin, PSTJProxyParam pstProxy);
typedef long(__stdcall *pFunJNetGetParam)(long lLogin, int iChn, int iParamID, void* lpData, int iDataLen, fcbJGetParam* pfcbGetParam, void* pUser);
typedef long(__stdcall *pFunJNetLogout)(long lLogin);
typedef long(__stdcall *pFunJNetRecOpen4Time)(long lLogin, const char*  lpszDevIP, int iChn, int iStreamID, const char*  lpszBeginTime, const char*  lpszEndTime, int iRecType, int iIsPlay, fcbJStream* pfcbStream, void* pUserData, long& lRec);
typedef long(__stdcall *pFunJNetRecCtrl)(long lRec, eJNetPBCtrl eCtrlCmd, void* lpCtrlValue);
typedef int(__stdcall *pFunAVP_CreateRecFile)(const char* lpszPath, DWORD dwProtocol, DWORD dwEncoder);
typedef int(__stdcall *pFunAVP_GetFreePort)();

typedef int(__stdcall *pFunAVP_SetPlayPriority)(int iPort, int iPriorityType);
typedef int(__stdcall *pFunAVP_SetDataProtocol)(int iPort, DWORD dwProtocol);
typedef int(__stdcall *pFunAVP_SetCoder)(int iPort, LPCTSTR lpszCoderName);
typedef int(__stdcall *pFunAVP_AddPlayWnd)(int iPort, PSTDisplayDev pstDispDev, HWND hWnd, LPRECT lpDrawOffset, LPRECT lpSrcOffset);
typedef int(__stdcall *pFunAVP_Play)(int iPort);
typedef int(__stdcall *pFunAVP_Seek)(int iPort, DWORD dwTime);
typedef int(__stdcall *pFunAVP_Stop)(int iPort);
typedef int(__stdcall *pFunAVP_ReleasePort)(int iPort);
typedef long(__stdcall *pFunJNetRecClose)(long lRec);
typedef int(__stdcall *pFunAVP_CloseRecFile)(int iFile);


class Api
{
    static std::shared_ptr<Api> spInstance;
public:
    Api();
    virtual ~Api();
    
    static Api& instance(){
        if (!spInstance)
        {
            spInstance = std::make_shared<Api>();
        }
        return *spInstance;
    }

public:
    pFunJNetInit mJNetInit;
    pFunAVP_Init mAVP_Init;
    pFunAVP_InitRecMng mAVP_InitRecMng;
    pFunAVP_Cleanup mAVP_Cleanup;
    pFunJNetCleanup mJNetCleanup;
    pFunJNetLogin mJNetLogin;
    pFunJNetGetParam mJNetGetParam;
    pFunJNetLogout mJNetLogout;
    pFunJNetRecOpen4Time mJNetRecOpen4Time;
    pFunJNetRecCtrl mJNetRecCtrl;
    pFunAVP_CreateRecFile mAVP_CreateRecFile;
    pFunAVP_GetFreePort mAVP_GetFreePort;

    pFunAVP_SetPlayPriority mAVP_SetPlayPriority;
    pFunAVP_SetDataProtocol mAVP_SetDataProtocol;
    pFunAVP_SetCoder mAVP_SetCoder;
    pFunAVP_AddPlayWnd mAVP_AddPlayWnd;
    pFunAVP_Play mAVP_Play;
    pFunAVP_Seek mAVP_Seek;
    pFunAVP_Stop mAVP_Stop;
    pFunAVP_ReleasePort mAVP_ReleasePort;
    pFunJNetRecClose mJNetRecClose;
    pFunAVP_CloseRecFile mAVP_CloseRecFile;

private:
	HMODULE m_hModNet;
    HMODULE m_hModAvp;
};
#endif