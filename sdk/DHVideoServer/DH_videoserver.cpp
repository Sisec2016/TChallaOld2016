#include "dh_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"

Log g_log("DH_videoserver");

IVideoServerFactory* VideoServerFactory()
{
    return new CFactoryDH();
}

static std::string GetLastErrorString()
{
    DWORD dwError;
    dwError = Api_DH::Api().m_pGetLastError();

    switch (dwError)
    {
        case NET_NOERROR: return "没有错误";
		case NET_ERROR: return "未知错误";
		case NET_SYSTEM_ERROR: return "Windows系统出错";
		case NET_NETWORK_ERROR: return "网络错误，可能是因为网络超时";
		case NET_DEV_VER_NOMATCH: return "设备协议不匹配";
		case NET_INVALID_HANDLE: return "句柄无效";
		case NET_OPEN_CHANNEL_ERROR: return "打开通道失败";
		case NET_CLOSE_CHANNEL_ERROR: return "关闭通道失败";
		case NET_ILLEGAL_PARAM: return "用户参数不合法";
		case NET_SDK_INIT_ERROR: return "SDK初始化出错";
		case NET_SDK_UNINIT_ERROR: return "SDK清理出错";
		case NET_RENDER_OPEN_ERROR: return "申请render资源出错";
		case NET_DEC_OPEN_ERROR: return "打开解码库出错";
		case NET_DEC_CLOSE_ERROR: return "关闭解码库出错";
		case NET_MULTIPLAY_NOCHANNEL: return "多画面预览中检测到通道数为0";
		case NET_TALK_INIT_ERROR: return "录音库初始化失败";
		case NET_TALK_NOT_INIT: return "录音库未经初始化";
		case NET_TALK_SENDDATA_ERROR: return "发送音频数据出错";
		case NET_REAL_ALREADY_SAVING: return "实时数据已经处于保存状态";
		case NET_NOT_SAVING: return "未保存实时数据";
		case NET_OPEN_FILE_ERROR: return "打开文件出错";
		case NET_PTZ_SET_TIMER_ERROR: return "启动云台控制定时器失败";
		case NET_RETURN_DATA_ERROR: return "对返回数据的校验出错";
		case NET_INSUFFICIENT_BUFFER: return "没有足够的缓存";
		case NET_NOT_SUPPORTED: return "当前SDK未支持该功能";
		case NET_NO_RECORD_FOUND: return "查询不到录象";
		case NET_NOT_AUTHORIZED: return "无操作权限";
		case NET_NOT_NOW: return "暂时无法执行";
		case NET_NO_TALK_CHANNEL: return "未发现对讲通道";
		case NET_NO_AUDIO: return "未发现音频";
		case NET_NO_INIT: return "网络SDK未经初始化";
		case NET_DOWNLOAD_END: return "下载已结束";
		case NET_EMPTY_LIST: return "查询结果为空";
		case NET_ERROR_GETCFG_SYSATTR: return "获取系统属性配置失败";
		case NET_ERROR_GETCFG_SERIAL: return "获取序列号失败";
		case NET_ERROR_GETCFG_GENERAL: return "获取常规属性失败";
		case NET_ERROR_GETCFG_DSPCAP: return "获取DSP能力描述失败";
		case NET_ERROR_GETCFG_NETCFG: return "获取网络配置失败";
		case NET_ERROR_GETCFG_CHANNAME: return "获取通道名称失败";
		case NET_ERROR_GETCFG_VIDEO: return "获取视频属性失败";
		case NET_ERROR_GETCFG_RECORD: return "获取录象配置失败";
		case NET_ERROR_GETCFG_PRONAME: return "获取解码器协议名称失败";
		case NET_ERROR_GETCFG_FUNCNAME: return "获取232串口功能名称失败";
		case NET_ERROR_GETCFG_485DECODER: return "获取解码器属性失败";
		case NET_ERROR_GETCFG_232COM: return "获取232串口配置失败";
		case NET_ERROR_GETCFG_ALARMIN: return "获取外部报警输入配置失败";
		case NET_ERROR_GETCFG_ALARMDET: return "获取动态检测报警失败";
		case NET_ERROR_GETCFG_SYSTIME: return "获取设备时间失败";
		case NET_ERROR_GETCFG_PREVIEW: return "获取预览参数失败";
		case NET_ERROR_GETCFG_AUTOMT: return "获取自动维护配置失败";
		case NET_ERROR_GETCFG_VIDEOMTRX: return "获取视频矩阵配置失败";
		case NET_ERROR_GETCFG_COVER: return "获取区域遮挡配置失败";
		case NET_ERROR_GETCFG_WATERMAKE: return "获取图象水印配置失败";
		case NET_ERROR_SETCFG_GENERAL: return "修改常规属性失败";
		case NET_ERROR_SETCFG_NETCFG: return "修改网络配置失败";
		case NET_ERROR_SETCFG_CHANNAME: return "修改通道名称失败";
		case NET_ERROR_SETCFG_VIDEO: return "修改视频属性失败";
		case NET_ERROR_SETCFG_RECORD: return "修改录象配置失败";
		case NET_ERROR_SETCFG_485DECODER: return "修改解码器属性失败";
		case NET_ERROR_SETCFG_232COM: return "修改232串口配置失败";
		case NET_ERROR_SETCFG_ALARMIN: return "修改外部输入报警配置失败";
		case NET_ERROR_SETCFG_ALARMDET: return "修改动态检测报警配置失败";
		case NET_ERROR_SETCFG_SYSTIME: return "修改设备时间失败";
		case NET_ERROR_SETCFG_PREVIEW: return "修改预览参数失败";
		case NET_ERROR_SETCFG_AUTOMT: return "修改自动维护配置失败";
		case NET_ERROR_SETCFG_VIDEOMTRX: return "修改视频矩阵配置失败";
		case NET_ERROR_SETCFG_COVER: return "修改区域遮挡配置失败";
		case NET_ERROR_SETCFG_WATERMAKE: return "修改图象水印配置失败";
		case NET_ERROR_SETCFG_WLAN: return "修改无线网络信息失败";
		case NET_ERROR_SETCFG_WLANDEV: return "选择无线网络设备失败";
		case NET_ERROR_SETCFG_REGISTER: return "修改主动注册参数配置失败";
		case NET_ERROR_SETCFG_CAMERA: return "修改摄像头属性配置失败";
		case NET_ERROR_SETCFG_INFRARED: return "修改红外报警配置失败";
		case NET_ERROR_SETCFG_SOUNDALARM: return "修改音频报警配置失败";
		case NET_ERROR_SETCFG_STORAGE: return "修改存储位置配置失败";
		case NET_AUDIOENCODE_NOTINIT: return "音频编码接口没有成功初始化";
		case NET_DATA_TOOLONGH: return "数据过长";
		case NET_UNSUPPORTED: return "设备不支持该操作";
		case NET_DEVICE_BUSY: return "设备资源不足";
		case NET_SERVER_STARTED: return "服务器已经启动";
		case NET_SERVER_STOPPED: return "服务器尚未成功启动";
		case NET_LISTER_INCORRECT_SERIAL: return "输入序列号有误";
		case NET_QUERY_DISKINFO_FAILED: return "获取硬盘信息失败";
		case NET_ERROR_GETCFG_SESSION: return "获取连接Session信息";
		case NET_USER_FLASEPWD_TRYTIME: return "输入密码错误超过限制次数";
		case NET_LOGIN_ERROR_PASSWORD: return "密码不正确";
		case NET_LOGIN_ERROR_USER: return "帐户不存在";
		case NET_LOGIN_ERROR_TIMEOUT: return "等待登录返回超时";
		case NET_LOGIN_ERROR_RELOGGIN: return "帐号已登录";
		case NET_LOGIN_ERROR_LOCKED: return "帐号已被锁定";
		case NET_LOGIN_ERROR_BLACKLIST: return "帐号已被列为黑名单";
		case NET_LOGIN_ERROR_BUSY: return "资源不足，系统忙";
		case NET_LOGIN_ERROR_CONNECT: return "登录设备超时，请检查网络并重试";
		case NET_LOGIN_ERROR_NETWORK: return "网络连接失败";
		case NET_LOGIN_ERROR_SUBCONNECT: return "登录设备成功，但无法创建视频通道，请检查网络状况";
		case NET_LOGIN_ERROR_MAXCONNECT: return "超过最大连接数";
		case NET_LOGIN_ERROR_PROTOCOL3_ONLY: return "只支持3代协议";
		case NET_LOGIN_ERROR_UKEY_LOST: return "未插入U盾或U盾信息错误";
		case NET_LOGIN_ERROR_NO_AUTHORIZED: return "客户端IP地址没有登录权限";
		case NET_RENDER_SOUND_ON_ERROR: return "Render库打开音频出错";
		case NET_RENDER_SOUND_OFF_ERROR: return "Render库关闭音频出错";
		case NET_RENDER_SET_VOLUME_ERROR: return "Render库控制音量出错";
		case NET_RENDER_ADJUST_ERROR: return "Render库设置画面参数出错";
		case NET_RENDER_PAUSE_ERROR: return "Render库暂停播放出错";
		case NET_RENDER_SNAP_ERROR: return "Render库抓图出错";
		case NET_RENDER_STEP_ERROR: return "Render库步进出错";
		case NET_RENDER_FRAMERATE_ERROR: return "Render库设置帧率出错";
		case NET_RENDER_DISPLAYREGION_ERROR: return "Render库设置显示区域出错";
		case NET_GROUP_EXIST: return "组名已存在";
		case NET_GROUP_NOEXIST: return "组名不存在";
		case NET_GROUP_RIGHTOVER: return "组的权限超出权限列表范围";
		case NET_GROUP_HAVEUSER: return "组下有用户，不能删除";
		case NET_GROUP_RIGHTUSE: return "组的某个权限被用户使用，不能出除";
		case NET_GROUP_SAMENAME: return "新组名同已有组名重复";
		case NET_USER_EXIST: return "用户已存在";
		case NET_USER_NOEXIST: return "用户不存在";
		case NET_USER_RIGHTOVER: return "用户权限超出组权限";
		case NET_USER_PWD: return "保留帐号，不容许修改密码";
		case NET_USER_FLASEPWD: return "密码不正确";
		case NET_USER_NOMATCHING: return "密码不匹配";
		case NET_USER_INUSE: return "账号正在使用中";
		case NET_ERROR_GETCFG_ETHERNET: return "获取网卡配置失败";
		case NET_ERROR_GETCFG_WLAN: return "获取无线网络信息失败";
		case NET_ERROR_GETCFG_WLANDEV: return "获取无线网络设备失败";
		case NET_ERROR_GETCFG_REGISTER: return "获取主动注册参数失败";
		case NET_ERROR_GETCFG_CAMERA: return "获取摄像头属性失败";
		case NET_ERROR_GETCFG_INFRARED: return "获取红外报警配置失败";
		case NET_ERROR_GETCFG_SOUNDALARM: return "获取音频报警配置失败";
		case NET_ERROR_GETCFG_STORAGE: return "获取存储位置配置失败";
		case NET_ERROR_GETCFG_MAIL: return "获取邮件配置失败";
		case NET_CONFIG_DEVBUSY: return "暂时无法设置";
		case NET_CONFIG_DATAILLEGAL: return "配置数据不合法";
		case NET_ERROR_GETCFG_DST: return "获取夏令时配置失败";
		case NET_ERROR_SETCFG_DST: return "设置夏令时配置失败";
		case NET_ERROR_GETCFG_VIDEO_OSD: return "获取视频OSD叠加配置失败";
		case NET_ERROR_SETCFG_VIDEO_OSD: return "设置视频OSD叠加配置失败";
		case NET_ERROR_GETCFG_GPRSCDMA: return "获取CDMA\GPRS网络配置失败";
		case NET_ERROR_SETCFG_GPRSCDMA: return "设置CDMA\GPRS网络配置失败";
		case NET_ERROR_GETCFG_IPFILTER: return "获取IP过滤配置失败";
		case NET_ERROR_SETCFG_IPFILTER: return "设置IP过滤配置失败";
		case NET_ERROR_GETCFG_TALKENCODE: return "获取语音对讲编码配置失败";
		case NET_ERROR_SETCFG_TALKENCODE: return "设置语音对讲编码配置失败";
		case NET_ERROR_GETCFG_RECORDLEN: return "获取录像打包长度配置失败";
		case NET_ERROR_SETCFG_RECORDLEN: return "设置录像打包长度配置失败";
		case NET_DONT_SUPPORT_SUBAREA: return "不支持网络硬盘分区";
		case NET_ERROR_GET_AUTOREGSERVER: return "获取设备上主动注册服务器信息失败";
		case NET_ERROR_CONTROL_AUTOREGISTER: return "主动注册重定向注册错误";
		case NET_ERROR_DISCONNECT_AUTOREGISTER: return "断开主动注册服务器错误";
		case NET_ERROR_GETCFG_MMS: return "获取mms配置失败";
		case NET_ERROR_SETCFG_MMS: return "设置mms配置失败";
		case NET_ERROR_GETCFG_SMSACTIVATION: return "获取短信激活无线连接配置失败";
		case NET_ERROR_SETCFG_SMSACTIVATION: return "设置短信激活无线连接配置失败";
		case NET_ERROR_GETCFG_DIALINACTIVATION: return "获取拨号激活无线连接配置失败";
		case NET_ERROR_SETCFG_DIALINACTIVATION: return "设置拨号激活无线连接配置失败";
		case NET_ERROR_GETCFG_VIDEOOUT: return "查询视频输出参数配置失败";
		case NET_ERROR_SETCFG_VIDEOOUT: return "设置视频输出参数配置失败";
		case NET_ERROR_GETCFG_OSDENABLE: return "获取osd叠加使能配置失败";
		case NET_ERROR_SETCFG_OSDENABLE: return "设置osd叠加使能配置失败";
		case NET_ERROR_SETCFG_ENCODERINFO: return "设置数字通道前端编码接入配置失败";
		case NET_ERROR_GETCFG_TVADJUST: return "获取TV调节配置失败";
		case NET_ERROR_SETCFG_TVADJUST: return "设置TV调节配置失败";
		case NET_ERROR_CONNECT_FAILED: return "请求建立连接失败";
		case NET_ERROR_SETCFG_BURNFILE: return "请求刻录文件上传失败";
		case NET_ERROR_SNIFFER_GETCFG: return "获取抓包配置信息失败";
		case NET_ERROR_SNIFFER_SETCFG: return "设置抓包配置信息失败";
		case NET_ERROR_DOWNLOADRATE_GETCFG: return "查询下载限制信息失败";
		case NET_ERROR_DOWNLOADRATE_SETCFG: return "设置下载限制信息失败";
		case NET_ERROR_SEARCH_TRANSCOM: return "查询串口参数失败";
		case NET_ERROR_GETCFG_POINT: return "获取预制点信息错误";
		case NET_ERROR_SETCFG_POINT: return "设置预制点信息错误";
		case NET_SDK_LOGOUT_ERROR: return "SDK没有正常登出设备";
		case NET_ERROR_GET_VEHICLE_CFG: return "获取车载配置失败";
		case NET_ERROR_SET_VEHICLE_CFG: return "设置车载配置失败";
		case NET_ERROR_GET_ATM_OVERLAY_CFG: return "获取atm叠加配置失败";
		case NET_ERROR_SET_ATM_OVERLAY_CFG: return "设置atm叠加配置失败";
		case NET_ERROR_GET_ATM_OVERLAY_ABILITY: return "获取atm叠加能力失败";
		case NET_ERROR_GET_DECODER_TOUR_CFG: return "获取解码器解码轮巡配置失败";
		case NET_ERROR_SET_DECODER_TOUR_CFG: return "设置解码器解码轮巡配置失败";
		case NET_ERROR_CTRL_DECODER_TOUR: return "控制解码器解码轮巡失败";
		case NET_GROUP_OVERSUPPORTNUM: return "超出设备支持最大用户组数目";
		case NET_USER_OVERSUPPORTNUM: return "超出设备支持最大用户数目";
		case NET_ERROR_GET_SIP_CFG: return "获取SIP配置失败";
		case NET_ERROR_SET_SIP_CFG: return "设置SIP配置失败";
		case NET_ERROR_GET_SIP_ABILITY: return "获取SIP能力失败";
		case NET_ERROR_GET_WIFI_AP_CFG: return "获取WIFI ap配置失败";
		case NET_ERROR_SET_WIFI_AP_CFG: return "设置WIFI ap配置失败";
		case NET_ERROR_GET_DECODE_POLICY: return "获取解码策略配置失败";
		case NET_ERROR_SET_DECODE_POLICY: return "设置解码策略配置失败";
		case NET_ERROR_TALK_REJECT: return "拒绝对讲";
		case NET_ERROR_TALK_OPENED: return "对讲被其他客户端打开";
		case NET_ERROR_TALK_RESOURCE_CONFLICIT: return "资源冲突";
		case NET_ERROR_TALK_UNSUPPORTED_ENCODE: return "不支持的语音编码格式";
		case NET_ERROR_TALK_RIGHTLESS: return "无权限";
		case NET_ERROR_TALK_FAILED: return "请求对讲失败";
		case NET_ERROR_GET_MACHINE_CFG: return "获取机器相关配置失败";
		case NET_ERROR_SET_MACHINE_CFG: return "设置机器相关配置失败";
		case NET_ERROR_GET_DATA_FAILED: return "设备无法获取当前请求数据";
		case NET_ERROR_MAC_VALIDATE_FAILED: return "MAC地址验证失败";
		case NET_ERROR_GET_INSTANCE: return "获取服务器实例失败";
		case NET_ERROR_JSON_REQUEST: return "生成的jason字符串错误";
		case NET_ERROR_JSON_RESPONSE: return "响应的jason字符串错误";
		case NET_ERROR_VERSION_HIGHER: return "协议版本低于当前使用的版本";
		case NET_SPARE_NO_CAPACITY: return "热备操作失败, 容量不足";
		case NET_ERROR_SOURCE_IN_USE: return "显示源被其他输出占用";
		case NET_ERROR_REAVE: return "高级用户抢占低级用户资源";
		case NET_ERROR_NETFORBID: return "禁止入网";
		case NET_ERROR_GETCFG_MACFILTER: return "获取MAC过滤配置失败";
		case NET_ERROR_SETCFG_MACFILTER: return "设置MAC过滤配置失败";
		case NET_ERROR_GETCFG_IPMACFILTER: return "获取IP/MAC过滤配置失败";
		case NET_ERROR_SETCFG_IPMACFILTER: return "设置IP/MAC过滤配置失败";
		case NET_ERROR_OPERATION_OVERTIME: return "当前操作超时";
		case NET_ERROR_SENIOR_VALIDATE_FAILED: return "高级校验失败";
		case NET_ERROR_DEVICE_ID_NOT_EXIST: return "设备ID不存在";
		case NET_ERROR_UNSUPPORTED: return "不支持当前操作";
		case NET_ERROR_PROXY_DLLLOAD: return "代理库加载失败";
		case NET_ERROR_PROXY_ILLEGAL_PARAM: return "代理用户参数不合法";
		case NET_ERROR_PROXY_INVALID_HANDLE: return "代理句柄无效";
		case NET_ERROR_PROXY_LOGIN_DEVICE_ERROR: return "代理登入前端设备失败";
		case NET_ERROR_PROXY_START_SERVER_ERROR: return "启动代理服务失败";
		case NET_ERROR_SPEAK_FAILED: return "请求喊话失败";
		case NET_ERROR_NOT_SUPPORT_F6: return "设备不支持此F6接口调用";
		default: return "未知错误";
    }
}



CFactoryDH::CFactoryDH()
{
    init();
}

CFactoryDH::~CFactoryDH()
{
    clean();
}






bool CFactoryDH::init()
{
    if (!m_init)
    {
        m_init = Api_DH::Api().m_pInit(0, 0);
        //NET_DVR_SetConnectTime(1000, 30);
        //NET_DVR_SetReconnect(3000);
        //NET_DVR_SetDVRMessage()
        if (!m_init)
        {
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("初始化SDK失败，错误原因：") + m_sLastError);
        }

		g_log.AddLog(string("初始化SDK成功"));
    }

    return m_init;
}


void CFactoryDH::clean()
{
    Api_DH::Api().m_pUninit();
}




IVideoServer* CFactoryDH::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new dh_videoserver();
}

bool CFactoryDH::searchDevice(std::vector<DeviceInfo>& devices){
    g_log.AddLog(std::string("searchDevice :"));
    DH::DEVICE_NET_INFO dhdevices[254];
    int retLen = 0;
    Api_DH::Api().m_pSearchDevices((char*)dhdevices, sizeof(dhdevices), &retLen, 1000, NULL);
    g_log.AddLog(QString("Api_DH::Api().m_pSearchDevices:%1 %2").arg(retLen).arg(sizeof(DH::DEVICE_NET_INFO)));
    for (int num = retLen / sizeof(DH::DEVICE_NET_INFO), i = 0; i < num; i++){
        DeviceInfo d;
        d.szIP = dhdevices[i].szIP;
        d.nPort = dhdevices[i].nPort;
        d.Factory = SISC_IPC_DH;
        devices.push_back(d);
    }
    return true;
}


static void timeDHToStd(DH::NET_TIME *pTimeDH, tm *pTimeStd)
{
	pTimeStd->tm_year = pTimeDH->dwYear - 1900;
	pTimeStd->tm_mon = pTimeDH->dwMonth - 1;
	pTimeStd->tm_mday = pTimeDH->dwDay;
	pTimeStd->tm_hour = pTimeDH->dwHour;
	pTimeStd->tm_min = pTimeDH->dwMinute;
	pTimeStd->tm_sec = pTimeDH->dwSecond;
}

static void timeStdToDH(tm *pTimeStd, DH::NET_TIME *pTimeDH)
{
	pTimeDH->dwYear = pTimeStd->tm_year + 1900;
	pTimeDH->dwMonth = pTimeStd->tm_mon + 1;
	pTimeDH->dwDay = pTimeStd->tm_mday;
	pTimeDH->dwHour = pTimeStd->tm_hour;
	pTimeDH->dwMinute = pTimeStd->tm_min;
	pTimeDH->dwSecond = pTimeStd->tm_sec;
}

// std::vector<dh_videoserver*> dh_videoserver::sServers;
// std::recursive_mutex dh_videoserver::sMtServers;

/*
 * 析构函数
 */
dh_videoserver::dh_videoserver()
{
//     std::lock_guard<std::recursive_mutex> lock(dh_videoserver::sMtServers);
//     sServers.push_back(this);
}

dh_videoserver::~dh_videoserver()
{
    logout();
//     std::lock_guard<std::recursive_mutex> lock(dh_videoserver::sMtServers);
//     for (int i = 0; i < sServers.size(); i++)
//     {
//         if (sServers[i] == this)
//         {
//             sServers.erase(sServers.begin() + i);
//             break;
//         }
//     }
}

static void CALLBACK PosCallBack(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, LDWORD dwUser)
{
	dh_videoserver * pThis = (dh_videoserver *)dwUser;
	{
		Mutex::ScopedLock lock(pThis->m_mtxPos);
		map<long long, stPos_DownPlay>::iterator itr = pThis->m_mapPosDownPlay.find(lPlayHandle);
		if (itr != pThis->m_mapPosDownPlay.end())
		{
			itr->second.iTotalSize = dwTotalSize * 1024;
			itr->second.iCurSize = dwDownLoadSize * 1024;
			itr->second.iPercent = ((float)dwDownLoadSize/(float)dwTotalSize)*100;
		}
	}
}

IVideoServer* dh_videoserver::clone()
{
 dh_videoserver *svr = new dh_videoserver();
// 	memcpy(svr, this, sizeof(dh_videoserver));
//     return svr;
 return svr;
}

bool dh_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
//     if (0 < m_lLoginHandle && !logout())
//     {
//         return false;
//     }

    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));

	int iError = 0;
    m_lLoginHandle = Api_DH::Api().m_pLogin((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo, &iError);
    if (m_lLoginHandle == 0)
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 登录失败，错误原因：") + m_sLastError);
        return false;
    }

	/*char szChannelNames[16*32];
	ZeroMemory(szChannelNames, sizeof(szChannelNames));
	int iChannelCount = 0;
    bool bRet = Api_DH::Api().m_pGetChannel(m_lLoginHandle, szChannelNames, 16*32, &iChannelCount, 500);
	if (!bRet)
	{
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("login 获取通道失败，错误原因：") + m_sLastError);
		return false;
	}
	g_log.AddLog(string(szChannelNames, 16 * 32));*/

	int nRetLen = 0;
	int iChannelCount = 0;
	DH::NET_DEV_CHN_COUNT_INFO stuChn = { sizeof(DH::NET_DEV_CHN_COUNT_INFO) };
	stuChn.stuVideoIn.dwSize = sizeof(stuChn.stuVideoIn);
	stuChn.stuVideoOut.dwSize = sizeof(stuChn.stuVideoOut);
	if (Api_DH::Api().m_pQueryDevState(m_lLoginHandle, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&stuChn, stuChn.dwSize, &nRetLen, 1000))
	{
		iChannelCount = stuChn.stuVideoIn.nMaxTotal;
	}
	else
	{
		iChannelCount = m_deviceInfo.byChanNum;
	}

	channels.clear();
	char szName[32+2];
	for (int i=1; i<=iChannelCount; i++)
	{
		ZeroMemory(szName, sizeof(szName));
		//memcpy(szName, szChannelNames + (i - 1)*32, 32);
		sprintf(szName, "通道%d", i);
		string strName = szName;
		channels.insert(std::make_pair(i, strName));
	}

    return true;
}

bool dh_videoserver::logout()
{
    if (m_lLoginHandle > 0 && !Api_DH::Api().m_pLogout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}



#define MAX_SEARCH_COUNT 1000
bool dh_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
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

		DH::NET_TIME stime;
		DH::NET_TIME etime;
		tm STime;
		tm ETime;
		_localtime64_s(&STime, (const time_t*)&timeStart);
		_localtime64_s(&ETime, (const time_t*)&timeEnd);

		timeStdToDH(&STime, &stime);
		timeStdToDH(&ETime, &etime);
		char szTime[512];
		ZeroMemory(szTime, 512);
		sprintf(szTime, " s_time:%d-%02d-%02d %02d:%02d:%02d e_time:%d-%02d-%02d %02d:%02d:%02d channel:%d linkID:%d", stime.dwYear, stime.dwMonth, stime.dwDay,
			stime.dwHour, stime.dwMinute, stime.dwSecond,
			etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond, nChannelId, m_lLoginHandle);
		g_log.AddLog(string("GetRecordFileList ") + string(szTime));

		DH::NET_RECORDFILE_INFO ifileinfo[MAX_SEARCH_COUNT];
		ZeroMemory(ifileinfo, sizeof(ifileinfo));
		int iMaxNum = 0;
		bool bRet = Api_DH::Api().m_pSearchFileByTime(m_lLoginHandle,
			nChannelId - 1,
			0,
			&stime,
			&etime,
			0,
			ifileinfo,
			sizeof(ifileinfo),
			&iMaxNum,
			5000, true);

		if (!bRet)
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("GetRecordFileList 查询录像失败，错误原因：") + m_sLastError);
			continue;
		}
		if (iMaxNum <= 0)
		{
			g_log.AddLog(string("GetRecordFileList 查询录像成功，录像个数为0"));
			continue;
		}

		{
			Mutex::ScopedLock lock(m_mtx);
			DH::NET_RECORDFILE_INFO item;
			RecordFile info;
			tm sTm;
			tm eTm;
			for (int i = 0; i < iMaxNum; i++)
			{
				item = ifileinfo[i];

				timeDHToStd(&item.starttime, &sTm);
				timeDHToStd(&item.endtime, &eTm);

				stime = item.starttime;
				etime = item.endtime;
// 				ZeroMemory(szTime, 512);
// 				sprintf(szTime, "channel%d %d-%02d-%02d %02d-%02d-%02d %d-%02d-%02d %02d-%02d-%02d", nChannelId,
// 					stime.dwYear, stime.dwMonth, stime.dwDay,
// 					stime.dwHour, stime.dwMinute, stime.dwSecond,
// 					etime.dwYear, etime.dwMonth, etime.dwDay, etime.dwHour, etime.dwMinute, etime.dwSecond);
// 				m_mapArcItem.insert(std::make_pair(string(szTime), item));

				info.channel = item.ch + 1;
				info.size = item.size * 1024;
				info.name = szTime;
				info.beginTime = mktime(&sTm);
				info.endTime = mktime(&eTm);
				info.setPrivateData(&ifileinfo[i], sizeof(DH::NET_RECORDFILE_INFO));
				files.push_back(info);

				char szLog[1024];
				ZeroMemory(szLog, 1024);
				sprintf(szLog, "GetRecordFileList 文件名:%s 文件大小:%d 通道:%d", item.filename, item.size, item.ch);
				g_log.AddLog(string(szLog));
			}
		}
	}
	return true;
}



bool dh_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 >= m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
		g_log.AddLog(string("downLoadByRecordFile 请先登录"));
        return false;
    }

// 	DH::NET_RECORDFILE_INFO info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, DH::NET_RECORDFILE_INFO>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("downLoadByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}

	DH::NET_RECORDFILE_INFO* pData = (DH::NET_RECORDFILE_INFO*)file.getPrivateData();
	g_log.AddLog(string("downLoadByRecordFile 文件名:") + saveFileName);
	hdl = Api_DH::Api().m_pDownloadByFile(m_lLoginHandle, pData, (char *)saveFileName, PosCallBack, (DWORD)this);
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
		pos.iTotalSize = file.size;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(hdl, pos));
	}

	return true;
}


bool  dh_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 >= m_lLoginHandle)
    {
		m_sLastError = "请先登录!";
		g_log.AddLog(string("PlayBackByRecordFile 请先登录"));
        return false;
	}

// 	DH::NET_RECORDFILE_INFO info;
// 	{
// 		Mutex::ScopedLock lock(m_mtx);
// 		map<string, DH::NET_RECORDFILE_INFO>::iterator itr = m_mapArcItem.find(file.name);
// 		if (itr == m_mapArcItem.end())
// 		{
// 			m_sLastError = "该文件不存在";
// 			g_log.AddLog(string("PlayBackByRecordFile 该文件不存在"));
// 			return false;
// 		}
// 
// 		info = itr->second;
// 	}
	DH::NET_RECORDFILE_INFO* pData = (DH::NET_RECORDFILE_INFO*)file.getPrivateData();
	playbackHandle = Api_DH::Api().m_pPlayBackByFile(m_lLoginHandle, pData, hwnd, PosCallBack, (DWORD)this);
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
		pos.iTotalSize = file.size;
		pos.iCurSize = 0;
		pos.iPercent = 0;
		Mutex::ScopedLock lock(m_mtxPos);
		m_mapPosDownPlay.insert(std::make_pair(playbackHandle, pos));
	}

	return true;
}

bool dh_videoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
	RecordFile file;
	{
		Mutex::ScopedLock lock(m_mtx);
		map<long long, RecordFile>::iterator itr = m_mapDownloadOrPlay.find(playbackHandle);
		if (itr == m_mapDownloadOrPlay.end())
		{
			m_sLastError = "该文件不存在";
			g_log.AddLog(string("SetPlayBack 该文件不存在"));
			return false;
		}
		file = itr->second;
	}
	__time64_t iPlayPos = (file.size * pos)/100;
	iPlayPos /= 1024;
    return FALSE != Api_DH::Api().m_pSeekPlayBack(playbackHandle, 0xffffffff, (unsigned int)iPlayPos);
}

bool dh_videoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
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
		if (!Api_DH::Api().m_pPausePlayBack(playbackHandle, TRUE))
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

		{
			Mutex::ScopedLock lock(m_mtx);
			m_mapDownloadOrPlay.erase(playbackHandle);
		}
		{
			Mutex::ScopedLock lock(m_mtxPos);
			m_mapPosDownPlay.erase(playbackHandle);
		}
		if (!Api_DH::Api().m_pStopPlayBack(playbackHandle))
		{
			m_sLastError = GetLastErrorString();
			g_log.AddLog(string("StopPlayBack 停止播放失败，错误原因：") + m_sLastError);
			return false;
		}
	}

    return true;
}

bool dh_videoserver::stopDownload(download_handle_t h)
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

    if (FALSE == Api_DH::Api().m_pStopDownload(h))
    {
		m_sLastError = GetLastErrorString();
		g_log.AddLog(string("stopDownload 停止下载失败，错误原因：") + m_sLastError);
        return false;
    }

    return true;
}

bool dh_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
	if (0 >= m_lLoginHandle)
	{
		m_sLastError = "请先登录!";
		g_log.AddLog(string("getPlayBackPos 请先登录"));
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
	g_log.AddLog(string("getPlayBackPos 找不到该回放"));
	return false;
}

bool dh_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed)
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