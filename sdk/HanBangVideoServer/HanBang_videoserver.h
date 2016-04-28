#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
// #include "hcnetsdk.h"
#include <memory>
// #include <mutex>
#include <string>
using namespace std;
#include "Api_HanBang.h"
#include "Poco/Mutex.h"
using Poco::Mutex;


class CFactoryHanBang : public IVideoServerFactory
{
public:
    CFactoryHanBang();
    ~CFactoryHanBang();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "ºº°î";
    }

    virtual int defaultPort()
    {
		return 8101;
    }
	virtual const char* defaultUser()
    {
        return "admin";
    }

	virtual const char* defaultPasswords()
    {
        return "888888";
    }
    virtual DeviceFactory factory()
    {
		return SISC_IPC_HB;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("mp4");
        externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

class HanBang_videoserver : public IVideoServer
{
    friend class CFactoryHanBang;
public:
//     static std::recursive_mutex sMtServers;
//     static std::vector<HanBang_videoserver*> sServers;
public:
    HanBang_videoserver();
    ~HanBang_videoserver();

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
	map<string, HanBang::HB_SDVR_FIND_DATA> m_mapArcItem;

	Mutex m_mtxdown;
	struct DownLoadInfo
	{
		unsigned long lTotalSize;
		unsigned long lDownSize;
	};
    map<download_handle_t, RecordFile> m_mapDownInfo;

protected:

    HanBang::HB_SDVR_DEVICEINFO_EX m_deviceInfo;

};


#endif // HIKAN_VIDEOSERVER_H
