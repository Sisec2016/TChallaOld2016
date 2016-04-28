#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include "NetDEVSDK.h"
#include <memory>
#include <mutex>
#include <string>

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
        return "”Ó ”ø∆ºº";
    }

    virtual int defaultPort()
    {
        return 0;
    }
    virtual const char* defaultUser()
    {
        return "admin";
    }

    virtual const char* defaultPasswords()
    {
        return "123456";
    }
    virtual DeviceFactory factory()
    {
        return SISC_IPC_YUSHIKEJI;
    }

    virtual void videoFileExterns(std::vector<std::string>& externs)
    {
        externs.push_back("mp4");
    }

    virtual IVideoServer* create();

};
class DownloadPosCaculator
{
public:
    DownloadPosCaculator();
    void init(__int64 size, const std::string& sFile)
    {
        mTotalSize = size;
        mSaveFile = sFile;
    }
    static __int64 getFileSize(const std::string& sFile);
    int getPos(__int64& totalSize, __int64& currentSize);
    const char* getSaveFile(){
        return mSaveFile.c_str();
    }
    __int64 getLastCurrentSize(){
        return mLastSize;
    }
    bool isMaybeFishish(){
        return mMaybeFinish;
    }
private:
    __int64 mTotalSize;
    __int64 mLastSize;
    std::string mSaveFile;
    int mLittleTimes;
    bool mMaybeFinish;
};


class YyShiKejiVideoServer : public IVideoServer
{
    friend class CFactory;
public:
    static std::recursive_mutex sMtServers;
    static std::vector<YyShiKejiVideoServer*> sServers;
public:
    YyShiKejiVideoServer();
    ~YyShiKejiVideoServer();

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels);
    virtual bool logout();
	virtual bool GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                 __time64_t timeEnd);

    virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    bool SetPlayBack(download_handle_t playbackHandle, __int32 pos);
    virtual bool StopPlayBack(download_handle_t playbackHandle,__int32 mPause);
    virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
private:
    bool   playVideo(INT64 beginTime, INT64 tEndTime, int channel);
    __time64_t mStartPlayTime;
    std::map<download_handle_t, DownloadPosCaculator> mMpDownloadPosCaculators;
    std::map<download_handle_t, RecordFile> mMpDownloadRecords;
protected:

    NETDEV_DEVICE_INFO_S m_deviceInfo;
    const RecordFile* m_pPlayFile;
};


#endif // HIKAN_VIDEOSERVER_H
