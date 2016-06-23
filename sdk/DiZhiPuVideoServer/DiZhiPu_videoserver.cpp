#include "DiZhiPu_videoserver.h"
#include <qdatetime.h>
#include <QObject>
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <boost/thread.hpp>
#include <boost/thread/lock_guard.hpp>
#include <QTimer>
#include <QProcess>
//#include "windowutils.h"
#include "log.h"
#include "netsdk.h"
#include "H264Play.h"
#include <algorithm>

#define ONEDAY   24 * 60 * 60
#pragma comment(lib,"ws2_32.lib")
#ifndef NEW_SERVER
extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{
    Log::instance().initFileName("gzll");
    return new CFactory();
}
#endif


std::string GZLL_GetLastErrorString(int error)
{
    switch (error)
    {
        case H264_DVR_NOERROR: return std::string("没有错误");
        case H264_DVR_SUCCESS: return std::string("返回成功");
        case H264_DVR_SDK_NOTVALID: return std::string("非法请求");
        case H264_DVR_NO_INIT: return std::string("SDK未经初始化");
        case H264_DVR_ILLEGAL_PARAM: return std::string("用户参数不合法");
        case H264_DVR_INVALID_HANDLE: return std::string("句柄无效");
        case H264_DVR_SDK_UNINIT_ERROR	: return std::string("SDK清理出错");
        case H264_DVR_SDK_TIMEOUT: return std::string("等待超时");
        case H264_DVR_SDK_MEMORY_ERROR: return std::string("内存错误，创建内存失败");
        case H264_DVR_SDK_NET_ERROR: return std::string("网络错误");
        case H264_DVR_SDK_OPEN_FILE_ERROR: return std::string("打开文件失败");
        case H264_DVR_SDK_UNKNOWNERROR: return std::string("未知错误");
        case H264_DVR_DEV_VER_NOMATCH: return std::string("收到数据不正确，可能版本不匹配");
        case H264_DVR_SDK_NOTSUPPORT: return std::string("版本不支持");
        case H264_DVR_OPEN_CHANNEL_ERROR: return std::string("打开通道失败");
        case H264_DVR_CLOSE_CHANNEL_ERROR: return std::string("关闭通道失败");
        case H264_DVR_SUB_CONNECT_ERROR: return std::string("建立媒体子连接失败");
        case H264_DVR_SUB_CONNECT_SEND_ERROR: return std::string("媒体子连接通讯失败");
        case H264_DVR_NATCONNET_REACHED_MAX: return std::string("Nat视频链接达到最大，不允许新的Nat视频链接");
        case H264_DVR_NOPOWER: return std::string("无权限");
        case H264_DVR_PASSWORD_NOT_VALID: return std::string("账号密码不对");
        case H264_DVR_LOGIN_USER_NOEXIST: return std::string("用户不存在");
        case H264_DVR_USER_LOCKED: return std::string("该用户被锁定");
        case H264_DVR_USER_IN_BLACKLIST: return std::string("该用户不允许访问(在黑名单中)");
        case H264_DVR_USER_HAS_USED: return std::string("该用户以登陆");
        case H264_DVR_USER_NOT_LOGIN: return std::string("该用户没有登陆");
        case H264_DVR_CONNECT_DEVICE_ERROR: return std::string("可能设备不存在");
        case H264_DVR_ACCOUNT_INPUT_NOT_VALID: return std::string("用户管理输入不合法");
        case H264_DVR_ACCOUNT_OVERLAP: return std::string("索引重复");
        case H264_DVR_ACCOUNT_OBJECT_NONE: return std::string("不存在对象, 用于查询时");
        case H264_DVR_ACCOUNT_OBJECT_NOT_VALID: return std::string("不存在对象");
        case H264_DVR_ACCOUNT_OBJECT_IN_USE: return std::string("对象正在使用");
        case H264_DVR_ACCOUNT_SUBSET_OVERLAP: return std::string("子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)");
        case H264_DVR_ACCOUNT_PWD_NOT_VALID: return std::string("密码不正确");
        case H264_DVR_ACCOUNT_PWD_NOT_MATCH: return std::string("密码不匹配");
        case H264_DVR_ACCOUNT_RESERVED: return std::string("保留帐号");
        case H264_DVR_OPT_RESTART: return std::string("保存配置后需要重启应用程序");
        case H264_DVR_OPT_REBOOT: return std::string("需要重启系统");
        case H264_DVR_OPT_FILE_ERROR: return std::string("写文件出错");
        case H264_DVR_OPT_CAPS_ERROR: return std::string("配置特性不支持");
        case H264_DVR_OPT_VALIDATE_ERROR: return std::string("配置校验失败");
        case H264_DVR_OPT_CONFIG_NOT_EXIST: return std::string("请求或者设置的配置不存在");
        case H264_DVR_CTRL_PAUSE_ERROR: return std::string("暂停失败");
        case H264_DVR_SDK_NOTFOUND: return std::string("查找失败，没有找到对应文件");
        case H264_DVR_CFG_NOT_ENABLE: return std::string("配置未启用");
        case H264_DVR_DECORD_FAIL: return std::string("解码失败");
        case H264_DVR_SOCKET_ERROR: return std::string("创建套节字失败");
        case H264_DVR_SOCKET_CONNECT: return std::string("连接套节字失败");
        case H264_DVR_SOCKET_DOMAIN: return std::string("域名解析失败");
        case H264_DVR_SOCKET_SEND: return std::string("发送数据失败");
        case H264_DVR_ARSP_NO_DEVICE: return std::string("没有获取到设备信息，设备应该不在线");
        case H264_DVR_ARSP_BUSING: return std::string("ARSP服务繁忙");
        case H264_DVR_ARSP_BUSING_SELECT: return std::string("ARSP服务繁忙,select失败");
        case H264_DVR_ARSP_BUSING_RECVICE: return std::string("ARSP服务繁忙,recvice失败");
        case H264_DVR_CONNECTSERVER_ERROR: return std::string("连接服务器失败");
        case H264_DVR_CONNECT_FULL: return std::string("服务器连接数已满");
        case H264_DVR_PIRATESOFTWARE: return std::string("设备盗版");
    }

    return "";
}

std::string GZLL_GetLastErrorString()
{

    return GZLL_GetLastErrorString(H264_DVR_GetLastError());
}

CFactory::CFactory()
{
    init();
}

CFactory::~CFactory()
{
    clean();
}



bool CFactory::init()
{
    if (!m_init)
    {

        m_init = H264_DVR_Init(nullptr,  0);
        if (!m_init)
        {
           m_sLastError = GZLL_GetLastErrorString();
        }
        //H264_DVR_SetDVRMessCallBack(MessCallBack,(DWORD)this);

        H264_DVR_SetConnectTime(5000, 3);
    }

    return m_init;

}

IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new gzll_videoserver();
}

bool CFactory::searchDevice(std::vector<DeviceInfo>& devices){
    Log::instance().AddLog(std::string("gzll_videoserver::searchDevice"));
    SDK_CONFIG_NET_COMMON_V2 m_Device[100] = { 0 };
    memset(&m_Device, 0, sizeof(SDK_CONFIG_NET_COMMON_V2)* 100);
    int nRetLength = 0;
    devices.clear();
    bool bRet = H264_DVR_SearchDevice((char*)m_Device, sizeof(SDK_CONFIG_NET_COMMON_V2)* 100, &nRetLength, 1000);
    if (bRet)
    {
        Log::instance().AddLog(std::string("gzll_videoserver::bRet"));
        DeviceInfo d;

        int ncount = nRetLength / sizeof(SDK_CONFIG_NET_COMMON_V2);
        Log::instance().AddLog(QString("%1 %2").arg(nRetLength).arg(ncount));
        for (int i = 0; i < ncount; i++)
        {
            char sTmp[20] = { 0 };
            struct in_addr in;
            in.s_addr = m_Device[i].HostIP.l;
            d.szIP = inet_ntoa(in);
            d.nPort = m_Device[i].TCPPort;
            d.Factory = this->factory();
            devices.push_back(d);
        }
    }

    return devices.size() > 0;
}

void CFactory::clean()
{
    H264_DVR_Cleanup();
}
std::vector<gzll_videoserver*> gzll_videoserver::sServers;
boost::recursive_mutex gzll_videoserver::sMtServers;

gzll_videoserver::gzll_videoserver() :m_lLoginHandle(0)
{
    boost::lock_guard<boost::recursive_mutex> lock(gzll_videoserver::sMtServers);
    sServers.push_back(this);
}

gzll_videoserver::~gzll_videoserver()
{
    logout();
    boost::lock_guard<boost::recursive_mutex> lock(gzll_videoserver::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* gzll_videoserver::clone()
{
    gzll_videoserver *svr = new gzll_videoserver();
    return svr;
}




bool gzll_videoserver::login(const char* IP, __int32 port, const char* user,
                             const char* password, std::map<__int32, std::string>& channels)
{
    Log::instance().AddLog(std::string("gzll_videoserver::login"));
    H264_DVR_DEVICEINFO OutDev;
	memset(&OutDev, 0, sizeof(H264_DVR_DEVICEINFO));
    int nError = 0;

	channels.clear();

    H264_DVR_SetConnectTime(3000, 1);

    m_lLoginHandle = H264_DVR_Login((char*)IP, port, (char*)user, (char*)password, &OutDev, &nError, TCPSOCKET);
    if (m_lLoginHandle <= 0)
    {
        m_sLastError = GZLL_GetLastErrorString(nError);
        Log::instance().AddLog(std::string("gzll_videoserver::H264_DVR_Login failed") + m_sLastError + IP);
        return false;
    }

    for (int i = 0; i < OutDev.byChanNum + OutDev.iDigChannel; i++)
    {
        channels[i];
    }

    return true;
}

bool gzll_videoserver::logout()
{    

    if (m_lLoginHandle != 0 && !H264_DVR_Logout(m_lLoginHandle))
    {
        m_sLastError = GZLL_GetLastErrorString();
        return false;
    }

    return true;
}

void NetTimeToTM(const SDK_SYSTEM_TIME& nt, tm& t)
{
    t.tm_year = nt.year - 1900;
    t.tm_mon = nt.month - 1;
    t.tm_mday = nt.day;
    t.tm_hour = nt.hour;
    t.tm_min = nt.minute;
    t.tm_sec = nt.second;
}

void TMToNetTime(const tm& t, H264_DVR_TIME& nt)
{
    nt.dwYear = t.tm_year + 1900;
    nt.dwMonth = t.tm_mon + 1;
    nt.dwDay = t.tm_mday;
    nt.dwHour = t.tm_hour;
    nt.dwMinute = t.tm_min;
    nt.dwSecond = t.tm_sec;
}


bool gzll_videoserver::downLoad(const char* saveFileName, int nChannelId,__time64_t timeStart,
                                __time64_t timeEnd, download_handle_t& hdl)
{
    struct tm Tm;
    _localtime64_s(&Tm, (const time_t*)&timeStart);

    H264_DVR_FINDINFO info;
    memset(&info, 0, sizeof(info));
    info.nChannelN0 = nChannelId;
    info.nFileType = SDK_RECORD_ALL;
    TMToNetTime(Tm, info.startTime);
    _localtime64_s(&Tm, (const time_t*)&timeEnd);
    TMToNetTime(Tm, info.endTime);

    hdl = H264_DVR_GetFileByTime(m_lLoginHandle, &info,(char *)saveFileName,true, nullptr, 0);
    if (hdl <= 0)
    {
        m_sLastError = std::string("下载失败！错误为:") + GZLL_GetLastErrorString();
        Log::instance().AddLog(QString::fromLocal8Bit(m_sLastError.c_str()));
        return false;
    }


    return true;
}

bool gzll_videoserver::GetRecordFileList(std::vector<RecordFile>& files, __int32 nChannelId, __time64_t timeStart,
                                         __time64_t timeEnd)
{

	H264_DVR_FINDINFO info;
	memset(&info, 0, sizeof(info));
	info.nChannelN0 = nChannelId;
	info.nFileType = SDK_RECORD_ALL;

	H264_DVR_TIME stime, etime;
    struct tm Tm;
    _localtime64_s(&Tm, (const time_t*)&timeStart);
	TMToNetTime(Tm, stime);
    _localtime64_s(&Tm, (const time_t*)&timeEnd);
	TMToNetTime(Tm, etime);

	__time64_t everytime, begintime, endtime;
	begintime = timeStart;

	struct tm Tms = { 0, 0, 0, stime.dwDay, stime.dwMonth - 1, stime.dwYear - 1900 };
	everytime = mktime(&Tms);
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
	
		tm STime;
		tm ETime;
		_localtime64_s(&STime, (const time_t*)&begintime);
		_localtime64_s(&ETime, (const time_t*)&endtime);
		TMToNetTime(STime, info.startTime);
		TMToNetTime(ETime, info.endTime);


		H264_DVR_FILE_DATA nriFileinfo[2000];
		int fileCount;
		long hdl = H264_DVR_FindFile(m_lLoginHandle, &info, nriFileinfo, sizeof(nriFileinfo) / sizeof(H264_DVR_FILE_DATA), &fileCount);
		if (hdl <= 0)
		{
			m_sLastError = std::string("查询失败！错误为:") + GZLL_GetLastErrorString();
			return false;
		}
		else
		{
			if (fileCount > 0)
			{
				RecordFile f;
				for (int i = 0; i < fileCount; i++)
				{
					if (nriFileinfo[i].size>0)//视频文件必须大于0(测试中有发现文件大小为0情况,所以必须过滤掉改部分)
					{
						struct tm Tm;
						NetTimeToTM(nriFileinfo[i].stBeginTime, Tm);
						f.beginTime = _mktime64(&Tm);
						NetTimeToTM(nriFileinfo[i].stEndTime, Tm);
						f.endTime = _mktime64(&Tm);

						f.channel = nChannelId;
						f.name = nriFileinfo[i].sFileName;
						f.size = nriFileinfo[i].size * 1024;
						f.setPrivateData(&nriFileinfo[i], sizeof(H264_DVR_FILE_DATA));
						files.push_back(f);
					}
				}
			}

		}
	}
    return true;
}

bool gzll_videoserver::GetRecordFileList(std::vector<RecordFile>& files, /*__int32 nChannelId*/const std::vector<int>& channelVec, __time64_t timeStart,
                                __time64_t timeEnd){
    for (int i = 0; i < channelVec.size(); i++){
        if (!GetRecordFileList(files, channelVec[i], timeStart, timeEnd)){
            return false;
        }
    }
    return true;
}

bool gzll_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{

    if (0 == m_lLoginHandle)
    {
        m_sLastError = std::string ("请先登录!");
        return false;
    }


    //qDebug()<<codec->toUnicode("当前下载的文件信息:")<<H264_DVR_FILE_DATA(nFileinfo[fileInfoIndex]).ch <<H264_DVR_FILE_DATA(nFileinfo[fileInfoIndex]).size<<H264_DVR_FILE_DATA(nFileinfo[fileInfoIndex]).sFileName;
    H264_DVR_FILE_DATA* pData =  (H264_DVR_FILE_DATA*)file.getPrivateData();
    hdl = H264_DVR_GetFileByName(m_lLoginHandle, pData,(char *)saveFileName);
    if (0 == hdl)
    {
        m_sLastError = GZLL_GetLastErrorString();
        return false;
    }



    return true;
}



bool gzll_videoserver::stopDownload(download_handle_t h)
{
    //if (!H264_DVR_StopGetFile((long)h))
    {
       // m_sLastError = GZLL_GetLastErrorString();
       // return false;
    }


    return true;
}

bool gzll_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{

    if (0 == m_lLoginHandle)
    {
        m_sLastError = std::string ("请先登录!");
        return false;
    }

    H264_DVR_FILE_DATA* fileData=(H264_DVR_FILE_DATA*)file.getPrivateData();
    fileData->hWnd = hwnd;
    playbackHandle = H264_DVR_PlayBackByName(m_lLoginHandle, fileData, nullptr, NULL, 0);
    Log::instance().AddLog(QString("gzll,playbackHandle:%1").arg(m_hPlayBack));
    if (playbackHandle == 0)
    {
        H264_DVR_StopPlayBack(m_hPlayBack);
        m_sLastError = GZLL_GetLastErrorString();
    }
    return playbackHandle != 0;
}

bool gzll_videoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
    return H264_DVR_SetPlayPos(playbackHandle, pos / 100.0);
}

bool gzll_videoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
    *pos = H264_DVR_GetPlayPos(playbackHandle) * 100;
    return true;
}


bool gzll_videoserver::StopPlayBack(__int64 playbackHandle,__int32 mPause)
{
    if (0 == m_lLoginHandle)
    {
        m_sLastError = std::string ("请先登录!");
        return false;
    }
    if( H264_DVR_StopPlayBack(playbackHandle))
    {
        return true;
    }
    else
    {
       return false;
    }
}

