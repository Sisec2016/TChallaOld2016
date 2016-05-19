#ifndef VIDEOSERVER_SVR_H
#define VIDEOSERVER_SVR_H
#include "../../VideoServer/IVideoServer.h"
#include "RCF/RCF.hpp"
#include "Service.h"

class SvrFactory : public IVideoServerFactory
{
    std::string mName;
    std::string mDefaultUser;
    std::string mDefaultPasswords;
    int mFactory;

    static std::recursive_mutex sMutexService;
	static std::shared_ptr< RcfClient<VideoserverFactorySvr> > spService;
	static bool init_service();
public:
    static void startSver();
	static int getByIndex(int index);
	static int getByName(std::string sName);
	static void getFactorys(std::vector< int >& vcFactorys);
    static bool getRefreshPort(int& newProt, int32_t factory, int32_t oldPort);
public:
	SvrFactory(int f);
	~SvrFactory();

	virtual const char* name();
	virtual int defaultPort();
	virtual const char* defaultUser();

	virtual const char* defaultPasswords();	
	bool init();
	void clean();
	virtual DeviceFactory factory();

	virtual void videoFileExterns(std::vector<std::string>& externs);

	virtual IVideoServer* create();

};

class SvrVideoserver : public IVideoServer
{
    friend class SvrFactory;
    int mPort;
    int mFactory;
    std::recursive_mutex mMutexService;
    std::shared_ptr< RcfClient<VideoserverSvr> > mpService;
    bool init_service();
public:
    static SvrVideoserver* getServerByPort(int port);

public:
	static std::recursive_mutex sMtServers;
    static std::vector<SvrVideoserver*> sServers;
public:
    SvrVideoserver(int port, int factory);
    ~SvrVideoserver();
    virtual void destroy();
	virtual IVideoServer* clone();
	virtual bool login(const char* IP, __int32 port, const char* user,
		const char* password, std::map<__int32, std::string>& channels);
	virtual bool logout();
	virtual bool GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
		__time64_t timeEnd);
	//清除已查询到得视频文件清单
	virtual void ClearRecordFileList();

	virtual bool downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl);
	virtual bool stopDownload(download_handle_t h);
	virtual bool PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle);
	virtual bool SetPlayBack(__int64 playbackHandle, __int32 pos);
	virtual bool getPlayBackPos(__int64 playbackHandle, __int32* pos);
	virtual bool StopPlayBack(__int64 playbackHandle, __int32 mPause);
    virtual const char* getLastError();
    virtual bool getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed);
protected:
};


#endif // VIDEOSERVER_H
