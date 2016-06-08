#include "dy_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>

#include "../../VideoServer/log.h"

#define ONEDAY		24 * 60 * 60

Log g_log("DongYang_videoserver");

IVideoServerFactory* VideoServerFactory()
{
	return new CDongYangFactory();
}

std::string GetLastErrorString(int errorCode)
{
	switch (errorCode)
	{
	case DONGYANG::eRetSuccess: return "成功";
	case DONGYANG::eRetFailed: return "失败";
	case DONGYANG::eRetFailVersion: return"版本不匹配";
	case DONGYANG::eRetFailBoardType: return"板型不匹配，无法升级";

	case DONGYANG::eRetFailSdkNotInit: return"客户端sdk未初始化";
	case DONGYANG::eRetFailUnsupported: return"不支持的操作";
	case DONGYANG::eRetFailHasStarted: return"已经启动";
	case DONGYANG::eRetFailNotStart: return"未启动";

	case DONGYANG::eRetFailInvalidParameter: return"参数无效";
	case DONGYANG::eRetFailInvalidHandle: return"句柄值无效";
	case DONGYANG::eRetFailInvalidFile: return"文件无效";
	case DONGYANG::eRetFailNoResource: return"资源不足";

	case DONGYANG::eRetFailUserName: return"用户名错误";
	case DONGYANG::eRetFailUserPwd: return"用户密码错误";
	case DONGYANG::eRetFailIpNotAllowed: return"不允许的ip地址";
	case DONGYANG::eRetFailTooManyLoginedUser: return"登录用户过多";

	case DONGYANG::eRetFailNetworkError: return"网络错误";
	case DONGYANG::eRetFailCmdTimeout: return"命令超时";
	case DONGYANG::eRetFailReplyError: return"设备端回复错误";
	case DONGYANG::eRetFailDisconnect: return"连接断开";

	case DONGYANG::eRetFailDecodeShow: return"解码显示失败";
	case DONGYANG::eRetFailAudioCapture: return"音频捕获失败";
	case DONGYANG::eRetFailVoicePlay: return"语音播放失败";
	case DONGYANG::eRetFailNotFind: return"未找到";

	case DONGYANG::eRetFailNoRight: return"没有权限";
	case DONGYANG::eRetFailChannelDisabled: return"通道被禁用";
	case DONGYANG::eRetFailSameIPLoginLimit: return"同一ip地址登陆次数过多";
	}

	return "没有错误";
}



CDongYangFactory::CDongYangFactory()
{
    init();
}

CDongYangFactory::~CDongYangFactory()
{
    clean();
}






bool CDongYangFactory::init()
{
    if (!m_init)
    {
		int ret = 0;
		ret = Api_DY::Api().m_pDyNetwork_ClientInit();
		if (ret != 0)
        {
			m_sLastError = GetLastErrorString(ret);
		    m_init = false;
        }
		else
		{
			m_init = true;
		}
    }

    return m_init;
}


void CDongYangFactory::clean()
{
	Api_DY::Api().m_pDyNetwork_ClientUnInit();
}




IVideoServer* CDongYangFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new DongYang_videoserver();
}


std::vector<DongYang_videoserver*> DongYang_videoserver::sServers;
std::recursive_mutex DongYang_videoserver::sMtServers;

/*
 * 析构函数
 */
DongYang_videoserver::DongYang_videoserver()
{
	std::lock_guard<std::recursive_mutex> lock(DongYang_videoserver::sMtServers);
    sServers.push_back(this);
	m_total_ch_cnt = 0;
}

DongYang_videoserver::~DongYang_videoserver()
{
    //logout();
	std::lock_guard<std::recursive_mutex> lock(DongYang_videoserver::sMtServers);
    for (unsigned int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* DongYang_videoserver::clone()
{
	return nullptr;
	DongYang_videoserver *svr = new DongYang_videoserver();
    return svr;
}

bool DongYang_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
	channels.clear();
	m_hDevice = INVALID_HANDLE_VALUE;
	int nRet = -1;
	nRet = Api_DY::Api().m_pDyNetwork_ClientLogin(&m_hDevice, (char*)IP, port, (char*)user, (char*)password);
	if (DONGYANG::eRetSuccess != nRet || INVALID_HANDLE_VALUE == m_hDevice)
	{
		m_sLastError = GetLastErrorString(nRet);
		g_log.AddLog(m_sLastError);
		return false;
	}

	// 获取系统信息
	DONGYANG::dvr_device_info cSysCfg;
	memset(&cSysCfg, 0, sizeof(cSysCfg));
	nRet = Api_DY::Api().m_pDyNetwork_ClientGetDeviceConfig(m_hDevice, DONGYANG::msg_get_device_info, 0, (BYTE *)&cSysCfg, sizeof(cSysCfg));
	g_log.AddLog(string("[2]run here!"));
	if (nRet != 0)
	{
		m_sLastError = GetLastErrorString(nRet);
		g_log.AddLog(m_sLastError);
		return false;
	}

	m_total_ch_cnt = cSysCfg.video_analog_cnt_max + cSysCfg.video_digital_cnt_max;
/*	char m_total_ch_cntS[64] = { 0 };*/
	int nChannelMask = 0;
	for (int i = 0; i < m_total_ch_cnt; i++)
	{
		nChannelMask |= (1 << i);
	}

	DONGYANG::dvr_channel_attr_cfg m_cChAttr[32];
	nRet = Api_DY::Api().m_pDyNetwork_ClientGetDeviceConfig(m_hDevice, DONGYANG::msg_get_channel_attr_cfg, nChannelMask, (BYTE *)m_cChAttr, sizeof(m_cChAttr));
	if (nRet != 0)
	{
		m_sLastError = GetLastErrorString(nRet);
		g_log.AddLog(m_sLastError);
		return false;
	}

	for (int i = 0; i < 32; i++)
	{
// 		sprintf_s(m_total_ch_cntS, "i=%d,%d,%d", i, m_cChAttr[i].enable, m_cChAttr[i].video_channel);
// 		g_log.AddLog(string("[3]run here!") + m_total_ch_cntS);
		if (m_cChAttr[i].enable)
		{
			char name[16] = { 0 };
			sprintf_s(name, "通道 %d", i+1);
			channels.insert(std::make_pair(i, name));
		}
	}

	m_lLoginHandle = (long)m_lLoginHandle;
    return true;
}

bool DongYang_videoserver::logout()
{
	// 用户登出
	int nRet = Api_DY::Api().m_pDyNetwork_ClientLogout(m_hDevice);
	if (0 != nRet)
	{
		m_sLastError = GetLastErrorString(nRet);
		return false;
	}

	m_hDevice = INVALID_HANDLE_VALUE;

    return true;
}

bool DongYang_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
	__time64_t timeEnd)
{
	if (INVALID_HANDLE_VALUE == m_hDevice) return false;

	if (timeStart >= timeEnd) return false;

	DONGYANG::TimeInfo staTime = { 0 };
	DONGYANG::TimeInfo stopTime = { 0 };

	InitTime(staTime, stopTime, timeStart, timeEnd);

	__time64_t everydaytime, begintime, endtime;
	begintime = timeStart;

	struct tm Tm = { 0, 0, 0, staTime.wDay, staTime.wMonth - 1, staTime.wYear - 1900 };
	everydaytime = mktime(&Tm);

	if (staTime.wDay == stopTime.wDay && staTime.wMonth == stopTime.wMonth && staTime.wYear == stopTime.wYear)
	{
		begintime = timeStart;
		endtime = timeEnd;
	}

	__int32 nChannelId = 0;
	for (; everydaytime < timeEnd; everydaytime += ONEDAY)
	{
		if (staTime.wDay != stopTime.wDay || staTime.wMonth != stopTime.wMonth || staTime.wYear != stopTime.wYear)
		{
			if (begintime == timeStart)	{
				timeStart += 1;
				endtime = everydaytime + ONEDAY - 1;
			}
			else
			{
				begintime = everydaytime;
				if ((everydaytime + ONEDAY) > timeEnd)
				{
					endtime = timeEnd;
				}
				else{
					endtime = everydaytime + ONEDAY - 1;
				}

			}

		}
		DONGYANG::TimeInfo Begin_Time = { 0 };
		DONGYANG::TimeInfo End_Time = { 0 };
		InitTime(Begin_Time, End_Time, begintime, endtime);
		for (int ch = 0; ch < channelVec.size(); ch++)
		{
			nChannelId = channelVec[ch];

			HANDLE hQuery = INVALID_HANDLE_VALUE;
			int nRet = Api_DY::Api().m_pDyNetwork_ClientStartFileQuery(&hQuery, m_hDevice, nChannelId, DONGYANG::RECORD_TYPE_ALL, &Begin_Time, &End_Time);
			g_log.AddLog(string("[3]GetRecordFileList run here"));
			if (DONGYANG::eRetSuccess != nRet || INVALID_HANDLE_VALUE == hQuery)
			{
				if (DONGYANG::eRetFailNetworkError == nRet)
					break;
				continue;
			}
			// get 50 logs once time
			DONGYANG::RecFileQueryResult cFileResult[50];
			memset(cFileResult, 0, 50 * sizeof(DONGYANG::RecFileQueryResult));

			g_log.AddLog(string("[4]GetRecordFileList run here"));
			while (1)
			{
				DWORD dwFileCnt = 50;
				nRet = Api_DY::Api().m_pDyNetwork_ClientGetFileQueryResult(hQuery, dwFileCnt, (BYTE *)cFileResult, 50 * sizeof(cFileResult));
				char str[32] = { 0 };
				sprintf_s(str, "dwFileCnt:%d", dwFileCnt);
				g_log.AddLog(string("[5]GetRecordFileList run here") + string(str));
				if (DONGYANG::eRetSuccess != nRet)
				{
					Api_DY::Api().m_pDyNetwork_ClientStopFileQuery(hQuery);
					break;
				}

				SaveToFiles(cFileResult, dwFileCnt, nChannelId, files);
			}
		}
	}
	g_log.AddLog(string("[6]GetRecordFileList run here"));
	return true;
}

void DongYang_videoserver::SaveToFiles(DONGYANG::RecFileQueryResult* cFileResult, DWORD dwFileCnt, __int32 nChannelId,
	std::vector<RecordFile>& files)
{
	RecordFile rf;
	for (DWORD k = 0; k < dwFileCnt; k++)
	{
		struct tm Tm;
		Tm.tm_year = cFileResult[k].cBeginTime.wYear - 1900;
		Tm.tm_mon = cFileResult[k].cBeginTime.wMonth - 1;
		Tm.tm_mday = cFileResult[k].cBeginTime.wDay;
		Tm.tm_hour = cFileResult[k].cBeginTime.wHour;
		Tm.tm_min = cFileResult[k].cBeginTime.wMinute;
		Tm.tm_sec = cFileResult[k].cBeginTime.wMinute;
		rf.beginTime = _mktime64(&Tm);

		Tm.tm_year = cFileResult[k].cEndTime.wYear - 1900;
		Tm.tm_mon = cFileResult[k].cEndTime.wMonth - 1;
		Tm.tm_mday = cFileResult[k].cEndTime.wDay;
		Tm.tm_hour = cFileResult[k].cEndTime.wHour;
		Tm.tm_min = cFileResult[k].cEndTime.wMinute;
		Tm.tm_sec = cFileResult[k].cEndTime.wMinute;
		rf.endTime = _mktime64(&Tm);

		rf.channel = nChannelId;


		string strFileName(cFileResult[k].acFileName);
		int iPos = strFileName.rfind('//', strlen(cFileResult[k].acFileName));
		strFileName.erase(0, iPos + 1);
		int iPos1 = strFileName.rfind('.', strFileName.length());
		strFileName.erase(iPos1, strFileName.length());
		rf.name = strFileName.c_str();

		rf.size = cFileResult[k].dwFileSize;
		rf.setPrivateData(&cFileResult[k], sizeof(DONGYANG::RecFileQueryResult));

		files.push_back(rf);
	}
}


void DongYang_videoserver::InitTime(DONGYANG::TimeInfo& staTime, DONGYANG::TimeInfo& stopTime, __time64_t timeStart, __time64_t timeEnd)
{
	struct tm Tm;

	_localtime64_s(&Tm, (const time_t*)&timeStart);
	//_gmtime64_s(&Tm, (const time_t*)&timeStart);
	staTime.wYear = Tm.tm_year + 1900;
	staTime.wMonth = Tm.tm_mon + 1;
	staTime.wDay = Tm.tm_mday;
	staTime.wHour = Tm.tm_hour;
	staTime.wMinute = Tm.tm_min;
	staTime.wSecond = Tm.tm_sec;

	_localtime64_s(&Tm, (const time_t*)&timeEnd);
	//_gmtime64_s(&Tm, (const time_t*)&timeEnd);
	stopTime.wYear = Tm.tm_year + 1900;
	stopTime.wMonth = Tm.tm_mon + 1;
	stopTime.wDay = Tm.tm_mday;
	stopTime.wHour = Tm.tm_hour;
	stopTime.wMinute = Tm.tm_min;
	stopTime.wSecond = Tm.tm_sec;
}

bool DongYang_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
	if (INVALID_HANDLE_VALUE == m_hDevice)
	{
		m_sLastError = "未登录，请先登录!";
		g_log.AddLog(m_sLastError);
		return false;
	}

// 	map<string, string>::iterator itr;
// 	{
// 		Mutex::ScopedLock lock(m_mtxFileInfo);
// 		itr = m_mapFileInfo.find(string(file.name));
// 		if (itr == m_mapFileInfo.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("downLoadByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 	}

	HANDLE hDownload;
	int nRet = DONGYANG::eRetSuccess;
	//nRet = Api_DY::Api().m_pDyNetwork_ClientStartDownload(&hDownload, m_hDevice, (char *)itr->second.c_str(), (char*)saveFileName, NULL, NULL);
	DONGYANG::RecFileQueryResult* pData = (DONGYANG::RecFileQueryResult*)file.getPrivateData();
	nRet = Api_DY::Api().m_pDyNetwork_ClientStartDownload(&hDownload, m_hDevice, pData->acFileName, (char*)saveFileName, NULL, NULL);
	if (DONGYANG::eRetSuccess != nRet || INVALID_HANDLE_VALUE == hDownload)
	{
		m_sLastError = GetLastErrorString(nRet);
		g_log.AddLog(string("last error:") + m_sLastError);
		return false;
	}
	g_log.AddLog(string("run here, begin download"));
	hdl = download_handle_t(hDownload);

	{
		stPos_DownPlay pos;
		ZeroMemory(&pos, sizeof(pos));
		pos.iTotalSize = file.size;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(hdl, pos));
	}

    return true;
}


bool  DongYang_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
	if (INVALID_HANDLE_VALUE == m_hDevice)
    {
        m_sLastError = "请先登录!";
        return false;
    }

	HANDLE hPlayback = INVALID_HANDLE_VALUE;
	struct tm Tm;
	DONGYANG::TimeInfo staTime = { 0 };
	//_gmtime64_s(&Tm, (const time_t*)&(file.beginTime));
	_localtime64_s(&Tm, (const time_t*)&(file.beginTime));
	staTime.wYear = Tm.tm_year + 1900;
	staTime.wMonth = Tm.tm_mon + 1;
	staTime.wDay = Tm.tm_mday;
	staTime.wHour = Tm.tm_hour;
	staTime.wMinute = Tm.tm_min;
	staTime.wSecond = Tm.tm_sec;

	DONGYANG::TimeInfo stopTime = { 0 };
	//_gmtime64_s(&Tm, (const time_t*)&(file.endTime));
	_localtime64_s(&Tm, (const time_t*)&(file.endTime));
	stopTime.wYear = Tm.tm_year + 1900;
	stopTime.wMonth = Tm.tm_mon + 1;
	stopTime.wDay = Tm.tm_mday;
	stopTime.wHour = Tm.tm_hour;
	stopTime.wMinute = Tm.tm_min;
	stopTime.wSecond = Tm.tm_sec;
	int nRet = Api_DY::Api().m_pDyNetwork_ClientStartPlayback(&hPlayback, m_hDevice, file.channel, DONGYANG::RECORD_TYPE_ALL, &staTime, &stopTime, hwnd);
	if (DONGYANG::eRetSuccess != nRet || INVALID_HANDLE_VALUE == hPlayback)
	{
		if (DONGYANG::eRetFailNoRight == nRet)
		{
			m_sLastError = "没有权限";
		}
		return false;
	}

	m_playFile = &file;
	playbackHandle = download_handle_t(hPlayback);
	return true;
}

bool DongYang_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
	__time64_t seekTime = m_playFile->beginTime + (m_playFile->endTime - m_playFile->beginTime) * ((pos * 100) / (m_playFile->size));
	DONGYANG::TimeInfo DYseekTime = { 0 };
	struct tm Tm;
	_gmtime64_s(&Tm, (const time_t*)&seekTime);
	DYseekTime.wYear = Tm.tm_year;
	DYseekTime.wMonth = Tm.tm_mon;
	DYseekTime.wDay = Tm.tm_mday;
	DYseekTime.wHour = Tm.tm_hour;
	DYseekTime.wMinute = Tm.tm_min;
	DYseekTime.wSecond = Tm.tm_sec;

	int ret = Api_DY::Api().m_pDyNetwork_ClientPlaybackControl((HANDLE)playbackHandle, DONGYANG::ePlaybackSeek, &DYseekTime);

	if (0 != ret)
	{
		m_sLastError = GetLastErrorString(ret);
		return false;
	}

	return true;
}

bool DongYang_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
	int ret = Api_DY::Api().m_pDyNetwork_ClientStopPlayback((HANDLE)playbackHandle);

	if (0 != ret)
	{
		m_sLastError = GetLastErrorString(ret);
		return false;
	}

	return true;
}



bool DongYang_videoserver::stopDownload(download_handle_t h)
{
	{
		Mutex::ScopedLock lock(m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(h);
		if (itr != m_mapPosDownPlay.end())
		{
			m_mapPosDownPlay.erase(itr);
		}
	}
	int ret = Api_DY::Api().m_pDyNetwork_ClientStopDownload((HANDLE)h);

	if (0 != ret)
	{
		m_sLastError = GetLastErrorString(ret);
		return false;
	}

	return true;
}

bool DongYang_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	DONGYANG::TimeInfo tCurTime = { 0 };
	int nRet = Api_DY::Api().m_pDyNetwork_ClientPlaybackControl((HANDLE)playbackHandle, DONGYANG::ePlaybackGetCurPlayTime, (void *)&tCurTime);
	if (0 != nRet)
	{
		m_sLastError = GetLastErrorString(nRet);
		return false;
	}

	struct tm Tm;
	Tm.tm_year = tCurTime.wYear;
	Tm.tm_mon = tCurTime.wMonth;
	Tm.tm_mday = tCurTime.wDay;
	Tm.tm_hour = tCurTime.wHour;
	Tm.tm_min = tCurTime.wMinute;
	Tm.tm_sec = tCurTime.wMinute;
	__time64_t currentTime = _mktime64(&Tm);

	*pos = (100*(currentTime - m_playFile->beginTime)) / (m_playFile->endTime - m_playFile->beginTime);

	return true;
}

bool DongYang_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	unsigned long pos = 0;

	int ret = Api_DY::Api().m_pDyNetwork_ClientGetDownloadStatus((HANDLE)h, pos);
	if (0 != ret)
	{
		m_sLastError = GetLastErrorString(ret);
		g_log.AddLog(string("getDownloadPos 找不到该下载文件 m_sLastError:") + m_sLastError);
		return false;
	}

	Mutex::ScopedLock lock(m_mtxPos);
	map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(h);
	if (itr != m_mapPosDownPlay.end())
	{
		*totalSize = itr->second.iTotalSize;
		*currentSize = itr->second.iTotalSize * (pos) / 100;

		*failed = false;
		return true;
	}
	else
	{
		m_sLastError = "找不到该下载文件";
		g_log.AddLog(string("getDownloadPos 找不到该下载文件"));
		*failed = true;
		return false;
	}
}
