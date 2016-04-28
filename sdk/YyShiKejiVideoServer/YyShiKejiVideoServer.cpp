#include "YyShiKejiVideoServer.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
#include <thread>
#include <QFile>
#include <qdebug.h>
Log hk_log("YyShiKejiVideoServer");

extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{

    return new CFactory();
}


std::string GetLastErrorString()
{
    LONG error = NETDEV_GetLastError();
    switch (error)
    {
        case NETDEV_E_COMMON_FAILED: return "通用错误  Common error";
        case NETDEV_E_DEV_COMMON_FAILED: return "由设备返回的通用错误  Common error returned by device";
        case NETDEV_E_SYSCALL_FALIED: return "系统函数调用失败，请查看errno  Failed to call system function. See errno";
        case NETDEV_E_NULL_POINT: return "空指针  Null pointer";
        case NETDEV_E_INVALID_PARAM: return "无效参数  Invalid parameter";
        case NETDEV_E_INVALID_MODULEID: return "无效模块ID  Invalid module ID";
        case NETDEV_E_NO_MEMORY: return "内存分配失败  Failed to allocate memory";
        case NETDEV_E_NOT_SUPPORT: return "设备不支持  Not supported by device";
        case NETDEV_E_SDK_SOCKET_LSN_FAIL: return "创建socket listen失败  Failed to create socket listen";
        case NETDEV_E_INIT_MUTEX_FAIL: return "初始化锁失败  Failed to initialize lock";
        case NETDEV_E_INIT_SEMA_FAIL: return "初始化信号量失败  Failed to initialize semaphore";
        case NETDEV_E_ALLOC_RESOURCE_ERROR: return "SDK资源分配错误  Error occurred during SDK resource allocation";
        case NETDEV_E_SDK_NOINTE_ERROR: return "SDK未初始化  SDK not initialized";
        case NETDEV_E_ALREDY_INIT_ERROR: return "SDK已经初始化。  SDK already initialized";
        case NETDEV_E_HAVEDATA: return "还有数据   Data not all sent";
        case NETDEV_E_NEEDMOREDATA: return "需要更多数据  More data required ";
        case NETDEV_E_CONNECT_ERROR: return "创建连接失败  Failed to create connection";
        case NETDEV_E_SEND_MSG_ERROR: return "发送请求消息失败  Failed to send request message";
        case NETDEV_E_TIMEOUT: return "消息超时  Message timeout";
        case NETDEV_E_DECODE_RSP_ERROR: return "解析响应消息失败  Failed to decode response message";
        case NETDEV_E_SOCKET_RECV_ERROR: return "Socket接收消息失败  Socket failed to receive message";
        case NETDEV_E_NUM_MAX_ERROR: return "个数达到最大。分配的注册连接数、预览连接数超过SDK支持的最大数  Maximum number reached. The assigned numbers of registration connections and preview connections reached the maximum supported by SDK";
        case NETDEV_E_GET_PORT_ERROR: return "获取本地端口号失败  Failed to obtain local port number";
        case NETDEV_E_CREATE_THREAD_FAIL: return "创建线程失败  Failed to create thread";
        case NETDEV_E_NOENOUGH_BUF: return "缓冲区太小: 接收设备数据的缓冲区  Buffer is too small for receiving device data";
        case NETDEV_E_GETLOCALIPANDMACFAIL: return "获得本地PC的IP地址或物理地址失败  Failed to obtain the IP or MAC address of the local PC";
        case NETDEV_E_RESCODE_NO_EXIST: return "资源编码不存在  Resource code not exist";
        case NETDEV_E_MSG_DATA_INVALID: return "消息内容错误  Incorrect message content";
        case NETDEV_E_GET_CAPABILITY_ERROR: return "获取能力级失败  Failed to obtain capabilities";
        case NETDEV_E_USER_NOT_BIND: return "该用户没有订阅告警   User not subscribed to alarms";
        case NETDEV_E_AUTHORIZATIONFAIL: return "用户鉴权失败  User authentication failed";
        case NETDEV_E_BINDNOTIFY_FAIL: return "绑定告警失败  Failed to bind alarms";
//        case NDEDEV_E_NOTADMIN: return "操作权限不足，windows下一般为非管理员帐号操作导致 Not enough permission. In Windows, it is normally because the operator is not an administrator.";
//        case NDEDEV_E_DEVICE_FACTURER_ERR: return "不支持的设备厂商 Manufacturers that are not supported";
        case NETDEV_E_NONSUPPORT: return "该功能不支持  Function not supported";
        case NETDEV_E_TRANSFILE_FAIL: return "文件传输失败  File transmission failed";
        case NETDEV_E_JSON_ERROR: return "Json 通用错误  Json common error";


        case NETDEV_E_USER_WRONG_PASSWD: return "用户密码错误  Incorrect password";
        case NETDEV_E_USER_LOGIN_MAX_NUM: return "用户登录数已达上限  Number of login users reached the upper limit";
        case NETDEV_E_USER_NOT_ONLINE: return "用户不在线  User not online";
        case NETDEV_E_USER_NO_SUCH_USER: return "没有该用户  User not online";
        case NETDEV_E_USER_NO_AUTH: return "用户无权限  User has no rights";
        case NETDEV_E_USER_MAX_NUM: return "用户上限-不能再被添加  Reached the upper limit–no more users can be added";
        case NETDEV_E_USER_EXIST: return "用户已存在  User already exists";
        case NETDEV_E_USER_PASSWORD_CHANGE: return "用户密码修改  Password changed";

        case NETDEV_E_LIVE_EXISTED: return "实况业务已经建立  Live video service already established";
        case NETDEV_E_LIVE_INPUT_NOT_READY: return "媒体流未准备就绪  Media stream not ready";
        case NETDEV_E_LIVE_OUTPUT_BUSY: return "实况业务显示资源忙  Display resource is busy for live video service";
        case NETDEV_E_LIVE_CB_NOTEXIST: return "实况控制块不存在  Control module for live video not exist";
        case NETDEV_E_LIVE_STREAM_FULL: return "实况流资源已满  Live stream resource full";

        case NETDEV_E_CAPTURE_NO_SUPPORT_FORMAT: return "抓拍格式不支持  Format of captured image not supported";
        case NETDEV_E_CAPTURE_NO_ENOUGH_CAPACITY: return "硬盘空间不足  Insufficient disk space";
        case NETDEV_E_CAPTURE_NO_DECODED_PICTURE: return "没有解码过的图片可供抓拍  No decoded image for capture";
        case NETDEV_E_CAPTURE_SINGLE_FAILED: return "单次抓拍操作失败  Single capture failed";

        case NETDEV_E_VOD_PLAY_END: return "回放结束  Playback ended";
        case NETDEV_E_VOD_NO_CM: return "回放控制块不存在  Playback controlling module not exist";
        case NETDEV_E_VOD_OVER_ABILITY: return "回放能力超出限制  Beyond playback capability";
        case NETDEV_E_VOD_NO_RECORDING_CM: return "录像文件控制块不存在  Recording file controlling module not exist ";
        case NETDEV_E_VOD_NO_RECORDING: return "无录像内容   No recording";
        case NETDEV_E_VOD_NO_REPLAYURL: return "无法获取回放的url   Cannot get the URL for playback";
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






bool CFactory::init()
{

    if (!m_init)
    {

        m_init = NETDEV_Init();
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
    NETDEV_Cleanup();
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new YyShiKejiVideoServer();
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

std::vector<YyShiKejiVideoServer*> YyShiKejiVideoServer::sServers;
std::recursive_mutex YyShiKejiVideoServer::sMtServers;

/*
 * 析构函数
 */
YyShiKejiVideoServer::YyShiKejiVideoServer()
{
    std::lock_guard<std::recursive_mutex> lock(YyShiKejiVideoServer::sMtServers);
    sServers.push_back(this);
    m_pPlayFile = nullptr;
    m_lLoginHandle = NULL;
}

YyShiKejiVideoServer::~YyShiKejiVideoServer()
{

    //logout();
    hk_log.AddLog(std::string("YyShiKejiVideoServer::~YyShiKejiVideoServer()"));
    std::lock_guard<std::recursive_mutex> lock(YyShiKejiVideoServer::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* YyShiKejiVideoServer::clone()
{
    YyShiKejiVideoServer *svr = new YyShiKejiVideoServer();
    return svr;
}

bool YyShiKejiVideoServer::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{

	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));
    m_lLoginHandle = (long)NETDEV_Login((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);
    if (m_lLoginHandle == NULL)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NETDEV_Login failed:") + m_sLastError);
        return false;
    }

    for (int i = 0; i < m_deviceInfo.dwChannelNum; i++)
    {
        channels[i + 1] = QString("channel%1").arg(i + 1).toStdString();
    }
    return true;
}

bool YyShiKejiVideoServer::logout()
{

    if (m_lLoginHandle >= 0 && !NETDEV_Logout((LPVOID)m_lLoginHandle))
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("logout failed:") + m_sLastError);
        return false;
    }
    else {
        hk_log.AddLog(std::string("YyShiKejiVideoServerlogout ok!"));
    }

    return true;
}

bool YyShiKejiVideoServer::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    const int BYTE_ONE_SECONDS = 234947;
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

    struct tm Tm;
    NETDEV_FILECOND_S f;
    memset(&f, 0, sizeof(NETDEV_FILECOND_S));
    //stFileCond.dwChannelID = m_lChannelID;
    LPVOID dwFileHandle = 0;

    /* UTC time. The found period of time is 24 hours from current system time. */
    f.tBeginTime = timeStart;
    f.tEndTime = timeEnd;

    auto itr = channelVec.begin();
    RecordFile rf;
    for (; itr != channelVec.end(); itr++)
    {
        int nChannelId = *itr;
        f.dwChannelID = nChannelId;

        dwFileHandle = NETDEV_FindFile((LPVOID)m_lLoginHandle, &f);
        if (NULL != dwFileHandle)
        {
            NETDEV_FINDDATA_S stVodFile = { 0 };
            hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
            while (NETDEV_FindNextFile(dwFileHandle, &stVodFile))
            {
                if (stVodFile.tBeginTime == stVodFile.tEndTime)
                {
                    continue;
                }
                hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
                rf.beginTime = stVodFile.tBeginTime;
                rf.endTime = stVodFile.tEndTime;

                rf.channel = nChannelId;
                rf.name = stVodFile.szFileName;
                rf.size = (rf.endTime - rf.beginTime) * BYTE_ONE_SECONDS;

                rf.setPrivateData(&stVodFile, sizeof(NETDEV_FINDDATA_S));
                files.push_back(rf);

            }
            hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
            NETDEV_FindClose(dwFileHandle);
            hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
        }

        hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
    }

    hk_log.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
   return true;
}


bool YyShiKejiVideoServer::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (m_lLoginHandle == NULL)
    {
        m_sLastError = "请先登录!";
        hk_log.AddLog("downLoadByRecordFile 请先登录!");
        return false;
    }

    NETDEV_PLAYBACKCOND_S stPlayBackInfo = { 0 };
    stPlayBackInfo.hPlayWnd = NULL;
    stPlayBackInfo.dwDownloadSpeed = NETDEV_DOWNLOAD_SPEED_FOUR;

    stPlayBackInfo.tBeginTime = file.beginTime;
    stPlayBackInfo.tEndTime = file.endTime + file.endTime - file.beginTime;
    stPlayBackInfo.dwChannelID = file.channel;

    hdl = (download_handle_t)NETDEV_GetFileByTime((LPVOID)m_lLoginHandle, &stPlayBackInfo, (char *)saveFileName, NETDEV_MEDIA_FILE_MP4);
    if (NULL == hdl)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NETDEV_GetFileByTime failed:") + m_sLastError + " 文件：" + saveFileName);
        return false;
    }
//     int enSpeed = NETDEV_DOWNLOAD_SPEED_EIGHT;
//     int bRet = NETDEV_PlayBackControl((LPVOID)hdl, NETDEV_PLAY_CTRL_SETPLAYSPEED, &enSpeed);

    QString qsFile(QString::fromLocal8Bit(saveFileName));
    QFile::remove(qsFile);

    mMpDownloadPosCaculators[hdl].init(file.size, qsFile.left(QString(saveFileName).lastIndexOf(".")).toLocal8Bit().data());
    QFile::remove(QString::fromLocal8Bit(mMpDownloadPosCaculators[hdl].getSaveFile()));
    mMpDownloadRecords[hdl] = file;
    return true;
}

HWND playWwnd = NULL;
LPVOID playHandle = NULL;
bool YyShiKejiVideoServer::playVideo(INT64 beginTime, INT64 tEndTime, int channel){
    NETDEV_PLAYBACKCOND_S stPlayBackByTimeInfo = { 0 };

    /* Assume to play the first recording found */
    stPlayBackByTimeInfo.tBeginTime = beginTime;
    stPlayBackByTimeInfo.tEndTime = tEndTime;
    stPlayBackByTimeInfo.dwChannelID = channel;

    stPlayBackByTimeInfo.hPlayWnd = playWwnd;
    stPlayBackByTimeInfo.dwLinkMode = NETDEV_TRANSPROTOCAL_RTPTCP;

    playHandle =  NETDEV_PlayBackByTime((LPVOID)m_lLoginHandle, &stPlayBackByTimeInfo);
    if (NULL == playHandle)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_PlayBackControl failed:") + m_sLastError);
        return false;
    }
    
    return true;
}

bool  YyShiKejiVideoServer::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (0 == m_lLoginHandle)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    StopPlayBack(playbackHandle, 0);
    playWwnd = hwnd;
    if (!this->playVideo(file.beginTime, file.endTime, file.channel)){
        return false;
    }

    m_pPlayFile = &file;
    playbackHandle = (play_handle_t)m_pPlayFile;
    return true;
}

bool YyShiKejiVideoServer::SetPlayBack(play_handle_t playbackHandle, __int32 pos)
{
    if (m_lLoginHandle == NULL)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    
//    StopPlayBack(playbackHandle, 0);
    INT64 iTime = m_pPlayFile->beginTime + (m_pPlayFile->endTime - m_pPlayFile->beginTime) * pos / 100;
//     RecordFile* pFile = (RecordFile*)playbackHandle;
//     return this->playVideo(iTime, pFile->endTime, pFile->channel);
// 

//     BOOL bRet = NETDEV_PlayBackControl((LPVOID)playbackHandle, NETDEV_PLAY_CTRL_GETPLAYTIME, &(iTime));
//     if (TRUE != bRet)
//     {
//         hk_log.AddLog(std::string("Get playtime failed. failed:") + m_sLastError);
//         return false;
//     }

    BOOL bRet = NETDEV_PlayBackControl((LPVOID)playbackHandle, NETDEV_PLAY_CTRL_SETPLAYTIME, &iTime);
    if (TRUE != bRet)
    {
        m_sLastError = GetLastErrorString();
        hk_log.AddLog(std::string("NET_DVR_PlayBackControl failed:") + m_sLastError);
        return false;
    }

    return true;
}

bool YyShiKejiVideoServer::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (m_lLoginHandle == NULL)
    {
        m_sLastError = "请先登录!";
        return false;
    }
    if (NULL == playHandle)
    {
        return true;
    }
    int bRet = NETDEV_StopPlayBack(playHandle);
    if (TRUE != bRet)
    {
        m_sLastError = GetLastErrorString();
        return false;
        
    }
    playHandle = NULL;
    return true;
}



bool YyShiKejiVideoServer::stopDownload(download_handle_t h)
{

    if (TRUE != NETDEV_StopGetFile((LPVOID)h))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }
    if (mMpDownloadPosCaculators.find(h) == mMpDownloadPosCaculators.end())
    {
        return false;
    }

    QFile::remove(QString::fromLocal8Bit(mMpDownloadPosCaculators[h].getSaveFile()));
    mMpDownloadRecords.erase(h);
    mMpDownloadPosCaculators.erase(h);
    return true;
}


bool YyShiKejiVideoServer::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed){
    
    mMpDownloadPosCaculators[h].getPos(*totalSize, *currentSize);
    *failed = false;
    if (mMpDownloadPosCaculators[h].isMaybeFishish())
    {
        INT64 iTime = 0;
        BOOL bRet = NETDEV_PlayBackControl((LPVOID)h, NETDEV_PLAY_CTRL_GETPLAYTIME, &(iTime));
        if (bRet)
        {
            RecordFile& file = mMpDownloadRecords[h];
            *currentSize = file.size * (iTime - file.beginTime) / (file.endTime - file.beginTime);
            *totalSize = file.size;
        }
        else{
            return true;
        }
    }
    
    
    
    if (*currentSize >= *totalSize)
    {
        *totalSize = *currentSize;
        this->stopDownload(h);
    }
    return true;
}