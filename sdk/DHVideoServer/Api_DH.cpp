#include "Api_DH.h"
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

Api_DH::Api_DH()
{
// 	char szCurDir[MAX_PATH];
// 	ZeroMemory(szCurDir, sizeof(szCurDir));
// 	GetCurrentDirectoryA(MAX_PATH, szCurDir);
// 	string strPath = GetExePath();
// 	strPath += "DH";
// 	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
// 	assert(bRet);
	m_hMod = LoadLibraryA(".\\dhnetsdk.dll");
	if (m_hMod == NULL)
	{
// 		bRet = SetCurrentDirectoryA(szCurDir);
// 		assert(bRet);
		assert(m_hMod);
		return;
	}
// 	bRet = SetCurrentDirectoryA(szCurDir);
// 	assert(bRet);

	m_pGetLastError = (pCLIENT_GetLastError)GetProcAddress(m_hMod, "CLIENT_GetLastError");
	assert(m_pGetLastError);
	m_pGetChannel = (pCLIENT_QueryChannelName)GetProcAddress(m_hMod, "CLIENT_QueryChannelName");
	assert(m_pGetChannel);
	m_pInit = (pCLIENT_Init)GetProcAddress(m_hMod, "CLIENT_Init");
	assert(m_pInit);
	m_pUninit = (pCLIENT_Cleanup)GetProcAddress(m_hMod, "CLIENT_Cleanup");
	assert(m_pUninit);
	m_pLogin = (pCLIENT_Login)GetProcAddress(m_hMod, "CLIENT_Login");
	assert(m_pLogin);
	m_pLogout = (pCLIENT_Logout)GetProcAddress(m_hMod, "CLIENT_Logout");
	assert(m_pLogout);
	m_pSearchFileByTime = (pCLIENT_QueryRecordFile)GetProcAddress(m_hMod, "CLIENT_QueryRecordFile");
	assert(m_pSearchFileByTime);
	m_pDownloadByFile = (pCLIENT_DownloadByRecordFile)GetProcAddress(m_hMod, "CLIENT_DownloadByRecordFile");
	assert(m_pDownloadByFile);
	m_pDownloadByTime = (pCLIENT_DownloadByTime)GetProcAddress(m_hMod, "CLIENT_DownloadByTime");
	assert(m_pDownloadByTime);
	m_pGetDownloadPos = (pCLIENT_GetDownloadPos)GetProcAddress(m_hMod, "CLIENT_GetDownloadPos");
	assert(m_pGetDownloadPos);
	m_pStopDownload = (pCLIENT_StopDownload)GetProcAddress(m_hMod, "CLIENT_StopDownload");
	assert(m_pStopDownload);
	m_pPlayBackByFile = (pCLIENT_PlayBackByRecordFile)GetProcAddress(m_hMod, "CLIENT_PlayBackByRecordFile");
	assert(m_pPlayBackByFile);
	m_pSeekPlayBack = (pCLIENT_SeekPlayBack)GetProcAddress(m_hMod, "CLIENT_SeekPlayBack");
	assert(m_pSeekPlayBack);
	m_pPausePlayBack = (pCLIENT_PausePlayBack)GetProcAddress(m_hMod, "CLIENT_PausePlayBack");
	assert(m_pPausePlayBack);
	m_pStopPlayBack = (pCLIENT_StopPlayBack)GetProcAddress(m_hMod, "CLIENT_StopPlayBack");
	assert(m_pStopPlayBack);

    m_pSearchDevices = (pCLIENT_SearchDevices)GetProcAddress(m_hMod, "CLIENT_SearchDevices");
    assert(m_pSearchDevices);

	//<<<<<<<<<<<<<<<add by zhangyaofa 2016/6/15
	m_pQueryDevState = (pCLIENT_QueryDevState)GetProcAddress(m_hMod, "CLIENT_QueryDevState");
	assert(m_pQueryDevState);
	//>>>>>>>>>>>>>>>add end
} 

Api_DH::~Api_DH()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_DH& Api_DH::Api()
{
	static SingletonHolder<Api_DH> sh;
	return *sh.get();
}