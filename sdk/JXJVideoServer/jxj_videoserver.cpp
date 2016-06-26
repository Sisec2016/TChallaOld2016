#include "jxj_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
#include <thread>
#include <QFile>
#include <qdebug.h>
#include "j_sdk.h"
#include "Jtype.h"
#include "mb_api.h"
Log jxj_log("jxj_videoserver");

extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{
    return new CFactory();
}

const char* GetErrorString(int error)
{
    switch (error)
    {
    case JNETErrSuccess: return "成功";
    case JNETErrUnInit: return "未初始化";
    case JNETErrHandle: return "句柄不存在";
    case JNETErrParam: return "参数错误";
    case JNETErrBuffSize: return "缓存满";
    case JNETErrNoMem: return "内存不足";
    case JNETErrRecv: return "接收错误";
    case JNETErrSend: return "发送错误";
    case JNETErrOperate: return "操作错误";
    case JNETErrURL: return "URL有误";
    case JNETErrLogining: return "用户正在登录";
    case JNETErrLogout: return "已经登出";
    case JNETErrNoFreePort: return "没有空闲通道";
    case JNETErrProtocol: return "协议错误";
    case JNETErrXMLFormat: return "错误的XML数据";
    case JNETErrNotSupport: return "不支持的操作";
    case JNETErrGetParam: return "获取参数错误";
    case JNETErrSetParam: return "设置参数错误";
    case JNETErrOpenFile: return "打开文件出错";
    case JNETErrUpgOpen: return "升级出错";
        
    }

    return "未定义";
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
        int r = JNetInit(NULL);
        m_init = (r == JNETErrSuccess);
        if (!m_init)
        {
           m_sLastError = GetErrorString(r);
           jxj_log.AddLog(std::string("init failed:") + m_sLastError);
        }
        r = AVP_Init();
        m_init = (r == AVPErrSuccess);
        if (m_init)
        {
            AVP_InitRecMng(128, 8);
        }
        else{
            jxj_log.AddLog(std::string("init failed:") + m_sLastError);
        }
    }

    return m_init;
}


void CFactory::clean()
{
    AVP_Cleanup();
    JNetCleanup();
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new jxj_videoserver();
}

int __stdcall OnMBNotify(long lHandle, DWORD dwProtocol, int iErr, int iMsgID, LPCTSTR lpszDstID, void* pData, int iDataLen, void* pUserParam)
{
    jxj_log.AddLog(std::string("OnMBNotify :"));
    if (NULL == lpszDstID || NULL == pData || NULL == pUserParam)
    {
        return -1;
    }
    std::vector<DeviceInfo>*		pDeves = (std::vector<DeviceInfo>*)(pUserParam);
    try
    {
        DeviceInfo d;
        j_Device_T *pDev = (j_Device_T *)(pData);
        d.szIP = (char*)(pDev->NetworkInfo.network[0].ip);
        d.nPort = pDev->NetworkInfo.cmd_port;
        jxj_log.AddLog(QString("%1,%2,%3,%4").arg(pDev->NetworkInfo.data_port).arg(pDev->NetworkInfo.cmd_port)
            .arg(pDev->NetworkInfo.talk_port).arg(pDev->NetworkInfo.talk_port));
        d.Factory = SISC_IPC_JXJ;
        pDeves->push_back(d);
    }
    catch (...)
    {
        return 0;
    }
    return 0;

}
BOOL  m_bSerachDevice = FALSE;
bool CFactory::searchDevice(std::vector<DeviceInfo>& devices){
    jxj_log.AddLog(std::string("JNetMBSearch :") + m_sLastError);
    if (m_bSerachDevice)
    {
        return true;
    }
    m_bSerachDevice = TRUE;
    long m_hBhandle = 0;
    JNetMBOpen(GROUP_IP, GROUP_PORT, OnMBNotify, &devices, JNET_PRO_T_JPF, m_hBhandle);
    if (m_hBhandle)
    {
        if (JNetMBSearch(m_hBhandle, 5) != 0){
            jxj_log.AddLog(std::string("JNetMBSearch failed:") + m_sLastError);
        }
            
    }
    else{
        jxj_log.AddLog(std::string("JNetMBOpen failed:") + m_sLastError);
    }

    int waitMilliSeconds = 200;
    while (waitMilliSeconds--){
        Sleep(1);
    }

    if (0 != JNetMBClose(m_hBhandle))
    {
        jxj_log.AddLog(std::string("JNetMBClose failed:") + m_sLastError);
    }

    m_bSerachDevice = FALSE;
    return true;
}

std::vector<jxj_videoserver*> jxj_videoserver::sServers;
std::recursive_mutex jxj_videoserver::sMtServers;

/*
 * 析构函数
 */
jxj_videoserver::jxj_videoserver()
{
    std::lock_guard<std::recursive_mutex> lock(jxj_videoserver::sMtServers);
    sServers.push_back(this);
}

jxj_videoserver::~jxj_videoserver()
{

    //logout();
    jxj_log.AddLog(std::string("jxj_videoserver::~jxj_videoserver()"));
    std::lock_guard<std::recursive_mutex> lock(jxj_videoserver::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* jxj_videoserver::clone()
{
    jxj_videoserver *svr = new jxj_videoserver();
    return svr;
}

bool jxj_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
	channels.clear();
    int nTimeOut = 10;
    long lLogin = -1;

    int r = JNetLogin((char*)IP, port, (char*)user, (char*)password, 1000,
        NULL, NULL, JNET_PRO_T_JPF, lLogin, NULL);
    if (r < 0)
    {
        m_sLastError = GetErrorString(r);
        jxj_log.AddLog(std::string("JNetLogin failed:") + m_sLastError);
        return false;
    }
    ::Sleep(1000);
    m_lLoginHandle = lLogin;
    JDeviceInfo deviceinfo;
    r = JNetGetParam(m_lLoginHandle, 0, PARAM_DEVICE_INFO, (char *)&deviceinfo, sizeof(deviceinfo), NULL, NULL);

    if (r != JNETErrSuccess)
    {
        m_sLastError = GetErrorString(r);
        jxj_log.AddLog(std::string("JNetGetParam failed:") + m_sLastError);
        return false;
    }

    for (int i = 0; i < deviceinfo.channel_num; i++)
    {
        channels[i];
    }

    return true;
}

bool jxj_videoserver::logout()
{
    if (m_lLoginHandle >= 0)
    {
        int r = JNetLogout(m_lLoginHandle);
        if (r != JNETErrSuccess)
        {
            m_sLastError = GetErrorString(r);
            jxj_log.AddLog(std::string("logout failed:") + m_sLastError);
            return false;
        }
    }
    else {
        jxj_log.AddLog(std::string("jxj_videoserverlogout ok!"));
    }

    return true;
}

void NetTimeToTM(const JTime& nt, tm& t)
{
    t.tm_year = nt.year;
    t.tm_mon = nt.month - 1;
    t.tm_mday = nt.date;
    t.tm_hour = nt.hour;
    t.tm_min = nt.minute;
    t.tm_sec = nt.second;
}

void TMToNetTime(const tm& t, JTime& nt)
{
    nt.year = t.tm_year;
    nt.month = t.tm_mon + 1;
    nt.date = t.tm_mday;
    nt.hour = t.tm_hour;
    nt.minute = t.tm_min;
    nt.second = t.tm_sec;
    nt.weekday = t.tm_wday + 1;
}

bool jxj_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    if (m_lLoginHandle < 0)
    {
        m_sLastError = "请先登录!";
        jxj_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }
    if (timeStart >= timeEnd)
    {
        m_sLastError = "时间范围不对!";
        jxj_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }

    struct tm Tm;
    JStoreLog storeLog;
    ZeroMemory(&storeLog, sizeof(JStoreLog));

    _localtime64_s(&Tm, (const time_t*)&timeStart);
    TMToNetTime(Tm, storeLog.beg_time);
    qDebug()<<"timeStart:"<<timeStart<<":"<<Tm.tm_year<<"/"<<Tm.tm_mon<<"/"<<Tm.tm_mday<<" "<<Tm.tm_hour
              <<":"<<Tm.tm_min<<":"<<Tm.tm_sec;
    jxj_log.AddLog((QDateTime::fromTime_t(timeStart).toString("yyyyMMddhhmmss")
        + "-" + QDateTime::fromTime_t(timeEnd).toString("yyyyMMddhhmmss")).toStdString());
    jxj_log.AddLog((QDateTime::fromTime_t(_mktime64(&Tm)).toString("yyyyMMddhhmmss")
        + "-" + QDateTime::fromTime_t(_mktime64(&Tm)).toString("yyyyMMddhhmmss")).toStdString());
    _localtime64_s(&Tm, (const time_t*)&timeEnd);
    TMToNetTime(Tm, storeLog.end_time);
    qDebug()<<"timeEnd:"<<timeEnd<<":"<<Tm.tm_year<<"/"<<Tm.tm_mon<<"/"<<Tm.tm_mday<<" "<<Tm.tm_hour
              <<":"<<Tm.tm_min<<":"<<Tm.tm_sec;
    

    RecordFile rf;
	for (auto itr = channelVec.begin(); itr != channelVec.end(); itr++)
	{
		int nChannelId = *itr;
        bool beg = true;
        storeLog.rec_type = ALL_RECODE;
        storeLog.beg_node = 0;
        storeLog.end_node = J_SDK_MAX_STORE_LOG_SIZE - 1;
        storeLog.sess_id = -1;
        while (beg || storeLog.beg_node < storeLog.total_count){
            beg = false;
            int r = JNetGetParam(m_lLoginHandle, nChannelId, PARAM_STORE_LOG, &storeLog, sizeof(storeLog), NULL, NULL);
            if (r != JNETErrSuccess)
            {
                m_sLastError = GetErrorString(r);
                jxj_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
                return false;
            }
            jxj_log.AddLog(QString("%1 %2 ").arg(storeLog.node_count).arg(storeLog.total_count));
            for (int i = 0; i < storeLog.node_count; i++)
            {
                Store& s = storeLog.store[i];
                struct tm Tm;
                NetTimeToTM(s.beg_time, Tm);
                rf.beginTime = _mktime64(&Tm);
                NetTimeToTM(s.end_time, Tm);
                rf.endTime = _mktime64(&Tm);

                if (rf.beginTime >= timeEnd){
                    continue;
                }
                else if (rf.endTime < timeStart)
                {
                   continue;
                }
                rf.channel = nChannelId;
                rf.name = (QDateTime::fromTime_t(rf.beginTime).toString("yyyyMMddhhmmss")
                    + "-" + QDateTime::fromTime_t(rf.endTime).toString("yyyyMMddhhmmss")).toStdString();
                rf.size = s.file_size;

                rf.setPrivateData(&s, sizeof(s));
                files.push_back(rf);
            }
            storeLog.beg_node += J_SDK_MAX_STORE_LOG_SIZE;
            storeLog.end_node += J_SDK_MAX_STORE_LOG_SIZE;
            if (storeLog.end_node >= storeLog.total_count)
            {
                storeLog.end_node = storeLog.total_count - 1;
            }
        }
	}

    return true;
}

void addLog(const JTime& nt)
{
    jxj_log.AddLog(QString("%1/%2/%3 %4:%5:%6").arg(nt.year).arg(nt.month)
                           .arg(nt.date).arg(nt.hour).arg(nt.minute).arg(nt.second));
}
int  __stdcall JRecDownload(long lHandle, LPBYTE pBuff, DWORD dwRevLen, void* pUserParam)
{
    DownloadInfo *pDlg = (DownloadInfo *)pUserParam;
    if (pBuff)
    {

        j_frame_t *pFrame = (j_frame_t *)pBuff;

        if (pDlg->mDownloadBeginTime == -1)
        {
            pDlg->mDownloadBeginTime = pFrame->timestamp_sec;
        }

        const RecordFile& f = pDlg->mDownloadFile;
        if (f.endTime <= f.beginTime)
        {
            return 0;
        }
        //jxj_log.AddLog(QString("pFrame->timestamp_sec %1 pDlg->mDownloadBeginTime %2 f.size %3 "
       //     "(f.endTime - f.beginTime) %4").arg(pFrame->timestamp_sec).arg(pDlg->mDownloadBeginTime).arg(f.size).arg(f.endTime - f.beginTime));
        pDlg->mDownloadSize = (pFrame->timestamp_sec - pDlg->mDownloadBeginTime) * f.size / (f.endTime - f.beginTime);
        AVP_WriteRecFile(pDlg->mDownloadHandle, pBuff, dwRevLen, NULL, 0);
    }
    return 0;
}
bool jxj_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    QString begTime = QDateTime::fromTime_t(file.beginTime).toString("yyyyMMddhhmmss");
    QString endTime = QDateTime::fromTime_t(file.endTime).toString("yyyyMMddhhmmss");
    long recHandle = 0;
    DownloadInfo *pInfo = new DownloadInfo();
    hdl = JNetRecOpen4Time(m_lLoginHandle, "", file.channel, 0, begTime.toStdString().c_str(),
        endTime.toStdString().c_str(), 4096, 0, JRecDownload, pInfo, recHandle);
    if (hdl > 0)
    {
        //jxj_log.AddLog(QString("downLoadByRecordFile lHandle %1").arg(hdl));
        Sleep(1000);
        JNetRecCtrl(recHandle, JNET_PB_CTRL_START, NULL);
    
        pInfo->mDownloadHandle = AVP_CreateRecFile(saveFileName, AVP_PROTOCOL_JPF, 0);
        pInfo->mDownloadFile = file;
        mMpDownloadInfos[hdl] = pInfo;
    }
    else{
        delete pInfo;
        m_sLastError = GetErrorString(hdl);
        jxj_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }

    return true;
}
int __stdcall JRecStream(long lHandle, LPBYTE pBuff, DWORD dwRevLen, void* pUserParam)
{
    jxj_videoserver *pDlg = (jxj_videoserver *)pUserParam;
    j_frame_t *pFrame = (j_frame_t *)pBuff;
    //TRACE("--------%d    %d\r\n",  pFrame->timestamp_sec, pFrame->timestamp_usec);
    AVP_PutFrame(pDlg->gChannel, pBuff);
    return 0;
}

bool  jxj_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    mPlayBeg = QDateTime::fromTime_t(file.beginTime);
    QString begTime = mPlayBeg.toString("yyyyMMddhhmmss");
    mPlayEnd = QDateTime::fromTime_t(file.endTime);
    QString endTime = mPlayEnd.toString("yyyyMMddhhmmss");
    long recHandle = 0;
    gChannel = AVP_GetFreePort();
    playbackHandle = JNetRecOpen4Time(m_lLoginHandle, "", file.channel, 0, begTime.toStdString().c_str(),
        endTime.toStdString().c_str(), ALL_RECODE, 1, JRecStream, this, recHandle);
    if (playbackHandle > 0)
    {
        Sleep(1000);
        JNetRecCtrl(playbackHandle, JNET_PB_CTRL_START, NULL);

        AVP_SetPlayPriority(gChannel, AVPPlaySmooth);
        AVP_SetDataProtocol(gChannel, AVP_PROTOCOL_JPF);
        int iRet = AVP_SetCoder(gChannel, AVP_CODER_JXJ);
        if (iRet != AVPErrSuccess)
        {
            m_sLastError = "AVP_SetCoder failed";
            jxj_log.AddLog(std::string("PlayBackByRecordFile failed:") + m_sLastError);
            return false;
        }

        AVP_AddPlayWnd(gChannel, NULL, hwnd, NULL, NULL);
        AVP_Play(gChannel);
        mMpPlaybackHandles[playbackHandle] = gChannel;
    }
    else{
        m_sLastError = GetErrorString(playbackHandle);
        jxj_log.AddLog(std::string("PlayBackByRecordFile failed:") + m_sLastError);
        return false;
    }

    return true;
}

bool jxj_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
    AVP_Seek(mMpPlaybackHandles[playbackHandle], mPlayBeg.secsTo(mPlayEnd) * pos / 100);
    JNetRecCtrl(playbackHandle, JNET_PB_CTRL_SET_TIME, (void *)(mPlayBeg.secsTo(mPlayEnd) * pos / 100));
    return true;
}

bool jxj_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    if (mMpPlaybackHandles.find(playbackHandle) != mMpPlaybackHandles.end())
    {
        AVP_Stop(mMpPlaybackHandles[playbackHandle]);
        AVP_ReleasePort(mMpPlaybackHandles[playbackHandle]);
        mMpPlaybackHandles.erase(playbackHandle);
    }
    
    JNetRecClose(playbackHandle);
    return true;
}



bool jxj_videoserver::stopDownload(download_handle_t h)
{
    if (!h)
    {
        return true;
    }

    JNetRecCtrl(h, JNET_PB_CTRL_STOP, NULL);
    AVP_CloseRecFile(mMpDownloadInfos[h]->mDownloadHandle);


    JNetRecClose(h);
    delete mMpDownloadInfos[h];
    mMpDownloadInfos.erase(h);
    return true;
}

bool jxj_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed){
    
    *failed = false;
    if (mMpDownloadInfos[h]->mDownloadBeginTime != -1)
    {
        *currentSize = mMpDownloadInfos[h]->mDownloadSize;
        *totalSize = mMpDownloadInfos[h]->mDownloadFile.size;
        return *currentSize * 100 >= *totalSize;
    }
    *failed = false;
    return false;
}