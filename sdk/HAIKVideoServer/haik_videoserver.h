#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include "hcnetsdk.h"
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
        return "º£¿µ";
    }

    virtual int defaultPort()
    {
        return 8000;
    }
    virtual const char* defaultUser()
    {
        return "admin";
    }

    virtual const char* defaultPasswords()
    {
        return "12345";
    }
    virtual DeviceFactory factory()
    {
        return SISC_IPC_HIKVISION;
    }

    virtual void videoFileExterns(std::vector<std::string>& externs)
    {
        externs.push_back("mp4");
        externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

class haik_videoserver : public IVideoServer
{
    friend class CFactory;
public:
    static std::recursive_mutex sMtServers;
    static std::vector<haik_videoserver*> sServers;
public:
    haik_videoserver();
    ~haik_videoserver();

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

private:
    __time64_t mStartPlayTime;

protected:

    NET_DVR_DEVICEINFO_V30 m_deviceInfo;

};


#endif // HIKAN_VIDEOSERVER_H
