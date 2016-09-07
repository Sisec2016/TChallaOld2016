#ifndef DH_VIDEOSERVER_H
#define DH_VIDEOSERVER_H
#include "../../VideoServer/IVideoServer.h"
#include <memory>
#include <string>
#include <map>
#include <mutex>
#include <QString>
using std::map;
using std::string;
#include "Api_ZhongWei.h"
#include "Poco/Mutex.h"
using Poco::Mutex;
using Poco::ScopedLock;

class CFactoryZhongWei : public IVideoServerFactory
{
public:
    CFactoryZhongWei();
    ~CFactoryZhongWei();

    bool init();
    void clean();

    virtual const char* name()
    {
        return "ÖÐÎ¬";
    }

    virtual int defaultPort()
    {
        return 9101;
    }
    virtual const char* defaultUser()
    {
        return "abc";
    }

    virtual const char* defaultPasswords()
    {
        return "123";
    }
    virtual DeviceFactory factory()
    {
		return SISC_IPC_ZHONGWEI;
    }

    virtual void videoFileExterns(std::vector<std::string >& externs)
    {
        externs.push_back("mp4");
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

typedef struct
{
	int iLinkId;
}stChannelInfo;

class ZhongWei_videoserver : public IVideoServer
{
    friend class CFactoryZhongWei;
    static std::map<int, ZhongWei_videoserver*> sLinkeVideoserver;
    static std::recursive_mutex sMutexLinkVideservrs;
public:
    static void dealConnected(ZhongWei::JCLink_t nLinkID, const QString& sError);
    static void dealDisConnected(ZhongWei::JCLink_t nLinkID, const QString& sError);
    static void dealDownloadData(ZhongWei::JCLink_t nLinkID, char* data, int len);
    static void dealFinishDownload(ZhongWei::JCLink_t nLinkID, const QString& sError);
    static void dealFindFiles(ZhongWei::JCLink_t nLinkID, ZhongWei::PJCRecFileInfo pInfos, int nCount);
public:
    void onConnected(const QString& sError);
    void onDisConnected(const QString& sError);
    void onDownloadData(char* data, int len);
    void onFinishDownload(const QString& sError);
    void onFindFiles(ZhongWei::PJCRecFileInfo pInfos, int nCount);
public:
    ZhongWei_videoserver();
    ~ZhongWei_videoserver();

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
	Mutex m_mtx;
	map<string, ZhongWei::JCRecFileInfo> m_mapArcItem;
	map<long long, RecordFile> m_mapDownloadOrPlay;
public:
	Mutex m_mtxPos;
	map<long long, stPos_DownPlay> m_mapPosDownPlay;
	map<int, stChannelInfo> m_mapChannelInfo;

// 	Mutex m_mtxLinkinfo;
// 	map<int, int> m_mapLinkInfo;

	int    m_iPort;
	bool   m_bDownLoading;
	string m_strIP;
	string m_strUser;
	string m_strPsw;

    
    HANDLE mhConnectEvent;// = CreateEventA(NULL, FALSE, FALSE, NULL)
    std::vector<ZhongWei::JCRecFileInfo> m_RecFileInfoList;
    HANDLE m_hEventSearch;
    bool m_bDownloadFinished;
    ZhongWei::JCLink_t mCurLink;
    FILE *m_pRecFile;
    QString msConnectError;
    QString msDownloadError;
    std::recursive_mutex m_recFileMutex;
    std::recursive_mutex m_linksMutex;
    std::map<int, int> m_mpLinks;
    INT64 mDownloadTotalSize;
    INT64 mDownloadSize;
    INT64 mLastDownloadSize;
private:
    bool connectChannel(int channel);
    bool disconnectChannel(int channel);
    bool hasLogin();
};


#endif // HIKAN_VIDEOSERVER_H
