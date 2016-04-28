#include "dizhipu_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "log.h"
Log g_log("dizhipu_videoserver");

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryDiZhiPu();
}


DWORD ErrorTry()
{
	DWORD dwError;
/*	bool bExp = false;*/
	__try
	{
		//dwError = Api_DiZhiPu::Api().m_pGetLastError();
		dwError = H264_DVR_GetLastError();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pGetLastError()"));
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pGetLastError()"));
// 	}

	return dwError;
}

static std::string GetLastErrorString()
{
     DWORD dwError;
// 	__try
// 	{
// 		dwError = Api_DiZhiPu::Api().m_pGetLastError();
// 	}
// 	__except (EXCEPTION_EXECUTE_HANDLER)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pGetLastError()"));
// 	}

	dwError = ErrorTry();

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
	bool init = true;
/*	bool bExp = false;*/
	__try
	{
		init = H264_DVR_Init(0, 0);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pInit(0, 0)"));
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pInit(0, 0)"));
// 	}

	return init;
}


bool CFactoryDiZhiPu::init()
{
    if (!m_init)
    {
		m_init = InitTry();

// 		__try
// 		{
// 			m_init = Api_DiZhiPu::Api().m_pInit(0, 0);
// 		}
// 		__except (EXCEPTION_EXECUTE_HANDLER)
// 		{
// 			g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pInit(0, 0)"));
// 		}
        //NET_DVR_SetConnectTime(1000, 30);
        //NET_DVR_SetReconnect(3000);
        //NET_DVR_SetDVRMessage()
        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
			//g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
		}

		//g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


bool cleanTry()
{
	bool uninit = true;
/*	bool bExp = false;*/
	__try
	{
		uninit = H264_DVR_Cleanup();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pUninit()"));
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pUninit()"));
// 	}

	return uninit;
}

void CFactoryDiZhiPu::clean()
{
    //Api_DiZhiPu::Api().m_pUninit();
// 	__try
// 	{
// 		m_init = Api_DiZhiPu::Api().m_pUninit();
// 	}
// 	__except (EXCEPTION_EXECUTE_HANDLER)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pUninit()"));
// 	}
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

// std::vector<dizhipu_videoserver*> dizhipu_videoserver::sServers;
// std::recursive_mutex dizhipu_videoserver::sMtServers;

/*
 * 析构函数
 */
dizhipu_videoserver::dizhipu_videoserver()
{
//     std::lock_guard<std::recursive_mutex> lock(dizhipu_videoserver::sMtServers);
//     sServers.push_back(this);
}

dizhipu_videoserver::~dizhipu_videoserver()
{
		logout();

//     std::lock_guard<std::recursive_mutex> lock(dizhipu_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

static void CALL_METHOD PosCallBack(long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser)
{
/*	bool bExp = false;*/
	__try
	{
		dizhipu_videoserver * pThis = (dizhipu_videoserver *)dwUser;
		if (pThis == NULL)
		{
			return;
		}
		//Mutex::ScopedLock lock(pThis->m_mtxPos);
		pThis->m_mtxPos.lock();
		map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosDownPlay.find(lPlayHandle);
		if (itr != pThis->m_mapPosDownPlay.end())
		{
			itr->second.iTotalSize = lTotalSize * 1024;
			itr->second.iCurSize = lDownLoadSize * 1024;
			itr->second.iPercent = ((float)lDownLoadSize/(float)lTotalSize)*100;
		}
		pThis->m_mtxPos.unlock();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("PosCallBack 捕获致命异常"));
/*		bExp = true;*/
		
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("PosCallBack exception"));
// 	}
	return;
}

IVideoServer* dizhipu_videoserver::clone()
{
//     dizhipu_videoserver *svr = new dizhipu_videoserver();
// 	memcpy(svr, this, sizeof(dizhipu_videoserver));
//     return svr;
	return NULL;
}

long loginTry(const char* IP, __int32 port, const char* user, const char* password, H264_DVR_DEVICEINFO* ptDevInfo, int *iError)
{
	long lhandle = 0;
/*	bool bExp = false;*/
	__try
	{
		lhandle = H264_DVR_Login((char*)IP, port,
			(char*)user, (char*)password,
			ptDevInfo, iError, 0);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pLogin"));
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pLogin"));
// 	}

	return lhandle;
}

bool GetDevConfigTry(long lhandle, char* channelName, DWORD *dwRetLen, int nWaitTime)
{
	bool bSuccess = false;
/*	bool bExp = false;*/
	__try
	{
		bSuccess = H264_DVR_GetDevConfig(lhandle, E_SDK_CONFIG_CHANNEL_NAME, -1,
			channelName, sizeof(SDK_ChannelNameConfigAll), dwRetLen, nWaitTime);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pGetConfig"));
// 	}

	return bSuccess;
}

bool dizhipu_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
//     if (0 < m_lLoginHandle && !logout())
// 	{
// 		g_log.AddLog(string("login 设备已登录，尝试反登陆失败"));
//         return false;
//     }

    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

	int iError = 0;
//     m_lLoginHandle = Api_DiZhiPu::Api().m_pLogin((char*)IP, port,
//                                    (char*)user,(char*)password,
//                                    &m_deviceInfo, &iError, 0);

// 	try
// 	{
// 		m_lLoginHandle = H264_DVR_Login((char*)IP, port,
// 			(char*)user, (char*)password,
// 			&m_deviceInfo, &iError, 0);
// 	}
// 	catch (...)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pLogin"));
// 	}

	m_lLoginHandle = loginTry((char*)IP, port, (char*)user, (char*)password, &m_deviceInfo, &iError);

    if (m_lLoginHandle == 0)
    {
		m_sLastError = GetLastErrorString();
		//g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

	SDK_ChannelNameConfigAll pChannelName;
	DWORD dwRetLen = 0;
	int nWaitTime = 1000;
	BOOL bSuccess = FALSE;

// 	bSuccess = Api_DiZhiPu::Api().m_pGetConfig(m_lLoginHandle, DiZhiPu::E_SDK_CONFIG_CHANNEL_NAME, -1,
// 		(char *)&pChannelName, sizeof(DiZhiPu::SDK_ChannelNameConfigAll), &dwRetLen, nWaitTime);

// 	try
// 	{
// 		bSuccess = H264_DVR_GetDevConfig(m_lLoginHandle, E_SDK_CONFIG_CHANNEL_NAME, -1,
// 			(char *)&pChannelName, sizeof(SDK_ChannelNameConfigAll), &dwRetLen, nWaitTime);
// 	}
// 	catch (...)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pGetConfig"));
// 	}

	bSuccess = GetDevConfigTry(m_lLoginHandle, (char *)&pChannelName, &dwRetLen, nWaitTime);

	if (!bSuccess || dwRetLen != sizeof(SDK_ChannelNameConfigAll))
	{
		m_sLastError = GetLastErrorString();
		//g_log.AddLog(string("login 获取通道失败，错误原因：") + m_sLastError);
		return false;
	}

	channels.clear();
	char szName[64+2];
	char *pChannelNameTmp = (char *)&pChannelName;
	//g_log.AddLog(string(pChannelNameTmp, 64));

	int i = 1;
	for ( ; i <= m_deviceInfo.byChanNum; i++)
	{
		ZeroMemory(szName, sizeof(szName));
		//memcpy(szName, pChannelNameTmp + (i - 1), 64);
		sprintf(szName, "CAM%02d", i);
		string strName = szName;
		channels.insert(std::make_pair(i, strName));
	}
	for ( ; i <= m_deviceInfo.iDigChannel + m_deviceInfo.byChanNum; i++)
	{
		ZeroMemory(szName, sizeof(szName));
		//memcpy(szName, pChannelNameTmp + (i - 1), 64);
		sprintf(szName, "CAM%02d", i);
		string strName = szName;
		channels.insert(std::make_pair(i, strName));
	}
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "login 通道个数:%d 数字通道个数:%d", m_deviceInfo.byChanNum, m_deviceInfo.iDigChannel);
	//g_log.AddLog(string(szLog));
    return true;
}

bool logoutTry(long lhandle)
{
	bool bSuccess = false;
/*	bool bExp = false;*/
	__try
	{
		bSuccess = H264_DVR_Logout(lhandle);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pLogout"));
		bSuccess = false;
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pLogout"));
// 	}

	return bSuccess;
}

bool dizhipu_videoserver::logout()
{
	bool bSuccess = false;
// 	__try
// 	{
// 		bSuccess = H264_DVR_Logout(m_lLoginHandle);
// 	}
// 	__except (EXCEPTION_EXECUTE_HANDLER)
// 	{
// 		//g_log.AddLog(string("EXCEPTION : Api_DiZhiPu::Api().m_pLogout"));
// 	}

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
	bool bRet = false;
/*	bool bExp = false;*/
	__try
	{
		bRet = H264_DVR_FindFile(lhandle, findInfo, szSend, MAX_SEARCH_COUNT, iMaxNum, 5 * 1000);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("GetRecordFileList 致命异常"));
		bRet = false;
/*		bExp = true;*/
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("GetRecordFileList 致命异常"));
// 	}

	return bRet;
}
bool dizhipu_videoserver::GetRecordFileList(std::vector<RecordFile>& files, std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{

    if (m_lLoginHandle <= 0)
    {
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("GetRecordFileList 请先登录"));
        return false;
    }

    if (timeStart >= timeEnd)
    {
		m_sLastError = "时间范围不对!";
		//g_log.AddLog(string("GetRecordFileList 时间范围不对"));
        return false;
    }

	files.clear();
	//m_mapArcItem.clear();

	std::vector<int>::iterator itr = channelVec.begin();
	for (; itr != channelVec.end(); itr++)
	{
		int nChannelId = *itr;

		H264_DVR_TIME stime;
		H264_DVR_TIME etime;
		tm STime;
		tm ETime;
		_localtime64_s(&STime, (const time_t*)&timeStart);
		_localtime64_s(&ETime, (const time_t*)&timeEnd);

		timeStdToDiZhiPu2(&STime, &stime);
		timeStdToDiZhiPu2(&ETime, &etime);
		char szTime[512];
		ZeroMemory(szTime, 512);
		sprintf(szTime, " s_time:%d-%02d-%02d %02d:%02d:%02d e_time:%d-%02d-%02d %02d:%02d:%02d channel:%d linkID:%d", stime.dwYear, stime.dwMonth, stime.dwDay,
			stime.dwHour, stime.dwMinute, stime.dwSecond,
			etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond, nChannelId, m_lLoginHandle);
		//g_log.AddLog(string("GetRecordFileList ") + string(szTime));

		char szTime64_s[64];
		ZeroMemory(szTime64_s, 64);
		char szTime64_e[64];
		ZeroMemory(szTime64_e, 64);
		_i64toa(timeStart, szTime64_s, 10);
		_i64toa(timeEnd, szTime64_e, 10);
		//g_log.AddLog(string("time64 s_time:") + string(szTime64_s) + string(" e_time:") + string(szTime64_e));

		H264_DVR_FINDINFO findInfo;
		ZeroMemory(&findInfo, sizeof(findInfo));
		findInfo.nChannelN0 = nChannelId - 1;
		findInfo.nFileType = 0;
		findInfo.startTime = stime;
		findInfo.endTime = etime;

		H264_DVR_FILE_DATA *szSend = new H264_DVR_FILE_DATA[MAX_SEARCH_COUNT];
		ZeroMemory(szSend, sizeof(H264_DVR_FILE_DATA)*MAX_SEARCH_COUNT);

		int iMaxNum = 0;
		bool bRet = false;
		bRet = getFileTry(m_lLoginHandle, &findInfo, szSend, MAX_SEARCH_COUNT, &iMaxNum);
		if (bRet == false)
		{
			continue;
		}
// 		try
// 		{
// 			bRet = H264_DVR_FindFile(m_lLoginHandle, &findInfo, szSend, MAX_SEARCH_COUNT, &iMaxNum, 5 * 1000);
// 		}
// 		catch (...)
// 		{
// 			g_log.AddLog(string("GetRecordFileList 致命异常"));
// 			continue;
// 		}

		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
			//g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
		if (iMaxNum == 0)
		{
			continue;;
		}

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
				//strcpy(szFileName, item.sFileName);
				m_mapArcItem.insert(make_pair(string(szFileName), item));

				timeDiZhiPuToStd(&item.stBeginTime, &sTm);
				timeDiZhiPuToStd(&item.stEndTime, &eTm);

				char szLog[1024];
				ZeroMemory(szLog, 1024);
				sprintf(szLog, "GetRecordFileList 文件名:%s 文件大小:%d", item.sFileName, item.size);
				//g_log.AddLog(string(szLog));

				info.channel = nChannelId/*item.ch*/;
				info.size = item.size * 1024;
				info.name = szFileName;
				info.beginTime = mktime(&sTm);
				info.endTime = mktime(&eTm);
				files.push_back(info);
			}
		}
	}
	return true;
}

bool downloadTry(long lhandle, H264_DVR_FILE_DATA *info, const char* saveFileName, long ptr, download_handle_t& hdl)
{
/*	bool bExp = false;*/
	__try
	{
		hdl = H264_DVR_GetFileByName(lhandle, info, (char *)saveFileName, PosCallBack, ptr, NULL);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		hdl = -1;
/*		bExp = true;*/
		//g_log.AddLog(string("downLoadByRecordFile 致命异常"));
		return false;
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("downLoadByRecordFile 致命异常"));
// 		return false;
// 	}
	return true;
}

bool dizhipu_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

	H264_DVR_FILE_DATA info;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<string, H264_DVR_FILE_DATA>::iterator itr = m_mapArcItem.find(file.name);
		if (itr == m_mapArcItem.end())
		{
			m_sLastError = "该文件不存在";
			//g_log.AddLog(string("downLoadByRecordFile 该文件不存在"));
			return false;
		}

		info = itr->second;
	}
	//g_log.AddLog(string("downLoadByRecordFile 文件名：") + saveFileName);
	bool bRet = downloadTry(m_lLoginHandle, &info, saveFileName, (long)this, hdl);
// 	try
// 	{
// 		hdl = H264_DVR_GetFileByName(m_lLoginHandle, &info, (char *)saveFileName, PosCallBack, (long)this, NULL);
// 	}
// 	catch (...)
// 	{
// 		hdl = -1;
// 		g_log.AddLog(string("downLoadByRecordFile 致命异常"));
// 		return false;
// 	}
	if (hdl <= 0)//modify by tsx 小于或等于0 迪智浦系列下载会挂掉的根源
	{
		m_sLastError = GetLastErrorString();
		//g_log.AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
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
/*	bool bExp = false;*/
	__try
	{
		playbackHandle = H264_DVR_PlayBackByName(lhandle, info, PosCallBack, NULL, ptr);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		playbackHandle = -1;
/*		bExp = true;*/
		//g_log.AddLog(string("downLoadByRecordFile 致命异常"));
		return false;
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("PlayBackByRecordFile 致命异常"));
// 		return false;
// 	}
	return true;
}

bool  dizhipu_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
        return false;
	}

	H264_DVR_FILE_DATA info;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<string, H264_DVR_FILE_DATA>::iterator itr = m_mapArcItem.find(file.name);
		if (itr == m_mapArcItem.end())
		{
			m_sLastError = "该文件不存在";
			//g_log.AddLog(string("PlayBackByRecordFile 该文件不存在"));
			return false;
		}

		info = itr->second;
	}
	info.hWnd = hwnd;
// 	try
// 	{
// 		playbackHandle = H264_DVR_PlayBackByName(m_lLoginHandle, &info, PosCallBack, NULL, (long)this);
// 	}
// 	catch (...)
// 	{
// 		playbackHandle = -1;
// 		g_log.AddLog(string("PlayBackByRecordFile 致命异常"));
// 		return false;
// 	}

	bool bRet = PlayBackloadTry(m_lLoginHandle, &info, (long)this, playbackHandle);
	if (bRet != true)
	{
		return false;
	}

	if (playbackHandle == 0)
	{
		m_sLastError = GetLastErrorString();
		//g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
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

	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "PlayBackByRecordFile start playbackHandle:%d", playbackHandle);
	//g_log.AddLog(string("StopPlayBack 开始停止播放"));
	//g_log.AddLog(string(szLog));


	return true;
}


bool SetPlayBackTry(__int64 playbackHandle, __int32 pos)
{
	bool bRet = false;
/*	bool bExp = false;*/
	__try
	{
		bRet = H264_DVR_PlayBackControl(playbackHandle, SDK_PLAY_BACK_SEEK_PERCENT, pos);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
/*		bExp = true;*/
		return false;
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("SetPlayBack 致命异常"));
// 		return false;
// 	}

	return bRet;
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
			//g_log.AddLog(string("SetPlayBack 该文件不存在"));
			return false;
		}
		file = itr->second;
	}
	//return FALSE != H264_DVR_PlayBackControl(playbackHandle, SDK_PLAY_BACK_SEEK_PERCENT, pos);

	return SetPlayBackTry(playbackHandle, pos);
}

bool playcontrolTry(__int64 playbackHandle)
{
	bool bRet = false;
/*	bool bExp = false;*/
	__try
	{
		bRet = H264_DVR_PlayBackControl(playbackHandle, SDK_PLAY_BACK_PAUSE, 0);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
/*		bExp = true;*/
		return false;
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("StopPlayBack Exception"));
// 		return false;
// 	}

	return bRet;
}

bool stopPlayTry(__int64 playbackHandle)
{
	bool bRet = false;
/*	bool bExp = false;*/
	__try
	{
		bRet = H264_DVR_StopPlayBack(playbackHandle);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
/*		bExp = true;*/
		return false;
	}

// 	if (bExp)
// 	{
// 		g_log.AddLog(string("StopPlayBack 致命异常"));
// 		return false;
// 	}

	return bRet;
}

bool dizhipu_videoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("StopPlayBack 请先登录"));
        return false;
    }
	if (mPause == 1)
	{
		//g_log.AddLog(string("StopPlayBack 开始暂停播放"));
		if (!playcontrolTry(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			//g_log.AddLog(string("StopPlayBack 暂停播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}
	else
	{
		char szLog[1024];
		ZeroMemory(szLog, 1024);
		sprintf(szLog, "StopPlayBack 开始停止播放 playbackHandle:%d", playbackHandle);
		//g_log.AddLog(string("StopPlayBack 开始停止播放"));
		//g_log.AddLog(string(szLog));

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
		//if (!Api_DiZhiPu::Api().m_pStopPlayBack(playbackHandle))
		bool bRet = false;
// 		try
// 		{
// 			bRet = H264_DVR_StopPlayBack(playbackHandle);
// 		}
// 		catch (...)
// 		{
// 			g_log.AddLog(string("StopPlayBack 致命异常"));
// 			return false;
// 		}
		bRet = stopPlayTry(playbackHandle);
		if (false == bRet)
		{
			m_sLastError = GetLastErrorString();
			//g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}

    return true;
}


bool stopDownloadTry(download_handle_t h)
{
	bool bRet = false;
	__try
	{
		bRet = H264_DVR_StopGetFile(h);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		//g_log.AddLog(string("stopDownload 致命异常"));
		return false;
	}

	return bRet;
}

bool dizhipu_videoserver::stopDownload(download_handle_t h)
{
	//g_log.AddLog(string("stopDownload 开始停止下载"));
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("stopDownload 请先登录"));
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
		//g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
	}

    return true;
}

bool dizhipu_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("getPlayBackPos 请先登录"));
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
	//g_log.AddLog(string("getPlayBackPos 找不到该回放"));
	return false;
}

bool dizhipu_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		//g_log.AddLog(string("getDownloadPos 请先登录"));
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
	//g_log.AddLog(string("getDownloadPos 找不到该下载"));
	*failed = true;
	return false;
}