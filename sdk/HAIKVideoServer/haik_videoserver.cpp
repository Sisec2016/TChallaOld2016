#include "haik_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
#include <thread>
#include <QFile>
#include <qdebug.h>
Log hk_log("haik_videoserver");

extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{

    return new CFactory();
}

std::string GetLastErrorString()
{
    LONG error;
    std::string sError = NET_DVR_GetErrorMsg(&error);

    switch (error)
    {
        case NET_DVR_NOERROR: return "NOERROR";
        case NET_DVR_PASSWORD_ERROR: return "用户名密码错误";
        case NET_DVR_NOENOUGHPRI: return "权限不足";
        case NET_DVR_NOINIT: return "没有初始化";
        case NET_DVR_CHANNEL_ERROR: return "通道号错误";
        case NET_DVR_OVER_MAXLINK: return "连接到DVR的客户端个数超过最大";
        case NET_DVR_VERSIONNOMATCH: return "版本不匹配";
        case NET_DVR_NETWORK_FAIL_CONNECT: return "连接服务器失败";
        case NET_DVR_NETWORK_SEND_ERROR: return "向服务器发送失败";
        case NET_DVR_NETWORK_RECV_ERROR: return "从服务器接收数据失败";
        case NET_DVR_NETWORK_RECV_TIMEOUT: return "从服务器接收数据超时";
        case NET_DVR_NETWORK_ERRORDATA: return "传送的数据有误";
        case NET_DVR_ORDER_ERROR: return "调用次序错误";
        case NET_DVR_OPERNOPERMIT: return "无此权限";
        case NET_DVR_COMMANDTIMEOUT: return "DVR命令执行超时";
        case NET_DVR_ERRORSERIALPORT: return "串口号错误";
        case NET_DVR_ERRORALARMPORT: return "报警端口错误";
        case NET_DVR_PARAMETER_ERROR: return "参数错误";
        case NET_DVR_CHAN_EXCEPTION: return "服务器通道处于错误状态";
        case NET_DVR_NODISK: return "没有硬盘";
        case NET_DVR_ERRORDISKNUM: return "硬盘号错误";
        case NET_DVR_DISK_FULL: return "服务器硬盘满";
        case NET_DVR_DISK_ERROR: return "服务器硬盘出错";
        case NET_DVR_NOSUPPORT: return "服务器不支持";
        case NET_DVR_BUSY: return "服务器忙";
        case NET_DVR_MODIFY_FAIL: return "服务器修改不成功";
        case NET_DVR_PASSWORD_FORMAT_ERROR: return "密码输入格式不正确";
        case NET_DVR_DISK_FORMATING: return "硬盘正在格式化，不能启动操作";
        case NET_DVR_DVRNORESOURCE: return "DVR资源不足";
        case NET_DVR_DVROPRATEFAILED: return "DVR操作失败";
        case NET_DVR_OPENHOSTSOUND_FAIL: return "打开PC声音失败";
        case NET_DVR_DVRVOICEOPENED: return "服务器语音对讲被占用";
        case NET_DVR_TIMEINPUTERROR: return "时间输入不正确";
        case NET_DVR_NOSPECFILE: return "回放时服务器没有指定的文件";
        case NET_DVR_CREATEFILE_ERROR: return "创建文件出错";
        case NET_DVR_FILEOPENFAIL: return "打开文件出错";
        case NET_DVR_OPERNOTFINISH: return "上次的操作还没有完成";
        case NET_DVR_GETPLAYTIMEFAIL: return "获取当前播放的时间出错";
        case NET_DVR_PLAYFAIL: return "播放出错";
        case NET_DVR_FILEFORMAT_ERROR: return "文件格式不正确";
        case NET_DVR_DIR_ERROR: return "路径错误";
        case NET_DVR_ALLOC_RESOURCE_ERROR: return "资源分配错误";
        case NET_DVR_AUDIO_MODE_ERROR: return "声卡模式错误";
        case NET_DVR_NOENOUGH_BUF: return "缓冲区太小";
        case NET_DVR_CREATESOCKET_ERROR: return "创建SOCKET出错";
        case NET_DVR_SETSOCKET_ERROR: return "设置SOCKET出错";
        case NET_DVR_MAX_NUM: return "个数达到最大";
        case NET_DVR_USERNOTEXIST: return "用户不存在";
        case NET_DVR_WRITEFLASHERROR: return "写FLASH出错";
        case NET_DVR_UPGRADEFAIL: return "DVR升级失败";
        case NET_DVR_CARDHAVEINIT: return "解码卡已经初始化过";
        case NET_DVR_PLAYERFAILED: return "调用播放库中某个函数失败";
        case NET_DVR_MAX_USERNUM: return "设备端用户数达到最大";
        case NET_DVR_GETLOCALIPANDMACFAIL: return "获得客户端的IP地址或物理地址失败";
        case NET_DVR_NOENCODEING: return "该通道没有编码";
        case NET_DVR_IPMISMATCH: return "IP地址不匹配";
        case NET_DVR_MACMISMATCH: return "MAC地址不匹配";
        case NET_DVR_UPGRADELANGMISMATCH: return "升级文件语言不匹配";
        case NET_DVR_MAX_PLAYERPORT: return "播放器路数达到最大";
        case NET_DVR_NOSPACEBACKUP: return "备份设备中没有足够空间进行备份";
        case NET_DVR_NODEVICEBACKUP: return "没有找到指定的备份设备";
        case NET_DVR_PICTURE_BITS_ERROR: return "图像素位数不符，限24色";
        case NET_DVR_PICTURE_DIMENSION_ERROR: return "图片高*宽超限， 限128*256";
        case NET_DVR_PICTURE_SIZ_ERROR: return "图片大小超限，限100K";
        case NET_DVR_LOADPLAYERSDKFAILED: return "载入当前目录下Player Sdk出错";
        case NET_DVR_LOADPLAYERSDKPROC_ERROR: return "找不到Player Sdk中某个函数入口";
        case NET_DVR_LOADDSSDKFAILED: return "载入当前目录下DSsdk出错";
        case NET_DVR_LOADDSSDKPROC_ERROR: return "找不到DsSdk中某个函数入口";
        case NET_DVR_DSSDK_ERROR: return "调用硬解码库DsSdk中某个函数失败";
        case NET_DVR_VOICEMONOPOLIZE: return "声卡被独占";
        case NET_DVR_JOINMULTICASTFAILED: return "加入多播组失败";
        case NET_DVR_CREATEDIR_ERROR: return "建立日志文件目录失败";
        case NET_DVR_BINDSOCKET_ERROR: return "绑定套接字失败";
        case NET_DVR_SOCKETCLOSE_ERROR: return "socket连接中断，此错误通常是由于连接中断或目的地不可达";
        case NET_DVR_USERID_ISUSING: return "注销时用户ID正在进行某操作";
        case NET_DVR_SOCKETLISTEN_ERROR: return "监听失败";
        case NET_DVR_PROGRAM_EXCEPTION: return "程序异常";
        case NET_DVR_WRITEFILE_FAILED: return "写文件失败";
        case NET_DVR_FORMAT_READONLY: return "禁止格式化只读硬盘";
        case NET_DVR_WITHSAMEUSERNAME: return "用户配置结构中存在相同的用户名";
        case NET_DVR_DEVICETYPE_ERROR : return "导入参数时设备型号不匹配";
        case NET_DVR_LANGUAGE_ERROR: return "导入参数时语言不匹配";
        case NET_DVR_PARAVERSION_ERROR : return "导入参数时软件版本不匹配";
        case NET_DVR_IPCHAN_NOTALIVE: return "预览时外接IP通道不在线";
        case NET_DVR_RTSP_SDK_ERROR: return "加载高清IPC通讯库StreamTransClient.dll失败";
        case NET_DVR_CONVERT_SDK_ERROR: return "加载转码库失败";
        case NET_DVR_IPC_COUNT_OVERFLOW: return "超出最大的ip接入通道数";
        case NET_DVR_MAX_ADD_NUM: return "添加标签(一个文件片段64)等个数达到最大";
        case NET_DVR_PARAMMODE_ERROR: return "图像增强仪，参数模式错误（用于硬件设置时，客户端进行软件设置时错误值）";
        case NET_DVR_CODESPITTER_OFFLINE: return "视频综合平台，码分器不在线";
        case NET_DVR_BACKUP_COPYING: return "设备正在备份";
        case NET_DVR_CHAN_NOTSUPPORT: return "通道不支持该操作";
        case NET_DVR_CALLINEINVALID : return "高度线位置太集中或长度线不够倾斜";
        case NET_DVR_CALCANCELCONFLICT: return "取消标定冲突，如果设置了规则及全局的实际大小尺寸过滤";
        case NET_DVR_CALPOINTOUTRANGE: return "标定点超出范围";
        case NET_DVR_FILTERRECTINVALID: return "尺寸过滤器不符合要求";
        case NET_DVR_DDNS_DEVOFFLINE: return "设备没有注册到ddns上";
        case NET_DVR_DDNS_INTER_ERROR : return "DDNS 服务器内部错误";
        case NET_DVR_FUNCTION_NOT_SUPPORT_OS : return "此功能不支持该操作系统";
        case NET_DVR_DEC_CHAN_REBIND : return "解码通道绑定显示输出次数受限";
        case NET_DVR_INTERCOM_SDK_ERROR: return "加载当前目录下的语音对讲库失败";
        case NET_DVR_NO_CURRENT_UPDATEFILE: return "没有正确的升级包";
        case NET_DVR_USER_NOT_SUCC_LOGIN: return "用户还没登陆成功";
        case NET_DVR_USE_LOG_SWITCH_FILE: return "正在使用日志开关文件";
        case NET_DVR_POOL_PORT_EXHAUST: return "端口池中用于绑定的端口已耗尽";
        case NET_DVR_PACKET_TYPE_NOT_SUPPORT: return "码流封装格式错误";
        case NET_DVR_ALIAS_DUPLICATE: return "别名重复";
    }

     return sError;
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
#ifdef LNM_TEST
    return true;
#endif

    if (!m_init)
    {

        m_init = NET_DVR_Init();
        NET_DVR_SetConnectTime(1000, 30);
        NET_DVR_SetReconnect(3000);
        //NET_DVR_SetDVRMessage()
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
    NET_DVR_Cleanup();
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new haik_videoserver();
}


std::vector<haik_videoserver*> haik_videoserver::sServers;
std::recursive_mutex haik_videoserver::sMtServers;

/*
 * 析构函数
 */
haik_videoserver::haik_videoserver()
{
    std::lock_guard<std::recursive_mutex> lock(haik_videoserver::sMtServers);
    sServers.push_back(this);
}

haik_videoserver::~haik_videoserver()
{

    //logout();
    hk_log.AddLog(std::string("haik_videoserver::~haik_videoserver()"));
    std::lock_guard<std::recursive_mutex> lock(haik_videoserver::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* haik_videoserver::clone()
{
    haik_videoserver *svr = new haik_videoserver();
    return svr;
}

bool haik_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
    logout();
	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));
    m_lLoginHandle = NET_DVR_Login_V30((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);
    if (m_lLoginHandle == -1)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_Login_V30 failed:") + m_sLastError);
        return false;
    }

    NET_DVR_PICCFG_V40 channelInfo;
    DWORD returnBytes = 0;
    hk_log.AddLog(QString("m_deviceInfo.byChanNum:%1, m_deviceInfo.byIPChanNum:%2 ")
                           .arg(m_deviceInfo.byChanNum).arg(m_deviceInfo.byIPChanNum));
    for (int i = 0; i < m_deviceInfo.byChanNum; i++)
    {
        if (NET_DVR_GetDVRConfig(m_lLoginHandle, NET_DVR_GET_PICCFG_V40,
                             m_deviceInfo.byStartChan + i, &channelInfo,
                             sizeof(NET_DVR_PICCFG_V40), &returnBytes) != FALSE)
        {
            channels[m_deviceInfo.byStartChan + i] = std::string ((char *)channelInfo.sChanName);
        }
        else
        {
            channels[m_deviceInfo.byStartChan + i];
        }
    }

    for (int i = 0; i < m_deviceInfo.byIPChanNum + 255*m_deviceInfo.byHighDChanNum; i++)
    {
        if (NET_DVR_GetDVRConfig(m_lLoginHandle, NET_DVR_GET_PICCFG_V40,
                             m_deviceInfo.byStartDChan + i, &channelInfo,
                             sizeof(NET_DVR_PICCFG_V40), &returnBytes) != FALSE)
        {
            channels[m_deviceInfo.byStartDChan + i] = std::string ((char *)channelInfo.sChanName);
        }
        else
        {
            channels[m_deviceInfo.byStartDChan + i];
        }
    }


    return true;
}

bool haik_videoserver::logout()
{
    #ifdef LNM_TEST
    return true;
    #endif

    if (m_lLoginHandle != -1 && !NET_DVR_Logout(m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("logout failed:") + m_sLastError);
        m_lLoginHandle = -1;
        return false;
    }
    else {
        m_lLoginHandle = -1;
        hk_log.AddLog(std::string("haik_videoserverlogout ok!"));
    }

    return true;
}

void NetTimeToTM(const NET_DVR_TIME& nt, tm& t)
{
    t.tm_year = nt.dwYear - 1900;
    t.tm_mon = nt.dwMonth - 1;
    t.tm_mday = nt.dwDay;
    t.tm_hour = nt.dwHour;
    t.tm_min = nt.dwMinute;
    t.tm_sec = nt.dwSecond;
}
void TMToNetTime(const tm& t, NET_DVR_TIME& nt)
{
    nt.dwYear = t.tm_year + 1900;
    nt.dwMonth = t.tm_mon + 1;
    nt.dwDay = t.tm_mday;
    nt.dwHour = t.tm_hour;
    nt.dwMinute = t.tm_min;
    nt.dwSecond = t.tm_sec;
}
void addLog(const char* sLog, int nLine)
{

    hk_log.AddLog(QString("%1 %2").arg(nLine).arg(sLog));
}

void sheNET_DVR_FindClose_V30(LONG lFind){
    SHE_BEGING
    //NET_DVR_FindClose(lFind);
    SHE_END
}
bool haik_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    struct tm Tm;
    NET_DVR_FILECOND_V40 f;
    memset(&f, 0, sizeof(NET_DVR_FILECOND_V40));

    _localtime64_s(&Tm, (const time_t*)&timeStart);
    TMToNetTime(Tm, f.struStartTime);

    _localtime64_s(&Tm, (const time_t*)&timeEnd);
    TMToNetTime(Tm, f.struStopTime);

    if (m_lLoginHandle < 0)
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


	auto itr = channelVec.begin();
	for (; itr != channelVec.end(); itr++)
	{
        hk_log.AddLog(QString("channelVec beg:%1").arg(files.size()));
		int nChannelId = *itr;
        hk_log.AddLog(QString("nChannelId:%1").arg(nChannelId));
		f.dwFileType = 0xff;
		f.dwIsLocked = 0xff;
		f.dwUseCardNo = 0;
		f.lChannel = nChannelId;
		f.sCardNumber[0] = 0;


		LONG lfind = NET_DVR_FindFile_V40(m_lLoginHandle, &f);

		if (lfind == -1)
		{
			m_sLastError = GetLastErrorString();
			hk_log.AddLog(std::string("NET_DVR_FindFile_V40 failed:") + m_sLastError);
			continue;
		}
		std::shared_ptr<NET_DVR_FINDDATA_V40> nriFileinfo(new NET_DVR_FINDDATA_V40());
		LONG re = NET_DVR_FindNextFile_V40(lfind, nriFileinfo.get());
		RecordFile rf;
		hk_log.AddLog(QString("NET_DVR_FindNextFile_V40 re:%1").arg(re));
		while (re == NET_DVR_ISFINDING || re == NET_DVR_FILE_SUCCESS)
		{
			if (re == NET_DVR_FILE_SUCCESS && nriFileinfo->dwFileSize > 0)
			{
                hk_log.AddLog(QString("NET_DVR_FindNextFile_V40:%1").arg(re));
				struct tm Tm;
				NetTimeToTM(nriFileinfo->struStartTime, Tm);
				rf.beginTime = _mktime64(&Tm);

				NetTimeToTM(nriFileinfo->struStopTime, Tm);
				rf.endTime = _mktime64(&Tm);

				rf.channel = nChannelId;
				rf.name = nriFileinfo->sFileName;
				rf.size = nriFileinfo->dwFileSize;

				rf.setPrivateData(nriFileinfo.get(), sizeof(NET_DVR_FINDDATA_V40));
				files.push_back(rf);
			}
			else
			{
				::Sleep(5);
			}

			re = NET_DVR_FindNextFile_V40(lfind, nriFileinfo.get());
		}

		hk_log.AddLog(QString("NET_DVR_FindNextFile_V40 end re:%1").arg(re));

        sheNET_DVR_FindClose_V30(lfind);
        hk_log.AddLog(QString("sheNET_DVR_FindClose_V30 end:%1").arg(files.size()));
	}

    hk_log.AddLog(QString("files:%1").arg(files.size()));
    return true;
}

void addLog(const NET_DVR_TIME& nt)
{
    hk_log.AddLog(QString("%1/%2/%3 %4:%5:%6").arg(nt.dwYear).arg(nt.dwMonth)
                           .arg(nt.dwDay).arg(nt.dwHour).arg(nt.dwMinute).arg(nt.dwSecond));
}

bool haik_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
#ifdef LNM_TEST

    std::string fn(saveFileName);
    long long size = file.size;
    qDebug()<<QString::fromLocal8Bit(saveFileName);
    new std::thread([=]{
        QFile f(fn.c_str());
        if (f.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QDataStream out(&f);
            std::string s(200 * 11 * 1024, 's');
            qDebug()<<f.size()<<" "<<size;
            while (f.size() < size)
            {
                ::Sleep(1000);
                int num = rand() % 200;
                if (num < 0)
                {
                    num = -num;
                }
                out.writeBytes(s.c_str(), num * 10 * 1024);
                qDebug()<<fn.c_str()<<" size:"<<f.size();
            }

            f.close();
        }
        else
        {
            qDebug()<<"file open failed";
        }

    });
    hdl = GetTickCount64();
    return true;
#endif



    if (0 > m_lLoginHandle)
    {

        m_sLastError = "请先登录!";

        return false;
    }

    NET_DVR_PLAYCOND struDownloadCond={0};
    memset(&struDownloadCond, 0, sizeof(NET_DVR_PLAYCOND));
    struDownloadCond.dwChannel = file.channel;
    struDownloadCond.byDrawFrame = 1;

    struct tm Tm;

    _localtime64_s(&Tm, (const time_t*)&file.beginTime);
    TMToNetTime(Tm, struDownloadCond.struStartTime);
    addLog(struDownloadCond.struStartTime);

    time_t tEnd = file.endTime + 100;
    _localtime64_s(&Tm, (const time_t*)&tEnd);
    TMToNetTime(Tm, struDownloadCond.struStopTime);
    addLog(struDownloadCond.struStopTime);

    hk_log.AddLog(QString("m_deviceInfo.wDevType:%1")
                           .arg(m_deviceInfo.wDevType));
    NET_DVR_FINDDATA_V40& info = *((NET_DVR_FINDDATA_V40*)file.getPrivateData());
    hdl = NET_DVR_GetFileByName(m_lLoginHandle, (char*)info.sFileName, (char*)saveFileName);
    hk_log.AddLog(QString::fromLocal8Bit("NET_DVR_GetFileByName"));
    if (hdl < 0)
    {
        hdl = NET_DVR_GetFileByTime_V40(m_lLoginHandle, (char*)info.sFileName, &struDownloadCond);
        hk_log.AddLog(QString::fromLocal8Bit("NET_DVR_GetFileByTime_V40"));
    }
	//领域OEM海康，但是领域用 NET_DVR_GetFileByTime_V40 无法下载
//    if (this->m_deviceInfo.wDevType == 2015 || this->m_deviceInfo.wDevType == 2215)

    if (hdl < 0)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_GetFileBy failed:") + m_sLastError + " 文件：" + saveFileName);
        return false;
    }

    if (!NET_DVR_PlayBackControl_V40(hdl, NET_DVR_PLAYSTART, NULL, 0, NULL,NULL))
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_PlayBackControl failed:") + m_sLastError + " 文件：" + saveFileName);
        return false;
    }

    return true;
}


bool  haik_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    NET_DVR_VOD_PARA struVodPara={0};
    memset(&struVodPara, 0, sizeof(NET_DVR_VOD_PARA));
    struVodPara.dwSize=sizeof(struVodPara);
    struVodPara.struIDInfo.dwChannel = file.channel; //通道号
    struVodPara.hWnd = hwnd;

    struct tm Tm;

    _localtime64_s(&Tm, (const time_t*)&file.beginTime);
    TMToNetTime(Tm, struVodPara.struBeginTime);

    _localtime64_s(&Tm, (const time_t*)&file.endTime);
    TMToNetTime(Tm, struVodPara.struEndTime);

    playbackHandle = NET_DVR_PlayBackByTime_V40(m_lLoginHandle, &struVodPara);
    if (playbackHandle < 0)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_PlayBackByTime_V40 failed:") + m_sLastError);
        return false;
    }

    if (!NET_DVR_PlayBackControl(playbackHandle, NET_DVR_PLAYSTART, NULL, 0))
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_PlayBackControl failed:") + m_sLastError);
        return false;
    }

    return true;
}

bool haik_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
    return FALSE != NET_DVR_PlayBackControl_V40(playbackHandle, NET_DVR_PLAYSETPOS,
                                                &pos);
}

bool haik_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    if (!NET_DVR_StopPlayBack(playbackHandle))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}



bool haik_videoserver::stopDownload(download_handle_t h)
{
    #ifdef LNM_TEST
    return true;
    #endif

    if (FALSE == NET_DVR_StopGetFile(h))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }

    return true;
}
