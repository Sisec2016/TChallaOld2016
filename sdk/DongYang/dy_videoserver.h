#ifndef DY_VIDEOSERVER_H
#define DY_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include "Api_dy.h"

#include <memory>
#include <mutex>
#include <string>
#include <map>

#include "Poco/Mutex.h"
using namespace std;
using Poco::Mutex;

class CDongYangFactory : public IVideoServerFactory
{
public:
	CDongYangFactory();
	~CDongYangFactory();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "¶«Ñô¹ú¼Ê";
    }

    virtual int defaultPort()
    {
        return 6001;
    }
	virtual const char* defaultUser()
    {
        return "Admin";
    }

	virtual const char* defaultPasswords()
    {
        return "";
    }
    virtual DeviceFactory factory()
    {
		return SISC_IPC_DOANGYANG;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("avi");
    }

    virtual IVideoServer* create();

};

typedef struct
{
	__time64_t iTotalSize;
	__time64_t iCurSize;
	int iPercent;
}stPos_DownPlay;

class DongYang_videoserver : public IVideoServer
{
    friend class CFactory;
public:
    static std::recursive_mutex sMtServers;
	static std::vector<DongYang_videoserver*> sServers;
public:
	DongYang_videoserver();
	~DongYang_videoserver();

    virtual IVideoServer* clone();
	virtual bool login(const char* IP, __int32 port, const char* user, const char* password, std::map<__int32, std::string >& channels);
    virtual bool logout();
	virtual bool GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
                                                 __time64_t timeEnd);
	void SaveToFiles(DONGYANG::RecFileQueryResult* cFileResult, DWORD dwFileCnt, __int32 nChannelId,
		std::vector<RecordFile>& files);
	void InitTime(DONGYANG::TimeInfo& staTime, DONGYANG::TimeInfo& stopTime, __time64_t timeStart, __time64_t timeEnd);
	virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
    virtual bool stopDownload(download_handle_t h);
    virtual bool  PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
    bool SetPlayBack(download_handle_t playbackHandle, __int32 pos);
    virtual bool StopPlayBack(download_handle_t playbackHandle,__int32 mPause);

	virtual bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
	virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);

private:
    const RecordFile* m_playFile;
    __time64_t mStartPlayTime;

	Mutex m_mtxPos;
	map<long long, stPos_DownPlay> m_mapPosDownPlay;

	Mutex m_mtxFileInfo;
	map<string, string> m_mapFileInfo;
protected:
	
	HDEVICE m_hDevice;
	int m_total_ch_cnt;
};


#endif // DY_VIDEOSERVER_H
