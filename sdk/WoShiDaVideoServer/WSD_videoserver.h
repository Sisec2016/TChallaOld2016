#ifndef WSD_VIDEOSERVER_H
#define WSD_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <memory>
#include <string>
#include <map>
using std::map;
using std::string;
#include "Api_WSD.h"
#include "Poco/Mutex.h"

using Poco::Mutex;

class CFactoryWSD : public IVideoServerFactory
{
public:
	CFactoryWSD();
	~CFactoryWSD();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "Œ÷ À¥Ô";
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
        return "";
    }
    virtual DeviceFactory factory()
    {
        return SISC_IPC_WSD;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

typedef struct
{
	__time64_t iTotalSize;
	__time64_t iCurSize;
	int iPercent;
}stPos_DownPlay;

class WSD_videoserver : public IVideoServer
{
    friend class CFactoryWSD;
public:
	WSD_videoserver();
	~WSD_videoserver();

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels);
    virtual bool logout();
	virtual bool GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                 __time64_t timeEnd);

    virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    bool SetPlayBack(__int64 playbackHandle, __int32 pos);
	virtual bool StopPlayBack(__int64 playbackHandle,__int32 mPause);
	virtual bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
	virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
private:
    const RecordFile* m_playFile;
    __time64_t mStartPlayTime;

protected:

    WSD::ZLNET_DEVICEINFO m_deviceInfo;
	Mutex m_mtx;
	map<string, WSD::ZLNET_RECORDFILE_INFO*> m_mapArcItem;
	map<long long, RecordFile> m_mapDownloadOrPlay;
public:
	Mutex m_mtxPos;
	map<long long, stPos_DownPlay> m_mapPosDownPlay;
};


#endif // HIKAN_VIDEOSERVER_H
