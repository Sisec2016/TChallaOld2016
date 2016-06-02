#include "dizhipu_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
//#include "log.h"
//Log g_log("dizhipu_videoserver");

#define ONEDAY	24 * 60 * 60

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryDiZhiPu();
}


DWORD ErrorTry()
{
	DWORD dwError = H264_DVR_GetLastError();
	return dwError;
}

static std::string GetLastErrorString()
{
	 DWORD dwError = ErrorTry();

    switch (dwError)
    {
        case  H264_DVR_NOERROR: return "没有错误";
		case  H264_DVR_SUCCESS: return "返回成功";
		case  H264_DVR_SDK_NOTVALID: return "非法请求";
		case  H264_DVR_NO_INIT: return "SDK未经初始化";
		case  H264_DVR_ILLEGAL_PARAM: return "用户参数不合法";
		case  H264_DVR_INVALID_HANDLE: return "句柄无效";
		case  H264_DVR_SDK_UNINIT_ERROR: return "SDK清理出错";
		case  H264_DVR_SDK_TIMEOUT: return "等待超时";
		case  H264_DVR_SDK_MEMORY_ERROR: return "内存错误，创建内存失败";
		case  H264_DVR_SDK_NET_ERROR: return "网络错误";
		case  H264_DVR_SDK_OPEN_FILE_ERROR: return "打开文件失败";
		case  H264_DVR_SDK_UNKNOWNERROR: return "未知错误";
		case  H264_DVR_DEV_VER_NOMATCH: return "收到数据不正确，可能版本不匹配";
		case  H264_DVR_SDK_NOTSUPPORT: return "版本不支持";
		case  H264_DVR_OPEN_CHANNEL_ERROR: return "打开通道失败";
		case  H264_DVR_CLOSE_CHANNEL_ERROR: return "关闭通道失败";
		case  H264_DVR_SUB_CONNECT_ERROR: return "建立媒体子连接失败";
		case  H264_DVR_SUB_CONNECT_SEND_ERROR: return "媒体子连接通讯失败";
		case  H264_DVR_NATCONNET_REACHED_MAX: return "Nat视频链接达到最大，不允许新的Nat视频链接";
		case  H264_DVR_NOPOWER: return "无权限";
		case  H264_DVR_PASSWORD_NOT_VALID: return "账号密码不对";
		case  H264_DVR_LOGIN_USER_NOEXIST: return "用户不存在";
		case  H264_DVR_USER_LOCKED: return "该用户被锁定";
		case  H264_DVR_USER_IN_BLACKLIST: return "该用户不允许访问(在黑名单中)";
		case  H264_DVR_USER_HAS_USED: return "该用户以登陆";
		case  H264_DVR_USER_NOT_LOGIN: return "该用户没有登陆";
		case  H264_DVR_CONNECT_DEVICE_ERROR: return "可能设备不存在";
		case  H264_DVR_ACCOUNT_INPUT_NOT_VALID: return "用户管理输入不合法";
		case  H264_DVR_ACCOUNT_OVERLAP: return "索引重复";
		case  H264_DVR_ACCOUNT_OBJECT_NONE: return "不存在对象, 用于查询时";
		case  H264_DVR_ACCOUNT_OBJECT_NOT_VALID: return "不存在对象";
		case  H264_DVR_ACCOUNT_OBJECT_IN_USE: return "对象正在使用";
		case  H264_DVR_ACCOUNT_SUBSET_OVERLAP: return "子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)";
		case  H264_DVR_ACCOUNT_PWD_NOT_VALID: return "密码不正确";
		case  H264_DVR_ACCOUNT_PWD_NOT_MATCH: return "密码不匹配";
		case  H264_DVR_ACCOUNT_RESERVED: return "保留帐号";
		case  H264_DVR_OPT_RESTART: return "保存配置后需要重启应用程序";
		case  H264_DVR_OPT_REBOOT: return "需要重启系统";
		case  H264_DVR_OPT_FILE_ERROR: return "写文件出错";
		case  H264_DVR_OPT_CAPS_ERROR: return "配置特性不支持";
		case  H264_DVR_OPT_VALIDATE_ERROR: return "配置校验失败";
		case  H264_DVR_OPT_CONFIG_NOT_EXIST: return "请求或者设置的配置不存在";
		case  H264_DVR_CTRL_PAUSE_ERROR: return "暂停失败";
		case  H264_DVR_SDK_NOTFOUND: return "查找失败，没有找到对应文件";
		case  H264_DVR_CFG_NOT_ENABLE: return "配置未启用";
		case  H264_DVR_DECORD_FAIL: return "解码失败";
		case  H264_DVR_SOCKET_ERROR: return "创建套节字失败";
		case  H264_DVR_SOCKET_CONNECT: return "连接套节字失败";
		case  H264_DVR_SOCKET_DOMAIN: return "域名解析失败";
		case  H264_DVR_SOCKET_SEND: return "发送数据失败";
		case  H264_DVR_ARSP_NO_DEVICE: return "没有获取到设备信息，设备应该不在线";
		case  H264_DVR_ARSP_BUSING: return "ARSP服务繁忙";
		case  H264_DVR_ARSP_BUSING_SELECT: return "ARSP服务繁忙,select失败";
		case  H264_DVR_ARSP_BUSING_RECVICE: return "ARSP服务繁忙,recvice失败";
		case  H264_DVR_CONNECTSERVER_ERROR: return "连接服务器失败";
		case  H264_DVR_CONNECT_FULL: return "服务器连接数已满";
		case  H264_DVR_PIRATESOFTWARE: return "设备盗版";
		default: return "未知错误";
    }
}



CFactoryDiZhiPu::CFactoryDiZhiPu()
{
    init();
}

CFactoryDiZhiPu::~CFactoryDiZhiPu()
{
    clean();
}



bool InitTry()
{
	return H264_DVR_Init(0, 0);
}


bool CFactoryDiZhiPu::init()
{
    if (!m_init)
    {
		m_init = InitTry();

        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
		}
    }

    return m_init;
}


bool cleanTry()
{
	return H264_DVR_Cleanup();
}

void CFactoryDiZhiPu::clean()
{
	cleanTry();
	m_init = false;
}




IVideoServer* CFactoryDiZhiPu::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new dizhipu_videoserver();
}

dizhipu_videoserver::dizhipu_videoserver()
{
}

dizhipu_videoserver::~dizhipu_videoserver()
{
		logout();
}

static void CALL_METHOD PosCallBack(long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser)
{
	dizhipu_videoserver * pThis = (dizhipu_videoserver *)dwUser;
	if (pThis == NULL) return;
	//Mutex::ScopedLock lock(pThis->m_mtxPos);
	pThis->m_mtxPos.lock();
	map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosDownPlay.find(lPlayHandle);
	if (itr != pThis->m_mapPosDownPlay.end())
	{
		itr->second.iTotalSize = lTotalSize * 1024;
		itr->second.iCurSize = lDownLoadSize * 1024;
		itr->second.iPercent = ((float)lDownLoadSize / (float)lTotalSize) * 100;
	}
	pThis->m_mtxPos.unlock();
}

IVideoServer* dizhipu_videoserver::clone()
{
	return NULL;
}

long loginTry(const char* IP, __int32 port, const char* user, const char* password, H264_DVR_DEVICEINFO* ptDevInfo, int *iError)
{
	return H264_DVR_Login((char*)IP, port,
			(char*)user, (char*)password,
			ptDevInfo, iError, 0);
}

bool GetDevConfigTry(long lhandle, char* channelName, DWORD *dwRetLen, int nWaitTime)
{
	return H264_DVR_GetDevConfig(lhandle, E_SDK_CONFIG_CHANNEL_NAME, -1,
		channelName, sizeof(SDK_ChannelNameConfigAll), dwRetLen, nWaitTime);
}

bool dizhipu_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
//	g_log.AddLog(string("asdasd"));

    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

	int iError = 0;

	m_lLoginHandle = loginTry((char*)IP, port, (char*)user, (char*)password, &m_deviceInfo, &iError);

    if (m_lLoginHandle == 0)
    {
		m_sLastError = GetLastErrorString();
        return false;
    }

	SDK_ChannelNameConfigAll pChannelName;
	DWORD dwRetLen = 0;
	int nWaitTime = 1000;
	BOOL bSuccess = FALSE;

	bSuccess = GetDevConfigTry(m_lLoginHandle, (char *)&pChannelName, &dwRetLen, nWaitTime);

	if (!bSuccess || dwRetLen != sizeof(SDK_ChannelNameConfigAll))
	{
		m_sLastError = GetLastErrorString();
		return false;
	}

	channels.clear();
	char szName[64+2];
	char *pChannelNameTmp = (char *)&pChannelName;

	int i = 1;
	for ( ; i <= m_deviceInfo.byChanNum; i++)
	{
		ZeroMemory(szName, sizeof(szName));

		sprintf(szName, "CAM%02d", i);
		string strName = szName;
		channels.insert(std::make_pair(i, strName));
	}
	for ( ; i <= m_deviceInfo.iDigChannel + m_deviceInfo.byChanNum; i++)
	{
		ZeroMemory(szName, sizeof(szName));
		sprintf(szName, "CAM%02d", i);
		string strName = szName;
		channels.insert(std::make_pair(i, strName));
	}
	
    return true;
}

bool logoutTry(long lhandle)
{
	return H264_DVR_Logout(lhandle);
}

bool dizhipu_videoserver::logout()
{
	bool bSuccess = false;

	bSuccess = logoutTry(m_lLoginHandle);

	if (m_lLoginHandle > 0 && !bSuccess)
    {
        m_sLastError = GetLastErrorString();
        return false;
    }
	m_lLoginHandle = 0;
    return true;
}

static void timeDiZhiPuToStd(SDK_SYSTEM_TIME *pTimeDH, tm *pTimeStd)
{
	pTimeStd->tm_year = pTimeDH->year - 1900;
	pTimeStd->tm_mon = pTimeDH->month - 1;
	pTimeStd->tm_mday = pTimeDH->day;
	pTimeStd->tm_hour = pTimeDH->hour;
	pTimeStd->tm_min = pTimeDH->minute;
	pTimeStd->tm_sec = pTimeDH->second;

	pTimeStd->tm_wday = pTimeDH->wday;
	pTimeStd->tm_isdst = pTimeDH->isdst;
}

static void timeStdToDiZhiPu(tm *pTimeStd, SDK_SYSTEM_TIME *pTimeDH)
{
	pTimeDH->year = pTimeStd->tm_year + 1900;
	pTimeDH->month = pTimeStd->tm_mon + 1;
	pTimeDH->day = pTimeStd->tm_mday;
	pTimeDH->hour = pTimeStd->tm_hour;
	pTimeDH->minute = pTimeStd->tm_min;
	pTimeDH->second = pTimeStd->tm_sec;

	pTimeDH->wday = pTimeStd->tm_wday;
	pTimeDH->isdst = pTimeStd->tm_isdst;
}

static void timeDiZhiPuToStd2(H264_DVR_TIME *pTimeDH, tm *pTimeStd)
{
	pTimeStd->tm_year = pTimeDH->dwYear - 1900;
	pTimeStd->tm_mon = pTimeDH->dwMonth - 1;
	pTimeStd->tm_mday = pTimeDH->dwDay;
	pTimeStd->tm_hour = pTimeDH->dwHour;
	pTimeStd->tm_min = pTimeDH->dwMinute;
	pTimeStd->tm_sec = pTimeDH->dwSecond;
}

static void timeStdToDiZhiPu2(tm *pTimeStd, H264_DVR_TIME *pTimeDH)
{
	pTimeDH->dwYear = pTimeStd->tm_year + 1900;
	pTimeDH->dwMonth = pTimeStd->tm_mon + 1;
	pTimeDH->dwDay = pTimeStd->tm_mday;
	pTimeDH->dwHour = pTimeStd->tm_hour;
	pTimeDH->dwMinute = pTimeStd->tm_min;
	pTimeDH->dwSecond = pTimeStd->tm_sec;
}

#define MAX_SEARCH_COUNT 1000

bool getFileTry(long lhandle, H264_DVR_FINDINFO *findInfo, H264_DVR_FILE_DATA *szSend, int icount, int *iMaxNum)
{
	return H264_DVR_FindFile(lhandle, findInfo, szSend, MAX_SEARCH_COUNT, iMaxNum, 5 * 1000);
}

bool dizhipu_videoserver::GetRecordFileList(std::vector<RecordFile>& files, std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
	if (m_lLoginHandle <= 0) return false;

	if (timeStart >= timeEnd) return false;

	files.clear();

	H264_DVR_TIME stime, etime;
//	H264_DVR_TIME stimeTmp, everydayTime;

	tm STime;
	tm ETime;
	_localtime64_s(&STime, (const time_t*)&timeStart);
	_localtime64_s(&ETime, (const time_t*)&timeEnd);
	timeStdToDiZhiPu2(&STime, &stime);
	timeStdToDiZhiPu2(&ETime, &etime);

	__time64_t everytime, begintime, endtime;
	begintime = timeStart;

	struct tm Tm = { 0, 0, 0, stime.dwDay, stime.dwMonth - 1, stime.dwYear - 1900 };
	everytime = mktime(&Tm);
	if (stime.dwDay == etime.dwDay && stime.dwMonth == etime.dwMonth && stime.dwYear == etime.dwYear)
	{
		begintime = timeStart;
		endtime = timeEnd;
	}

	for (; everytime < timeEnd; everytime += ONEDAY)
	{
		if (stime.dwDay != etime.dwDay || stime.dwMonth != etime.dwMonth || stime.dwYear != etime.dwYear)
		{
			if (begintime == timeStart)
			{
				timeStart += 1;
				endtime = everytime + ONEDAY - 1;
			}
			else
			{
				begintime = everytime;
				if ((everytime + ONEDAY) > timeEnd)
				{
					endtime = timeEnd;
				}
				else{
					endtime = everytime + ONEDAY - 1;
				}
			}
		}
		H264_DVR_TIME Begin_Time, End_Time;

		tm STime;
		tm ETime;
		_localtime64_s(&STime, (const time_t*)&begintime);
		_localtime64_s(&ETime, (const time_t*)&endtime);
		timeStdToDiZhiPu2(&STime, &Begin_Time);
		timeStdToDiZhiPu2(&ETime, &End_Time);

		std::vector<int>::iterator itr = channelVec.begin();
		for (; itr != channelVec.end(); itr++)
		{
			int nChannelId = *itr;

			H264_DVR_FINDINFO findInfo;
			ZeroMemory(&findInfo, sizeof(findInfo));
			findInfo.nChannelN0 = nChannelId - 1;
			findInfo.nFileType = 0;
			findInfo.startTime = Begin_Time;
			findInfo.endTime = End_Time;

			H264_DVR_FILE_DATA *szSend = new H264_DVR_FILE_DATA[MAX_SEARCH_COUNT];
			ZeroMemory(szSend, sizeof(H264_DVR_FILE_DATA)*MAX_SEARCH_COUNT);

			int iMaxNum = 0;
			bool bRet = false;
			bRet = getFileTry(m_lLoginHandle, &findInfo, szSend, MAX_SEARCH_COUNT, &iMaxNum);
			if (bRet == false || iMaxNum == 0)
			{
				m_sLastError = GetLastErrorString();
				continue;
			}	
			SaveToFiles(files, szSend, iMaxNum, nChannelId);
		}
	}
	return true;
}

void dizhipu_videoserver::SaveToFiles(std::vector<RecordFile>& files, H264_DVR_FILE_DATA* szSend, int iMaxNum, int nChannelId)
{
	Mutex::ScopedLock lock(m_mtx);
	H264_DVR_FILE_DATA item;
	RecordFile info;
	tm sTm;
	tm eTm;
	char szFileName[MAX_PATH];
	for (int i = 0; i < iMaxNum; i++)
	{
		item = szSend[i];
		ZeroMemory(szFileName, sizeof(szFileName));
		sprintf(szFileName, "channel%d %04d-%02d-%02d %02d-%02d-%02d -- %04d-%02d-%02d %02d-%02d-%02d",
			nChannelId,
			item.stBeginTime.year,
			item.stBeginTime.month,
			item.stBeginTime.day,
			item.stBeginTime.hour,
			item.stBeginTime.minute,
			item.stBeginTime.second,
			item.stEndTime.year,
			item.stEndTime.month,
			item.stEndTime.day,
			item.stEndTime.hour,
			item.stEndTime.minute,
			item.stEndTime.second);
		m_mapArcItem.insert(make_pair(string(szFileName), item));

		timeDiZhiPuToStd(&item.stBeginTime, &sTm);
		timeDiZhiPuToStd(&item.stEndTime, &eTm);

		info.channel = nChannelId/*item.ch*/;
		info.size = item.size * 1024;
		info.name = szFileName;
		info.beginTime = mktime(&sTm);
		info.endTime = mktime(&eTm);
		files.push_back(info);
	}
}

bool downloadTry(long lhandle, H264_DVR_FILE_DATA *info, const char* saveFileName, long ptr, download_handle_t& hdl)
{
	return H264_DVR_GetFileByName(lhandle, info, (char *)saveFileName, PosCallBack, ptr, NULL);
}

bool dizhipu_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
        return false;
    }

	H264_DVR_FILE_DATA info;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<string, H264_DVR_FILE_DATA>::iterator itr = m_mapArcItem.find(file.name);
		if (itr == m_mapArcItem.end())
		{
			m_sLastError = "该文件不存在";
			return false;
		}

		info = itr->second;
	}
	bool bRet = downloadTry(m_lLoginHandle, &info, saveFileName, (long)this, hdl);

	if (hdl <= 0)//modify by tsx 小于或等于0 迪智浦系列下载会挂掉的根源
	{
		m_sLastError = GetLastErrorString();
		return false;
	}

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.insert(std::make_pair(hdl, file));
	}
	{
		stPos_DownPlay pos;
		pos.iTotalSize = info.size * 1024;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(hdl, pos));
	}

	return true;
}


bool PlayBackloadTry(long lhandle, H264_DVR_FILE_DATA *info, long ptr, play_handle_t& playbackHandle)
{

	return H264_DVR_PlayBackByName(lhandle, info, PosCallBack, NULL, ptr);
}

bool  dizhipu_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
        return false;
	}

	H264_DVR_FILE_DATA info;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<string, H264_DVR_FILE_DATA>::iterator itr = m_mapArcItem.find(file.name);
		if (itr == m_mapArcItem.end())
		{
			m_sLastError = "该文件不存在";
			return false;
		}

		info = itr->second;
	}
	info.hWnd = hwnd;

	bool bRet = PlayBackloadTry(m_lLoginHandle, &info, (long)this, playbackHandle);
	if (bRet != true)
	{
		return false;
	}

	if (playbackHandle == 0)
	{
		m_sLastError = GetLastErrorString();
		return false;
	}

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.insert(std::make_pair(playbackHandle, file));
	}
	{
		stPos_DownPlay pos;
		pos.iTotalSize = info.size * 1024;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(playbackHandle, pos));
	}

	return true;
}


bool SetPlayBackTry(__int64 playbackHandle, __int32 pos)
{
	return H264_DVR_PlayBackControl(playbackHandle, SDK_PLAY_BACK_SEEK_PERCENT, pos);
}

bool dizhipu_videoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
	RecordFile file;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<long long, RecordFile>::iterator itr = m_mapDownloadOrPlay.find(playbackHandle);
		if (itr == m_mapDownloadOrPlay.end())
		{
			m_sLastError = "该文件不存在";
			return false;
		}
		file = itr->second;
	}

	return SetPlayBackTry(playbackHandle, pos);
}

bool playcontrolTry(__int64 playbackHandle)
{
	return H264_DVR_PlayBackControl(playbackHandle, SDK_PLAY_BACK_PAUSE, 0);
}

bool stopPlayTry(__int64 playbackHandle)
{
	return H264_DVR_StopPlayBack(playbackHandle);
}

bool dizhipu_videoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
        return false;
    }
	if (mPause == 1)
	{
		if (!playcontrolTry(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			return false;
		}
	}
	else
	{
		{
			Mutex::ScopedLock lock(m_mtx);
			map<long long, RecordFile>::iterator itr = m_mapDownloadOrPlay.find(playbackHandle);
			if (itr == m_mapDownloadOrPlay.end())
			{
				return false;
			}
		}
		{
			Mutex::ScopedLock lock(m_mtx);
			m_mapDownloadOrPlay.erase(playbackHandle);
		}
		{
			Mutex::ScopedLock lock2(m_mtxPos);
			m_mapPosDownPlay.erase(playbackHandle);
		}
		bool bRet = stopPlayTry(playbackHandle);
		return bRet;
	}

    return true;
}


bool stopDownloadTry(download_handle_t h)
{
	return H264_DVR_StopGetFile(h);
}

bool dizhipu_videoserver::stopDownload(download_handle_t h)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
        return false;
	}
	{
		Mutex::ScopedLock lock(m_mtx);
		map<long long, RecordFile>::iterator itr = m_mapDownloadOrPlay.find(h);
		if (itr == m_mapDownloadOrPlay.end())
		{
			return false;
		}
	}
	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.erase(h);
	}
	{
		Mutex::ScopedLock lock2(m_mtxPos);
		m_mapPosDownPlay.erase(h);
	}
	bool bRet = false;
	bRet = stopDownloadTry(h);

	if (false == bRet)
    {
		m_sLastError = GetLastErrorString();
        return false;
	}

    return true;
}

bool dizhipu_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		return false;
	}

	Mutex::ScopedLock lock(m_mtxPos);
	map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(playbackHandle);
	if (itr != m_mapPosDownPlay.end())
	{
		*pos = itr->second.iPercent;
		return true;
	}
	m_sLastError = "找不到该回放";
	return false;
}

bool dizhipu_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		return false;
	}

	Mutex::ScopedLock lock(m_mtxPos);
	map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(h);
	if (itr != m_mapPosDownPlay.end())
	{
		*totalSize = itr->second.iTotalSize;
		*currentSize = itr->second.iCurSize;

		*failed = false;
		return true;
	}
	m_sLastError = "找不到该下载";
	*failed = true;
	return false;
}
