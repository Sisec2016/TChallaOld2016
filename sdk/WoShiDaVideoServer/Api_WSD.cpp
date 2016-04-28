#include "Api_WSD.h"
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
Api_WSD::Api_WSD()
{
	char szCurDir[MAX_PATH];
	ZeroMemory(szCurDir, sizeof(szCurDir));
	GetCurrentDirectoryA(MAX_PATH, szCurDir);
	string strPath = GetExePath();
	strPath += "WoShiDa";
	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
	assert(bRet);
	m_hMod = LoadLibraryA(".\\zlnetsdk.dll");
	if (m_hMod == NULL)
	{
		bRet = SetCurrentDirectoryA(szCurDir);
		assert(bRet);
		assert(m_hMod);
		return;
	}
	bRet = SetCurrentDirectoryA(szCurDir);
	assert(bRet);
	ZLNET_GetLastError = (pZLNET_GetLastError)GetProcAddress(m_hMod, "ZLNET_GetLastError");
	assert(ZLNET_GetLastError);
	ZLNET_GetDevConfig = (pZLNET_GetDevConfig)GetProcAddress(m_hMod, "ZLNET_GetDevConfig");
	assert(ZLNET_GetDevConfig);
	ZLNET_Init = (pZLNET_Init)GetProcAddress(m_hMod, "ZLNET_Init");
	assert(ZLNET_Init);
	ZLNET_Cleanup = (pZLNET_Cleanup)GetProcAddress(m_hMod, "ZLNET_Cleanup");
	assert(ZLNET_Cleanup);
	ZLNET_Login = (pZLNET_Login)GetProcAddress(m_hMod, "ZLNET_Login");
	assert(ZLNET_Login);
	ZLNET_Logout = (pZLNET_Logout)GetProcAddress(m_hMod, "ZLNET_Logout");
	assert(ZLNET_Logout);
	ZLNET_QueryRecordFile = (pZLNET_QueryRecordFile)GetProcAddress(m_hMod, "ZLNET_QueryRecordFile");
	assert(ZLNET_QueryRecordFile);
	ZLNET_DownloadByRecordFile = (pZLNET_DownloadByRecordFile)GetProcAddress(m_hMod, "ZLNET_DownloadByRecordFile");
	assert(ZLNET_DownloadByRecordFile);
	ZLNET_DownloadByTime = (pZLNET_DownloadByTime)GetProcAddress(m_hMod, "ZLNET_DownloadByTime");
	assert(ZLNET_DownloadByTime);
	ZLNET_GetDownloadPos = (pZLNET_GetDownloadPos)GetProcAddress(m_hMod, "ZLNET_GetDownloadPos");
	assert(ZLNET_GetDownloadPos);
	ZLNET_StopDownload = (pZLNET_StopDownload)GetProcAddress(m_hMod, "ZLNET_StopDownload");
	assert(ZLNET_StopDownload);
	ZLNET_PlayBackByRecordFile = (pZLNET_PlayBackByRecordFile)GetProcAddress(m_hMod, "ZLNET_PlayBackByRecordFile");
	assert(ZLNET_PlayBackByRecordFile);
	ZLNET_StopPlayBack = (pZLNET_StopPlayBack)GetProcAddress(m_hMod, "ZLNET_StopPlayBack");
	assert(ZLNET_StopPlayBack);

	ZLNET_FindFile = (pZLNET_FindFile)GetProcAddress(m_hMod, "ZLNET_FindFile");
	assert(ZLNET_FindFile);

	ZLNET_FindNextFile = (pZLNET_FindNextFile)GetProcAddress(m_hMod, "ZLNET_FindNextFile");
	assert(ZLNET_FindNextFile);
	
	ZLNET_FindClose = (pZLNET_FindClose)GetProcAddress(m_hMod, "ZLNET_FindClose");
	assert(ZLNET_FindClose);
} 

Api_WSD::~Api_WSD()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_WSD& Api_WSD::Api()
{
	static SingletonHolder<Api_WSD> sh;
	return *sh.get();
}