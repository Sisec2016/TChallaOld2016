#ifndef DiZhiPu_VIDEOSERVER_H
#define DiZhiPu_VIDEOSERVER_H
#include "IVideoServer.h"
#include <memory>
#include <string>
#include <map>
using std::map;
using std::string;
/*#include "Api_DiZhiPu.h"*/
#include "Poco/Mutex.h"
#include "netsdk.h"

using Poco::Mutex;

class CFactoryDiZhiPu : public IVideoServerFactory
{
public:
    CFactoryDiZhiPu();
    ~CFactoryDiZhiPu();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "������";
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
    virtual DeviceFactory factory()
    {
        return ETIM_IPC_DIZHIPU;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("h264");
        //externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

typedef struct
{
	__time64_t iTotalSize;
	__time64_t iCurSize;
	int iPercent;
}stPos_DownPlay;

class dizhipu_videoserver : public IVideoServer
{
    friend class CFactoryDiZhiPu;
public:
    dizhipu_videoserver();
    ~dizhipu_videoserver();

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels);
    virtual bool logout();
	virtual bool GetRecordFileList(std::vector<RecordFile>& files, std::vector<int>& channelVec, __time64_t timeStart,
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

    H264_DVR_DEVICEINFO m_deviceInfo;
	Mutex m_mtx;
	map<string, H264_DVR_FILE_DATA> m_mapArcItem;
	map<long long, RecordFile> m_mapDownloadOrPlay;
public:
	Mutex m_mtxPos;
	map<long long, stPos_DownPlay> m_mapPosDownPlay;
};


#endif // HIKAN_VIDEOSERVER_H
