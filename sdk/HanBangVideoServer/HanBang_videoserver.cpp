#include "HanBang_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
Log g_log("HanBang_videoserver");

// #pragma comment(lib, "HCNetSDK.lib")

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryHanBang();
}

std::string GetLastErrorString()
{
    DWORD dwErr;
    dwErr = Api_HanBang::Api().m_pGetLastError();

    switch (dwErr)
    {
        case HB_SDVR_NOERROR: return "没有错误";
        case HB_SDVR_PASSWORD_ERROR: return "用户名密码错误";
        case HB_SDVR_NOENOUGHPRI: return "权限不足";
        case HB_SDVR_NOINIT: return "没有初始化";
        case HB_SDVR_CHANNEL_ERROR: return "通道号错误";
        case HB_SDVR_OVER_MAXLINK: return "连接到DVR的客户端个数超过最大";
        case HB_SDVR_VERSIONNOMATCH: return "版本不匹配";
        case HB_SDVR_NETWORK_FAIL_CONNECT: return "连接服务器失败";
        case HB_SDVR_NETWORK_SEND_ERROR: return "向服务器发送失败";
        case HB_SDVR_NETWORK_RECV_ERROR: return "从服务器接收数据失败";
        case HB_SDVR_NETWORK_RECV_TIMEOUT: return "从服务器接收数据超时";
        case HB_SDVR_NETWORK_ERRORDATA: return "传送的数据有误";
        case HB_SDVR_ORDER_ERROR: return "调用次序错误";
        case HB_SDVR_OPERNOPERMIT: return "无此权限";
        case HB_SDVR_COMMANDTIMEOUT: return "DVR命令执行超时";
        case HB_SDVR_ERRORSERIALPORT: return "串口号错误";
        case HB_SDVR_ERRORALARMPORT: return "报警端口错误";
        case HB_SDVR_PARAMETER_ERROR: return "参数错误";
        case HB_SDVR_CHAN_EXCEPTION: return "服务器通道处于错误状态";
        case HB_SDVR_NODISK: return "没有硬盘";
        case HB_SDVR_ERRORDISKNUM: return "硬盘号错误";
        case HB_SDVR_DISK_FULL: return "服务器硬盘满";
        case HB_SDVR_DISK_ERROR: return "服务器硬盘出错";
        case HB_SDVR_NOSUPPORT: return "服务器不支持";
        case HB_SDVR_BUSY: return "服务器忙";
        case HB_SDVR_MODIFY_FAIL: return "服务器修改不成功";
        case HB_SDVR_PASSWORD_FORMAT_ERROR: return "密码输入格式不正确";
        case HB_SDVR_DISK_FORMATING: return "硬盘正在格式化，不能启动操作";
        case HB_SDVR_DVRNORESOURCE: return "DVR资源不足";
        case HB_SDVR_DVROPRATEFAILED: return "DVR操作失败";
        case HB_SDVR_OPENHOSTSOUND_FAIL: return "打开PC声音失败";
        case HB_SDVR_DVRVOICEOPENED: return "服务器语音对讲被占用";
        case HB_SDVR_TIMEINPUTERROR: return "时间输入不正确";
        case HB_SDVR_NOSPECFILE: return "回放时服务器没有指定的文件";
        case HB_SDVR_CREATEFILE_ERROR: return "创建文件出错";
        case HB_SDVR_FILEOPENFAIL: return "打开文件出错";
        case HB_SDVR_OPERNOTFINISH: return "上次的操作还没有完成";
        case HB_SDVR_GETPLAYTIMEFAIL: return "获取当前播放的时间出错";
        case HB_SDVR_PLAYFAIL: return "播放出错";
        case HB_SDVR_FILEFORMAT_ERROR: return "文件格式不正确";
        case HB_SDVR_DIR_ERROR: return "路径错误";
        case HB_SDVR_ALLOC_RESOUCE_ERROR: return "资源分配错误";
        case HB_SDVR_AUDIO_MODE_ERROR: return "声卡模式错误";
        case HB_SDVR_NOENOUGH_BUF: return "缓冲区太小";
        case HB_SDVR_CREATESOCKET_ERROR: return "创建SOCKET出错";
        case HB_SDVR_SETSOCKET_ERROR: return "设置SOCKET出错";
        case HB_SDVR_MAX_NUM: return "个数达到最大";
        case HB_SDVR_USERNOTEXIST: return "用户不存在";
        case HB_SDVR_WRITEFLASHERROR: return "写FLASH出错";
        case HB_SDVR_UPGRADEFAIL: return "DVR升级失败";
        case HB_SDVR_CARDHAVEINIT: return "解码卡已经初始化过";
        case HB_SDVR_PLAYERFAILED: return "播放器中错误";
        case HB_SDVR_MAX_USERNUM: return "设备端用户数达到最大";
        case HB_SDVR_GETLOCALIPANDMACFAIL: return "获得客户端的IP地址或物理地址失败";
        case HB_SDVR_NOENCODEING: return "该通道没有编码";
        case HB_SDVR_IPMISMATCH: return "IP地址不匹配";
        case HB_SDVR_MACMISMATCH: return "MAC地址不匹配";
        case HB_SDVR_UPGRADELANGMISMATCH: return "升级文件语言不匹配";
        case HB_SDVR_USERISALIVE: return "用户已登陆";
        case HB_SDVR_UNKNOWNERROR: return "未知错误";
        case HB_SDVR_KEYVERIFYFAIL: return "密钥验证失败";
        case HB_SDVR_IPERR: return "IP地址不匹配";
        case HB_SDVR_MACERR: return "MAC地址不匹配";
        case HB_SDVR_PSWERR: return "用户名密码错误";
        case HB_SDVR_USERERR: return "用户名密码错误";
        case HB_SDVR_USERISFULL: return "登录用户个数超过限制";
        case NO_PERMISSION: return "用户没有权限";
		default: return "未知错误";
    }
}



CFactoryHanBang::CFactoryHanBang()
{
    init();
}

CFactoryHanBang::~CFactoryHanBang()
{
    clean();
}






bool CFactoryHanBang::init()
{
    if (!m_init)
    {

        m_init = Api_HanBang::Api().m_pInit();
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


void CFactoryHanBang::clean()
{
    Api_HanBang::Api().m_pUninit();
}




IVideoServer* CFactoryHanBang::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new HanBang_videoserver();
}


// std::vector<HanBang_videoserver*> HanBang_videoserver::sServers;
// std::recursive_mutex HanBang_videoserver::sMtServers;

/*
 * 析构函数
 */
HanBang_videoserver::HanBang_videoserver()
{
    m_lLoginHandle = 0;
//     std::lock_guard<std::recursive_mutex> lock(HanBang_videoserver::sMtServers);
//     sServers.push_back(this);
}

HanBang_videoserver::~HanBang_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(HanBang_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

IVideoServer* HanBang_videoserver::clone()
{
//     HanBang_videoserver *svr = new HanBang_videoserver();
// 	memcpy(svr, this, sizeof(HanBang_videoserver));
//     return svr;
	return NULL;
}

bool HanBang_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels)
{
    if (m_lLoginHandle > 0 && !logout())
    {
        g_log.AddLog("login out failed");
        return false;
    }
    else{

    }
	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

    m_lLoginHandle = Api_HanBang::Api().m_pLogin((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d ip:%s port:%d user:%s psw:%s", m_lLoginHandle, IP, port, user, password);
	g_log.AddLog(string(szLog));

    if (m_lLoginHandle <= 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

    for (int i = 0; i < m_deviceInfo.byChanNum; i++)
    {
        channels[/*m_deviceInfo.byStartChan*/1 + i] = std::string ((char *)m_deviceInfo.sChanName[i]);
    }

	ZeroMemory(szLog, 1024);
	sprintf(szLog, "login 通道个数:%d", m_deviceInfo.byChanNum);
	g_log.AddLog(string(szLog));
    return true;
}

bool HanBang_videoserver::logout()
{
    g_log.AddLog("videoserver::logout");
    if (m_lLoginHandle > 0 && !Api_HanBang::Api().m_pLogout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }
    m_lLoginHandle = 0;
    return true;
}

void changeToHBTime(__time64_t from, HanBang::HB_SDVR_TIME& to){
    struct tm Tm;
    _localtime64_s(&Tm, (const time_t*)&from);
    to.dwYear = Tm.tm_year + 1900;
    to.dwMonth = Tm.tm_mon + 1;
    to.dwDay = Tm.tm_mday;
    to.dwHour = Tm.tm_hour;
    to.dwMinute = Tm.tm_min;
    to.dwSecond = Tm.tm_sec;
}


bool HanBang_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
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

		HanBang::HB_SDVR_FILEGETCOND f;
		memset(&f, 0, sizeof(HanBang::HB_SDVR_FILEGETCOND));

		HanBang::HB_SDVR_TIME struStartTime;
        changeToHBTime(timeStart, struStartTime);

		HanBang::HB_SDVR_TIME struStopTime;
        changeToHBTime(timeEnd, struStopTime);

		LONG lfind = Api_HanBang::Api().m_pFindFile(m_lLoginHandle, nChannelId, MFS_REC_TYPE_ALL, &struStartTime, &struStopTime);

		if (lfind == FALSE)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
		HanBang::HB_SDVR_FIND_DATA findInfo;
		ZeroMemory(&findInfo, sizeof(findInfo));
		int iFinds = 0;

		LONG re = Api_HanBang::Api().m_pFindNext(lfind, &findInfo);
		RecordFile rf;
		while (re == HB_SDVR_ISFINDING || re == HB_SDVR_FILE_SUCCESS)
		{
			if (re == HB_SDVR_FILE_SUCCESS && findInfo.dwFileSize > 0)//获得视频文件必须大于0(测试中有发现文件大小为0情况,所以必须过滤掉改部分)
			{
				struct tm Tm;
				Tm.tm_year = findInfo.struStartTime.dwYear - 1900;
				Tm.tm_mon = findInfo.struStartTime.dwMonth - 1;
				Tm.tm_mday = findInfo.struStartTime.dwDay;
				Tm.tm_hour = findInfo.struStartTime.dwHour;
				Tm.tm_min = findInfo.struStartTime.dwMinute;
				Tm.tm_sec = findInfo.struStartTime.dwSecond;
				rf.beginTime = _mktime64(&Tm);

				Tm.tm_year = findInfo.struStopTime.dwYear - 1900;
				Tm.tm_mon = findInfo.struStopTime.dwMonth - 1;
				Tm.tm_mday = findInfo.struStopTime.dwDay;
				Tm.tm_hour = findInfo.struStopTime.dwHour;
				Tm.tm_min = findInfo.struStopTime.dwMinute;
				Tm.tm_sec = findInfo.struStopTime.dwSecond;
				rf.endTime = _mktime64(&Tm);

				rf.channel = nChannelId;
				rf.name = findInfo.sFileName;
				rf.size = findInfo.dwFileSize;
				rf.setPrivateData(&findInfo, sizeof(HanBang::HB_SDVR_FIND_DATA));

				files.push_back(rf);
				iFinds++;
			}
			else
			{
				::Sleep(20);
			}

			ZeroMemory(&findInfo, sizeof(findInfo));
			re = Api_HanBang::Api().m_pFindNext(lfind, &findInfo);
		}


		if (-1 == re)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 01 查询录像失败，错误原因：") + m_sLastError);
			continue;
		}

		if (FALSE == Api_HanBang::Api().m_pFindClose(lfind))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 关闭查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
	}

    return true;
}



bool HanBang_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }
    
    if (m_mapDownInfo.size() > 0)
    {
        g_log.AddLog(string("m_mapDownInfo.size()"));
        return false;
    }

    HanBang::HB_SDVR_TIME struStartTime;
    changeToHBTime(file.beginTime, struStartTime);

    HanBang::HB_SDVR_TIME struStopTime;
    changeToHBTime(file.endTime, struStopTime);

    g_log.AddLog(QString("m_lLoginHandle:%1, file.channel:%2, struStartTime:%3,%4,%5,%6,%7,%8")
        .arg(m_lLoginHandle).arg(file.channel).arg(struStartTime.dwYear).arg(struStartTime.dwMonth).arg(struStartTime.dwDay)
        .arg(struStartTime.dwHour).arg(struStartTime.dwMinute).arg(struStartTime.dwSecond));
	hdl = Api_HanBang::Api().m_pDownloadByFile(m_lLoginHandle, (char *)file.name.c_str(), (char *)saveFileName);
	//<<<<<<<<<add by zhangyaofa 2016/6/8
	if (!hdl)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("NET_DVR_GetFileBy failed : ") + m_sLastError + " 文件：" + saveFileName);
		hdl = Api_HanBang::Api().m_pDownloadByTime(m_lLoginHandle, file.channel, &struStartTime, &struStopTime, (char *)saveFileName);		
	}
	//>>>>>>>>>>add ebd
    if (!hdl)
    {
        m_sLastError = GetLastErrorString();
        g_log.AddLog(string("m_pDownloadByFile 错误原因：") + m_sLastError);
    }
    else
    {
        m_mapDownInfo[hdl] = file;
    }
    return hdl;
}


bool  HanBang_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
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
// 	HanBang::HB_SDVR_FIND_DATA info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, HanBang::HB_SDVR_FIND_DATA>::iterator itr = m_mapArcItem.find(file.name);
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
	HanBang::HB_SDVR_TIME struBeginTime;
	_localtime64_s(&Tm, (const time_t*)&file.beginTime);
    struBeginTime.dwYear = Tm.tm_year + 1900;
    struBeginTime.dwMonth = Tm.tm_mon + 1;
    struBeginTime.dwDay = Tm.tm_mday;
    struBeginTime.dwHour = Tm.tm_hour;
    struBeginTime.dwMinute = Tm.tm_min;
    struBeginTime.dwSecond = Tm.tm_sec;
// 	char szTime[512];
// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d", 
// 		Tm.tm_year, Tm.tm_mon, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);
// 	g_log.AddLog(string(szTime));

	HanBang::HB_SDVR_TIME struEndTime;
	_localtime64_s(&Tm, (const time_t*)&file.endTime);
    struEndTime.dwYear = Tm.tm_year + 1900;
    struEndTime.dwMonth = Tm.tm_mon + 1;
    struEndTime.dwDay = Tm.tm_mday;
    struEndTime.dwHour = Tm.tm_hour;
    struEndTime.dwMinute = Tm.tm_min;
    struEndTime.dwSecond = Tm.tm_sec;

// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d", 
// 		Tm.tm_year, Tm.tm_mon, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);
// 	g_log.AddLog(string(szTime));

	HanBang::HB_SDVR_TIME stime = struBeginTime;
	HanBang::HB_SDVR_TIME etime = struEndTime;

// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, "%d-%02d-%02d %02d-%02d-%02d %d-%02d-%02d %02d-%02d-%02d", stime.dwYear, stime.dwMonth, stime.dwDay,
// 		stime.dwHour, stime.dwMinute, stime.dwSecond,
// 		etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);
// 	g_log.AddLog(string(szTime));
// 	char szTmp[64];
// 	ZeroMemory(szTmp, 64);
// 	sprintf(szTmp, "~%02d", info.nCh);
// 	string strFileName = info.sFileName;
// 	strFileName.insert(19, szTmp);
// 	g_log.AddLog(string("PlayBackByRecordFile 文件名:") + strFileName);
// 	char szLog[1024];
// 	ZeroMemory(szLog, 1024);
// 	sprintf(szLog, "登录ID:%d 通道:%d 时间:%d-%02d-%02d %02d:%02d:%02d %d-%02d-%02d %02d:%02d:%02d", m_lLoginHandle, info.nCh,
// 		stime.dwYear, stime.dwMonth, stime.dwDay, stime.dwHour, stime.dwMinute, stime.dwSecond,
// 		etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);
// 	g_log.AddLog(string(szLog));

	//playbackHandle = Api_HanBang::Api().m_pPlayBackByName(m_lLoginHandle, (char *)strFileName.c_str(), hwnd);
	//Api_HanBang::Api().m_pPlayBackByTime(m_lLoginHandle, file.channel, &struBeginTime, &struEndTime, hwnd);
	//playbackHandle = Api_HanBang::Api().m_pPlayBackByTime(m_lLoginHandle, info.nCh, &struBeginTime, &struEndTime, hwnd);
	playbackHandle = Api_HanBang::Api().m_pPlayBackByTime(m_lLoginHandle, file.channel, &struBeginTime, &struEndTime, hwnd);
	if (playbackHandle == FALSE)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
        return false;
    }

//     if (!Api_HanBang::Api().m_pPlayBackControl(playbackHandle, HB_SDVR_PLAYSTART, 0, NULL))
//     {
// 		m_sLastError = GetLastErrorString();
// 		g_log.AddLog(string("PlayBackByRecordFile 01 播放录像失败，错误原因：") + m_sLastError);
//         return false;
//     }

    return true;
}

bool HanBang_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
	g_log.AddLog(string("SetPlayBack"));
    return FALSE != Api_HanBang::Api().m_pPlayBackControl(playbackHandle, HB_SDVR_PLAYBYSLIDER, pos, NULL);
}

bool HanBang_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
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
		if (!Api_HanBang::Api().m_pPlayBackControl(playbackHandle, HB_SDVR_PLAYPAUSE, 0, NULL))
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
		if (!Api_HanBang::Api().m_pStopPlayBack(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}

    return true;
}

bool HanBang_videoserver::stopDownload(download_handle_t h)
{
    m_mapDownInfo.clear();
    return true;
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("stopDownload 请先登录"));
		return false;
	}
	g_log.AddLog(string("stopDownload 开始停止下载"));

	{
		Mutex::ScopedLock lock(m_mtxdown);
		auto itr = m_mapDownInfo.find(h);
		if (itr == m_mapDownInfo.end())
		{
			m_sLastError = "该文件不存在";
			g_log.AddLog(string("getDownloadPos 该文件不存在"));
			return false;
		}
		m_mapDownInfo.erase(itr);
	}
    if (FALSE == Api_HanBang::Api().m_pStopDownload(h))
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool HanBang_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	g_log.AddLog(string("getPlayBackPos"));
    return false;
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
		return false;
	}
	BOOL bRet = Api_HanBang::Api().m_pPlayBackControl(playbackHandle, HB_SDVR_PLAYGETPOS, NULL, (DWORD *)pos);
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

bool HanBang_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
    
    if (m_mapDownInfo.find(h) != m_mapDownInfo.end())
    {
        *totalSize = m_mapDownInfo[h].size;
        *currentSize = Api_HanBang::Api().m_pGetDownloadBytesSize(h);
        *failed = (*currentSize < 0);
    }
    else
    {
        return false;
    }

    if (*totalSize <= *currentSize)
    {
        m_mapDownInfo.clear();
    }

    return true;
}