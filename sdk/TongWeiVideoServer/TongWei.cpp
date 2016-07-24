#include "TongWei.h"
#include <iostream>

#include <time.h>
#include <io.h>
#include "../../VideoServer/log.h"
#include <thread>
#include <QFile>
#include <qdebug.h>
#include <QDateTime>
#include <algorithm>
Log logFile("TongWei");

extern "C" VIDEOSERVER_EXPORT IVideoServerFactory* VideoServerFactory()
{

    return new CFactory();
}


std::string GetLastErrorString()
{
    return NET_SDK_GetErrorMsg();
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

        m_init = NET_SDK_Init();
        if (!m_init)
        {

           m_sLastError = GetLastErrorString();
           logFile.AddLog(std::string("init failed:") + m_sLastError);
        }


    }

    return m_init;
}


void CFactory::clean()
{
    NET_SDK_Cleanup();
}




IVideoServer* CFactory::create()
{
    if (!init())
    {
        return nullptr;
    }

    return new VideoServer();
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

std::vector<VideoServer*> VideoServer::sServers;
std::recursive_mutex VideoServer::sMtServers;

#define  HANDLE_NULL -1
/*
 * Îö¹¹º¯Êý
 */
VideoServer::VideoServer()
{
    std::lock_guard<std::recursive_mutex> lock(VideoServer::sMtServers);
    sServers.push_back(this);
    m_pPlayFile = nullptr;
    m_lLoginHandle = HANDLE_NULL;
}

VideoServer::~VideoServer()
{

    //logout();
    logFile.AddLog(std::string("VideoServer::~VideoServer()"));
    std::lock_guard<std::recursive_mutex> lock(VideoServer::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}

IVideoServer* VideoServer::clone()
{
    //VideoServer *svr = new VideoServer();
    return NULL;
}

bool VideoServer::login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string>& channels)
{
    logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
    logout();
	channels.clear();
    memset(&m_deviceInfo, 0, sizeof(m_deviceInfo));
    m_lLoginHandle = (long)NET_SDK_Login((char*)IP, port,
                                   (char*)user,(char*)password,
                                   &m_deviceInfo);
    if (m_lLoginHandle == HANDLE_NULL)
    {
        m_sLastError = GetLastErrorString();
        logFile.AddLog(std::string("NETDEV_Login failed:") + m_sLastError);
        return false;
    }

    for (int i = 0; i < m_deviceInfo.videoInputNum; i++)
    {
        channels[i];
    }
    return true;
}

bool VideoServer::logout()
{

    if (m_lLoginHandle != HANDLE_NULL && NET_SDK_Logout(m_lLoginHandle) == -1)
    {
        m_sLastError = GetLastErrorString();
        logFile.AddLog(std::string("logout failed:") + m_sLastError);
        return false;
    }
    else {
        mMpDownloadRecords.clear();
        mMpDownloadSize.clear();
        m_lLoginHandle = HANDLE_NULL;
        logFile.AddLog(std::string("VideoServerlogout ok!"));
    }

    return true;
}


void NetTimeTo(const DD_TIME& nt, __time64_t& t)
{
    struct tm Tm;
    Tm.tm_year = nt.year;
    Tm.tm_mon = nt.month;
    Tm.tm_mday = nt.mday;
    Tm.tm_hour = nt.hour;
    Tm.tm_min = nt.minute;
    Tm.tm_sec = nt.second;

    t = _mktime64(&Tm);
}

void ToNetTime(const __time64_t& t, DD_TIME& nt)
{
    struct tm Tm;
    _localtime64_s(&Tm, (const time_t*)&t);
    nt.year = Tm.tm_year;
    nt.month = Tm.tm_mon;
    nt.mday = Tm.tm_mday;
    nt.hour = Tm.tm_hour;
    nt.minute = Tm.tm_min;
    nt.second = Tm.tm_sec;
}
const int BYTE_ONE_SECONDS = 37600;
bool VideoServer::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                       __time64_t timeEnd)
{
    logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));

    if (m_lLoginHandle == HANDLE_NULL)
    {
        m_sLastError = "ÇëÏÈµÇÂ¼!";
        logFile.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }

    if (timeStart >= timeEnd)
    {
        m_sLastError = "Ê±¼ä·¶Î§²»¶Ô!";
        logFile.AddLog(std::string("GetRecordFileList failed:") + m_sLastError);
        return false;
    }


    auto itr = channelVec.begin();
    RecordFile rf;
    DD_TIME start;
    DD_TIME end;
    for (; itr != channelVec.end(); itr++)
    {
        int nChannelId = *itr;
        ToNetTime(timeStart, start);
        ToNetTime(timeEnd, end);
        logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
        LONG searchHandle = NET_SDK_FindFile(m_lLoginHandle, nChannelId, &start, &end);
        if (searchHandle > 0)
        {
            logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
            while (true)
            {
                NET_SDK_REC_FILE file;
                if (NET_SDK_FindNextFile(searchHandle, &file) == NET_SDK_NOMOREFILE)
                {
                    break;
                }

                NetTimeTo(file.startTime, rf.beginTime);
                NetTimeTo(file.stopTime, rf.endTime);


                rf.channel = nChannelId;
                rf.name = (QDateTime::fromTime_t(rf.beginTime).toString("yyyyMMddhhmmss") 
                            + "_" + QDateTime::fromTime_t(rf.endTime).toString("yyyyMMddhhmmss")).toStdString();
                rf.size = (rf.endTime - rf.beginTime) * BYTE_ONE_SECONDS;

                rf.setPrivateData(&file, sizeof(NET_SDK_REC_FILE));
                files.push_back(rf);
            }
            NET_SDK_FindClose(searchHandle);
            logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
        }
        else{
            logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
        }
       

    }
    std::sort(files.begin(), files.end(), [](const RecordFile& a, const RecordFile& b){
        return a.beginTime < b.beginTime;
    });
    logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
   return true;
}

void addLog(const char* sLog, int nLine)
{

    logFile.AddLog(QString("%1 %2").arg(nLine).arg(sLog));
}

LONG sheNET_SDK_GetFileByTime(LONG lUserID, LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime, char *sSavedFileName){
    long hdl = HANDLE_NULL;
    SHE_BEGING
        hdl = (download_handle_t)NET_SDK_GetFileByTime(lUserID, lChannel, lpStartTime, lpStopTime, sSavedFileName);
    return hdl;
    SHE_END_RETURN(hdl)
}

bool VideoServer::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    std::lock_guard<std::recursive_mutex> lock(mDowloadMutex);
    if (m_lLoginHandle == HANDLE_NULL)
    {
        m_sLastError = "ÇëÏÈµÇÂ¼!";
        logFile.AddLog("downLoadByRecordFile ÇëÏÈµÇÂ¼!");
        return false;
    }

    if (mMpDownloadRecords.size() > 0)
    {
        return false;
    }

    DD_TIME start;
    ToNetTime(file.beginTime, start);
    DD_TIME end;
    ToNetTime(file.endTime, end);
    char sPath[MAX_PATH] = {0};
    strcpy_s(sPath, saveFileName);
    hdl = (download_handle_t)sheNET_SDK_GetFileByTime(m_lLoginHandle, file.channel, &start, &end, sPath);
    if (HANDLE_NULL == hdl)
    {
        m_sLastError = GetLastErrorString();
        logFile.AddLog(std::string("NETDEV_GetFileByTime failed:") + m_sLastError + " ÎÄ¼þ£º" + saveFileName);
        return false;
    }

    logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
    mMpDownloadRecords[hdl] = file;
    mMpDownloadSize[hdl] = 0;
    return true;
}

HWND playWwnd = NULL;
LONG playHandle = HANDLE_NULL;
bool VideoServer::playVideo(INT64 beginTime, INT64 tEndTime, LONG channel){
    DD_TIME start;
    ToNetTime(beginTime, start);
    DD_TIME end;
    ToNetTime(tEndTime, end);
    playHandle = NET_SDK_PlayBackByTime(m_lLoginHandle, &channel, 1, &start, &end, &playWwnd);
    if (NULL >= playHandle)
    {
        m_sLastError = GetLastErrorString();
        logFile.AddLog(std::string("NET_SDK_PlayBackByTime failed:") + m_sLastError);
        return false;
    }
    
    return true;
}

bool  VideoServer::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    if (HANDLE_NULL == m_lLoginHandle)
    {
        m_sLastError = "ÇëÏÈµÇÂ¼!";
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

bool VideoServer::SetPlayBack(play_handle_t playbackHandle, __int32 pos)
{
    if (m_lLoginHandle == HANDLE_NULL)
    {
        m_sLastError = "ÇëÏÈµÇÂ¼!";
        return false;
    }

    DWORD iTime = m_pPlayFile->beginTime + (m_pPlayFile->endTime - m_pPlayFile->beginTime) * pos / 100;
    BOOL bRet = NET_SDK_PlayBackControl(playbackHandle, NET_SDK_PLAYCTRL_SETPOS, iTime, NULL);
    if (!bRet)
    {
        m_sLastError = GetLastErrorString();
        logFile.AddLog(std::string("NET_SDK_PlayBackControl failed:") + m_sLastError);
        return false;
    }

    return true;
}

bool VideoServer::StopPlayBack(download_handle_t playbackHandle, __int32 mPause)
{
    if (m_lLoginHandle == HANDLE_NULL)
    {
        m_sLastError = "ÇëÏÈµÇÂ¼!";
        return false;
    }
    if (HANDLE_NULL == playHandle)
    {
        return true;
    }
    int bRet = NET_SDK_StopPlayBack(playHandle);
    if (TRUE != bRet)
    {
        m_sLastError = GetLastErrorString();
        return false;
        
    }
    playHandle = HANDLE_NULL;
    return true;
}



bool VideoServer::stopDownload(download_handle_t h)
{
    if (HANDLE_NULL == h)
    {
        return true;
    }
    if (TRUE != NET_SDK_StopGetFile(h))
    {
        m_sLastError = GetLastErrorString();
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(mDowloadMutex);
    mMpDownloadRecords.erase(h);
    mMpDownloadSize.erase(h);
    return true;
}


bool VideoServer::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed){
    //logFile.AddLog(QString("%1 %2 %3").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__));
    int pos = NET_SDK_GetDownloadPos(h);
    if (pos < 0 ||  pos > 100)
    {
        *failed = true;
        logFile.AddLog(std::string("NET_SDK_GetDownloadPos failed:") + m_sLastError);
        return true;
    }
    //logFile.AddLog(QString("getDownloadPos  %1").arg(pos));
    *failed = false;
    std::lock_guard<std::recursive_mutex> lock(mDowloadMutex);
    RecordFile& file = mMpDownloadRecords[h];
    *currentSize = file.size * pos / 100;
    *totalSize = file.size;
    if (mMpDownloadSize.find(h) == mMpDownloadSize.end() || mMpDownloadSize[h] < *currentSize)
    {
        mMpDownloadSize[h] = *currentSize;
    }
    else{
        if (mMpDownloadSize[h] * 100 / file.size >= 99){
            mMpDownloadSize[h]++;
        }
        else{
            mMpDownloadSize[h] += BYTE_ONE_SECONDS;
        }

        *currentSize = mMpDownloadSize[h];
    }
    if (pos == 100)
    {
        mMpDownloadRecords.erase(h);
        mMpDownloadSize.erase(h);
    }
    return true;
}