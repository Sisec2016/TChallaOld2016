#include "Api_XingWang.h"
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

Api_XingWang::Api_XingWang()
{
// 	char szCurDir[MAX_PATH];
// 	ZeroMemory(szCurDir, sizeof(szCurDir));
// 	GetCurrentDirectoryA(MAX_PATH, szCurDir);
// 	string strPath = GetExePath();
// 	strPath += "XingWang";
// 	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
// 	assert(bRet);
	m_hMod = LoadLibraryA(".\\DVRSDK.dll");
	m_hModPlay = LoadLibraryA(".\\snplaylib.dll");
// 	m_hModPlay = LoadLibraryA(".\\TLPlay.dll");
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

	m_pGetLastError = (pSN_DVR_GetLastError)GetProcAddress(m_hMod, "SN_DVR_GetLastError");
	assert(m_pGetLastError);
	m_pInit = (pSN_DVR_SDKInit)GetProcAddress(m_hMod, "SN_DVR_SDKInit");
	assert(m_pInit);
	m_pUninit = (pSN_DVR_SDKUninit)GetProcAddress(m_hMod, "SN_DVR_SDKUninit");
	assert(m_pUninit);
	m_pLogin = (pSN_DVR_UserLogon)GetProcAddress(m_hMod, "SN_DVR_UserLogon");
	assert(m_pLogin);
	m_pLogout = (pSN_DVR_UserLogoff)GetProcAddress(m_hMod, "SN_DVR_UserLogoff");
	assert(m_pLogout);
	m_pFindFile = (pSN_DVR_FindFirstFile)GetProcAddress(m_hMod, "SN_DVR_FindFirstFile");
	assert(m_pFindFile);
	m_pFindNext = (pSN_DVR_FindNextFile)GetProcAddress(m_hMod, "SN_DVR_FindNextFile");
	assert(m_pFindNext);
	m_pFindClose = (pSN_DVR_FindClose)GetProcAddress(m_hMod, "SN_DVR_FindClose");
	assert(m_pFindClose);
	m_pDownloadByFile = (pSN_DVR_DownloadFileByName)GetProcAddress(m_hMod, "SN_DVR_DownloadFileByName");
	assert(m_pDownloadByFile);
	m_pGetDownloadPos = (pSN_DVR_GetDownloadPos)GetProcAddress(m_hMod, "SN_DVR_GetDownloadPos");
	assert(m_pGetDownloadPos);
	m_pStopDownload = (pSN_DVR_StopDownloadFile)GetProcAddress(m_hMod, "SN_DVR_StopDownloadFile");
	assert(m_pStopDownload);
	m_pPlayBackByName = (pSN_DVR_PlayBackByFileName)GetProcAddress(m_hMod, "SN_DVR_PlayBackByFileName");
	assert(m_pPlayBackByName);
	m_pPlayBackControl = (pSN_DVR_PlayBackControl)GetProcAddress(m_hMod, "SN_DVR_PlayBackControl");
	assert(m_pPlayBackControl);
	m_pStopPlayBack = (pSN_DVR_StopPlayBack)GetProcAddress(m_hMod, "SN_DVR_StopPlayBack");
	assert(m_pStopPlayBack);


	m_pPlayInit = (pSnPlay_Init)GetProcAddress(m_hModPlay, "SnPlay_Init");
	assert(m_pPlayInit);
	m_pPlayGetPort = (pSnPlay_GetPort)GetProcAddress(m_hModPlay, "SnPlay_GetPort");
	assert(m_pPlayGetPort);
	m_pPlayFreePort = (pSnPlay_FreePort)GetProcAddress(m_hModPlay, "SnPlay_FreePort");
	assert(m_pPlayFreePort);
	m_pPlaySetMode = (pSnPlay_SetStreamOpenMode)GetProcAddress(m_hModPlay, "SnPlay_SetStreamOpenMode");
	assert(m_pPlaySetMode);
	m_pPlayPlay = (pSnPlay_Play)GetProcAddress(m_hModPlay, "SnPlay_Play");
	assert(m_pPlayPlay);
	m_pPlayStop = (pSnPlay_Stop)GetProcAddress(m_hModPlay, "SnPlay_Stop");
	assert(m_pPlayStop);
	m_pPlayInputV = (pSnPlay_InputData)GetProcAddress(m_hModPlay, "SnPlay_InputData");
	assert(m_pPlayInputV);


// 	m_pPlayGetPort = (pTLPlay_GetPort)GetProcAddress(m_hModPlay, "TLPlay_GetPort");
// 	assert(m_pPlayGetPort);
// 	m_pPlayFreePort = (pTLPlay_FreePort)GetProcAddress(m_hModPlay, "TLPlay_FreePort");
// 	assert(m_pPlayFreePort);
// 	m_pPlaySetMode = (pTLPlay_SetPlayMode)GetProcAddress(m_hModPlay, "TLPlay_SetPlayMode");
// 	assert(m_pPlaySetMode);
// 	m_pPlayOpenStream = (pTLPlay_OpenStream)GetProcAddress(m_hModPlay, "TLPlay_OpenStream");
// 	assert(m_pPlayOpenStream);
// 	m_pPlaySetDelay = (pTLPlay_SetDelayTime)GetProcAddress(m_hModPlay, "TLPlay_SetDelayTime");
// 	assert(m_pPlaySetDelay);
// 	m_pPlayClose = (pTLPlay_Close)GetProcAddress(m_hModPlay, "TLPlay_Close");
// 	assert(m_pPlayClose);
// 	m_pPlayPlay = (pTLPlay_Play)GetProcAddress(m_hModPlay, "TLPlay_Play");
// 	assert(m_pPlayPlay);
// 	m_pPlayStop = (pTLPlay_Stop)GetProcAddress(m_hModPlay, "TLPlay_Stop");
// 	assert(m_pPlayStop);
// 	m_pPlayInputV = (pTLPlay_InputVideoData)GetProcAddress(m_hModPlay, "TLPlay_InputVideoData");
// 	assert(m_pPlayInputV);
// 	m_pPlayInputA = (pTLPlay_InputAudioData)GetProcAddress(m_hModPlay, "TLPlay_InputAudioData");
// 	assert(m_pPlayInputA);
} 

Api_XingWang::~Api_XingWang()
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

void Api_XingWang::ReloadPlayLib()
{
	if (m_hModPlay)
	{
		FreeLibrary(m_hModPlay);
		m_hModPlay = NULL;
	}

	char szCurDir[MAX_PATH];
	ZeroMemory(szCurDir, sizeof(szCurDir));
	GetCurrentDirectoryA(MAX_PATH, szCurDir);
	string strPath = GetExePath();
	//strPath += "XingWang";
	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
	assert(bRet);

	m_hModPlay = LoadLibraryA(".\\snplaylib.dll");
	bRet = SetCurrentDirectoryA(szCurDir);
	if (m_hModPlay == NULL)
	{
		assert(m_hModPlay);
	}
}

Api_XingWang& Api_XingWang::Api()
{
	static SingletonHolder<Api_XingWang> sh;
	return *sh.get();
}

#ifdef RESET_NDEBUG
#define NDEBUG
#endif