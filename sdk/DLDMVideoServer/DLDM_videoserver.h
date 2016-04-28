#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
// #include "hcnetsdk.h"
#include <memory>
#include <string>
#include <map>
using std::map;
using std::string;
#include "Poco/Mutex.h"
using Poco::Mutex;
#include "Api_DLDM.h"


class CFactoryDaLi_DM : public IVideoServerFactory
{
public:
    CFactoryDaLi_DM();
    ~CFactoryDaLi_DM();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "大立科技DM";
    }

    virtual int defaultPort()
    {
        return 9998;
    }
	virtual const char* defaultUser()
    {
        return "Admin";
    }

	virtual const char* defaultPasswords()
    {
        return "123456";
    }
    virtual DeviceFactory factory()
    {
		return SISC_IPC_DALIKEJI;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("mp4");
        externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

class DaLi_DM_videoserver : public IVideoServer
{
    friend class CFactoryDaLi_DM;
	friend DWORD WINAPI ThreadProcTimer(
		LPVOID lpParameter   // thread data
		);
public:
//     static std::recursive_mutex sMtServers;
//     static std::vector<DaLi_DM_videoserver*> sServers;
public:
    DaLi_DM_videoserver();
    ~DaLi_DM_videoserver();

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

protected:
	Mutex m_mtx;
	map<string, NET_DLDVR_FIND_DATA> m_mapArcItem;

    NET_DLDVR_DEVICEINFO m_deviceInfo;
	Mutex m_mtxDownload;
	map<long, RecordFile> m_mapDownload;
public:
	string m_strIp;
	int m_iPort;
};


#endif // HIKAN_VIDEOSERVER_H
