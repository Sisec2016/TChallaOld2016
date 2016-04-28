#include "Api_DLDM.h"
#include "Poco/SingletonHolder.h"
using Poco::SingletonHolder;
#include <assert.h>
#include <string>
using namespace std;

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

Api_DaLi_DM::Api_DaLi_DM()
{
// 	char szCurDir[MAX_PATH];
// 	ZeroMemory(szCurDir, sizeof(szCurDir));
// 	GetCurrentDirectoryA(MAX_PATH, szCurDir);
// 	string strPath = GetExePath();
// 	strPath += "DaLi_DM";
// 	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
// 	assert(bRet);
	m_hMod = LoadLibraryA(".\\NetSDK.dll");
	if (m_hMod == NULL)
	{
// 		bRet = SetCurrentDirectoryA(szCurDir);
// 		assert(bRet);
		assert(m_hMod);
		return;
	}
// 	bRet = SetCurrentDirectoryA(szCurDir);
// 	assert(bRet);

	m_pGetLastError = (pNET_DLDVR_GetLastError)GetProcAddress(m_hMod, "NET_DLDVR_GetLastError");
	assert(m_pGetLastError);
	m_pInit = (pNET_DLDVR_Init)GetProcAddress(m_hMod, "NET_DLDVR_Init");
	assert(m_pInit);
	m_pUninit = (pNET_DLDVR_Cleanup)GetProcAddress(m_hMod, "NET_DLDVR_Cleanup");
	assert(m_pUninit);
	m_pLogin = (pNET_DLDVR_Login)GetProcAddress(m_hMod, "NET_DLDVR_Login");
	assert(m_pLogin);
	m_pLogout = (pNET_DLDVR_Logout)GetProcAddress(m_hMod, "NET_DLDVR_Logout");
	assert(m_pLogout);
	m_pHeartBeat = (pNET_DLDVR_OnlineHearBeat)GetProcAddress(m_hMod, "NET_DLDVR_OnlineHearBeat");
	assert(m_pHeartBeat);
	m_pGetConfig = (pNET_DLDVR_GetDVRConfig)GetProcAddress(m_hMod, "NET_DLDVR_GetDVRConfig");
	assert(m_pGetConfig);
	m_pFindFile = (pNET_DLDVR_FindFile)GetProcAddress(m_hMod, "NET_DLDVR_FindFile");
	assert(m_pFindFile);
	m_pFindNext = (pNET_DLDVR_FindNextFile)GetProcAddress(m_hMod, "NET_DLDVR_FindNextFile");
	assert(m_pFindNext);
	m_pFindClose = (pNET_DLDVR_FindClose)GetProcAddress(m_hMod, "NET_DLDVR_FindClose");
	assert(m_pFindClose);
	m_pDownloadByFile = (pNET_DLDVR_GetFileByName)GetProcAddress(m_hMod, "NET_DLDVR_GetFileByName");
	assert(m_pDownloadByFile);
	m_pGetDownloadPos = (pNET_DLDVR_GetDownloadPos)GetProcAddress(m_hMod, "NET_DLDVR_GetDownloadPos");
	assert(m_pGetDownloadPos);
	m_pStopDownload = (pNET_DLDVR_StopGetFile)GetProcAddress(m_hMod, "NET_DLDVR_StopGetFile");
	assert(m_pStopDownload);
	m_pPlayBackByName = (pNET_DLDVR_PlayBackByName)GetProcAddress(m_hMod, "NET_DLDVR_PlayBackByName");
	assert(m_pPlayBackByName);
	m_pPlayBackByTime = (pNET_DLDVR_PlayBackByTime)GetProcAddress(m_hMod, "NET_DLDVR_PlayBackByTime");
	assert(m_pPlayBackByTime);
	m_pPlayBackControl = (pNET_DLDVR_PlayBackControl)GetProcAddress(m_hMod, "NET_DLDVR_PlayBackControl");
	assert(m_pPlayBackControl);
	m_pStopPlayBack = (pNET_DLDVR_StopPlayBack)GetProcAddress(m_hMod, "NET_DLDVR_StopPlayBack");
	assert(m_pStopPlayBack);
} 

Api_DaLi_DM::~Api_DaLi_DM()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_DaLi_DM& Api_DaLi_DM::Api()
{
	static SingletonHolder<Api_DaLi_DM> sh;
	return *sh.get();
}