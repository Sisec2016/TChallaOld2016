
#ifndef GZLL_VIDEOSERVER_H
#define GZLL_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <qdatetime.h>
#include <boost/thread.hpp>
#include <QObject>
#include <QFileInfo>
#include <boost/thread/recursive_mutex.hpp>

#ifndef CALL_METHOD
#define CALL_METHOD __stdcall
#endif

class CFactory : public IVideoServerFactory
{
public:
    CFactory();
    ~CFactory();

    virtual const char* name()
    {
        return "µœ÷«∆÷";
    }

    virtual int defaultPort()
    {
        return 34567;
    }
    virtual const char* defaultUser()
    {
        return "admin";
    }

    virtual const char* defaultPasswords()
    {
        return "";
    }
    bool init();
    void clean();
    virtual DeviceFactory factory()
    {
        return SISC_IPC_DIZHIPU;
    }

    virtual void videoFileExterns(std::vector<std::string>& externs)
    {
        externs.push_back("h264");
    }

    virtual IVideoServer* create();
    virtual bool searchDevice(std::vector<DeviceInfo>& devices);
};

class H264_DVR_FILE_DATA;
class gzll_videoserver : public IVideoServer
{
    friend class CFactory;
public:
    static boost::recursive_mutex sMtServers;
    static std::vector<gzll_videoserver*> sServers;
public:
    gzll_videoserver();
    ~gzll_videoserver();

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user,
                       const char* password, std::map<__int32, std::string>& channels);
    virtual bool logout();
    virtual bool downLoad(const char* saveFileName, int nChannelId,__time64_t timeStart,
                          __time64_t timeEnd, download_handle_t& hdl);

    virtual bool GetRecordFileList(std::vector<RecordFile>& files, __int32 nChannelId, __time64_t timeStart,
                                   __time64_t timeEnd);
    virtual bool GetRecordFileList(std::vector<RecordFile>& files, /*__int32 nChannelId*/const std::vector<int>& channelVec, __time64_t timeStart,
                                    __time64_t timeEnd);

    virtual void ClearRecordFileList()
    {
    }

    virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    virtual bool SetPlayBack(__int64 playbackHandle, __int32 pos);
    virtual bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
    virtual bool StopPlayBack(__int64 playbackHandle,__int32 mPause);

protected:
    long m_lLoginHandle;
    long m_hPlayBack;
private:
    bool isConnected();
};

#endif // GZLL_VIDEOSERVER_H
