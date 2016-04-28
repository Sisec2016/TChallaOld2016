#include "Api.h"
#include <string>
#include "log.h"
using namespace std;

static string GetExePath()
{
	char szPath[MAX_PATH];
	ZeroMemory(szPath, sizeof(szPath));
	HMODULE hIns = GetModuleHandle(NULL);
	GetModuleFileNameA(hIns, szPath, MAX_PATH);
	string strPath = szPath;
	int iIndex = strPath.rfind('\\');
	if (iIndex != string::npos)
	{
		strPath = strPath.substr(0, iIndex+1);
	}
	return strPath;
}
std::shared_ptr<Api> Api::spInstance;
Api::Api()
{

    m_hModNet = LoadLibraryA("JNetSDK.dll");
    if (m_hModNet == NULL)
	{
        Log::instance().AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
    }

    m_hModAvp = LoadLibraryA("AVPlayer.dll");
    if (m_hModAvp == NULL)
    {
        Log::instance().AddLog(QString("%1 %2").arg(__FUNCTION__).arg(__LINE__));
        return;
    }


    mJNetInit = (pFunJNetInit)GetProcAddress(m_hModNet, "JNetInit");
    mAVP_Init = (pFunAVP_Init)GetProcAddress(m_hModAvp, "AVP_Init");
    mAVP_InitRecMng = (pFunAVP_InitRecMng)GetProcAddress(m_hModAvp, "AVP_InitRecMng");
    mAVP_Cleanup = (pFunAVP_Cleanup)GetProcAddress(m_hModAvp, "AVP_Cleanup");
    mJNetCleanup = (pFunJNetCleanup)GetProcAddress(m_hModNet, "JNetCleanup");
    mJNetLogin = (pFunJNetLogin)GetProcAddress(m_hModNet, "JNetLogin");
    mJNetGetParam = (pFunJNetGetParam)GetProcAddress(m_hModNet, "JNetGetParam");
    mJNetLogout = (pFunJNetLogout)GetProcAddress(m_hModNet, "JNetLogout");

    mJNetRecCtrl = (pFunJNetRecCtrl)GetProcAddress(m_hModNet, "JNetRecCtrl");
    mJNetRecOpen4Time = (pFunJNetRecOpen4Time)GetProcAddress(m_hModNet, "JNetRecOpen4Time");

    mAVP_CreateRecFile = (pFunAVP_CreateRecFile)GetProcAddress(m_hModAvp, "AVP_CreateRecFile");
    mAVP_GetFreePort = (pFunAVP_GetFreePort)GetProcAddress(m_hModAvp, "AVP_GetFreePort");
    mAVP_SetPlayPriority = (pFunAVP_SetPlayPriority)GetProcAddress(m_hModAvp, "AVP_SetPlayPriority");

    mAVP_SetDataProtocol = (pFunAVP_SetDataProtocol)GetProcAddress(m_hModAvp, "AVP_SetDataProtocol");
    mAVP_SetCoder = (pFunAVP_SetCoder)GetProcAddress(m_hModAvp, "AVP_SetCoder");
    mAVP_AddPlayWnd = (pFunAVP_AddPlayWnd)GetProcAddress(m_hModAvp, "AVP_AddPlayWnd");

    mAVP_Play = (pFunAVP_Play)GetProcAddress(m_hModAvp, "AVP_Play");
    mAVP_Seek = (pFunAVP_Seek)GetProcAddress(m_hModAvp, "AVP_Seek");
    mAVP_Stop = (pFunAVP_Stop)GetProcAddress(m_hModAvp, "AVP_Stop");

    mAVP_ReleasePort = (pFunAVP_ReleasePort)GetProcAddress(m_hModAvp, "AVP_ReleasePort");
    mJNetRecClose = (pFunJNetRecClose)GetProcAddress(m_hModNet, "JNetRecClose");
    mAVP_CloseRecFile = (pFunAVP_CloseRecFile)GetProcAddress(m_hModAvp, "AVP_CloseRecFile");
   
} 

Api::~Api()
{
    if (m_hModAvp)
	{
        FreeLibrary(m_hModAvp);
        m_hModAvp = NULL;
	}
    if (m_hModNet)
    {
        FreeLibrary(m_hModNet);
        m_hModNet = NULL;
    }
}

