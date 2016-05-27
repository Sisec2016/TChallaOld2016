#include "BaoXinShengVideoServer.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
#include <thread>
#include <QFile>
#include <qdebug.h>
Log hk_log("BaoXinShengVideoServer");

extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{

    return new CFactory();
}


std::string GetLastErrorString()
{
    LONG error = ZLNET_GetLastError();
    switch (error)
    {
    case ZLNET_NOERROR: return "没有错误";
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
    case ZLNET_MULTIPLAY_NOCHANNEL: return "多画面预览中检测到通道数为";
    case ZLNET_TALK_INIT_ERROR: return "录音库初始化失败";
    case ZLNET_TALK_NOT_INIT: return "录音库未经初始化";
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
    case ZLNET_ERROR_SETCFG_RECORD: return "修改录象配置失败";
    case ZLNET_ERROR_SETCFG_485DECODER: return "修改解码器属性失败";
    case ZLNET_ERROR_SETCFG_232COM: return "修改232串口配置失败";
    case ZLNET_ERROR_SETCFG_ALARMIN: return "修改外部输入报警配置失败";
    case ZLNET_ERROR_SETCFG_ALARMDET: return "修改动态检测报警配置失败";
    case ZLNET_ERROR_SETCFG_SYSTIME: return "修改设备时间失败";
    case ZLNET_ERROR_SETCFG_PREVIEW: return "修改预览参数失败";
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
    case ZLNET_RENDER_SNAP_ERROR: return " Render库抓图出错";
    case ZLNET_RENDER_STEP_ERROR: return "Render";
    case ZLNET_RENDER_FRAMERATE_ERROR: return "Render库设置帧率出错";
    case ZLNET_GROUP_EXIST: return "组名已存在";
    case ZLNET_GROUP_RIGHTOVER: return "组的权限超出权限列表范围";
    case ZLNET_GROUP_HAVEUSER: return "组下有用户，不能删除";
    case ZLNET_GROUP_RIGHTUSE: return "组的某个权限被用户使用，不能出除";
    case ZLNET_GROUP_SAMENAME: return "新组名同已有组名重复";
    case ZLNET_USER_EXIST: return "用户已存在";
    case ZLNET_USER_NOEXIST: return " 用户不存在";
    case ZLNET_USER_RIGHTOVER: return " 用户权限超出组权限";
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
        case ZLNET_ERROR_GETCFG_GPRSCDMA: return " 获取CDMA\GPRS网络配置失败";
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
        case ZLNET_ERROR_DISCONNECT_AUTOREGISTER: return "断开主动注册服务器错误";
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

    }

    return "未知错误";
}



CFactory::CFactory()
{
    init();
}

CFactory::~CFactory()
{
    clean();
}



void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
    if (dwUser == 0)
    {
        return;
    }
    BaoXinShengVideoServer* psvr = (BaoXinShengVideoServer*)dwUser;
    psvr->reallogout();
    psvr->reLogin();
}


bool CFactory::init()
{

    if (!m_init)
    {

        m_init = ZLNET_Init(DisConnectFunc, (DWORD)this);
        if (!m_init)
        {

           m_sLastError = GetLastErrorString();
           hk_log.AddLog(std::string("init failed:") + m_sLastError);
        }


    }

    return m_init;
}


void CFactory::clean()
{
    ZLNET_Cleanup();
    m_init = false;
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new BaoXinShengVideoServer();
}
__int64 DownloadPosCaculator::getFileSize(const std::string& sFile)
{
    QFile f(QString::fromLocal8Bit(sFile.c_str()));
    if (f.exists())
    {
        return f.size();
    }
    else
    {
        return 0;
    }
}
DownloadPosCaculator::DownloadPosCaculator()
{
    mTotalSize = 0;
    mLastSize = 0;
    mLittleTimes = 0;
    mMaybeFinish = false;
}

int DownloadPosCaculator::getPos(__int64& totalSize, __int64& currentSize)
{
    currentSize = getFileSize(mSaveFile);
    mMaybeFinish = true;
    if (!mMaybeFinish)
    {
        mMaybeFinish = (mLastSize == currentSize && mLastSize > 1024 * 1024);
        if (currentSize - mLastSize <= 13 * 1024 * 3 && mLastSize > 1024 * 1024)
        {
            mLittleTimes++;
        }
        if (!mMaybeFinish)
        {
            mMaybeFinish = (mLittleTimes > 100);
        }
    }
    
    mLastSize = currentSize;
    totalSize = mTotalSize;
    if (totalSize > 0 && totalSize >= currentSize)
    {
        return currentSize * 100 / totalSize;
    }

    return 100;
}

std::vector<BaoXinShengVideoServer*> BaoXinShengVideoServer::sServers;
std::recursive_mutex BaoXinShengVideoServer::sMtServers;

/*
 * 析构函数
 */
BaoXinShengVideoServer::BaoXinShengVideoServer()
{
    std::lock_guard<std::recursive_mutex> lock(BaoXinShengVideoServer::sMtServers);
    sServers.push_back(this);
    m_pPlayFile = nullptr;
    m_lLoginHandle = NULL;
}

BaoXinShengVideoServer::~BaoXinShengVideoServer()
{

    logout();
    hk_log.AddLog(std::string("BaoXinShengVideoServer::~BaoXinShengVideoServer()"));
    std::lock_guard<std::recursive_mutex> lock(BaoXinShengVideoServer::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
    
}

IVideoServer* BaoXinShengVideoServer::clone()
{
    BaoXinShengVideoServer *svr = new BaoXinShengVideoServer();
    return svr;
}

bool BaoXinShengVideoServer::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
    if (mIP == IP && port == mPort && m_lLoginHandle > 0)
    {
        return true;
    }
    else{
        this->reallogout();
    }

	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));
    int err;
    m_lLoginHandle = ZLNET_Login((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo, &err);
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("ZLNET_Login failed:") + m_sLastError);
        return false;
    }
    mUser = user;
    mIP = IP;
    mPasswords = password;
    mPort = port;
    for (int i = 0; i < m_deviceInfo.byChanNum; i++)
    {
        channels[i + 1] = QString("channel%1").arg(i + 1).toStdString();
    }
    return true;
}
bool BaoXinShengVideoServer::reallogout()
{
    if (m_lLoginHandle >= 0 && !ZLNET_Logout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("logout failed:") + m_sLastError);
        return false;
    }
    else {
        hk_log.AddLog(std::string("BaoXinShengVideoServerlogout ok!"));
        m_lLoginHandle = 0;
    }

    return true;
}

bool BaoXinShengVideoServer::reLogin(){
    int err;
    m_lLoginHandle = ZLNET_Login((char*)mIP.c_str(), mPort,
        (char*)mUser.c_str(), (char*)mPasswords.c_str(),
        &m_deviceInfo, &err);
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("ZLNET_Login failed:") + m_sLastError);
        return false;
    }
    
    return true;
}

bool BaoXinShengVideoServer::logout()
{
    return true;

}
void NetTimeTo(const ZLNET_TIME& nt, __time64_t& t)
{
    struct tm Tm;
    Tm.tm_year = nt.dwYear - 1900;
    Tm.tm_mon = nt.dwMonth - 1;
    Tm.tm_mday = nt.dwDay;
    Tm.tm_hour = nt.dwHour;
    Tm.tm_min = nt.dwMinute;
    Tm.tm_sec = nt.dwSecond;

    t = _mktime64(&Tm);
}

void ToNetTime(const __time64_t& t, ZLNET_TIME& nt)
{
    struct tm Tm;
    _localtime64_s(&Tm, (const time_t*)&t);
    nt.dwYear = Tm.tm_year + 1900;
    nt.dwMonth = Tm.tm_mon + 1;
    nt.dwDay = Tm.tm_mday;
    nt.dwHour = Tm.tm_hour;
    nt.dwMinute = Tm.tm_min;
    nt.dwSecond = Tm.tm_sec;
}
bool BaoXinShengVideoServer::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    const int BYTE_ONE_SECONDS = 234947;
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = "请先登录!";
        hk_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }

    if (timeStart >= timeEnd)
    {
        m_sLastError = "时间范围不对!";
        hk_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }


    ZLNET_TIME stime, etime;
    ToNetTime(timeStart, stime);
    ToNetTime(timeEnd,etime);
    //stFileCond.dwChannelID = m_lChannelID;
    LPVOID dwFileHandle = 0;


    auto itr = channelVec.begin();
    RecordFile rf;
    for (; itr != channelVec.end(); itr++)
    {
        int nChannelId = *itr;

        BOOL dwFileHandle = ZLNET_FindFile(m_lLoginHandle,
            nChannelId - 1,
            0,
            (char*)"",
            &stime,
            &etime,
            false,
            2000);
        if (NULL != dwFileHandle)
        {
            ZLNET_RECORDFILE_INFO stVodFile = { 0 };
            hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
            while (ZLNET_FindNextFile(dwFileHandle, &stVodFile))
            {

                hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
                NetTimeTo(stVodFile.starttime, rf.beginTime);
                NetTimeTo(stVodFile.endtime, rf.endTime);

                rf.channel = nChannelId;
                rf.name = stVodFile.filename;
                rf.size = stVodFile.size * 1024;

                rf.setPrivateData(&stVodFile, sizeof(ZLNET_RECORDFILE_INFO));
                files.push_back(rf);
            }

            hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
            ZLNET_FindClose(dwFileHandle);
            hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
        }

        hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
    }

    hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
   return true;
}

void CALLBACK BTDownLoadPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, ZLNET_RECORDFILE_INFO recordfileinfo, DWORD dwUser)
{
    BaoXinShengVideoServer* svr = (BaoXinShengVideoServer *)dwUser;

    svr->UpdateDownloadPos(lPlayHandle, dwTotalSize, dwDownLoadSize, index, recordfileinfo);
}
//更新下载进度
void BaoXinShengVideoServer::UpdateDownloadPos(LONG iHandle, DWORD dwTotal, DWORD dwDownload, int index, ZLNET_RECORDFILE_INFO recordfileinfo)
{
}

bool BaoXinShengVideoServer::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = "请先登录!";
        hk_log.AddLog("downLoadByRecordFile 请先登录!");
        return false;
    }

    ZLNET_TIME stime, etime;
    ToNetTime(file.beginTime, stime);
    ToNetTime(file.endTime, etime);
    hdl = (download_handle_t)ZLNET_DownloadByTime(m_lLoginHandle, file.channel - 1, 0, &stime, &etime, (char *)saveFileName, BTDownLoadPos,
                (DWORD)this);
    if (NULL == hdl)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("ZLNET_GetFileByTime failed:") + m_sLastError + " 文件：" + saveFileName);
        return false;
    }
//     int enSpeed = ZLNET_DOWNLOAD_SPEED_EIGHT;
//     int bRet = ZLNET_PlayBackControl(hdl, ZLNET_PLAY_CTRL_SETPLAYSPEED, &enSpeed);

    QString qsFile(QString::fromLocal8Bit(saveFileName));
    QFile::remove(qsFile);

    mMpDownloadRecords[hdl] = file;
    return true;
}

void CALLBACK PlayCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser)
{
    if (dwUser == 0)
    {
        return;
    }

}

bool  BaoXinShengVideoServer::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    ZLNET_TIME stime, etime;
    ToNetTime(file.beginTime, stime);
    ToNetTime(file.endTime, etime);
    playbackHandle = ZLNET_PlayBackByTime(m_lLoginHandle, file.channel - 1, &stime, &etime, hwnd, PlayCallBack, (DWORD)this);
    if (NULL == playbackHandle)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_PlayBackControl failed:") + m_sLastError);
        return false;
    }

    m_pPlayFile = &file;
    return true;
}

bool BaoXinShengVideoServer::SetPlayBack(play_handle_t playbackHandle, __int32 pos)
{
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    BOOL bRet = ZLNET_SeekPlayBack(playbackHandle, (m_pPlayFile->endTime - m_pPlayFile->beginTime) * pos / 100, 0xffffffff);
    if (!bRet)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("ZLNET_SeekPlayBack failed:") + m_sLastError);
        return false;
    }

    return true;
}

bool BaoXinShengVideoServer::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    int bRet = ZLNET_StopPlayBack(playbackHandle);
    if (TRUE != bRet)
    {
        m_sLastError = GetLastErrorString();
        return false;
        
    }

    return true;
}



bool BaoXinShengVideoServer::stopDownload(download_handle_t h)
{

    if (TRUE != ZLNET_StopDownload(h))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }
    
    mMpDownloadRecords.erase(h);
    return true;
}


bool BaoXinShengVideoServer::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed){
    
    return false;
}