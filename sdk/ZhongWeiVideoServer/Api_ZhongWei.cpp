#include "Api_ZhongWei.h"
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

Api_ZhongWei::Api_ZhongWei()
{
	m_hMod = LoadLibraryA(".\\JCSDK.dll");
	if (m_hMod == NULL)
	{
		return;
	}

	m_pSetCallback = (pJCSDK_RegisterCallback)GetProcAddress(m_hMod, "JCSDK_RegisterCallback");
	assert(m_pSetCallback);
	m_pInit = (pJCSDK_InitSDK)GetProcAddress(m_hMod, "JCSDK_InitSDK");
	assert(m_pInit);
	m_pUninit = (pJCSDK_ReleaseSDK)GetProcAddress(m_hMod, "JCSDK_ReleaseSDK");
	assert(m_pUninit);
	m_pLogin = (pJCSDK_Connect)GetProcAddress(m_hMod, "JCSDK_Connect");
	assert(m_pLogin);
	m_pEnableDecoder = (pJCSDK_EnableDecoder)GetProcAddress(m_hMod, "JCSDK_EnableDecoder");
	assert(m_pEnableDecoder);
	m_pSetVPreview = (pJCSDK_SetVideoPreview)GetProcAddress(m_hMod, "JCSDK_SetVideoPreview");
	assert(m_pSetVPreview);
	m_pLogout = (pJCSDK_Disconnect)GetProcAddress(m_hMod, "JCSDK_Disconnect");
	assert(m_pLogout);
	m_pSearchFileByTime = (pJCSDK_GetRemoteRecFileList)GetProcAddress(m_hMod, "JCSDK_GetRemoteRecFileList");
	assert(m_pSearchFileByTime);
	m_pDownloadByFile = (pJCSDK_DownloadRemoteFile)GetProcAddress(m_hMod, "JCSDK_DownloadRemoteFile");
	assert(m_pDownloadByFile);
	m_pPlayBackByFile = (pJCSDK_RemotePlay)GetProcAddress(m_hMod, "JCSDK_RemotePlay");
	assert(m_pPlayBackByFile);
	m_pPlayBackControl = (pJCSDK_RemotePlayControl)GetProcAddress(m_hMod, "JCSDK_RemotePlayControl");
	assert(m_pPlayBackControl);
} 

Api_ZhongWei::~Api_ZhongWei()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_ZhongWei& Api_ZhongWei::Api()
{
	static SingletonHolder<Api_ZhongWei> sh;
	return *sh.get();
}