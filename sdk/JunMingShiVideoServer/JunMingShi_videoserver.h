#ifndef JunMingShi_VIDEOSERVER_H
#define JunMingShi_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <memory>
#include <string>
#include <map>
using std::map;
using std::string;
#include "Api_JunMingShi.h"
#include "Poco/Mutex.h"
using Poco::Mutex;

class CFactoryJunMingShi : public IVideoServerFactory
{
public:
    CFactoryJunMingShi();
    ~CFactoryJunMingShi();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "¿¡Ã÷ÊÓ";
    }

    virtual int defaultPort()
    {
		return 8670;
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
        return SISC_IPC_JUNMINGSHI;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("ifv");
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

typedef struct
{
	unsigned int iWnd;
	unsigned int iThis;
	long lPlayPort;
}PlayCBContext;

class JunMingShi_videoserver : public IVideoServer
{
    friend class CFactoryJunMingShi;
public:
    JunMingShi_videoserver();
    ~JunMingShi_videoserver();

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

    //JunMingShi::NET_DEVICEINFO m_deviceInfo;

	string m_strIp;
	string m_strUser;
	string m_strPsw;
	int m_iPort;

	HANDLE m_hEventRecordFile;
public:
	std::vector<RecordFile> m_files;
	map<string, JunMingShi::NETDVR_recFileInfo_t> m_mapArcItem;


	Mutex m_mtx;
	map<long long, RecordFile> m_mapDownload;
	map<long long, RecordFile> m_mapPlay;

	map<unsigned int, long long> m_mapWndHandle;

	Mutex m_mtxPos;
	map<long long, stPos_DownPlay> m_mapPosDown;
	map<long long, stPos_DownPlay> m_mapPosPlay;
};


#endif // HIKAN_VIDEOSERVER_H
