#include "Api_HanBang.h"
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

Api_HanBang::Api_HanBang()
{
// 	char szCurDir[MAX_PATH];
// 	ZeroMemory(szCurDir, sizeof(szCurDir));
// 	GetCurrentDirectoryA(MAX_PATH, szCurDir);
// 	string strPath = GetExePath();
// 	strPath += "HanBang";
// 	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
// 	assert(bRet);
	m_hMod = LoadLibraryA(".\\7000sdk.dll");
	if (m_hMod == NULL)
	{
// 		bRet = SetCurrentDirectoryA(szCurDir);
// 		assert(bRet);
		assert(m_hMod);
		return;
	}
// 	bRet = SetCurrentDirectoryA(szCurDir);
// 	assert(bRet);

	m_pGetLastError = (pHB_SDVR_GetLastError)GetProcAddress(m_hMod, "HB_SDVR_GetLastError");
	assert(m_pGetLastError);
	m_pInit = (pHB_SDVR_Init)GetProcAddress(m_hMod, "HB_SDVR_Init");
	assert(m_pInit);
	m_pUninit = (pHB_SDVR_Cleanup)GetProcAddress(m_hMod, "HB_SDVR_Cleanup");
	assert(m_pUninit);
	m_pLogin = (pHB_SDVR_Login_Ex_Nvs)GetProcAddress(m_hMod, "HB_SDVR_Login_Ex_Nvs");
	assert(m_pLogin);
	m_pLogout = (pHB_SDVR_Logout)GetProcAddress(m_hMod, "HB_SDVR_Logout");
	assert(m_pLogout);
	m_pGetConfig = (pHB_SDVR_GetDVRConfig)GetProcAddress(m_hMod, "HB_SDVR_GetDVRConfig");
	assert(m_pGetConfig);
	m_pFindFile = (pHB_SDVR_FindFile)GetProcAddress(m_hMod, "HB_SDVR_FindFile");
	assert(m_pFindFile);
	m_pFindNext = (pHB_SDVR_FindNextFile)GetProcAddress(m_hMod, "HB_SDVR_FindNextFile");
	assert(m_pFindNext);
	m_pFindClose = (pHB_SDVR_FindClose)GetProcAddress(m_hMod, "HB_SDVR_FindClose");
	assert(m_pFindClose);
	m_pDownloadByFile = (pHB_SDVR_GetFileByName)GetProcAddress(m_hMod, "HB_SDVR_GetFileByName");
	assert(m_pDownloadByFile);
	m_pGetDownloadTotal = (pHB_SDVR_GetDownloadTotalSize)GetProcAddress(m_hMod, "HB_SDVR_GetDownloadTotalSize");
	assert(m_pGetDownloadTotal);
	m_pGetDownloadPos = (pHB_SDVR_GetDownloadPos)GetProcAddress(m_hMod, "HB_SDVR_GetDownloadPos");
	assert(m_pGetDownloadPos);
	m_pStopDownload = (pHB_SDVR_StopGetFile)GetProcAddress(m_hMod, "HB_SDVR_StopGetFile");
	assert(m_pStopDownload);
	m_pPlayBackByName = (pHB_SDVR_PlayBackByName)GetProcAddress(m_hMod, "HB_SDVR_PlayBackByName");
	assert(m_pPlayBackByName);
	m_pPlayBackByTime = (pHB_SDVR_PlayBackByTime)GetProcAddress(m_hMod, "HB_SDVR_PlayBackByTime");
	assert(m_pPlayBackByTime);
	m_pPlayBackByTimeEx = (pHB_SDVR_PlayBackByTimeWithChl_ex)GetProcAddress(m_hMod, "HB_SDVR_PlayBackByTimeWithChl_ex");
	assert(m_pPlayBackByTimeEx);
	m_pPlayBackControl = (pHB_SDVR_PlayBackControl)GetProcAddress(m_hMod, "HB_SDVR_PlayBackControl");
	assert(m_pPlayBackControl);
	m_pStopPlayBack = (pHB_SDVR_StopPlayBack)GetProcAddress(m_hMod, "HB_SDVR_StopPlayBack");
	assert(m_pStopPlayBack);

	m_pGetDownloadBytesSize = (pHB_SDVR_GetDownloadBytesSize)GetProcAddress(m_hMod, "HB_SDVR_GetDownloadBytesSize");
	assert(m_pGetDownloadBytesSize);
	
	//<<<<<<<<<<<<<<<<<<add by zhangyaofa 2016/6/8
	m_pDownloadByTime = (pHB_SDVR_GetFileByTime)GetProcAddress(m_hMod, "HB_SDVR_GetFileByTime");
	assert(m_pDownloadByTime);
	//>>>>>>>>>>>>>>>>>>add end
} 

Api_HanBang::~Api_HanBang()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_HanBang& Api_HanBang::Api()
{
	static SingletonHolder<Api_HanBang> sh;
	return *sh.get();
}