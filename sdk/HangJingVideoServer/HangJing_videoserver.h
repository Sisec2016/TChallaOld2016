#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
// #include "hcnetsdk.h"
#include <memory>
// #include <mutex>
#include <string>
using namespace std;
#include "LvrNetSdk.h"
#pragma comment(lib, "LvrNetSdk.lib")
#include "Poco/Mutex.h"
using Poco::Mutex;


class CFactoryHangJing : public IVideoServerFactory
{
public:
    CFactoryHangJing();
    ~CFactoryHangJing();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "º½¾°¿Æ¼¼";
    }

    virtual int defaultPort()
    {
		return 7777;
    }
	virtual const char* defaultUser()
    {
        return "admin";
    }

	virtual const char* defaultPasswords()
    {
        return "666666";
    }
    virtual DeviceFactory factory()
    {
		return SISC_IPC_HANGJINGKEJI;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("mp4");
        //externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

class HangJing_videoserver : public IVideoServer
{
    friend class CFactoryHangJing;
public:
//     static std::recursive_mutex sMtServers;
//     static std::vector<HangJing_videoserver*> sServers;
public:
    HangJing_videoserver();
    ~HangJing_videoserver();

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
	bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
	bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
private:
    const RecordFile* m_playFile;
    __time64_t mStartPlayTime;

	Mutex m_mtx;
	map<string, LVR_NET_FILE> m_mapArcItem;
	map<long long, RecordFile> m_mapDownloadOrPlay;
public:
	LONG m_lStreamHandle;
	int m_iPort;
protected:

	LVR_NET_DEVICE_INFO m_deviceInfo;

};


#endif // HIKAN_VIDEOSERVER_H
