#include "Api_DiZhiPu.h"
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

Api_DiZhiPu::Api_DiZhiPu()
{
//	char szCurDir[MAX_PATH];
//	ZeroMemory(szCurDir, sizeof(szCurDir));
//	GetCurrentDirectoryA(MAX_PATH, szCurDir);
//	string strPath = GetExePath();
//	strPath += "DiZhiPu";
//	BOOL bRet = SetCurrentDirectoryA(strPath.c_str());
//	assert(bRet);
	m_hMod = LoadLibraryA(".\\netsdk.dll");
	if (m_hMod == NULL)
	{
//		bRet = SetCurrentDirectoryA(szCurDir);
//		assert(bRet);
		assert(m_hMod);
		return;
	}
//	bRet = SetCurrentDirectoryA(szCurDir);
//	assert(bRet);

	m_pGetLastError = (pH264_DVR_GetLastError)GetProcAddress(m_hMod, "H264_DVR_GetLastError");
	assert(m_pGetLastError);
	m_pGetConfig = (pH264_DVR_GetDevConfig)GetProcAddress(m_hMod, "H264_DVR_GetDevConfig");
	assert(m_pGetConfig);
	m_pInit = (pH264_DVR_Init)GetProcAddress(m_hMod, "H264_DVR_Init");
	assert(m_pInit);
	m_pUninit = (pH264_DVR_Cleanup)GetProcAddress(m_hMod, "H264_DVR_Cleanup");
	assert(m_pUninit);
	m_pLogin = (pH264_DVR_Login)GetProcAddress(m_hMod, "H264_DVR_Login");
	assert(m_pLogin);
	m_pLogout = (pH264_DVR_Logout)GetProcAddress(m_hMod, "H264_DVR_Logout");
	assert(m_pLogout);
	m_pSearchFileByTime = (pH264_DVR_FindFile)GetProcAddress(m_hMod, "H264_DVR_FindFile");
	assert(m_pSearchFileByTime);
	m_pDownloadByFile = (pH264_DVR_GetFileByName)GetProcAddress(m_hMod, "H264_DVR_GetFileByName");
	assert(m_pDownloadByFile);
	m_pDownloadByTime = (pH264_DVR_GetFileByTime)GetProcAddress(m_hMod, "H264_DVR_GetFileByTime");
	assert(m_pDownloadByTime);
	m_pGetDownloadPos = (pH264_DVR_GetDownloadPos)GetProcAddress(m_hMod, "H264_DVR_GetDownloadPos");
	assert(m_pGetDownloadPos);
	m_pStopDownload = (pH264_DVR_StopGetFile)GetProcAddress(m_hMod, "H264_DVR_StopGetFile");
	assert(m_pStopDownload);
	m_pPlayBackByFile = (pH264_DVR_PlayBackByName)GetProcAddress(m_hMod, "H264_DVR_PlayBackByName");
	assert(m_pPlayBackByFile);
	m_pPlayBackControl = (pH264_DVR_PlayBackControl)GetProcAddress(m_hMod, "H264_DVR_PlayBackControl");
	assert(m_pPlayBackControl);
	m_pStopPlayBack = (pH264_DVR_StopPlayBack)GetProcAddress(m_hMod, "H264_DVR_StopPlayBack");
	assert(m_pStopPlayBack);
} 

Api_DiZhiPu::~Api_DiZhiPu()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_DiZhiPu& Api_DiZhiPu::Api()
{
	static SingletonHolder<Api_DiZhiPu> sh;
	return *sh.get();
}

#ifdef RESET_NDEBUG
#define NDEBUG
#endif