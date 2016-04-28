#include "HangJing_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
Log g_log("HangJing_videoserver");
#include "LvrPlaySdk.h"
#pragma comment(lib, "LvrPlaySdk.lib")

// #pragma comment(lib, "HCNetSDK.lib")

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryHangJing();
}

std::string GetLastErrorString()
{
    DWORD dwErr;
	dwErr = LvrNetGetLastError();

    return "未知错误";
}



CFactoryHangJing::CFactoryHangJing()
{
    init();
}

CFactoryHangJing::~CFactoryHangJing()
{
    clean();
}






bool CFactoryHangJing::init()
{
    if (!m_init)
    {

		m_init = LvrNetStartup();
        //HB_SDVR_SetConnectTime(1000, 30);
        //HB_SDVR_SetReconnect(3000);
        //HB_SDVR_SetDVRMessage()
        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
			return false;
        }

		g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


void CFactoryHangJing::clean()
{
	LvrNetCleanup();
}




IVideoServer* CFactoryHangJing::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new HangJing_videoserver();
}


// std::vector<HangJing_videoserver*> HangJing_videoserver::sServers;
// std::recursive_mutex HangJing_videoserver::sMtServers;

/*
 * 析构函数
 */
HangJing_videoserver::HangJing_videoserver()
{
//     std::lock_guard<std::recursive_mutex> lock(HangJing_videoserver::sMtServers);
//     sServers.push_back(this);
}

HangJing_videoserver::~HangJing_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(HangJing_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

IVideoServer* HangJing_videoserver::clone()
{
//     HangJing_videoserver *svr = new HangJing_videoserver();
// 	memcpy(svr, this, sizeof(HangJing_videoserver));
//     return svr;
	return NULL;
}

void CALLBACK DataCallBack(LONG lvrHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwDataLen, DWORD dwTimeStamp, DWORD dwDataFlags, DWORD dwUser)
{
	HangJing_videoserver *pThis = (HangJing_videoserver *)dwUser;
	if (!pThis || pThis->m_lStreamHandle == -1)
	{
		return;
	}
	if (!LvrNetStreamDataInput(pThis->m_lStreamHandle, pBuffer, dwDataLen, dwTimeStamp, dwDataFlags))
	{
		g_log.AddLog(string("数据流投递失败"));
	}
}

bool HangJing_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels)
{
//     if (0 > m_lLoginHandle && !logout())
//     {
//         return false;
//     }
	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

	m_lLoginHandle = LvrNetLogin((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d ip:%s port:%d user:%s psw:%s", m_lLoginHandle, IP, port, user, password);
	g_log.AddLog(string(szLog));

    if (m_lLoginHandle < 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

	for (int i = 0; i < m_deviceInfo.byChannelsNum; i++)
    {
		char szName[16];
		ZeroMemory(szName, sizeof(szName));
		sprintf(szName, "通道%d", i + 1);
		channels[1 + i] = std::string(szName);
    }

	ZeroMemory(szLog, 1024);
	sprintf(szLog, "login 通道个数:%d", m_deviceInfo.byChannelsNum);
	g_log.AddLog(string(szLog));
    return true;
}

bool HangJing_videoserver::logout()
{
	if (m_lLoginHandle >= 0 && !LvrNetLogout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}




bool HangJing_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
	g_log.AddLog(string("GetRecordFileList"));
    if (m_lLoginHandle <= 0)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("GetRecordFileList 请先登录"));
        return false;
    }

    if (timeStart >= timeEnd)
    {
        m_sLastError = "时间范围不对!";
		g_log.AddLog(string("GetRecordFileList 时间范围不对"));
        return false;
    }

	files.clear();
	//m_mapArcItem.clear();

	auto itr = channelVec.begin();
	for (; itr != channelVec.end(); itr++)
	{
		int nChannelId = *itr;

		struct tm Tm;

		LVR_NET_TIME startTime;
		_localtime64_s(&Tm, (const time_t*)&timeStart);
		startTime.woYear = Tm.tm_year + 1900;
		startTime.byMonth = Tm.tm_mon + 1;
		startTime.byDay = Tm.tm_mday;
		startTime.byHour = Tm.tm_hour;
		startTime.byMinute = Tm.tm_min;
		startTime.bySecond = Tm.tm_sec;

		LVR_NET_TIME stopTime;
		_localtime64_s(&Tm, (const time_t*)&timeEnd);
		stopTime.woYear = Tm.tm_year + 1900;
		stopTime.byMonth = Tm.tm_mon + 1;
		stopTime.byDay = Tm.tm_mday;
		stopTime.byHour = Tm.tm_hour;
		stopTime.byMinute = Tm.tm_min;
		stopTime.bySecond = Tm.tm_sec;

		LVR_NET_TIME stime = startTime;
		LVR_NET_TIME etime = stopTime;

// 		char szTime[512];
// 		ZeroMemory(szTime, 512);
// 		sprintf(szTime, " s_time:%d-%02d-%02d %02d:%02d:%02d e_time:%d-%02d-%02d %02d:%02d:%02d channel:%d linkID:%d", stime.woYear, stime.byMonth, stime.byDay,
// 			stime.byHour, stime.byMinute, stime.bySecond,
// 			etime.woYear, etime.byMonth, etime.byDay, etime.byHour, etime.byMinute, etime.bySecond, nChannelId, m_lLoginHandle);
// 		g_log.AddLog(string("GetRecordFileList ") + string(szTime));

		LONG lfind = LvrNetFindFile(m_lLoginHandle, nChannelId - 1, LVR_NET_ALL_FILE, false, &startTime, &stopTime);

		if (lfind == FALSE)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
		LVR_NET_FILE findInfo;
		ZeroMemory(&findInfo, sizeof(findInfo));
		int iFinds = 0;

		RecordFile rf;
		while (LvrNetFindNextFile(lfind, &findInfo))
		{
			struct tm Tm;
			Tm.tm_year = findInfo.startTime.woYear - 1900;
			Tm.tm_mon = findInfo.startTime.byMonth - 1;
			Tm.tm_mday = findInfo.startTime.byDay;
			Tm.tm_hour = findInfo.startTime.byHour;
			Tm.tm_min = findInfo.startTime.byMinute;
			Tm.tm_sec = findInfo.startTime.bySecond;
			rf.beginTime = _mktime64(&Tm);

			Tm.tm_year = findInfo.stopTime.woYear - 1900;
			Tm.tm_mon = findInfo.stopTime.byMonth - 1;
			Tm.tm_mday = findInfo.stopTime.byDay;
			Tm.tm_hour = findInfo.stopTime.byHour;
			Tm.tm_min = findInfo.stopTime.byMinute;
			Tm.tm_sec = findInfo.stopTime.bySecond;
			rf.endTime = _mktime64(&Tm);

			stime = findInfo.startTime;
			etime = findInfo.stopTime;
// 			ZeroMemory(szTime, 512);
// 			sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d %d-%02d-%02d %02d-%02d-%02d", stime.woYear, stime.byMonth, stime.byDay,
// 				stime.byHour, stime.byMinute, stime.bySecond,
// 				etime.woYear, etime.byMonth, etime.byDay, etime.byHour, etime.byMinute, etime.bySecond);

			rf.channel = nChannelId;
			rf.name = findInfo.sFileName;
			rf.size = findInfo.dwFileSize;
			rf.setPrivateData(&findInfo, sizeof(LVR_NET_FILE));
// 			{
// 				Mutex::ScopedLock lock(m_mtx);
// 				m_mapArcItem.insert(std::make_pair(string(findInfo.sFileName), findInfo));
// 			}

			files.push_back(rf);
			iFinds++;

// 			char szLog[1024];
// 			ZeroMemory(szLog, 1024);
// 			sprintf(szLog, "GetRecordFileList 文件名:%s 文件大小:%d 文件时间:%s 通道:%d", findInfo.sFileName, findInfo.dwFileSize, szTime, rf.channel);
// 			g_log.AddLog(string(szLog));
		}

		if (FALSE == LvrNetFindFileClose(lfind))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 关闭查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
	}

    return true;
}



bool HangJing_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

//     HB_SDVR_PLAYCOND struDownloadCond={0};
//     memset(&struDownloadCond, 0, sizeof(HB_SDVR_PLAYCOND));
//     struDownloadCond.dwChannel = file.channel;
//     struDownloadCond.byDrawFrame = 1;
// 
//     struct tm Tm;
// 
//     _gmtime64_s(&Tm, (const time_t*)&file.beginTime);
//     struDownloadCond.startTime.woYear = Tm.tm_year;
//     struDownloadCond.startTime.byMonth = Tm.tm_mon;
//     struDownloadCond.startTime.byDay = Tm.tm_mday;
//     struDownloadCond.startTime.byHour = Tm.tm_hour;
//     struDownloadCond.startTime.byMinute = Tm.tm_min;
//     struDownloadCond.startTime.bySecond = Tm.tm_sec;
// 
//     _gmtime64_s(&Tm, (const time_t*)&file.endTime);
//     struDownloadCond.stopTime.woYear = Tm.tm_year;
//     struDownloadCond.stopTime.byMonth = Tm.tm_mon;
//     struDownloadCond.stopTime.byDay = Tm.tm_mday;
//     struDownloadCond.stopTime.byHour = Tm.tm_hour;
//     struDownloadCond.stopTime.byMinute = Tm.tm_min;
//     struDownloadCond.stopTime.bySecond = Tm.tm_sec;
// 	LVR_NET_FILE info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, LVR_NET_FILE>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("downLoadByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}
// 	char szTmp[64];
// 	ZeroMemory(szTmp, 64);
// 	sprintf(szTmp, "~%02d", file.channel);
// 	string strFileName = info.sFileName;
// 	strFileName.insert(19, szTmp);
//	g_log.AddLog(string("downLoadByRecordFile 文件名:") + string(info.sFileName) + string(" 保存文件名:") + saveFileName);
	//g_log.AddLog(string("downLoadByRecordFile 文件名:") + saveFileName);
//     if (this->m_deviceInfo.wDevType == 2015)
//     {

	//hdl = LvrNetGetFileByName(m_lLoginHandle, (char*)info.sFileName, (char*)saveFileName);
	LVR_NET_FILE* pData = (LVR_NET_FILE *)file.getPrivateData();
	hdl = LvrNetGetFileByName(m_lLoginHandle, pData->sFileName, (char*)saveFileName);
//     }
//     else
//     {
//         hdl = HB_SDVR_GetFileByTime_V40(m_lLoginHandle, (char*)saveFileName, &struDownloadCond);
//     }

	if (hdl <= 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
        return false;
    }

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.insert(make_pair(hdl, file));
	}
//     if (!Api_Api().m_pPlayBackControl(hdl, HB_SDVR_PLAYSTART, 0, NULL))
//     {
// 		m_sLastError = GetLastErrorString();
// 		g_log.AddLog(string("downLoadByRecordFile 01 下载录像失败，错误原因：") + m_sLastError);
//         return false;
//     }

    return true;
}


bool  HangJing_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
        return false;
    }

//     HB_SDVR_VOD_PARA struVodPara={0};
//     memset(&struVodPara, 0, sizeof(HB_SDVR_VOD_PARA));
//     dwSize=sizeof(struVodPara);
//     struIDInfo.dwChannel = file.channel; //通道号
//     hWnd = hwnd;
// 	LVR_NET_FILE info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, LVR_NET_FILE>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("PlayBackByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}

    struct tm Tm;
	LVR_NET_TIME struBeginTime;
	_localtime64_s(&Tm, (const time_t*)&file.beginTime);
    struBeginTime.woYear = Tm.tm_year + 1900;
    struBeginTime.byMonth = Tm.tm_mon + 1;
    struBeginTime.byDay = Tm.tm_mday;
    struBeginTime.byHour = Tm.tm_hour;
    struBeginTime.byMinute = Tm.tm_min;
    struBeginTime.bySecond = Tm.tm_sec;
// 	char szTime[512];
// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d", 
// 		Tm.tm_year, Tm.tm_mon, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);
// 	g_log.AddLog(string(szTime));

	LVR_NET_TIME struEndTime;
	_localtime64_s(&Tm, (const time_t*)&file.endTime);
    struEndTime.woYear = Tm.tm_year + 1900;
    struEndTime.byMonth = Tm.tm_mon + 1;
    struEndTime.byDay = Tm.tm_mday;
    struEndTime.byHour = Tm.tm_hour;
    struEndTime.byMinute = Tm.tm_min;
    struEndTime.bySecond = Tm.tm_sec;

// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d", 
// 		Tm.tm_year, Tm.tm_mon, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);
// 	g_log.AddLog(string(szTime));

	LVR_NET_TIME stime = struBeginTime;
	LVR_NET_TIME etime = struEndTime;

// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d %d-%02d-%02d %02d-%02d-%02d", stime.woYear, stime.byMonth, stime.byDay,
// 		stime.byHour, stime.byMinute, stime.bySecond,
// 		etime.woYear, etime.byMonth, etime.byDay, etime.byHour, etime.byMinute, etime.bySecond);
// 	g_log.AddLog(string(szTime));
// 	char szTmp[64];
// 	ZeroMemory(szTmp, 64);
// 	sprintf(szTmp, "~%02d", info.nCh);
// 	string strFileName = info.sFileName;
// 	strFileName.insert(19, szTmp);
// 	g_log.AddLog(string("PlayBackByRecordFile 文件名:") + strFileName);
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d 通道:%d 时间:%d-%02d-%02d %02d:%02d:%02d %d-%02d-%02d %02d:%02d:%02d", m_lLoginHandle, file.channel,
		stime.woYear, stime.byMonth, stime.byDay, stime.byHour, stime.byMinute, stime.bySecond,
		etime.woYear, etime.byMonth, etime.byDay, etime.byHour, etime.byMinute, etime.bySecond);
	g_log.AddLog(string(szLog));
	
	//playbackHandle = LvrNetPlayByFile(m_lLoginHandle, (char *)info.sFileName, NULL);
	LVR_NET_FILE* pData = (LVR_NET_FILE *)file.getPrivateData();
	playbackHandle = LvrNetPlayByFile(m_lLoginHandle, pData->sFileName, NULL);
	//Api_Api().m_pPlayBackByTime(m_lLoginHandle, file.channel, &struBeginTime, &struEndTime, hwnd);
	//playbackHandle = Api_Api().m_pPlayBackByTime(m_lLoginHandle, info.nCh, &struBeginTime, &struEndTime, hwnd);
	if (playbackHandle <= 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
        return false;
    }

	if (!LvrNetPlayDataCallBack(playbackHandle, DataCallBack, (DWORD)this))
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 设置播放流回调失败，错误原因：") + m_sLastError);
		return false;
	}

	LONG lStreamHandle = LvrNetStreamDataPlay(hwnd, 0);
	if (lStreamHandle < 0)
	{
		m_lStreamHandle = -1;
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 01 播放录像失败，错误原因：") + m_sLastError);
		return false;
	}
	m_lStreamHandle = lStreamHandle;

//     if (!Api_Api().m_pPlayBackControl(playbackHandle, HB_SDVR_PLAYSTART, 0, NULL))
//     {
// 		m_sLastError = GetLastErrorString();
// 		g_log.AddLog(string("PlayBackByRecordFile 01 播放录像失败，错误原因：") + m_sLastError);
//         return false;
//     }

    return true;
}

bool HangJing_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
	g_log.AddLog(string("SetPlayBack"));
	return FALSE != LvrNetPlayControl(playbackHandle, LVR_NET_SET_POS, pos);
}

bool HangJing_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("StopPlayBack 请先登录"));
        return false;
    }

	if (mPause == 1)
	{
		g_log.AddLog(string("StopPlayBack 开始暂停播放"));
		if (!LvrNetPlayControl(playbackHandle, LVR_NET_PLAY_PAUSE, 0))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 暂停播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}
	else
	{
		char szLog[1024];
		ZeroMemory(szLog, 1024);
		sprintf(szLog, "StopPlayBack 开始停止播放 playbackHandle:%d", playbackHandle);
		g_log.AddLog(string(szLog));
		if (!LvrNetPlayClose(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}

		if (!LvrNetStreamPlayClose(m_lStreamHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 01 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}

    return true;
}

bool HangJing_videoserver::stopDownload(download_handle_t h)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("stopDownload 请先登录"));
		return false;
	}
	g_log.AddLog(string("stopDownload 开始停止下载"));
	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.erase(h);
	}
	if (FALSE == LvrNetStopGetFile(h))
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool HangJing_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	g_log.AddLog(string("getPlayBackPos"));
// 	return false;
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
		return false;
	}
	BOOL bRet = LvrNetPlayControl(playbackHandle, LVR_NET_GET_POS, (LPARAM)pos);
	if (bRet < 0)
	{
		g_log.AddLog(string("getDownloadPos 获取播放进度失败"));
		return false;
	}
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "getPlayBackPos pos:%d", *pos);
	g_log.AddLog(string(szLog));
	return true;
}

bool HangJing_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
		return false;
	}

	RecordFile file;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<long long, RecordFile>::iterator itr = m_mapDownloadOrPlay.find(h);
		if (itr == m_mapDownloadOrPlay.end())
		{
			m_sLastError = "找不到该下载";
			g_log.AddLog(string("getPlayBackPos 找不到该下载"));
			*failed = true;
			return false;
		}
		file = itr->second;
	}

	int iPos = LvrNetGetFilePos(h);
	if (0 > iPos)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("getDownloadPos 获取进度失败"));
		*failed = true;
		return false;
	}
	*totalSize = file.size;
	*currentSize = ((float)iPos / (float)100) * (*totalSize);
	*failed = false;
	return true;
}