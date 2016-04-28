#include "Api_HangJing.h"
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

Api_HangJing::Api_HangJing()
{
// 	char szCurDir[MAX_PATH];
// 	ZeroMemory(szCurDir, sizeof(szCurDir));
// 	GetCurrentDirectoryA(MAX_PATH, szCurDir);
// 	string strPath = GetExePath();
// 	strPath += "HangJing";
// 	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
// 	assert(bRet);
	m_hMod = LoadLibraryA(".\\LvrNetSdk.dll");
	if (m_hMod == NULL)
	{
// 		bRet = SetCurrentDirectoryA(szCurDir);
// 		assert(bRet);
		assert(m_hMod);
		return;
	}
// 	bRet = SetCurrentDirectoryA(szCurDir);
// 	assert(bRet);

	m_pGetLastError = (pLvrNetGetLastError)GetProcAddress(m_hMod, "LvrNetGetLastError");
	assert(m_pGetLastError);
	m_pInit = (pLvrNetStartup)GetProcAddress(m_hMod, "LvrNetStartup");
	assert(m_pInit);
	m_pUninit = (pLvrNetCleanup)GetProcAddress(m_hMod, "LvrNetCleanup");
	assert(m_pUninit);
	m_pLogin = (pLvrNetLogin)GetProcAddress(m_hMod, "LvrNetLogin");
	assert(m_pLogin);
	m_pLogout = (pLvrNetLogout)GetProcAddress(m_hMod, "LvrNetLogout");
	assert(m_pLogout);
	m_pGetConfig = (pLvrNetGetConfig)GetProcAddress(m_hMod, "LvrNetGetConfig");
	assert(m_pGetConfig);
	m_pFindFile = (pLvrNetFindFile)GetProcAddress(m_hMod, "LvrNetFindFile");
	assert(m_pFindFile);
	m_pFindNext = (pLvrNetFindNextFile)GetProcAddress(m_hMod, "LvrNetFindNextFile");
	assert(m_pFindNext);
	m_pFindClose = (pLvrNetFindFileClose)GetProcAddress(m_hMod, "LvrNetFindFileClose");
	assert(m_pFindClose);
	m_pDownloadByFile = (pLvrNetGetFileByName)GetProcAddress(m_hMod, "LvrNetGetFileByName");
	assert(m_pDownloadByFile);
	m_pGetDownloadPos = (pLvrNetGetFilePos)GetProcAddress(m_hMod, "LvrNetGetFilePos");
	assert(m_pGetDownloadPos);
	m_pStopDownload = (pLvrNetStopGetFile)GetProcAddress(m_hMod, "LvrNetStopGetFile");
	assert(m_pStopDownload);
	m_pPlayBackByName = (pLvrNetPlayByFile)GetProcAddress(m_hMod, "LvrNetPlayByFile");
	assert(m_pPlayBackByName);
	m_pPlayBackControl = (pLvrNetPlayControl)GetProcAddress(m_hMod, "LvrNetPlayControl");
	assert(m_pPlayBackControl);
	m_pStopPlayBack = (pLvrNetPlayClose)GetProcAddress(m_hMod, "LvrNetPlayClose");
	assert(m_pStopPlayBack);
} 

Api_HangJing::~Api_HangJing()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_HangJing& Api_HangJing::Api()
{
	static SingletonHolder<Api_HangJing> sh;
	return *sh.get();
}

#ifdef RESET_NDEBUG
#define NDEBUG
#endif