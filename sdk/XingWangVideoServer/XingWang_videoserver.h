#ifndef HIKAN_VIDEOSERVER_H
#define HIKAN_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
// #include "hcnetsdk.h"
#include <memory>
// #include <mutex>
#include <string>
using namespace std;
#include "Api_XingWang.h"
#include "Poco/Mutex.h"
using Poco::Mutex;


class CFactoryXingWang : public IVideoServerFactory
{
public:
    CFactoryXingWang();
    ~CFactoryXingWang();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "ÐÇÍøÈñ½Ý";
    }

    virtual int defaultPort()
    {
		return 8081;
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
		return SISC_IPC_XINWANGRUIJIE;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("avi");
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

class XingWang_videoserver : public IVideoServer
{
    friend class CFactoryXingWang;
public:
//     static std::recursive_mutex sMtServers;
//     static std::vector<XingWang_videoserver*> sServers;
public:
    XingWang_videoserver();
    ~XingWang_videoserver();

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
	map<string, XingWang::SN_DVR_FILEDATA> m_mapArcItem;
	map<long long, RecordFile> m_mapDownloadOrPlay;
public:
	Mutex m_mtxPos;
	map<long long, stPos_DownPlay> m_mapPosDownPlay;
	int m_iPort;

protected:

	XingWang::SN_DEVICEINFO m_deviceInfo;
	string m_strDownFile;
};


#endif // HIKAN_VIDEOSERVER_H
