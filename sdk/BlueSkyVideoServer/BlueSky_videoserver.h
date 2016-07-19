#ifndef BlueSky_VIDEOSERVER_H
#define BlueSky_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <memory>
#include <string>
#include <map>
#include <mutex>
#include "dvxPlayer.h"
using std::map;
using std::string;


class CFactoryBlueSky : public IVideoServerFactory
{
public:
    CFactoryBlueSky();
    ~CFactoryBlueSky();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "À¶É«ÐÇ¼Ê";
    }

    virtual int defaultPort()
    {
		return 3721;
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
        return SISC_IPC_BLUESKY;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("bsr");
        //externs.push_back("dav");
    }

    virtual IVideoServer* create();

};

typedef struct
{
	__time64_t iTotalSize;
	__time64_t iCurSize;
	int iPercent;
	int count;
}stPos_DownPlay;

class bluesky_videoserver : public IVideoServer
{
    friend class CFactoryBlueSky;
public:
    bluesky_videoserver();
    ~bluesky_videoserver();

//     virtual IVideoServer* clone();
//     virtual bool login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels);
//     virtual bool logout();
// 	virtual bool GetRecordFileList(std::vector<RecordFile>& files, std::vector<int>& channelVec, __time64_t timeStart,
//                                                  __time64_t timeEnd);
// 
//     virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
//     virtual bool stopDownload(download_handle_t h);
//     virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
//     bool SetPlayBack(__int64 playbackHandle, __int32 pos);
// 	virtual bool StopPlayBack(__int64 playbackHandle,__int32 mPause);
// 	virtual bool getPlayBackPos(__int64 playbackHandle, __int32* pos);

    virtual IVideoServer* clone();
    virtual bool login(const char* IP, __int32 port, const char* user,
        const char* password, std::map<__int32, std::string>& channels);
    virtual bool logout();
    virtual bool GetRecordFileList(std::vector<RecordFile>& files, /*__int32 nChannelId*/const std::vector<int>& channelVec, __time64_t timeStart,
        __time64_t timeEnd);
    virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    virtual bool SetPlayBack(__int64 playbackHandle, __int32 pos);
    virtual bool StopPlayBack(__int64 playbackHandle, __int32 mPause);
    virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
private:
    std::recursive_mutex m_mtxPos;
    std::map<long long, RecordFile> mDownloadFiles;
};


#endif // HIKAN_VIDEOSERVER_H
