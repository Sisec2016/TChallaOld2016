#ifndef TDY_VIDEOSERVER_H
#define TDY_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include "NetClientTypes.h"
//#include "NetSdkClient.h"
#include "NetSDK.h"

#include "Poco/Mutex.h"

#include <memory>
#include <mutex>
#include <string>
#include <map>

using Poco::Mutex;
using std::string;

class CTDYFactory : public IVideoServerFactory
{
public:
	CTDYFactory();
	~CTDYFactory();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "ÌìµØÎ°Òµ";
    }

    virtual int defaultPort()
    {
        return 3000;
    }
	virtual const char* defaultUser()
    {
        return "Admin";
    }

	virtual const char* defaultPasswords()
    {
        return "1111";
    }
    virtual DeviceFactory factory()
    {
        return SISC_IPC_TDWY;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
		externs.push_back("sdv");
		//externs.push_back("mp4");
    }

    virtual IVideoServer* create();

};

struct DownLoadInfo
{
	int filesize;
};

class tdy_videoserver : public IVideoServer
{
    friend class CFactory;
public:
    static std::recursive_mutex sMtServers;
	static std::vector<tdy_videoserver*> sServers;
public:
	tdy_videoserver();
	~tdy_videoserver();

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

	virtual bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
//	virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);

private:
    const RecordFile* m_playFile;
    __time64_t mStartPlayTime;

	Mutex m_mtx;
	Mutex m_downloadMutex;

protected:

	int m_iLogonID;
	std::map<unsigned int, DownLoadInfo> m_DownLoadStream;
    //NET_DVR_DEVICEINFO_V30 m_deviceInfo;

};


#endif // HIKAN_VIDEOSERVER_H
