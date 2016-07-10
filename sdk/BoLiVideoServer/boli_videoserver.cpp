#include "boli_videoserver.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
#include <thread>
#include <QFile>
#include <qdebug.h>
#include "WPPdvrSdk.h"
#include "WPDecSdk.H"
#include "WPDisSdk.H"
#include "WP_SAVEIMAGE.H"

Log boli_log("boli_videoserver");

extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{

    return new CFactory();
}

const char* GetErrorString(int error)
{
    switch (error)
    {
    case WP_PDVR_NOINIT: return "without initialized";
    case WP_PDVR_NETINIT_FIAL: return "initialize network failed";
    case WP_PDVR_INVALID_INDEX: return "invalid PDVR index ";
    case WP_PDVR_INVALID_CAM_INDEX: return "invalid camera index";
    case WP_PDVR_NOT_CONNECT: return "not connect PDVR";
    case WP_PDVR_CONNECT_FAIL: return "connect PDVR failed";
    case WP_PDVR_PARAM_ERROR: return "invalid param";
    case WP_PDVR_MAX_NUM: return "the connect camera is max for this PDVR";
    case WP_PDVR_CON_CAM_FAIL: return "connect camera failed";
    case WP_PDVR_PLAYBACK_CON_FAIL: return "connect playback failed";
    case WP_PDVR_PLAYBACK_NOT_CON: return "not connect playback";
    case WP_PDVR_GET_RECORD_INFO_FAIL: return "get record information failed";
    case WP_PDVR_PLAYBACK_JUMPTO_FAIL: return "playback jump to failed";
    case WP_PDVR_OPEN_RECORD_FILE_FAIL: return "open record file failed";
    case WP_PDVR_START_RECORD_FILE_FAIL: return "start playback failed";
    case WP_PDVR_STOP_RECORD_FILE_FAIL: return "stop playback failed";
    case WP_PDVR_PAUSE_RECORD_FILE_FAIL: return "pause playback failed";
    case WP_PDVR_CONTINUE_RECORD_FILE_FAIL: return "continue playback failed";
    case WP_PDVR_SET_PLAYBACK_RATE_FAIL: return "set rate of playback failed";
    case WP_PDVR_FILEJUMP_FAIL: return "文件失败";
    case WP_PDVR_STOP_VIEW_CAMERA_FAIL: return "stop view failed";
    case WP_PDVR_DISCONNECT_FAIL: return "disconnect PDVR failed";
    case WP_PDVR_SURFACE_HAS_CREATE: return "the screen has been used";
    case WP_PDVR_SURFACE_NOT_CREATE: return "the surface has not exist";
    case WP_PDVR_NOT_CONNECT_CAMERA: return "not connect camera";
    case WP_PDVR_SENT_MESSAGE_FAILED: return "Send message to PDVR failed";
    case WP_PDVR_GET_CAMINFO_FAILED: return "Get camera info failed";
    case WP_PDVR_GET_NETINFO_FAILED: return "WP_PDVR_GET_NETINFO_FAILED";
    case WP_PDVR_CREATE_FILE_FAILED: return "Download record file failed";
    case WP_PDVR_RECV_FAILED: return "Recv data from PDVR failed";
    case WP_PDVR_HAS_NO_FILE_TO_DOWNLOAD: return "Has no record to download";
    case WP_PDVR_DOWNLOAD_HOUR_INVALID: return "Download start hour must be same with end hour";
    case WP_PDVR_DOWNLOAD_FILEPATH_NULL: return "The path to storage download file is null";
    case WP_PDVR_ALREADY_CONNECTED: return "The pdvr already connected";
    case WP_PDVR_DOWNLOAD_DATE_INVALID: return "The download date is invalid";
    case WP_PDVR_PLAYBACK_TIME_INVALID: return "The playback time is invalid";
    case WP_PDVR_PLAYBACK_DATE_INVALID: return "The playback date is invalid";
    case WP_PDVR_OTHER_DATE_IS_PLAYBACK: return "Other date is playback";
    case WP_PDVR_TALK_FAILED: return "WP_PDVR_TALK_FAILED";
    case WP_PDVR_STOP_LISTEN_FAILED: return "WP_PDVR_STOP_LISTEN_FAILED";
    case WP_PDVR_NOT_FINISHED_DOWNLOAD: return "WP_PDVR_NOT_FINISHED_DOWNLOAD";
    case WP_PDVR_CHANNEL_NOCAM: return "WP_PDVR_CHANNEL_NOCAM";
    case WP_PDVR_CHANNEL_NOTCONNECT: return "WP_PDVR_CHANNEL_NOTCONNECT";
    case WP_PDVR_CHANNEL_NOTPREVIEW: return "WP_PDVR_CHANNEL_NOTPREVIEW";
    case WP_PDVR_CHANNEL_CAPTURE_FAILED: return "WP_PDVR_CHANNEL_CAPTURE_FAILED";
    case WP_PDVR_USER_NOT_AUTHORITY: return "WP_PDVR_USER_NOT_AUTHORITY";
    case WP_PDVR_INITSOCK_FAILED: return "WP_PDVR_INITSOCK_FAILED";
    case WP_PDVR_USER_PASSWORD_ERROR: return "WP_PDVR_USER_PASSWORD_ERROR";
    case WP_PDVR_UPDATE_FAILED: return "WP_PDVR_UPDATE_FAILED";
    case WP_PDVR_UPDATE_CAMERA_FAILED: return "WP_PDVR_UPDATE_CAMERA_FAILED";
        
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



#define  DEAL_RETURN_VALUE(r, error_msg, error_reutrn) \
if (r != WP_PDVR_NOERROR) { \
    boli_log.AddLog(QString("%1:%2-%3").arg(error_msg).arg(r).arg(GetErrorString(r))); \
    return error_reutrn; \
}

#define  DEAL_RETURN_VALUE_FALSE(r, error_msg)  DEAL_RETURN_VALUE(r, error_msg, false)

bool CFactory::init()
{
    if (!m_init)
    {
        int r = WP_Init();
        DEAL_RETURN_VALUE_FALSE(r, QStringLiteral("初始化失败!"))
        WP_DISPLAY_InitSdk();
        WP_DECODE_InitSdk();
        m_init = true;
    }

    return m_init;
}


void CFactory::clean()
{
    WP_Cleanup();
    WP_DISPLAY_CleanupSdk();
    WP_DECODE_CleanupSdk();
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new boli_videoserver();
}

#define  ONE_SEC_FILE_SIZE    26 * 10 * 1024
std::vector<boli_videoserver*> boli_videoserver::sServers;
std::recursive_mutex boli_videoserver::sMtServers;
DownloadInfo g_DownloadInfo;
DATETIME dtStart;
DATETIME dtEnd;
bool CALLBACK ProgressDownload(int currentPos)
{
    if (g_DownloadInfo.mDownloadBeginTime == -1 || currentPos > 100 )
    {
        //g_DownloadInfo.mDownloadBeginTime = -1;
        //g_DownloadInfo.mDownloadSize = 0;
        boli_log.AddLog(QString("%1 %2 ").arg("g_DownloadInfo.mDownloadBeginTime == ").arg(currentPos));
        if (currentPos == 101)
        {
            int ret = WP_PDVR_GetFileByTime(g_DownloadInfo.mDownloadHandle, g_DownloadInfo.mDownloadFile.channel, 
                dtStart, dtEnd, g_DownloadInfo.mPath.toLocal8Bit().data());
            DEAL_RETURN_VALUE_FALSE(ret, "WP_PDVR_GetFileByTime failed")
        }
        return true;
    }



    if (g_DownloadInfo.mDownloadBeginTime != currentPos)
    {
        boli_log.AddLog(QString("%1 %2 ").arg("ProgressDownload").arg(currentPos));
        g_DownloadInfo.mDownloadBeginTime = currentPos;
        g_DownloadInfo.mDownloadSize = currentPos * g_DownloadInfo.mDownloadFile.size / 100;
    }
    else
    {

        if (g_DownloadInfo.mDownloadSize < (currentPos + 1) * g_DownloadInfo.mDownloadFile.size / 100
            && g_DownloadInfo.mDownloadSize < g_DownloadInfo.mDownloadFile.size - ONE_SEC_FILE_SIZE)
        {
            g_DownloadInfo.mDownloadSize += ONE_SEC_FILE_SIZE / 10;
        }
    }

    if (currentPos == 100)
    {
        g_DownloadInfo.mDownloadSize = g_DownloadInfo.mDownloadFile.size;
        return true;
    }

    return false;
}

/*
 * 析构函数
 */
boli_videoserver::boli_videoserver()
{
    std::lock_guard<std::recursive_mutex> lock(boli_videoserver::sMtServers);
    sServers.push_back(this);
}

boli_videoserver::~boli_videoserver()
{

    //logout();
    boli_log.AddLog(std::string("boli_videoserver::~boli_videoserver()"));
    std::lock_guard<std::recursive_mutex> lock(boli_videoserver::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* boli_videoserver::clone()
{
    //boli_videoserver *svr = new boli_videoserver();
    return nullptr;
}

bool boli_videoserver::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
    if (m_lLoginHandle >= 0)
    {
        logout();
    }
	channels.clear();
    int nTimeOut = 10;
    long lLogin = -1;

    m_lLoginHandle = WP_PDVR_Connect((char*)IP, port, (char*)user, (char*)password);
    if (m_lLoginHandle < 0 || m_lLoginHandle >= MAX_SERVER) {
        m_lLoginHandle = -1;
        boli_log.AddLog(QStringLiteral("登陆失败!"));
        return false;
    }

   
    memset(&mDeviceInfo, 0, sizeof(mDeviceInfo));
    int ret = WP_PDVR_GetDeviceInfo(m_lLoginHandle, &mDeviceInfo);
    DEAL_RETURN_VALUE_FALSE(ret, QStringLiteral("获取设备信息失败!"))
    boli_log.AddLog(QString("mDeviceInfo.connCamNum %1 mDeviceInfo.maxCamNum %2").arg(mDeviceInfo.connCamNum).arg(mDeviceInfo.maxCamNum));
    for (int i = 0; i < mDeviceInfo.maxCamNum; i++)
    {
        channels[i];
    }
    mChannels = channels;
    WP_GetProgressCallBack(ProgressDownload);
    return true;
}

bool boli_videoserver::logout()
{
    if (m_lLoginHandle >= 0)
    {
        int r = WP_PDVR_DisConnect(m_lLoginHandle);
        DEAL_RETURN_VALUE_FALSE(r, "登出失败")
        m_lLoginHandle = -1;
    }
    else {
        m_lLoginHandle = -1;
        boli_log.AddLog(std::string("boli_videoserverlogout ok!"));
    }

    return true;
}



bool boli_videoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    if (m_lLoginHandle < 0)
    {
        m_sLastError = "请先登录!";
        boli_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }
    if (timeStart >= timeEnd)
    {
        m_sLastError = "时间范围不对!";
        boli_log.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }
    
    QDateTime begDt = QDateTime::fromTime_t(timeStart);
    QDateTime endDt = QDateTime::fromTime_t(timeEnd);
    QTime tmS(begDt.time());
    QTime tmE(endDt.time());
    FIINFO *pFiHead = nullptr;
    
    RecordFile rf;
    QTime time;
    for (QDate start(begDt.date()); start <= endDt.date(); start = start.addDays(1))
    {
        if (start == begDt.date())
        {
            tmS = begDt.time();
        }
        else{
            tmS = QTime(0, 0);
        }

        if (start == endDt.date())
        {
            tmE = endDt.time();
            if (endDt.date() == QDateTime::currentDateTime().date())
            {
                tmE = QDateTime::currentDateTime().time();
            }
        }
        else{
            tmE = QTime(23, 59);
        }
        int has_record = WP_PDVR_CheckHasRecord(m_lLoginHandle, start.year(), start.month(), start.day());
        //DEAL_RETURN_VALUE_FALSE(has_record, QStringLiteral("WP_PDVR_CheckHasRecord！%1").arg(start.toString(Qt::LocaleDate)));
        if (THE_DAY_NOT_RECORD == has_record){
            boli_log.AddLog(QString("%1:%2/%3/%4").arg("no has record in ").arg(start.year()).arg(start.month()).arg(start.day()));
            continue;
        }

        FIINFO *pFiHead[MAX_CAMERA] = {0};
        int r = WP_PDVR_GetADayRecordInfo(m_lLoginHandle, start.year(), start.month(), start.day(), pFiHead);
        DEAL_RETURN_VALUE_FALSE(r, QStringLiteral("获取一天文件失败！"));
        if (pFiHead != nullptr)
        {
            for (int i = 0; i < channelVec.size(); i++)
            {
                for (FIINFO* pFileInfo = pFiHead[channelVec[i]]; pFileInfo != nullptr; pFileInfo = pFileInfo->next)
                {
                    time.setHMS(pFileInfo->fi.hour, pFileInfo->fi.min, pFileInfo->fi.sec);
                    rf.beginTime = QDateTime(start, time).toTime_t();
                    rf.endTime = QDateTime(start, time.addSecs(pFileInfo->fi.len)).toTime_t();
                    if (rf.endTime <= timeStart || rf.beginTime >= timeEnd){
                        continue;
                    }
                    
                    boli_log.AddLog(QString("%1:%2/%3/%4").arg(pFileInfo->fi.len).arg(pFileInfo->fi.hour).arg(pFileInfo->fi.min)
                        .arg(pFileInfo->fi.sec));
                    rf.channel = pFileInfo->fi.camId;
                    rf.size = ((__int64)(pFileInfo->fi.len)) * ONE_SEC_FILE_SIZE;
                    if (files.size() > 0)
                    {
                        RecordFile& lastFile = *files.rbegin();
                        if (lastFile.size == 0)
                        {
                            lastFile.endTime = rf.beginTime;
                            lastFile.size = (lastFile.endTime - lastFile.beginTime) * ONE_SEC_FILE_SIZE;
                        }
                    }
                    if (rf.size != 0 && (rf.endTime - rf.beginTime) < 4 * 60)
                    {
                        continue;
                    }
                    else{
                        files.push_back(rf);
                    }
                    
                
                }
                
                if (files.size() > 0)
                {
                    RecordFile& lastFile = *files.rbegin();
                    if (lastFile.size == 0)
                    {
                        lastFile.endTime = QDateTime(start, tmE).toTime_t();
                        lastFile.size = (lastFile.endTime - lastFile.beginTime) * ONE_SEC_FILE_SIZE;
                    }

                }
            }
        }
        else{
            boli_log.AddLog(QString("null fiHeads!"));
        }
    }

    return true;
}



bool boli_videoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        boli_log.AddLog(m_sLastError);
        return false;
    }

    if (g_DownloadInfo.mDownloadBeginTime >= 0)
    {
        m_sLastError = "只支持一个文件下载";
        boli_log.AddLog(m_sLastError);
        return false;
    }
    g_DownloadInfo.mDownloadBeginTime = 0; 
    g_DownloadInfo.mDownloadSize = 0;
    QDateTime begDt = QDateTime::fromTime_t(file.beginTime);
    QDateTime endDt = QDateTime::fromTime_t(file.endTime);

    dtStart.yy = begDt.date().year() % 100;
    dtStart.mon = begDt.date().month();
    dtStart.dd = begDt.date().day();
    dtStart.hh = begDt.time().hour();
    dtStart.min = begDt.time().minute();
    dtStart.ss = begDt.time().second();


    dtEnd.yy = endDt.date().year() % 100;
    dtEnd.mon = endDt.date().month();
    dtEnd.dd = endDt.date().day();
    dtEnd.hh = endDt.time().hour();
    dtEnd.min = endDt.time().minute();
    dtEnd.ss = endDt.time().second();
    boli_log.AddLog(begDt.toString() + "---" + endDt.toString() + QString::fromLocal8Bit(saveFileName));
    ::Sleep(1500);
    int ret = WP_PDVR_GetFileByTime(m_lLoginHandle, file.channel, dtStart, dtEnd, QString::fromLocal8Bit(saveFileName).replace("/", "\\").toLocal8Bit().data());
    DEAL_RETURN_VALUE_FALSE(ret, "WP_PDVR_GetFileByTime failed")
    
    hdl = (download_handle_t)new RecordFile(file);
    g_DownloadInfo.mDownloadFile = file;
    g_DownloadInfo.mDownloadHandle = m_lLoginHandle;
    g_DownloadInfo.mPath = QString::fromLocal8Bit(saveFileName).replace("/", "\\");
    return true;
}

BYTE* g_pPlaybackFrameBuf = new BYTE[1920 * 1080 * 3];
int g_pbDecodeId = 16;
int g_pbHwndId = -1;
int g_channel = -1;
bool CALLBACK recPlaybackDataCallBack(int serverId, int cameraId, int type, BYTE *pData, int len, int param1, int param2, void *pReserved)
{
    if (0 == len && 0 == param1 && 0 == param2) {
        int ret = WP_PDVR_StopPlayBack(serverId, cameraId);
        if (ret != WP_PDVR_NOERROR) {
            DEAL_RETURN_VALUE_FALSE(ret, "recPlaybackDataCallBack failed")
            return false;
        }
        return true;
    }


    int ret = 0;
    if (type != DATA_TYPE_AUDIO) {
        //if (type == DATA_TYPE_HD_IFRAME) {
            ret = WP_DECODE_DecVideo(g_pbDecodeId, pData, len, g_pPlaybackFrameBuf);
            if (ret != WP_DECODE_NOERROR) {
                DEAL_RETURN_VALUE_FALSE(ret, "WP_DECODE_DecVideo failed")
            }
            ret = WP_DISPLAY_DisplayFrame(g_pbHwndId, g_pPlaybackFrameBuf);
       // }
    }


    if (len == 0){
        //boli_videoserver* pservr = (boli_videoserver*)pReserved;
        //pservr->StopPlayBack()
    }
        

    return true;
}

bool  boli_videoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    QDateTime begDt = QDateTime::fromTime_t(file.beginTime);
    QDateTime endDt = QDateTime::fromTime_t(file.endTime);
    DATETIME dtStart;
    dtStart.yy = begDt.date().year() % 100;
    dtStart.mon = begDt.date().month();
    dtStart.dd = begDt.date().day();
    dtStart.hh = begDt.time().hour();
    dtStart.min = begDt.time().minute();
    dtStart.ss = begDt.time().second();

    DATETIME dtEnd;
    dtEnd.yy = endDt.date().year() % 100;
    dtEnd.mon = endDt.date().month();
    dtEnd.dd = endDt.date().day();
    dtEnd.hh = endDt.time().hour();
    dtEnd.min = endDt.time().minute();
    dtEnd.ss = endDt.time().second();

    int has_record = WP_PDVR_CheckHasRecord(m_lLoginHandle, begDt.date().year(), begDt.date().month(), begDt.date().day());

    int ret = WP_PDVR_StartPlayBack(m_lLoginHandle, file.channel);
    //int ret = WP_PDVR_PlaybackByTime(m_lLoginHandle, file.channel, dtStart, dtEnd);
    DEAL_RETURN_VALUE_FALSE(ret, "WP_PDVR_StartPlayBack")
    g_pbHwndId = WP_DISPLAY_InitDevice(hwnd);
    if (g_pbHwndId < 0 || g_pbHwndId >= MAX_DEVICE){
        boli_log.AddLog(QString("WP_DISPLAY_InitDevice failed!"));
        return false;
    }

    ret = WP_DISPLAY_CreateOneSurface(g_pbHwndId, mDeviceInfo.camVideoInfo[file.channel].stream0_width,
        mDeviceInfo.camVideoInfo[file.channel].stream0_height);
    DEAL_RETURN_VALUE_FALSE(ret, "WP_DISPLAY_CreateOneSurface failed")
    g_pbDecodeId = WP_DECODE_InitVideoDec(mDeviceInfo.camVideoInfo[file.channel].stream0_width,
        mDeviceInfo.camVideoInfo[file.channel].stream0_height,
        mDeviceInfo.camVideoInfo[file.channel].streamType);
    if (g_pbDecodeId >= 0 && g_pbDecodeId < MAX_DECODE) {
        int value = m_lLoginHandle;
        ret = WP_GetPlaybackDataCallBack(recPlaybackDataCallBack, m_lLoginHandle, &value, sizeof(value));
        DEAL_RETURN_VALUE_FALSE(ret, "WP_GetPlaybackDataCallBack failed")
    }
    else
    {
        boli_log.AddLog(QString("WP_DECODE_InitVideoDec failed!"));
        return false;
    }

    g_channel = file.channel;
    RecordFile *Temp = new RecordFile(file);
    playbackHandle = (play_handle_t)Temp;
    ret = WP_PDVR_JumpToPlay(m_lLoginHandle, file.channel, begDt.time().hour() * 3600 + begDt.time().minute() * 60 + begDt.time().second());
    DEAL_RETURN_VALUE_FALSE(ret, "WP_PDVR_JumpToPlay failed")
    return true;
}

bool boli_videoserver::SetPlayBack(download_handle_t playbackHandle, __int32 pos)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    if (g_channel >= 0)
    {
        RecordFile* f = (RecordFile *)playbackHandle;
        QDateTime begDt = QDateTime::fromTime_t(f->beginTime);
        QDateTime playDt = begDt.addSecs((f->endTime - f->beginTime) * pos / 100);
        int ret = WP_PDVR_JumpToPlay(m_lLoginHandle, g_channel, playDt.time().hour() * 3600 + playDt.time().minute() * 60 + playDt.time().second());
        DEAL_RETURN_VALUE_FALSE(ret, "WP_PDVR_JumpToPlay failed")
    }
    
    return true;
}

bool boli_videoserver::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (0 > m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }

    if (g_channel >= 0)
    {
        WP_PDVR_StopPlayBack(m_lLoginHandle, g_channel);
        g_channel = -1;
        WP_DISPLAY_FreeOneSurface(g_pbHwndId);
        WP_DISPLAY_ReleaseDevice(g_pbHwndId);
        g_pbHwndId = -1;
        WP_DECODE_DestroyVideoDec(g_pbDecodeId);
        WP_PDVR_DestroyPlayBack(m_lLoginHandle);
        g_pbDecodeId = 16;
        delete (RecordFile *)playbackHandle;
    }
    
    return true;
}



bool boli_videoserver::stopDownload(download_handle_t h)
{
    if (g_DownloadInfo.mDownloadBeginTime >= 0)
    {
        g_DownloadInfo.mDownloadBeginTime = -1;
        g_DownloadInfo.mDownloadSize = 0;
        WP_PDVR_DestroyPlayBack(m_lLoginHandle);
    }
    return true;
}

bool boli_videoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed){

    *failed = false;
    if (g_DownloadInfo.mDownloadBeginTime != -1)
    {
        *currentSize = g_DownloadInfo.mDownloadSize;
        *totalSize = g_DownloadInfo.mDownloadFile.size;
        if (*currentSize >= *totalSize)
        {
            g_DownloadInfo.mDownloadBeginTime = -1;
            g_DownloadInfo.mDownloadSize = 0;
        }
        return true;
    }

    return false;
}