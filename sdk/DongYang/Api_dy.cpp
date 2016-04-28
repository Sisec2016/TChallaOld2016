#include "Api_dy.h"
#include "Poco/SingletonHolder.h"
using Poco::SingletonHolder;
#include <assert.h>

Api_DY::Api_DY()
{
	m_hMod = LoadLibraryA(".\\client.dll");
	if (m_hMod == NULL)
	{
		assert(m_hMod);
		return;
	}
	m_pDyNetwork_ClientInit = (pDyNetwork_ClientInit)GetProcAddress(m_hMod, "Network_ClientInit");
	assert(m_pDyNetwork_ClientInit);
	m_pDyNetwork_ClientUnInit = (pDyNetwork_ClientUnInit)GetProcAddress(m_hMod, "Network_ClientUnInit");
	assert(m_pDyNetwork_ClientUnInit);
	m_pDyNetwork_ClientLogin = (pDyNetwork_ClientLogin)GetProcAddress(m_hMod, "Network_ClientLogin");
	assert(m_pDyNetwork_ClientLogin);
	m_pDyNetwork_ClientGetDeviceConfig = (pDyNetwork_ClientGetDeviceConfig)GetProcAddress(m_hMod, "Network_ClientGetDeviceConfig");
	assert(m_pDyNetwork_ClientGetDeviceConfig);
	m_pDyNetwork_ClientLogout = (pDyNetwork_ClientLogout)GetProcAddress(m_hMod, "Network_ClientLogout");
	assert(m_pDyNetwork_ClientLogout);
	m_pDyNetwork_ClientStartFileQuery = (pDyNetwork_ClientStartFileQuery)GetProcAddress(m_hMod, "Network_ClientStartFileQuery");
	assert(m_pDyNetwork_ClientStartFileQuery);
	m_pDyNetwork_ClientGetFileQueryResult = (pDyNetwork_ClientGetFileQueryResult)GetProcAddress(m_hMod, "Network_ClientGetFileQueryResult");
	assert(m_pDyNetwork_ClientGetFileQueryResult);
	m_pDyNetwork_ClientStopFileQuery = (pDyNetwork_ClientStopFileQuery)GetProcAddress(m_hMod, "Network_ClientStopFileQuery");
	assert(m_pDyNetwork_ClientStopFileQuery);
	m_pDyNetwork_ClientStartDownload = (pDyNetwork_ClientStartDownload)GetProcAddress(m_hMod, "Network_ClientStartDownload");
	assert(m_pDyNetwork_ClientStartDownload);
	m_pDyNetwork_ClientStartPlayback = (pDyNetwork_ClientStartPlayback)GetProcAddress(m_hMod, "Network_ClientStartPlayback");
	assert(m_pDyNetwork_ClientStartPlayback);
	m_pDyNetwork_ClientPlaybackControl = (pDyNetwork_ClientPlaybackControl)GetProcAddress(m_hMod, "Network_ClientPlaybackControl");
	assert(m_pDyNetwork_ClientPlaybackControl);
	m_pDyNetwork_ClientStopPlayback = (pDyNetwork_ClientStopPlayback)GetProcAddress(m_hMod, "Network_ClientStopPlayback");
	assert(m_pDyNetwork_ClientStopPlayback);
	m_pDyNetwork_ClientStopDownload = (pDyNetwork_ClientStopDownload)GetProcAddress(m_hMod, "Network_ClientStopDownload");
	assert(m_pDyNetwork_ClientStopDownload);
	m_pDyNetwork_ClientGetDownloadStatus = (pDyNetwork_ClientGetDownloadStatus)GetProcAddress(m_hMod, "Network_ClientGetDownloadStatus");
	assert(m_pDyNetwork_ClientGetDownloadStatus);
} 

Api_DY::~Api_DY()
{
	if (m_hMod)
	{
		FreeLibrary(m_hMod);
		m_hMod = NULL;
	}
}

Api_DY& Api_DY::Api()
{
	static SingletonHolder<Api_DY> sh;
	return *sh.get();
}