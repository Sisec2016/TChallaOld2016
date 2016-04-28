#include "WSD_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
Log g_log("WSD_videoserver");

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryWSD();
}

static std::string GetLastErrorString()
{
    DWORD dwError;
	dwError = Api_WSD::Api().ZLNET_GetLastError();
// 	char erch[128] = { 0 };
// 	sprintf_s(erch, "dwError:%d", dwError);
// 	g_log.AddLog(string(erch));
    switch (dwError)
    {
		case ZLNET_ERROR: return "未知错误";
		case ZLNET_SYSTEM_ERROR: return "Windows系统出错";
		case ZLNET_NETWORK_ERROR: return "网络错误，可能是因为网络超时";
		case ZLNET_DEV_VER_NOMATCH: return "设备协议不匹配";
		case ZLNET_INVALID_HANDLE: return "句柄无效";
		case ZLNET_OPEN_CHANNEL_ERROR: return "打开通道失败";
		case ZLNET_CLOSE_CHANNEL_ERROR: return "关闭通道失败";
		case ZLNET_ILLEGAL_PARAM: return "用户参数不合法";
		case ZLNET_SDK_INIT_ERROR: return "SDK初始化出错";
		case ZLNET_SDK_UNINIT_ERROR: return "SDK清理出错";
		case ZLNET_RENDER_OPEN_ERROR: return "申请render资源出错";
		case ZLNET_DEC_OPEN_ERROR: return "打开解码库出错";
		case ZLNET_DEC_CLOSE_ERROR: return "关闭解码库出错";
		case ZLNET_MULTIPLAY_NOCHANNEL: return "多画面预览中检测到通道数为0";
		case ZLNET_TALK_INIT_ERROR: return "录音库初始化失败";
		case ZLNET_TALK_NOT_INIT: return "录音库未经初始化";
		case ZLNET_TALK_SENDDATA_ERROR: return "发送音频数据出错";
		case ZLNET_REAL_ALREADY_SAVING: return "实时数据已经处于保存状态";
		case ZLNET_NOT_SAVING: return "未保存实时数据";
		case ZLNET_OPEN_FILE_ERROR: return "打开文件出错";
		case ZLNET_PTZ_SET_TIMER_ERROR: return "启动云台控制定时器失败";
		case ZLNET_RETURN_DATA_ERROR: return "对返回数据的校验出错";
		case ZLNET_INSUFFICIENT_BUFFER: return "没有足够的缓存";
		case ZLNET_NOT_SUPPORTED: return "当前SDK未支持该功能";
		case ZLNET_NO_RECORD_FOUND: return "查询不到录象";
		case ZLNET_NOT_AUTHORIZED: return "无操作权限";
		case ZLNET_NOT_NOW: return "暂时无法执行";
		case ZLNET_NO_TALK_CHANNEL: return "未发现对讲通道";
		case ZLNET_NO_AUDIO: return "未发现音频";
		case ZLNET_NO_INIT: return "网络SDK未经初始化";
		case ZLNET_DOWNLOAD_END: return "下载已结束";
		case ZLNET_EMPTY_LIST: return "查询结果为空";
		case ZLNET_ERROR_GETCFG_SYSATTR: return "获取系统属性配置失败";
		case ZLNET_ERROR_GETCFG_SERIAL: return "获取序列号失败";
		case ZLNET_ERROR_GETCFG_GENERAL: return "获取常规属性失败";
		case ZLNET_ERROR_GETCFG_DSPCAP: return "获取DSP能力描述失败";
		case ZLNET_ERROR_GETCFG_NETCFG: return "获取网络配置失败";
		case ZLNET_ERROR_GETCFG_CHANNAME: return "获取通道名称失败";
		case ZLNET_ERROR_GETCFG_VIDEO: return "获取视频属性失败";
		case ZLNET_ERROR_GETCFG_RECORD: return "获取录象配置失败";
		case ZLNET_ERROR_GETCFG_PRONAME: return "获取解码器协议名称失败";
		case ZLNET_ERROR_GETCFG_FUNCNAME: return "获取232串口功能名称失败";
		case ZLNET_ERROR_GETCFG_485DECODER: return "获取解码器属性失败";
		case ZLNET_ERROR_GETCFG_232COM: return "获取232串口配置失败";
		case ZLNET_ERROR_GETCFG_ALARMIN: return "获取外部报警输入配置失败";
		case ZLNET_ERROR_GETCFG_ALARMDET: return "获取动态检测报警失败";
		case ZLNET_ERROR_GETCFG_SYSTIME: return "获取设备时间失败";
		case ZLNET_ERROR_GETCFG_PREVIEW: return "获取预览参数失败";
		case ZLNET_ERROR_GETCFG_AUTOMT: return "获取自动维护配置失败";
		case ZLNET_ERROR_GETCFG_VIDEOMTRX: return "获取视频矩阵配置失败";
		case ZLNET_ERROR_GETCFG_COVER: return "获取区域遮挡配置失败";
		case ZLNET_ERROR_GETCFG_WATERMAKE: return "获取图象水印配置失败";
		case ZLNET_ERROR_SETCFG_GENERAL: return "修改常规属性失败";
		case ZLNET_ERROR_SETCFG_NETCFG: return "修改网络配置失败";
		case ZLNET_ERROR_SETCFG_CHANNAME: return "修改通道名称失败";
		case ZLNET_ERROR_SETCFG_VIDEO: return "修改视频属性失败";
		case ZLNET_ERROR_SETCFG_RECORD: return " 修改录象配置失败";
		case ZLNET_ERROR_SETCFG_485DECODER: return "修改解码器属性失败";
		case ZLNET_ERROR_SETCFG_232COM: return " 修改232串口配置失败";
		case ZLNET_ERROR_SETCFG_ALARMIN: return "修改外部输入报警配置失败";
		case ZLNET_ERROR_SETCFG_ALARMDET: return " 修改动态检测报警配置失败";
		case ZLNET_ERROR_SETCFG_SYSTIME: return " 修改设备时间失败";
		case ZLNET_ERROR_SETCFG_PREVIEW: return " 修改预览参数失败";
		case ZLNET_ERROR_SETCFG_AUTOMT: return "修改自动维护配置失败";
		case ZLNET_ERROR_SETCFG_VIDEOMTRX: return "修改视频矩阵配置失败";
		case ZLNET_ERROR_SETCFG_COVER: return "修改区域遮挡配置失败";
		case ZLNET_ERROR_SETCFG_WATERMAKE: return "修改图象水印配置失败";
		case ZLNET_ERROR_SETCFG_WLAN: return "修改无线网络信息失败";
		case ZLNET_ERROR_SETCFG_WLANDEV: return "选择无线网络设备失败";
		case ZLNET_ERROR_SETCFG_REGISTER: return "修改主动注册参数配置失败";
		case ZLNET_ERROR_SETCFG_CAMERA: return "修改摄像头属性配置失败";
		case ZLNET_ERROR_SETCFG_INFRARED: return "修改红外报警配置失败";
		case ZLNET_ERROR_SETCFG_SOUNDALARM: return "修改音频报警配置失败";
		case ZLNET_ERROR_SETCFG_STORAGE: return "修改存储位置配置失败";
		case ZLNET_AUDIOENCODE_NOTINIT: return "音频编码接口没有成功初始化";
		case ZLNET_DATA_TOOLONGH: return "数据过长";
		case ZLNET_UNSUPPORTED: return "设备不支持该操作";
		case ZLNET_DEVICE_BUSY: return "设备资源不足";
		case ZLNET_SERVER_STARTED: return "服务器已经启动";
		case ZLNET_SERVER_STOPPED: return "服务器尚未成功启动";
		case ZLNET_LISTER_INCORRECT_SERIAL: return "输入序列号有误";
		case ZLNET_QUERY_DISKINFO_FAILED: return "获取硬盘信息失败";
		case ZLNET_ERROR_GETCFG_SESSION: return "获取连接Session信息";
		case ZLNET_USER_FLASEPWD_TRYTIME: return "输入密码错误超过限制次数";
		case ZLNET_LOGIN_ERROR_PASSWORD: return "密码不正确";
		case ZLNET_LOGIN_ERROR_USER: return "帐户不存在";
		case ZLNET_LOGIN_ERROR_TIMEOUT: return "等待登录返回超时";
		case ZLNET_LOGIN_ERROR_RELOGGIN: return "帐号已登录";
		case ZLNET_LOGIN_ERROR_LOCKED: return "帐号已被锁定";
		case ZLNET_LOGIN_ERROR_BLACKLIST: return "帐号已被列为黑名单";
		case ZLNET_LOGIN_ERROR_BUSY: return "资源不足，系统忙";
		case ZLNET_LOGIN_ERROR_CONNECT: return "登录设备超时，请检查网络并重试";
		case ZLNET_LOGIN_ERROR_NETWORK: return "网络连接失败";
		case ZLNET_LOGIN_ERROR_SUBCONNECT: return "登录设备成功，但无法创建视频通道，请检查网络状况";
		case ZLNET_RENDER_SOUND_ON_ERROR: return "Render库打开音频出错";
		case ZLNET_RENDER_SOUND_OFF_ERROR: return "Render库关闭音频出错";
		case ZLNET_RENDER_SET_VOLUME_ERROR: return "Render库控制音量出错";
		case ZLNET_RENDER_ADJUST_ERROR: return "Render库设置画面参数出错";
		case ZLNET_RENDER_PAUSE_ERROR: return "Render库暂停播放出错";
		case ZLNET_RENDER_SNAP_ERROR: return "Render库抓图出错";
		case ZLNET_RENDER_STEP_ERROR: return "Render库步进出错";
		case ZLNET_RENDER_FRAMERATE_ERROR: return "Render库设置帧率出错";
		case ZLNET_GROUP_EXIST: return "组名已存在";
		case ZLNET_GROUP_NOEXIST: return "组名不存在";
		case ZLNET_GROUP_RIGHTOVER: return "组的权限超出权限列表范围";
		case ZLNET_GROUP_HAVEUSER: return "组下有用户，不能删除";
		case ZLNET_GROUP_RIGHTUSE: return "组的某个权限被用户使用，不能出除";
		case ZLNET_GROUP_SAMENAME: return "新组名同已有组名重复";
		case ZLNET_USER_EXIST: return "用户已存在";
		case ZLNET_USER_NOEXIST: return "用户不存在";
		case ZLNET_USER_RIGHTOVER: return "用户权限超出组权限";
		case ZLNET_USER_PWD: return "保留帐号，不容许修改密码";
		case ZLNET_USER_FLASEPWD: return "密码不正确";
		case ZLNET_USER_NOMATCHING: return "密码不匹配";
		case ZLNET_ERROR_GETCFG_ETHERNET: return "获取网卡配置失败";
		case ZLNET_ERROR_GETCFG_WLAN: return "获取无线网络信息失败";
		case ZLNET_ERROR_GETCFG_WLANDEV: return "获取无线网络设备失败";
		case ZLNET_ERROR_GETCFG_REGISTER: return "获取主动注册参数失败";
		case ZLNET_ERROR_GETCFG_CAMERA: return "获取摄像头属性失败";
		case ZLNET_ERROR_GETCFG_INFRARED: return "获取红外报警配置失败";
		case ZLNET_ERROR_GETCFG_SOUNDALARM: return "获取音频报警配置失败";
		case ZLNET_ERROR_GETCFG_STORAGE: return "获取存储位置配置失败";
		case ZLNET_ERROR_GETCFG_MAIL: return "获取邮件配置失败";
		case ZLNET_CONFIG_DEVBUSY: return "暂时无法设置";
		case ZLNET_CONFIG_DATAILLEGAL: return "配置数据不合法";
		case ZLNET_ERROR_GETCFG_DST: return "获取夏令时配置失败";
		case ZLNET_ERROR_SETCFG_DST: return "设置夏令时配置失败";
		case ZLNET_ERROR_GETCFG_VIDEO_OSD: return "获取视频OSD叠加配置失败";
		case ZLNET_ERROR_SETCFG_VIDEO_OSD: return "设置视频OSD叠加配置失败";
		case ZLNET_ERROR_GETCFG_GPRSCDMA: return "获取CDMA\GPRS网络配置失败";
		case ZLNET_ERROR_SETCFG_GPRSCDMA: return "设置CDMA\GPRS网络配置失败";
		case ZLNET_ERROR_GETCFG_IPFILTER: return "获取IP过滤配置失败";
		case ZLNET_ERROR_SETCFG_IPFILTER: return "设置IP过滤配置失败";
		case ZLNET_ERROR_GETCFG_TALKENCODE: return "获取语音对讲编码配置失败";
		case ZLNET_ERROR_SETCFG_TALKENCODE: return "设置语音对讲编码配置失败";
		case ZLNET_ERROR_GETCFG_RECORDLEN: return "获取录像打包长度配置失败";
		case ZLNET_ERROR_SETCFG_RECORDLEN: return "设置录像打包长度配置失败";
		case ZLNET_DONT_SUPPORT_SUBAREA: return "不支持网络硬盘分区";
		case ZLNET_ERROR_GET_AUTOREGSERVER: return "获取设备上主动注册服务器信息失败";
		case ZLNET_ERROR_CONTROL_AUTOREGISTER: return "主动注册重定向注册错误";
		case ZLNET_ERROR_DISCONNECT_AUTOREGISTER: return " 断开主动注册服务器错误";
		case ZLNET_ERROR_GETCFG_MMS: return "获取mms配置失败";
		case ZLNET_ERROR_SETCFG_MMS: return "设置mms配置失败";
		case ZLNET_ERROR_GETCFG_SMSACTIVATION: return "获取短信激活无线连接配置失败";
		case ZLNET_ERROR_SETCFG_SMSACTIVATION: return "设置短信激活无线连接配置失败";
		case ZLNET_ERROR_GETCFG_DIALINACTIVATION: return "获取拨号激活无线连接配置失败";
		case ZLNET_ERROR_SETCFG_DIALINACTIVATION: return "设置拨号激活无线连接配置失败";
		case ZLNET_ERROR_GETCFG_VIDEOOUT: return "查询视频输出参数配置失败";
		case ZLNET_ERROR_SETCFG_VIDEOOUT: return "设置视频输出参数配置失败";
		case ZLNET_ERROR_GETCFG_OSDENABLE: return "获取osd叠加使能配置失败";
		case ZLNET_ERROR_SETCFG_OSDENABLE: return "设置osd叠加使能配置失败";
		case ZLNET_ERROR_SETCFG_ENCODERINFO: return "设置数字通道前端编码接入配置失败";
		case ZLNET_ERROR_GETCFG_TVADJUST: return "获取TV调节配置失败";
		case ZLNET_ERROR_SETCFG_TVADJUST: return "设置TV调节配置失败";
		case ZLNET_ERROR_CONNECT_FAILED: return "请求建立连接失败";
		case ZLNET_ERROR_SETCFG_BURNFILE: return "请求刻录文件上传失败";
		case ZLNET_ERROR_SNIFFER_GETCFG: return "获取抓包配置信息失败";
		case ZLNET_ERROR_SNIFFER_SETCFG: return "设置抓包配置信息失败";
		case ZLNET_ERROR_DOWNLOADRATE_GETCFG: return "查询下载限制信息失败";
		case ZLNET_ERROR_DOWNLOADRATE_SETCFG: return "设置下载限制信息失败";
		case ZLNET_ERROR_SEARCH_TRANSCOM: return "查询串口参数失败";
		case ZLNET_ERROR_GETCFG_POINT: return "获取预制点信息错误";
		case ZLNET_ERROR_SETCFG_POINT: return "设置预制点信息错误";
		case ZLNET_SDK_LOGOUT_ERROR: return "SDK没有正常登出设备";
		case ZLNET_ERROR_GET_VEHICLE_CFG: return "获取车载配置失败";
		case ZLNET_ERROR_SET_VEHICLE_CFG: return "设置车载配置失败";
		case ZLNET_ERROR_GET_ATM_OVERLAY_CFG: return "获取atm叠加配置失败";
		case ZLNET_ERROR_SET_ATM_OVERLAY_CFG: return "设置atm叠加配置失败";
		case ZLNET_ERROR_GET_ATM_OVERLAY_ABILITY: return "获取atm叠加能力失败";
		case ZLNET_ERROR_GET_DECODER_TOUR_CFG: return "获取解码器解码轮巡配置失败";
		case ZLNET_ERROR_SET_DECODER_TOUR_CFG: return "设置解码器解码轮巡配置失败";
		case ZLNET_ERROR_CTRL_DECODER_TOUR: return "控制解码器解码轮巡失败";
		case ZLNET_GROUP_OVERSUPPORTNUM: return "超出设备支持最大用户组数目";
		case ZLNET_USER_OVERSUPPORTNUM: return "超出设备支持最大用户数目";
		case ZLNET_ERROR_GET_SIP_CFG: return "获取SIP配置失败";
		case ZLNET_ERROR_SET_SIP_CFG: return "设置SIP配置失败";
		case ZLNET_ERROR_GET_SIP_ABILITY: return "获取SIP能力失败";
		case ZLNET_TALK_REJECT: return "拒绝对讲";
		case ZLNET_TALK_BUSY: return "资源冲突、不能对讲";
		case ZLNET_TALK_FORMAT_NOT_SUPPORTED: return "拒绝对讲，编码格式不支持";
		case ZLNET_ERROR_UPSUPPORT_WAV: return "不支持的WAV文件";
		case ZLNET_ERROR_CHANGE_FORMAT_WAV: return "转换WAV采样率失败";
		case ZLNET_ERROR_PACKFRAME: return "打包失败";
		case ZLNET_ERROR_LATTICE_CFG: return "设置点阵配置失败";
		default: return "未知错误";
    }
}



CFactoryWSD::CFactoryWSD()
{
    init();
}

CFactoryWSD::~CFactoryWSD()
{
    clean();
}






bool CFactoryWSD::init()
{
    if (!m_init)
    {
		m_init = Api_WSD::Api().ZLNET_Init(NULL, 0);

        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
		}

		g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


void CFactoryWSD::clean()
{
	Api_WSD::Api().ZLNET_Cleanup();
}




IVideoServer* CFactoryWSD::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new WSD_videoserver();
}

// std::vector<WSD_videoserver*> WSD_videoserver::sServers;
// std::recursive_mutex WSD_videoserver::sMtServers;

/*
 * 析构函数
 */
WSD_videoserver::WSD_videoserver()
{
//     std::lock_guard<std::recursive_mutex> lock(WSD_videoserver::sMtServers);
//     sServers.push_back(this);
}

WSD_videoserver::~WSD_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(WSD_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

void CALLBACK PosCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser)
{
	WSD_videoserver * pThis = (WSD_videoserver *)dwUser;
	{
		Mutex::ScopedLock lock(pThis->m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosDownPlay.find(lPlayHandle);
		if (itr != pThis->m_mapPosDownPlay.end())
		{
			itr->second.iTotalSize = dwTotalSize*1024;
			itr->second.iCurSize = dwDownLoadSize*1024;
			itr->second.iPercent = ((float)dwTotalSize / (float)dwDownLoadSize) * 100;
		}
	}
}

IVideoServer* WSD_videoserver::clone()
{
	return nullptr;
// 	WSD_videoserver *svr = new WSD_videoserver();
// 	memcpy(svr, this, sizeof(WSD_videoserver));
//     return svr;
}

bool WSD_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
//     if (0 < m_lLoginHandle && !logout())
// 	{
// 		g_log.AddLog(string("login 设备已登录，尝试反登陆失败"));
//         return false;
//     }
	char addThis[32] = { 0 };
	sprintf(addThis, "this:%d", this);
	g_log.AddLog(string("WSD_videoserver::login ") + addThis);
	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

	int iError = 0;
	m_lLoginHandle = Api_WSD::Api().ZLNET_Login((char *)IP, port, (char *)user, (char *)password, &m_deviceInfo, &iError);

    if (m_lLoginHandle == 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

	char logInfo[128] = { 0 };
	sprintf_s(logInfo, "byChanNum:%d, deviceTye:%d, m_lLoginHandle:%d", m_deviceInfo.byChanNum, m_deviceInfo.byDVRType, m_lLoginHandle);
	g_log.AddLog(string(logInfo));

	for (int i = 0; i < m_deviceInfo.byChanNum; i++)
	{
		char chname[16] = { 0 };
		sprintf_s(chname, "通道%d", i+1);
		channels.insert(std::make_pair(i, chname));
	}

    return true;
}

bool WSD_videoserver::logout()
{
	char addThis[32] = { 0 };
	sprintf(addThis, "this:%d", this);
	g_log.AddLog(string("WSD_videoserver::logout ") + addThis);

    if (m_lLoginHandle > 0 && !Api_WSD::Api().ZLNET_Logout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}

static void timeWSDToStd(WSD::ZLNET_TIME *pTimeDH, tm *pTimeStd)
{
	pTimeStd->tm_year = pTimeDH->dwYear - 1900;
	pTimeStd->tm_mon = pTimeDH->dwMonth - 1;
	pTimeStd->tm_mday = pTimeDH->dwDay;
	pTimeStd->tm_hour = pTimeDH->dwHour;
	pTimeStd->tm_min = pTimeDH->dwMinute;
	pTimeStd->tm_sec = pTimeDH->dwSecond;
}

static void timeStdToWSD(tm *pTimeStd, WSD::ZLNET_TIME *pTimeDH)
{
	pTimeDH->dwDay = pTimeStd->tm_year + 1900;
	pTimeDH->dwMonth = pTimeStd->tm_mon + 1;
	pTimeDH->dwDay = pTimeStd->tm_mday;
	pTimeDH->dwHour = pTimeStd->tm_hour;
	pTimeDH->dwMinute = pTimeStd->tm_min;
	pTimeDH->dwSecond = pTimeStd->tm_sec;
}

static void timeWSDToStd2(WSD::ZLNET_TIME *pTimeDH, tm *pTimeStd)
{
	pTimeStd->tm_year = pTimeDH->dwYear - 1900;
	pTimeStd->tm_mon = pTimeDH->dwMonth - 1;
	pTimeStd->tm_mday = pTimeDH->dwDay;
	pTimeStd->tm_hour = pTimeDH->dwHour;
	pTimeStd->tm_min = pTimeDH->dwMinute;
	pTimeStd->tm_sec = pTimeDH->dwSecond;
}

static void timeStdToWSD2(tm *pTimeStd, WSD::ZLNET_TIME *pTimeDH)
{
	pTimeDH->dwYear = pTimeStd->tm_year + 1900;
	pTimeDH->dwMonth = pTimeStd->tm_mon + 1;
	pTimeDH->dwDay = pTimeStd->tm_mday;
	pTimeDH->dwHour = pTimeStd->tm_hour;
	pTimeDH->dwMinute = pTimeStd->tm_min;
	pTimeDH->dwSecond = pTimeStd->tm_sec;
}

#define MAX_SEARCH_COUNT 1000
bool WSD_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart, __time64_t timeEnd)
{
	char addThis[32] = { 0 };
	sprintf(addThis, "this:%d", this);
	g_log.AddLog(string("WSD_videoserver::GetRecordFileList ") + addThis);

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

	WSD::ZLNET_TIME stime;
	WSD::ZLNET_TIME etime;

	tm STime;
	tm ETime;
	_localtime64_s(&STime, (const time_t*)&timeStart);
	_localtime64_s(&ETime, (const time_t*)&timeEnd);

	timeStdToWSD2(&STime, &stime);
	timeStdToWSD2(&ETime, &etime);
	char szTime[512];
	ZeroMemory(szTime, 512);
	sprintf(szTime, " s_time:%d-%02d-%02d %02d:%02d:%02d e_time:%d-%02d-%02d %02d:%02d:%02d linkID:%d", stime.dwYear, stime.dwMonth, stime.dwDay,
		stime.dwHour, stime.dwMinute, stime.dwSecond,
		etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond, m_lLoginHandle);
	g_log.AddLog(string("GetRecordFileList ") + string(szTime));

	char szTime64_s[64];
	ZeroMemory(szTime64_s, 64);
	char szTime64_e[64];
	ZeroMemory(szTime64_e, 64);
	_i64toa(timeStart, szTime64_s, 10);
	_i64toa(timeEnd, szTime64_e, 10);
	//m_mapArcItem.clear();
	g_log.AddLog(string("time64 s_time:") + string(szTime64_s) + string(" e_time:") + string(szTime64_e));

	int iMaxNum = 0;
	__int32 nChannelId = 0;
	for (int ch = 0; ch < channelVec.size(); ch++)
	{
		nChannelId = channelVec[ch];
		LONG searchHandle = Api_WSD::Api().ZLNET_FindFile(m_lLoginHandle, nChannelId, 0, NULL, &stime, &etime, FALSE, 2000);
		if (searchHandle == 0)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
			/*return false*/;
			continue;
		}
	
		int getRet = -1;
		RecordFile info;
		tm sTm;
		tm eTm;
		char szFileName[MAX_PATH];
		while(1)
		{
			WSD::ZLNET_RECORDFILE_INFO findInfo = { 0 };
			getRet = Api_WSD::Api().ZLNET_FindNextFile(searchHandle, &findInfo);
			if (getRet == 0)
			{
				Api_WSD::Api().ZLNET_FindClose(searchHandle);
				break;
			}

// 			Mutex::ScopedLock lock(m_mtx);
// 
// 			ZeroMemory(szFileName, sizeof(szFileName));
// 			sprintf(szFileName, "ch%d%04d%02d%02d-%02d%02d%02d--%04d%02d%02d-%02d%02d%02d", nChannelId,
// 					findInfo.starttime.dwYear, findInfo.starttime.dwMonth, findInfo.starttime.dwDay,
// 					findInfo.starttime.dwHour, findInfo.starttime.dwMinute, findInfo.starttime.dwSecond,
// 					findInfo.endtime.dwYear, findInfo.endtime.dwMonth, findInfo.endtime.dwDay, 
// 					findInfo.endtime.dwHour, findInfo.endtime.dwMinute, findInfo.endtime.dwSecond);
// 			WSD::ZLNET_RECORDFILE_INFO * pFileInfo = new WSD::ZLNET_RECORDFILE_INFO;
// 			memset(pFileInfo, 0, sizeof(WSD::ZLNET_RECORDFILE_INFO));
// 			memcpy(pFileInfo, &findInfo, sizeof(WSD::ZLNET_RECORDFILE_INFO));
// 			sprintf(pFileInfo->filename, "channel%02d", nChannelId+1);
// 			m_mapArcItem.insert(make_pair(string(szFileName), pFileInfo));

			timeWSDToStd(&findInfo.starttime, &sTm);
			timeWSDToStd(&findInfo.endtime, &eTm);

			info.channel = findInfo.ch;
			info.size = findInfo.size*1024;
			/*info.name = szFileName;*/
			info.name = findInfo.filename;
			info.beginTime = mktime(&sTm);
			info.endTime = mktime(&eTm);
			info.setPrivateData(&findInfo, sizeof(WSD::ZLNET_RECORDFILE_INFO));
			files.push_back(info);
		}
	}
	return true;
}


bool WSD_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
	char addThis[32] = { 0 };
	sprintf(addThis, "this:%d", this);
	g_log.AddLog(string("WSD_videoserver::downLoadByRecordFile ") + addThis);

    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

// 	int size = m_mapArcItem.size();
// 	char csize[8] = { 0 };
// 	sprintf_s(csize, "size:%d,", size);
// 	g_log.AddLog(file.name+ csize);

// 	map<string, WSD::ZLNET_RECORDFILE_INFO*>::iterator itr = m_mapArcItem.begin();
// 	for (; itr != m_mapArcItem.end(); itr++)
// 	{
// 		g_log.AddLog(itr->first);
// 	}

// 	WSD::ZLNET_RECORDFILE_INFO info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, WSD::ZLNET_RECORDFILE_INFO*>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("[1]downLoadByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		memcpy(&info, itr->second, sizeof(WSD::ZLNET_RECORDFILE_INFO));
// 	}

// 	char szFileName[256] = { 0 };
// 	sprintf(szFileName, "%04d%02d%02d-%02d%02d%02d--%04d%02d%02d-%02d%02d%02d",
// 		info.starttime.dwYear, info.starttime.dwMonth, info.starttime.dwDay,
// 		info.starttime.dwHour, info.starttime.dwMinute, info.starttime.dwSecond,
// 		info.endtime.dwYear, info.endtime.dwMonth, info.endtime.dwDay,
// 		info.endtime.dwHour, info.endtime.dwMinute, info.endtime.dwSecond);
// 	g_log.AddLog(string(szFileName));
// 	char tch[256] = { 0 };
// 	sprintf_s(tch, "ch:%d,name:%s,sz:%d,dr:%d,st:%d,nr:%d,bi%d,bh%d,br%d", info.ch,info.filename,info.size,info.driveno,info.startcluster,info.nRecordFileType,info.bImportantRecID,info.bHint,info.bReserved);
// 	g_log.AddLog(string(tch));
// 	g_log.AddLog(string("downLoadByRecordFile 文件名：") + saveFileName);

	WSD::ZLNET_RECORDFILE_INFO* pData = (WSD::ZLNET_RECORDFILE_INFO*)file.getPrivateData();

	hdl = Api_WSD::Api().ZLNET_DownloadByRecordFile(m_lLoginHandle, pData, (char *)saveFileName, PosCallBack, (DWORD)this);
	if (hdl == 0)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("downLoadByRecordFile 下载录像失败，错误原因：") + m_sLastError);
		return false;
	}

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.insert(std::make_pair(hdl, file));
	}
	{
		stPos_DownPlay pos;
		pos.iTotalSize = pData->size * 1024;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(hdl, pos));
	}

	return true;
}


bool  WSD_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
		g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
        return false;
	}

// 	WSD::ZLNET_RECORDFILE_INFO info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, WSD::ZLNET_RECORDFILE_INFO*>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("PlayBackByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		memcpy(&info, itr->second, sizeof(WSD::ZLNET_RECORDFILE_INFO));
// 	}

	WSD::ZLNET_RECORDFILE_INFO* pData = (WSD::ZLNET_RECORDFILE_INFO*)file.getPrivateData();
	playbackHandle = Api_WSD::Api().ZLNET_PlayBackByRecordFile(m_lLoginHandle, pData, hwnd, PosCallBack, (DWORD)this);
	if (playbackHandle == 0)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("PlayBackByRecordFile 播放录像失败，错误原因：") + m_sLastError);
		return false;
	}

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.insert(std::make_pair(playbackHandle, file));
	}
	{
		stPos_DownPlay pos;
		pos.iTotalSize = 1;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(playbackHandle, pos));
	}

	char szLog[1024];
	ZeroMemory(szLog, 1024);
	sprintf(szLog, "PlayBackByRecordFile start playbackHandle:%d", playbackHandle);
	//g_log.AddLog(string("StopPlayBack 开始停止播放"));
	g_log.AddLog(string(szLog));
	return true;
}

bool WSD_videoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
// 	RecordFile file;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<long long, RecordFile>::iterator itr = m_mapDownloadOrPlay.find(playbackHandle);
// 		if (itr == m_mapDownloadOrPlay.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("SetPlayBack 该文件不存在"));
// 			return false;
// 		}
// 		file = itr->second;
// 	}
// 	return FALSE != Api_WSD::Api().m_pPlayBackControl(playbackHandle, WSD::SDK_PLAY_BACK_SEEK_PERCENT, pos);
	return true;
}

bool WSD_videoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
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
		if (!Api_WSD::Api().ZLNET_StopPlayBack(playbackHandle))
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
		//g_log.AddLog(string("StopPlayBack 开始停止播放"));
		g_log.AddLog(string(szLog));

		{
			Mutex::ScopedLock lock(m_mtx);
			m_mapDownloadOrPlay.erase(playbackHandle);
		}
		{
			Mutex::ScopedLock lock(m_mtxPos);
			m_mapPosDownPlay.erase(playbackHandle);
		}
		if (!Api_WSD::Api().ZLNET_StopPlayBack(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}

    return true;
}

bool WSD_videoserver::stopDownload(download_handle_t h)
{
	g_log.AddLog(string("stopDownload 开始停止下载"));
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("stopDownload 请先登录"));
        return false;
	}

	{
		Mutex::ScopedLock lock(m_mtx);
		m_mapDownloadOrPlay.erase(h);
	}
	{
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.erase(h);
	}

	if (FALSE == Api_WSD::Api().ZLNET_StopDownload(h))
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool WSD_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
// 	if (0 >= m_lLoginHandle)
// 	{
// 		m_sLastError = "请先登录!";
// 		g_log.AddLog(string("getPlayBackPos 请先登录"));
// 		return false;
// 	}
// 
// 	Mutex::ScopedLock lock(m_mtxPos);
// 	map<long long, stPos_DownPlay>::iterator itr = m_mapPosDownPlay.find(playbackHandle);
// 	if (itr != m_mapPosDownPlay.end())
// 	{
// 		*pos = itr->second.iPercent;
// 		return true;
// 	}
// 	m_sLastError = "找不到该回放";
// 	g_log.AddLog(string("getPlayBackPos 找不到该回放"));
	return false;
}

bool WSD_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getDownloadPos 请先登录"));
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
	g_log.AddLog(string("getDownloadPos 找不到该下载"));
	*failed = true;
	return false;
}