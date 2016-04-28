#include "Api_JunMingShi.h"
#include "Poco/SingletonHolder.h"
using Poco::SingletonHolder;
#include <assert.h>
#include <string>
using namespace std;
#ifdef NDEBUG
#undef NDEBUG
#define RESET_NDEBUG
#endif // NDEBUG

static string GetExePath()
{
	char szPath[MAX_PATH];
	ZeroMemory(szPath, sizeof(szPath));
	HMODULE hIns = GetModuleHandle(NULL);
	assert(hIns);
	GetModuleFileNameA(hIns, szPath, MAX_PATH);
	string strPath = szPath;
	int iIndex = strPath.rfind('\\');
	if (iIndex != string::npos)
	{
		strPath = strPath.substr(0, iIndex+1);
	}
	return strPath;
}

Api_JunMingShi::Api_JunMingShi()
{
// 	char szCurDir[MAX_PATH];
// 	ZeroMemory(szCurDir, sizeof(szCurDir));
// 	GetCurrentDirectoryA(MAX_PATH, szCurDir);
// 	string strPath = GetExePath();
// 	strPath += "JunMingShi";
// 	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
// 	assert(bRet);
	m_hMod = LoadLibraryA(".\\NetDvr2.dll");
	m_hModPlay = LoadLibraryA(".\\TLPlay.dll");
	if (m_hMod == NULL || m_hModPlay == NULL)
	{
// 		bRet = SetCurrentDirectoryA(szCurDir);
// 		assert(bRet);
		assert(m_hMod);
		assert(m_hModPlay);
		return;
	}
// 	bRet = SetCurrentDirectoryA(szCurDir);
// 	assert(bRet);

	m_pInit = (pNETDVR_startup)GetProcAddress(m_hMod, "NETDVR_startup");
	assert(m_pInit);
	m_pUninit = (pNETDVR_cleanup)GetProcAddress(m_hMod, "NETDVR_cleanup");
	assert(m_pUninit);
	m_pCreateDvr = (pNETDVR_createDVR)GetProcAddress(m_hMod, "NETDVR_createDVR");
	assert(m_pCreateDvr);
	m_pDestroyDvr = (pNETDVR_destroyDVR)GetProcAddress(m_hMod, "NETDVR_destroyDVR");
	assert(m_pDestroyDvr);
	m_pLogin = (pNETDVR_loginServer)GetProcAddress(m_hMod, "NETDVR_loginServer");
	assert(m_pLogin);
	m_pLogout = (pNETDVR_logoutServer)GetProcAddress(m_hMod, "NETDVR_logoutServer");
	assert(m_pLogout);
	m_pGetDeviceInfo = (pNETDVR_GetDeviceInfo)GetProcAddress(m_hMod, "NETDVR_GetDeviceInfo");
	assert(m_pGetDeviceInfo);
	m_pSearchFileByTime = (pNETDVR_recFilesSearch)GetProcAddress(m_hMod, "NETDVR_recFilesSearch");
	assert(m_pSearchFileByTime);
	m_pSearchFileByTimeClean = (pNETDVR_recFilesSearchClean)GetProcAddress(m_hMod, "NETDVR_recFilesSearchClean");
	assert(m_pSearchFileByTimeClean);
	m_pSetDownPosCallback = (pNETDVR_regCBFileRecieverProgress)GetProcAddress(m_hMod, "NETDVR_regCBFileRecieverProgress");
	assert(m_pSetDownPosCallback);
	m_pSetDownErrCallback = (pNETDVR_regCBFileRecieverError)GetProcAddress(m_hMod, "NETDVR_regCBFileRecieverError");
	assert(m_pSetDownErrCallback);
	m_pDownloadByFile = (pNETDVR_startFileDownload)GetProcAddress(m_hMod, "NETDVR_startFileDownload");
	assert(m_pDownloadByFile);
	m_pSetCb = (pNETDVR_regCBFileRecieverProgress)GetProcAddress(m_hMod, "NETDVR_regCBFileRecieverProgress");
	assert(m_pSetCb);
	m_pStopDownload = (pNETDVR_stopFileDownload)GetProcAddress(m_hMod, "NETDVR_stopFileDownload");
	assert(m_pStopDownload);
	m_pPlayBackByFile = (pNETDVR_startPlayByFile)GetProcAddress(m_hMod, "NETDVR_startPlayByFile");
	assert(m_pPlayBackByFile);
	m_pSeekPlayBack = (pNETDVR_playSeek)GetProcAddress(m_hMod, "NETDVR_playSeek");
	assert(m_pSeekPlayBack);
	m_pPausePlayBack = (pNETDVR_pausePlay)GetProcAddress(m_hMod, "NETDVR_pausePlay");
	assert(m_pPausePlayBack);
	m_pStopPlayBack = (pNETDVR_stopPlayBack)GetProcAddress(m_hMod, "NETDVR_stopPlayBack");
	assert(m_pStopPlayBack);


	m_pPlayGetPort = (pTLPlay_GetPort)GetProcAddress(m_hModPlay, "TLPlay_GetPort");
	assert(m_pPlayGetPort);
	m_pPlayFreePort = (pTLPlay_FreePort)GetProcAddress(m_hModPlay, "TLPlay_FreePort");
	assert(m_pPlayFreePort);
	m_pPlaySetMode = (pTLPlay_SetPlayMode)GetProcAddress(m_hModPlay, "TLPlay_SetPlayMode");
	assert(m_pPlaySetMode);
	m_pPlayOpenStream = (pTLPlay_OpenStream)GetProcAddress(m_hModPlay, "TLPlay_OpenStream");
	assert(m_pPlayOpenStream);
	m_pPlaySetDelay = (pTLPlay_SetDelayTime)GetProcAddress(m_hModPlay, "TLPlay_SetDelayTime");
	assert(m_pPlaySetDelay);
	m_pPlayClose = (pTLPlay_Close)GetProcAddress(m_hModPlay, "TLPlay_Close");
	assert(m_pPlayClose);
	m_pPlayPlay = (pTLPlay_Play)GetProcAddress(m_hModPlay, "TLPlay_Play");
	assert(m_pPlayPlay);
	m_pPlayStop = (pTLPlay_Stop)GetProcAddress(m_hModPlay, "TLPlay_Stop");
	assert(m_pPlayStop);
	m_pPlayInputV = (pTLPlay_InputVideoData)GetProcAddress(m_hModPlay, "TLPlay_InputVideoData");
	assert(m_pPlayInputV);
	m_pPlayInputA = (pTLPlay_InputAudioData)GetProcAddress(m_hModPlay, "TLPlay_InputAudioData");
	assert(m_pPlayInputA);
} 

Api_JunMingShi::~Api_JunMingShi()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
	if (m_hModPlay)
	{
		FreeLibrary(m_hModPlay);
		m_hModPlay = NULL;
	}
}

Api_JunMingShi& Api_JunMingShi::Api()
{
	static SingletonHolder<Api_JunMingShi> sh;
	return *sh.get();
}

#ifdef RESET_NDEBUG
#define NDEBUG
#endif