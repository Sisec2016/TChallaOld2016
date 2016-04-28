#include "DLDM_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
Log g_log("DLDM_videoserver");

// #pragma comment(lib, "HCNetSDK.lib")

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryDaLi_DM();
}

std::string GetLastErrorString()
{
    DWORD dwErr;
    dwErr = Api_DaLi_DM::Api().m_pGetLastError();

    switch (dwErr)
    {
        case NET_DLDVR_NOERROR: return "没有错误";
        case NET_DLDVR_PASSWORD_ERROR: return "用户名密码错误";
        case NET_DLDVR_NOENOUGHPRI: return "权限不足";
        case NET_DLDVR_NOINIT: return "没有初始化";
        case NET_DLDVR_CHANNEL_ERROR: return "通道号错误";
        case NET_DLDVR_OVER_MAXLINK: return "连接到DVR的客户端个数超过最大";
        case NET_DLDVR_VERSIONNOMATCH: return "版本不匹配";
        case NET_DLDVR_NETWORK_FAIL_CONNECT: return "连接服务器失败";
        case NET_DLDVR_NETWORK_SEND_ERROR: return "向服务器发送失败";
        case NET_DLDVR_NETWORK_RECV_ERROR: return "从服务器接收数据失败";
        case NET_DLDVR_NETWORK_RECV_TIMEOUT: return "从服务器接收数据超时";
        case NET_DLDVR_NETWORK_ERRORDATA: return "传送的数据有误";
        case NET_DLDVR_ORDER_ERROR: return "调用次序错误";
        case NET_DLDVR_OPERNOPERMIT: return "无此权限";
        case NET_DLDVR_COMMANDTIMEOUT: return "DVR命令执行超时";
        case NET_DLDVR_ERRORSERIALPORT: return "串口号错误";
        case NET_DLDVR_ERRORALARMPORT: return "报警端口错误";
        case NET_DLDVR_PARAMETER_ERROR: return "参数错误";
        case NET_DLDVR_CHAN_EXCEPTION: return "服务器通道处于错误状态";
        case NET_DLDVR_NODISK: return "没有硬盘";
        case NET_DLDVR_ERRORDISKNUM: return "硬盘号错误";
        case NET_DLDVR_DISK_FULL: return "服务器硬盘满";
        case NET_DLDVR_DISK_ERROR: return "服务器硬盘出错";
        case NET_DLDVR_NOSUPPORT: return "服务器不支持";
        case NET_DLDVR_BUSY: return "服务器忙";
        case NET_DLDVR_MODIFY_FAIL: return "服务器修改不成功";
        case NET_DLDVR_PASSWORD_FORMAT_ERROR: return "密码输入格式不正确";
        case NET_DLDVR_DISK_FORMATING: return "硬盘正在格式化，不能启动操作";
        case NET_DLDVR_DVRNORESOURCE: return "DVR资源不足";
        case NET_DLDVR_DVROPRATEFAILED: return "DVR操作失败";
        case NET_DLDVR_OPENHOSTSOUND_FAIL: return "打开PC声音失败";
        case NET_DLDVR_DVRVOICEOPENED: return "服务器语音对讲被占用";
        case NET_DLDVR_TIMEINPUTERROR: return "时间输入不正确";
        case NET_DLDVR_NOSPECFILE: return "回放时服务器没有指定的文件";
        case NET_DLDVR_CREATEFILE_ERROR: return "创建文件出错";
        case NET_DLDVR_FILEOPENFAIL: return "打开文件出错";
        case NET_DLDVR_OPERNOTFINISH: return "上次的操作还没有完成";
        case NET_DLDVR_GETPLAYTIMEFAIL: return "获取当前播放的时间出错";
        case NET_DLDVR_PLAYFAIL: return "播放出错";
        case NET_DLDVR_FILEFORMAT_ERROR: return "文件格式不正确";
        case NET_DLDVR_DIR_ERROR: return "路径错误";
        case NET_DLDVR_ALLOC_RESOUCE_ERROR: return "资源分配错误";
        case NET_DLDVR_AUDIO_MODE_ERROR: return "声卡模式错误";
        case NET_DLDVR_NOENOUGH_BUF: return "缓冲区太小";
        case NET_DLDVR_CREATESOCKET_ERROR: return "创建SOCKET出错";
        case NET_DLDVR_SETSOCKET_ERROR: return "设置SOCKET出错";
        case NET_DLDVR_MAX_NUM: return "个数达到最大";
        case NET_DLDVR_USERNOTEXIST: return "用户不存在";
        case NET_DLDVR_WRITEFLASHERROR: return "写FLASH出错";
        case NET_DLDVR_UPGRADEFAIL: return "DVR升级失败";
        case NET_DLDVR_CARDHAVEINIT: return "解码卡已经初始化过";
        case NET_DLDVR_PLAYERFAILED: return "播放器中错误";
        case NET_DLDVR_MAX_USERNUM: return "设备端用户数达到最大";
        case NET_DLDVR_GETLOCALIPANDMACFAIL: return "获得客户端的IP地址或物理地址失败";
        case NET_DLDVR_NOENCODEING: return "该通道没有编码";
        case NET_DLDVR_IPMISMATCH: return "IP地址不匹配";
        case NET_DLDVR_MACMISMATCH: return "MAC地址不匹配";
        case NET_DLDVR_UPGRADELANGMISMATCH: return "升级文件语言不匹配";
		default: return "未知错误";
    }
}



CFactoryDaLi_DM::CFactoryDaLi_DM()
{
    init();
}

CFactoryDaLi_DM::~CFactoryDaLi_DM()
{
    clean();
}






bool CFactoryDaLi_DM::init()
{
    if (!m_init)
    {

        m_init = Api_DaLi_DM::Api().m_pInit();
        //NET_DLDVR_SetConnectTime(1000, 30);
        //NET_DLDVR_SetReconnect(3000);
        //NET_DLDVR_SetDVRMessage()
        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
        }

		g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


void CFactoryDaLi_DM::clean()
{
    Api_DaLi_DM::Api().m_pUninit();
}




IVideoServer* CFactoryDaLi_DM::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new DaLi_DM_videoserver();
}


// std::vector<DaLi_DM_videoserver*> DaLi_DM_videoserver::sServers;
// std::recursive_mutex DaLi_DM_videoserver::sMtServers;

/*
 * 析构函数
 */
DaLi_DM_videoserver::DaLi_DM_videoserver()
{
	m_lLoginHandle = -1;
//     std::lock_guard<std::recursive_mutex> lock(DaLi_DM_videoserver::sMtServers);
//     sServers.push_back(this);
}

DaLi_DM_videoserver::~DaLi_DM_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(DaLi_DM_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

IVideoServer* DaLi_DM_videoserver::clone()
{
//     DaLi_DM_videoserver *svr = new DaLi_DM_videoserver();
// 	memcpy(svr, this, sizeof(DaLi_DM_videoserver));
//     return svr;
	return NULL;
}

DWORD WINAPI ThreadProcTimer(
	LPVOID lpParameter   // thread data
	)
{
	Sleep(2000);
	DaLi_DM_videoserver *pThis = (DaLi_DM_videoserver *)lpParameter;
	if (pThis == NULL)
	{
		return FALSE;
	}
	if (Api_DaLi_DM::Api().m_pHeartBeat)
	{
		Api_DaLi_DM::Api().m_pHeartBeat((char *)pThis->m_strIp.c_str(), pThis->m_iPort, pThis->m_lLoginHandle);
		g_log.AddLog(string("ThreadProcTimer"));
	}
	else
	{
		g_log.AddLog(string("ThreadProcTimer NULL"));
	}
}

bool DaLi_DM_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels)
{
//     if (0 > m_lLoginHandle && !logout())
//     {
//         return false;
//     }
	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

    m_lLoginHandle = Api_DaLi_DM::Api().m_pLogin((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d ip:%s port:%d user:%s psw:%s", m_lLoginHandle, IP, port, user, password);
	g_log.AddLog(string(szLog));
    if (m_lLoginHandle == -1)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

//     NET_DLDVR_DEVICECFG channelInfo;
// 	ZeroMemory(&channelInfo, sizeof(channelInfo));
//     DWORD returnBytes = 0;
    for (int i = 0; i < m_deviceInfo.byChanNum; i++)
    {
//         if (Api_DaLi_DM::Api().m_pGetConfig(m_lLoginHandle, NET_DLDVR_GET_DEVICECFG,
//                              m_deviceInfo.byStartChan + i, &channelInfo,
//                              sizeof(NET_DLDVR_PICCFG_EX), &returnBytes) != FALSE)
//         {
//             channels[m_deviceInfo.byStartChan + i] = std::string ((char *)channelInfo.sChanName);
//         }
//         else
//         {
//             channels[m_deviceInfo.byStartChan + i];
//         }
		char szChName[32];
		ZeroMemory(szChName, 32);
		sprintf(szChName, "通道%d", 1 + i);
		channels[1 + i] = std::string (szChName);
    }

	m_strIp = IP;
	m_iPort = port;
// 	CreateThread(NULL, 0, ThreadProcTimer, this, 0, NULL);

    return true;
}

bool DaLi_DM_videoserver::logout()
{
    if (m_lLoginHandle >= 0 && !Api_DaLi_DM::Api().m_pLogout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}




bool DaLi_DM_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    if (m_lLoginHandle < 0)
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

	if (channelVec.size() == 0)
	{
		return false;
	}
	int nChannelId = 0;
	auto itr = channelVec.begin();
	for (; itr != channelVec.end(); itr++)
	{
		int nChannelIdTmp = *itr;

		int iTmp = 1 << (nChannelIdTmp - 1);
		nChannelId |= iTmp;
	}

	struct tm Tm;

	NET_DLDVR_TIME struStartTime;
	_localtime64_s(&Tm, (const time_t*)&timeStart);
	struStartTime.dwYear = Tm.tm_year + 1900;
	struStartTime.dwMonth = Tm.tm_mon + 1;
	struStartTime.dwDay = Tm.tm_mday;
	struStartTime.dwHour = Tm.tm_hour;
	struStartTime.dwMinute = Tm.tm_min;
	struStartTime.dwSecond = Tm.tm_sec;

	NET_DLDVR_TIME struStopTime;
	_localtime64_s(&Tm, (const time_t*)&timeEnd);
	struStopTime.dwYear = Tm.tm_year + 1900;
	struStopTime.dwMonth = Tm.tm_mon + 1;
	struStopTime.dwDay = Tm.tm_mday;
	struStopTime.dwHour = Tm.tm_hour;
	struStopTime.dwMinute = Tm.tm_min;
	struStopTime.dwSecond = Tm.tm_sec;

	NET_DLDVR_TIME stime = struStartTime;
	NET_DLDVR_TIME etime = struStopTime;
// 	char szTime[512];
// 	ZeroMemory(szTime, 512);
// 	sprintf(szTime, " s_time:%d-%02d-%02d %02d:%02d:%02d e_time:%d-%02d-%02d %02d:%02d:%02d channel:%d linkID:%d", stime.dwYear, stime.dwMonth, stime.dwDay,
// 		stime.dwHour, stime.dwMinute, stime.dwSecond,
// 		etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond, nChannelId, m_lLoginHandle);
// 	g_log.AddLog(string("GetRecordFileList ") + string(szTime));

	LONG lfind = Api_DaLi_DM::Api().m_pFindFile(m_lLoginHandle, nChannelId, 0xff, &struStartTime, &struStopTime);
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "GetRecordFileList 登录句柄:%d 通道:%d 文件类型:%d 查找句柄:%d", m_lLoginHandle, nChannelId, 0xff, lfind);
	g_log.AddLog(string(szLog));
	if (lfind == -1)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
		return false;
	}
	NET_DLDVR_FIND_DATA findInfo;
	ZeroMemory(&findInfo, sizeof(findInfo));
	int iFinds = 0;

	LONG re = Api_DaLi_DM::Api().m_pFindNext(lfind, &findInfo);
	RecordFile rf;
	while (re == NET_DLDVR_ERROR_ISFINDING || re == NET_DLDVR_ERROR_FINDFILE_SUCCESS)
	{
		if (re == NET_DLDVR_ERROR_FINDFILE_SUCCESS && findInfo.dwFileSize > 0)//获得视频文件必须大于0(测试中有发现文件大小为0情况,所以必须过滤掉改部分)
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

			stime = findInfo.struStartTime;
			etime = findInfo.struStopTime;
// 			ZeroMemory(szTime, 512);
// 			sprintf(szTime, "channel%d %d-%02d-%02d %02d-%02d-%02d %d-%02d-%02d %02d-%02d-%02d", nChannelId,
// 				stime.dwYear, stime.dwMonth, stime.dwDay,
// 				stime.dwHour, stime.dwMinute, stime.dwSecond,
// 				etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);
// 			{
// 				Mutex::ScopedLock lock(m_mtx);
// 				m_mapArcItem.insert(std::make_pair(string(szTime), findInfo));
// 			}

			rf.channel = findInfo.dwChannel;
			rf.name = string(findInfo.sFileName);
			rf.size = findInfo.dwFileSize;
			rf.setPrivateData(&findInfo, sizeof(NET_DLDVR_FIND_DATA));
			files.push_back(rf);
			iFinds++;

// 			char szLog[1024];
// 			ZeroMemory(szLog, 1024);
// 			sprintf(szLog, "GetRecordFileList 文件名:%s 文件大小:%d 文件时间:%s 通道:%d", findInfo.sFileName, findInfo.dwFileSize, szTime, findInfo.dwChannel);
// 			g_log.AddLog(string(szLog));
		}
		else
		{
			::Sleep(20);
		}
		ZeroMemory(&findInfo, sizeof(findInfo));
		re = Api_DaLi_DM::Api().m_pFindNext(lfind, &findInfo);
	}

	if (FALSE == Api_DaLi_DM::Api().m_pFindClose(lfind))
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("GetRecordFileList 关闭查询录像失败，错误原因：") + m_sLastError);
		return true;
	}

    return true;
}



bool DaLi_DM_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 > m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

// 	NET_DLDVR_FIND_DATA info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, NET_DLDVR_FIND_DATA>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("downLoadByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}
	
	//g_log.AddLog(string("downLoadByRecordFile 文件名:") + string(info.sFileName) + string(" 保存文件名:") + saveFileName);pData->sFileName
	//hdl = Api_DaLi_DM::Api().m_pDownloadByFile(m_lLoginHandle, (char*)info.sFileName, (char*)saveFileName);
	NET_DLDVR_FIND_DATA* pData = (NET_DLDVR_FIND_DATA *)file.getPrivateData();
	hdl = Api_DaLi_DM::Api().m_pDownloadByFile(m_lLoginHandle, pData->sFileName, (char*)saveFileName);
    if (hdl < 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
        return false;
    }

//     if (!Api_DaLi_DM::Api().m_pPlayBackControl(hdl, NET_DLDVR_PLAYSTART, 0, NULL))
//     {
// 		Api_DaLi_DM::Api().m_pStopDownload(hdl);
//         m_sLastError = GetLastErrorString();
//         return false;
//     }

	{
		Mutex::ScopedLock lock(m_mtxDownload);
		m_mapDownload.insert(std::make_pair(hdl, file));
	}

    return true;
}


bool  DaLi_DM_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 > m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
        return false;
	}
	
// 	NET_DLDVR_FIND_DATA info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, NET_DLDVR_FIND_DATA>::iterator itr = m_mapArcItem.find(file.name);
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
	NET_DLDVR_TIME struBeginTime;
	_localtime64_s(&Tm, (const time_t*)&file.beginTime);
    struBeginTime.dwYear = Tm.tm_year + 1900;
    struBeginTime.dwMonth = Tm.tm_mon + 1;
    struBeginTime.dwDay = Tm.tm_mday;
    struBeginTime.dwHour = Tm.tm_hour;
    struBeginTime.dwMinute = Tm.tm_min;
    struBeginTime.dwSecond = Tm.tm_sec;

	NET_DLDVR_TIME struEndTime;
	_localtime64_s(&Tm, (const time_t*)&file.endTime);
    struEndTime.dwYear = Tm.tm_year + 1900;
    struEndTime.dwMonth = Tm.tm_mon + 1;
    struEndTime.dwDay = Tm.tm_mday;
    struEndTime.dwHour = Tm.tm_hour;
    struEndTime.dwMinute = Tm.tm_min;
    struEndTime.dwSecond = Tm.tm_sec;

	NET_DLDVR_TIME stime = struBeginTime;
	NET_DLDVR_TIME etime = struEndTime;
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d 通道:%d 时间:%d-%02d-%02d %02d:%02d:%02d %d-%02d-%02d %02d:%02d:%02d", m_lLoginHandle, file.channel,
		stime.dwYear, stime.dwMonth, stime.dwDay, stime.dwHour, stime.dwMinute, stime.dwSecond,
		etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);
	g_log.AddLog(string(szLog));
	//playbackHandle = Api_DaLi_DM::Api().m_pPlayBackByTime(m_lLoginHandle, file.channel, &struBeginTime, &struEndTime, hwnd);
	
	//playbackHandle = Api_DaLi_DM::Api().m_pPlayBackByName(m_lLoginHandle, info.sFileName, hwnd);
	NET_DLDVR_FIND_DATA* pData = (NET_DLDVR_FIND_DATA *)file.getPrivateData();
	playbackHandle = Api_DaLi_DM::Api().m_pPlayBackByName(m_lLoginHandle, pData->sFileName, hwnd);
    if (playbackHandle < 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
        return false;
    }

    if (!Api_DaLi_DM::Api().m_pPlayBackControl(playbackHandle, NET_DLDVR_PLAYSTART, 0, NULL))
    {
		Api_DaLi_DM::Api().m_pStopPlayBack(playbackHandle);
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 开始播放录像失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool DaLi_DM_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
	g_log.AddLog(string("SetPlayBack"));
	if (FALSE == Api_DaLi_DM::Api().m_pPlayBackControl(playbackHandle, NET_DLDVR_PLAYSETPOS, pos, NULL))
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("SetPlayBack 拖动播放失败，错误原因：") + m_sLastError);
		return false;
    }
	return true;
}

bool DaLi_DM_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (0 > m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("StopPlayBack 请先登录"));
        return false;
    }

	if (mPause == 1)
	{
		g_log.AddLog(string("StopPlayBack 开始暂停播放"));
		if (!Api_DaLi_DM::Api().m_pPlayBackControl(playbackHandle, NET_DLDVR_PLAYPAUSE, 0, NULL))
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
		if (!Api_DaLi_DM::Api().m_pStopPlayBack(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}

    return true;
}

bool DaLi_DM_videoserver::stopDownload(download_handle_t h)
{
	if (0 > m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("stopDownload 请先登录"));
		return false;
	}
	g_log.AddLog(string("stopDownload 开始停止下载"));

	{
		Mutex::ScopedLock lock(m_mtxDownload);
		m_mapDownload.erase(h);
	}
    if (FALSE == Api_DaLi_DM::Api().m_pStopDownload(h))
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool DaLi_DM_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	g_log.AddLog(string("getPlayBackPos"));
// 	return false;
	if (0 > m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getPlayBackPos 请先登录"));
		return false;
	}
	if (!Api_DaLi_DM::Api().m_pPlayBackControl(playbackHandle, NET_DLDVR_PLAYGETPOS, 0, (DWORD *)pos))
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("getPlayBackPos 获取播放进度失败"));
		return false;
	}
	return true;
}

bool DaLi_DM_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 > m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
		return false;
	}

	RecordFile file;
	{
		Mutex::ScopedLock lock(m_mtxDownload);
		map<long, RecordFile>::iterator itr = m_mapDownload.find(h);
		if (itr == m_mapDownload.end())
		{
			m_sLastError = "找不到该文件";
			g_log.AddLog(string("getDownloadPos 找不到该文件"));
			*failed = true;
			return false;
		}
		file = itr->second;
	}
	*totalSize = file.size;

	int iPos = Api_DaLi_DM::Api().m_pGetDownloadPos(h);
	if (FALSE == iPos)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("getDownloadPos 获取下载进度失败"));
		*failed = true;
		return false;
	}
	*currentSize = ((float)iPos / (float)100) * (*totalSize);
	*failed = false;
	return true;
}
