#include "XingWang_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
Log g_log("XingWang_videoserver");

// #pragma comment(lib, "HCNetSDK.lib")

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryXingWang();
}

std::string GetLastErrorString()
{
    DWORD dwErr;
    dwErr = Api_XingWang::Api().m_pGetLastError();

    switch (dwErr)
    {
		case SN_DVR_ERROR_SUCESS: return "没有错误";
        case SN_DVR_PASSWORD_ERROR: return "密码错误";
		case SN_DVR_USERNAME_ERROR: return "用户名错误";
		case SN_DVR_ACCESS_DENIED: return "访问拒绝";
		case SN_DVR_MAX_DEVICE_CONNECTION: return "设备达到最大连接数";
		case SN_DVR_OUT_OF_MEMORY: return "内存不足";
		case SN_DVR_REQUEST_TIMEOUT: return "请求超时";
		case SN_DVR_INVALID_PARAMETER: return "无效参数";
		case SN_DVR_CONNECT_SERVER_FAILED: return "连接服务器失败";
		case SN_DVR_SEND_FAILED: return "发送失败";
		case SN_DVR_CREATE_SOCKET_ERROR: return "创建socket失败";
		case SN_DVR_ALREADY_LOGIN: return "已经登录";
		case SN_DVR_MAC_OR_IP_NOT_MATCH: return "MAC地址或者IP地址不匹配";
		case SN_DVR_VIDEO_PREVIEW_ERROR: return "视频流预览出错";
		case SN_DVR_LOCAL_PORT_INUSE: return "本地端口已经被使用";
		case SN_DVR_FILE_NO_FOUND: return "文件(查找目标)未找到";
		case SN_DVR_DEVICE_CONNECTION_LIMIT: return "设备连接受限";
		case SN_DVR_SET_PARAMETER_ERROR: return "设置参数失败";
		case SN_DVR_PARAMETER_DATA_ERROR: return "参数数据错误";
		case SN_DVR_NOT_SUPPORT: return "不支持";
		case SN_DVR_INNER_DATA_ERROR: return "内部数据错误";
		case SN_DVR_RESPONSE_ERROR_MSG: return "设备返回请求失败消息";
		case SN_DVR_CRUISE_POINT_EXISTING: return "关键点已经存在";
		case SN_DVR_GSMERROR_OPER: return "操作异常";
		case SN_DVR_GSMERROR_PARAM: return "参数异常";
		case SN_DVR_GSMERROR_EXP: return "设备异常";
		case SN_DVR_GSMERROR_NOSIM: return "无SIM卡";
		case SN_DVR_GSMERROR_NONET: return "未联网";
		case SN_DVR_GSMERROR_NONE: return "配置成功";
		case SN_DVR_GSMRESTARTING_IND: return "设备重启";
		case SN_DVR_CRUISE_POINT_INVALID: return "预置点无效";
		case SN_DVR_MOD_VOA_TK_ERR_PB: return "对讲请求错误码,正在回放";
		case SN_DVR_SQL_ERROR: return "数据库操作失败";
		case SN_DVR_CONDITION_ERROR: return "条件错误";
		case SN_DVR_NO_MATCH_RECORD: return "没有可匹配的记录";
		case SN_DVR_MAX_RECORD: return "达到记录上限，一般用于增加记录操作";
		case SN_DVR_PTZ_POINT_INVALID_ERR: return "关键点不存在";
		case SN_DVR_PTZ_PRESET_USE_ERR: return "预置点已使用";
		case SN_DVR_PTZ_PRESET_INVALID_ERR: return "预置点无效";
		case SN_DVR_PTZ_CRUISE_USE_ERR: return "正在巡航";
		case SN_DVR_INNER_COMPONENT_CLOSED: return "内部组件处于关闭状态";
		case SN_DVR_CREATE_AUDIO_OUTPUT_DEVICE_ERROR: return "创建音频输出设备失败";
		case SN_DVR_CREATE_AUDIO_INPUT_DEVICE_ERROR: return "创建音频输入设备失败";
		case SN_DVR_CRUISE_OPERATION_ERROR: return "巡航操作失败";
		case SN_DVR_DEVICE_BUSY: return "设备忙";
		case SN_DVR_NO_HARDDISK: return "设备无硬盘";
		case SN_DVR_HARDDISK_FULL: return "硬盘数据满";
		case SN_DVR_ALL_HARDDISK_NOT_FORMATED: return "所有硬盘均未格式化";
		case SN_DVR_ANY_HARDDISK_NOT_FORMATED: return "部分硬盘未格式化";
		case SN_DVR_HARDDISK_ERROR: return "硬盘状态异常";
		case SN_DVR_NO_3G_MODULAR: return "无3G模块";
		case SN_DVR_IS_TALKING: return "设备对讲中";
		case SN_NVR_DIGITALCHAN_UNCONFIG: return "NVR当前通道未配置";
		case SN_DVR_AUTHORITY_LOCK: return "权限到期";
		case SN_DVR_UNAUTHORITY: return "无权限";
		case SN_DVR_DATASIZE_TOOLAEAGE: return "文件太大";
		case SN_DVR_SERIALCOM_UNOPEN: return "串口未打开";
		case SN_DVR_SERIALCOM_OPEN_FAIL: return "串口打开失败";
		case SN_DVR_DEVICE_EXP: return "设备端异常";
		case SN_NVR_REMOTE_CONF_DEVICE_EXP: return "NVR远程配置设备端异常";
		case SN_DVR_PASS_OR_USER_ERROR: return "用户名或密码错误";
		case SN_DVR_TEST_CONNECT_ERROR: return "测试连接失败";
		case SN_DVR_TEST_LOGON_ERROR: return "登陆测试失败";
		case SN_DVR_ERR_RESET_PASSWORD: return "密码重置";
		case SN_NVR_NOT_SUPPORT: return "NVR设备不支持";
		//case SN_NVS_NOT_SUPPORT: return "NVS设备不支持";
		case SN_NVR_PTZ_OPT_FAILED: return "云台操作不成功";
		case SN_DVR_3G_CONNECT_FAILED: return "3G连接失败";
		case SN_DVR_STARTED_RECORD_ERROR: return "已经开始录像";
		case SN_DVR_NO_STARTED_RECORD_ERROR: return "未开始录像";
		case SN_DVR_UNKNOWN_ERROR: return "未知错误";
		//case SN_NVR_PTZ_OPT_FAILED: return "云台操作不成功";
		case SN_ERR_PTZ_PASDECODE_LOCALPTZ: return "被动解码下，操作本地云台错误";
		case SN_ERR_PTZ_PASDECODE_REMOTEPTZ: return "被动解码下，操作远程云台错误";
		case SN_ERR_PTZ_SWITCHSTATE_LOCALPTZ: return "轮询状态下，操作本地云台错误";
		case SN_ERR_PTZ_SWITCHSTATE_REMOTEPTZ: return "轮询状态下，操作远程云台错误";
		default: return "未知错误";
    }
}



CFactoryXingWang::CFactoryXingWang()
{
    init();
}

CFactoryXingWang::~CFactoryXingWang()
{
    clean();
}






bool CFactoryXingWang::init()
{
    if (!m_init)
    {

        int iRet = Api_XingWang::Api().m_pInit();
        //SN_DVR_SetConnectTime(1000, 30);
        //SN_DVR_SetReconnect(3000);
        //SN_DVR_SetDVRMessage()
		if (iRet < -1)
        {
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
			return false;
        }

		bool bRet = Api_XingWang::Api().m_pPlayInit();
		if (!bRet)
		{
			g_log.AddLog(string("初始化播放库失败："));
			return false;
		}

		m_init = true;
		g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


void CFactoryXingWang::clean()
{
    Api_XingWang::Api().m_pUninit();
}




IVideoServer* CFactoryXingWang::create()
{
    if (!init())
    {
        return NULL;
    }

    return new XingWang_videoserver();
}


// std::vector<XingWang_videoserver*> XingWang_videoserver::sServers;
// std::recursive_mutex XingWang_videoserver::sMtServers;

/*
 * 析构函数
 */
XingWang_videoserver::XingWang_videoserver()
{
//     std::lock_guard<std::recursive_mutex> lock(XingWang_videoserver::sMtServers);
//     sServers.push_back(this);
}

XingWang_videoserver::~XingWang_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(XingWang_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

IVideoServer* XingWang_videoserver::clone()
{
//     XingWang_videoserver *svr = new XingWang_videoserver();
// 	memcpy(svr, this, sizeof(XingWang_videoserver));
//     return svr;
	return NULL;
}

void CALLBACK PosCallBack(LONG lFilePlay, BYTE *pData, int size, void *pContext)
{
	XingWang_videoserver *pThis = (XingWang_videoserver *)pContext;
	if (!pThis)
	{
		return;
	}
	{
		Mutex::ScopedLock lock(pThis->m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosDownPlay.find(lFilePlay);
		if (itr != pThis->m_mapPosDownPlay.end())
		{
			itr->second.iCurSize += size;
			itr->second.iPercent = ((float)itr->second.iCurSize / (float)itr->second.iTotalSize) * 100;
		}
	}

	while (1){
		BOOL flag = Api_XingWang::Api().m_pPlayInputV(pThis->m_iPort, pData, size);
		if (flag == FALSE)
		{
			Sleep(5);
		}
		else{
			break;
		}
	}
}

bool XingWang_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels)
{
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d ip:%s port:%d user:%s psw:%s", m_lLoginHandle, IP, port, user, password);
	g_log.AddLog(string(szLog));
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

    m_lLoginHandle = Api_XingWang::Api().m_pLogin((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);

    if (m_lLoginHandle < 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

	if (m_deviceInfo.byChannelCount > 0)
	{
		for (int i = 0; i < m_deviceInfo.byChannelCount; i++)
		{
			char szName[16];
			ZeroMemory(szName, sizeof(szName));
			sprintf(szName, "通道%d", i + 1);
			channels[1 + i] = std::string(szName);
		}
	}
	else if(m_deviceInfo.byIPChannelCount > 0)
	{
		for (int i = 0; i < m_deviceInfo.byIPChannelCount; i++)
		{
			char szName[16];
			ZeroMemory(szName, sizeof(szName));
			sprintf(szName, "通道%d", i + 1);
			channels[1 + i] = std::string(szName);
		}
	}

    return true;
}

bool XingWang_videoserver::logout()
{
    if (m_lLoginHandle >= 0 && !Api_XingWang::Api().m_pLogout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}




bool XingWang_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
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

		XingWang::SN_DVR_FILECONDITION f;
		memset(&f, 0, sizeof(XingWang::SN_DVR_FILECONDITION));
		struct tm Tm;

		XingWang::SN_DVR_TIME struStartTime;
		_localtime64_s(&Tm, (const time_t*)&timeStart);
		struStartTime.dwYear = Tm.tm_year + 1900;
		struStartTime.dwMonth = Tm.tm_mon + 1;
		struStartTime.dwDay = Tm.tm_mday;
		struStartTime.dwHour = Tm.tm_hour;
		struStartTime.dwMinute = Tm.tm_min;
		struStartTime.dwSecond = Tm.tm_sec;

		XingWang::SN_DVR_TIME struStopTime;
		_localtime64_s(&Tm, (const time_t*)&timeEnd);
		struStopTime.dwYear = Tm.tm_year + 1900;
		struStopTime.dwMonth = Tm.tm_mon + 1;
		struStopTime.dwDay = Tm.tm_mday;
		struStopTime.dwHour = Tm.tm_hour;
		struStopTime.dwMinute = Tm.tm_min;
		struStopTime.dwSecond = Tm.tm_sec;

		XingWang::SN_DVR_TIME stime = struStartTime;
		XingWang::SN_DVR_TIME etime = struStopTime;

		char szTime[512];
		ZeroMemory(szTime, 512);
		sprintf(szTime, " s_time:%d-%02d-%02d %02d:%02d:%02d e_time:%d-%02d-%02d %02d:%02d:%02d channel:%d linkID:%d", stime.dwYear, stime.dwMonth, stime.dwDay,
			stime.dwHour, stime.dwMinute, stime.dwSecond,
			etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond, nChannelId, m_lLoginHandle);
		g_log.AddLog(string("GetRecordFileList ") + string(szTime));

		f.lSessionID = m_lLoginHandle;
		f.lChannel = nChannelId;
		f.dwFileType = 0;
		f.dwIsLocked = 0xff;
		f.tmStartTime = struStartTime;
		f.tmEndTime = struStopTime;

		XingWang::SN_DVR_FILEDATA findInfo;
		ZeroMemory(&findInfo, sizeof(findInfo));
		LONG lfind = Api_XingWang::Api().m_pFindFile(&f, &findInfo);

		if (lfind == FALSE)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
			continue;
		}

		int iFinds = 0;
		RecordFile rf;
		while (lfind > 0)
		{
			if (findInfo.dwFileSizeHigh > 0 || findInfo.dwFileSizeLow > 0)//获得视频文件必须大于0(测试中有发现文件大小为0情况,所以必须过滤掉改部分)
			{
				struct tm Tm;
				Tm.tm_year = findInfo.tmFileStartTime.dwYear - 1900;
				Tm.tm_mon = findInfo.tmFileStartTime.dwMonth - 1;
				Tm.tm_mday = findInfo.tmFileStartTime.dwDay;
				Tm.tm_hour = findInfo.tmFileStartTime.dwHour;
				Tm.tm_min = findInfo.tmFileStartTime.dwMinute;
				Tm.tm_sec = findInfo.tmFileStartTime.dwSecond;
				rf.beginTime = _mktime64(&Tm);

				Tm.tm_year = findInfo.tmFileEndTime.dwYear - 1900;
				Tm.tm_mon = findInfo.tmFileEndTime.dwMonth - 1;
				Tm.tm_mday = findInfo.tmFileEndTime.dwDay;
				Tm.tm_hour = findInfo.tmFileEndTime.dwHour;
				Tm.tm_min = findInfo.tmFileEndTime.dwMinute;
				Tm.tm_sec = findInfo.tmFileEndTime.dwSecond;
				rf.endTime = _mktime64(&Tm);

				stime = findInfo.tmFileStartTime;
				etime = findInfo.tmFileEndTime;
				ZeroMemory(szTime, 512);
				sprintf(szTime, "channel%d %d-%02d-%02d %02d-%02d-%02d %d-%02d-%02d %02d-%02d-%02d", nChannelId,
					stime.dwYear, stime.dwMonth, stime.dwDay,
					stime.dwHour, stime.dwMinute, stime.dwSecond,
					etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);

				rf.channel = nChannelId;
				rf.name = szTime;
				rf.size = findInfo.dwFileSizeLow;
				rf.setPrivateData(&findInfo, sizeof(XingWang::SN_DVR_FILEDATA));

// 				{
// 					Mutex::ScopedLock lock(m_mtx);
// 					m_mapArcItem.insert(std::make_pair(string(szTime), findInfo));
// 				}

				files.push_back(rf);
				iFinds++;

				char szSize[64];
				ZeroMemory(szSize, sizeof(szSize));
				_i64toa(rf.size, szSize, 10);

				char szLog[1024];
				ZeroMemory(szLog, 1024);
				sprintf(szLog, "GetRecordFileList 文件名:%s 文件大小:%s 文件时间:%s 通道:%d", findInfo.strFileName, szSize, szTime, nChannelId);
				g_log.AddLog(string(szLog));
			}
			else
			{
				::Sleep(20);
			}
			ZeroMemory(&findInfo, sizeof(findInfo));
			bool bRet = Api_XingWang::Api().m_pFindNext(lfind, &findInfo);
			if (!bRet)
			{
				break;
			}
		}

		if (FALSE == Api_XingWang::Api().m_pFindClose(lfind))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 关闭查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
	}

    return true;
}



bool XingWang_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

// 	XingWang::SN_DVR_FILEDATA info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, XingWang::SN_DVR_FILEDATA>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			char szLog[1024];
// 			ZeroMemory(szLog, 1024);
// 			sprintf(szLog, "downLoadByRecordFile 该文件不存在 mapSize:%d this:%d filename:%s", m_mapArcItem.size(), (int)this, file.name.c_str());
// 			g_log.AddLog(string(szLog));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}
//	g_log.AddLog(string("downLoadByRecordFile 文件名:") + info.strFileName + string(" 保存文件名:") + saveFileName);

	DeleteFileA(saveFileName);
	XingWang::SN_DVR_FILEDATA* pData = (XingWang::SN_DVR_FILEDATA *)file.getPrivateData();
	hdl = Api_XingWang::Api().m_pDownloadByFile(m_lLoginHandle, pData->strFileName, (char*)saveFileName);
	if (hdl <= 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
        return false;
    }
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "downLoadByRecordFile hdl:%d", hdl);
	g_log.AddLog(string(szLog));

	m_strDownFile = saveFileName;
	{
		stPos_DownPlay pos;
		pos.iTotalSize = file.size;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(make_pair(hdl, pos));
	}

    return true;
}


bool  XingWang_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
        return false;
    }

// 	XingWang::SN_DVR_FILEDATA info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, XingWang::SN_DVR_FILEDATA>::iterator itr = m_mapArcItem.find(file.name);
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
	XingWang::SN_DVR_TIME struBeginTime;
	_localtime64_s(&Tm, (const time_t*)&file.beginTime);
    struBeginTime.dwYear = Tm.tm_year + 1900;
    struBeginTime.dwMonth = Tm.tm_mon + 1;
    struBeginTime.dwDay = Tm.tm_mday;
    struBeginTime.dwHour = Tm.tm_hour;
    struBeginTime.dwMinute = Tm.tm_min;
    struBeginTime.dwSecond = Tm.tm_sec;

	XingWang::SN_DVR_TIME struEndTime;
	_localtime64_s(&Tm, (const time_t*)&file.endTime);
    struEndTime.dwYear = Tm.tm_year + 1900;
    struEndTime.dwMonth = Tm.tm_mon + 1;
    struEndTime.dwDay = Tm.tm_mday;
    struEndTime.dwHour = Tm.tm_hour;
    struEndTime.dwMinute = Tm.tm_min;
    struEndTime.dwSecond = Tm.tm_sec;

	XingWang::SN_DVR_TIME stime = struBeginTime;
	XingWang::SN_DVR_TIME etime = struEndTime;

	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "登录ID:%d 通道:%d 时间:%d-%02d-%02d %02d:%02d:%02d %d-%02d-%02d %02d:%02d:%02d", m_lLoginHandle, file.channel,
		stime.dwYear, stime.dwMonth, stime.dwDay, stime.dwHour, stime.dwMinute, stime.dwSecond,
		etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);
	g_log.AddLog(string(szLog));

	Api_XingWang::Api().ReloadPlayLib();
	m_iPort = 0;
	bool bRet = false;
	bRet = Api_XingWang::Api().m_pPlayGetPort((LONG *)&m_iPort);
	if (!bRet)
	{
		g_log.AddLog(string("PlayBackByRecordFile 播放库获取通道失败"));
		return false;
	}
	bRet = Api_XingWang::Api().m_pPlaySetMode(m_iPort, XingWang::EX_FILE_STREAM);
	if (!bRet)
	{
		g_log.AddLog(string("PlayBackByRecordFile 播放库设置播放模式失败"));
		return false;
	}
	bRet = Api_XingWang::Api().m_pPlayPlay(m_iPort, hwnd);
	if (!bRet)
	{
		g_log.AddLog(string("PlayBackByRecordFile 播放库开始播放失败"));
		return false;
	}
	XingWang::SN_DVR_FILEDATA* pData = (XingWang::SN_DVR_FILEDATA *)file.getPrivateData();
	playbackHandle = Api_XingWang::Api().m_pPlayBackByName(m_lLoginHandle, pData->strFileName, NULL, PosCallBack, this);
	//Api_XingWang::Api().m_pPlayBackByTime(m_lLoginHandle, file.channel, &struBeginTime, &struEndTime, hwnd);
	//playbackHandle = Api_XingWang::Api().m_pPlayBackByTime(m_lLoginHandle, info.nCh, &struBeginTime, &struEndTime, hwnd);
	if (playbackHandle <= 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
        return false;
	}
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "PlayBackByRecordFile playbackHandle:%d", playbackHandle);
	g_log.AddLog(string(szLog));

	{
		stPos_DownPlay pos;
		pos.iTotalSize = file.size;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(make_pair(playbackHandle, pos));
	}

    return true;
}

bool XingWang_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
	g_log.AddLog(string("SetPlayBack 不支持"));
	return FALSE;// != Api_XingWang::Api().m_pPlayBackControl(playbackHandle, SN_DVR_PLAYBYSLIDER, pos, NULL);
}

bool XingWang_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
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
		if (!Api_XingWang::Api().m_pPlayBackControl(playbackHandle, SN_DVR_PLAYPAUSE, 0, NULL))
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

		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.erase(playbackHandle);

		if (!Api_XingWang::Api().m_pStopPlayBack(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}

		bool bRet = Api_XingWang::Api().m_pPlayStop(m_iPort);
		if (!bRet)
		{
			g_log.AddLog(string("PlayBackByRecordFile 播放库停止播放失败"));
			return false;
		}
		bRet = Api_XingWang::Api().m_pPlayFreePort(m_iPort);
		if (!bRet)
		{
			g_log.AddLog(string("PlayBackByRecordFile 播放库释放通道失败"));
			return false;
		}
	}

    return true;
}

bool XingWang_videoserver::stopDownload(download_handle_t h)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("stopDownload 请先登录"));
		return false;
	}
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "stopDownload 开始停止下载 hdl:%d", h);
	g_log.AddLog(string(szLog));

	{
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.erase(h);
	}
    if (FALSE == Api_XingWang::Api().m_pStopDownload(h))
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool XingWang_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	g_log.AddLog(string("getPlayBackPos"));
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getPlayBackPos 请先登录"));
		return false;
	}
	{
		Mutex::ScopedLock lock(m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(playbackHandle);
		if (itr != m_mapPosDownPlay.end())
		{
			*pos = itr->second.iPercent;
			return true;
		}
		else
		{
			g_log.AddLog(string("getPlayBackPos 找不到该播放"));
			return false;
		}
	}

	return false;
}

bool XingWang_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
		return false;
	}
	int iPos = Api_XingWang::Api().m_pGetDownloadPos(h);
	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "getDownloadPos hdl:%d 当前进度:%d", h, iPos);
	g_log.AddLog(string(szLog));

	if (0 > iPos)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("getDownloadPos 获取进度失败， 错误原因:") + m_sLastError);
		*failed = true;
		return false;
	}
	
	{
		Mutex::ScopedLock lock(m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(h);
		if (itr != m_mapPosDownPlay.end())
		{
			itr->second.iCurSize = ((float)iPos / (float)1000) * (itr->second.iTotalSize);
			itr->second.iPercent = iPos/10;

			*totalSize = itr->second.iTotalSize;
			*currentSize = itr->second.iCurSize;
		}
		else
		{
			g_log.AddLog(string("getDownloadPos 找不到该下载"));
			*failed = true;
			return false;
		}
	}
	*failed = false;
	return true;
}