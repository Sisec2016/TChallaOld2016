#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <memory>
#include <mutex>
#include <string>
#include <QDateTime>
#include "WPPdvrSdk.H"
//  #define LNM_TEST
class CFactory : public IVideoServerFactory
{
public:
    CFactory();
    ~CFactory();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "²¨Á£";
    }

    virtual int defaultPort()
    {
        return 9000;
    }
    virtual const char* defaultUser()
    {
        return "admin";
    }

    virtual const char* defaultPasswords()
    {
        return "admin";
    }
    virtual DeviceFactory factory()
    {
        return SISC_IPC_BOLI;
    }

    virtual void videoFileExterns(std::vector<std::string>& externs)
    {
        externs.push_back("dvr");
    }

    virtual IVideoServer* create();

};
struct DownloadInfo
{
    DownloadInfo() : mDownloadHandle(-1){
        
        init();
    }
    void init(){
        mDownloadHandle = -1;
        mDownloadSize = 0;
        mLastDownloadSize = 0;
        mLastFileSize = 0;
        mDownloadBeginTime = -1;
    }
    long mDownloadHandle;
    __int64 mDownloadSize;
    __int64 mLastDownloadSize;
    __int64 mLastFileSize;
    __int64 mDownloadBeginTime;
    RecordFile mDownloadFile;
    QString mPath;
};

class boli_videoserver : public IVideoServer
{
    friend class CFactory;
public:
    static std::recursive_mutex sMtServers;
    static std::vector<boli_videoserver*> sServers;
public:
    boli_videoserver();
    ~boli_videoserver();

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels);
    virtual bool logout();
	virtual bool GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                 __time64_t timeEnd);

    virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    bool SetPlayBack(play_handle_t playbackHandle, __int32 pos);
    virtual bool StopPlayBack(play_handle_t playbackHandle, __int32 mPause);
    virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
private:
    bool reLogin();
    __time64_t mStartPlayTime;
    std::string mIP;
    int mPort;
    std::string mUser;
    std::string mPassword;

    std::map<play_handle_t, long> mMpPlaybackHandles;
    QDateTime mPlayBeg;
    QDateTime mPlayEnd;
public:
    int gChannel;
    std::map<download_handle_t, DownloadInfo*> mMpDownloadInfos;
protected:
    DVR_DEVICEINFO mDeviceInfo;
    std::map<__int32, std::string> mChannels;
};


#endif // HIKAN_VIDEOSERVER_H
