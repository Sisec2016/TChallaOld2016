#pragma once
#include "videoserver.h"
#include "RCF/RCF.hpp"
#include <mutex>
#include "Service.h"

class VideoserverSvrImp
{
private:
	static int sMaxPort;
	static std::recursive_mutex sMutexServers;
	static std::map< std::shared_ptr< RCF::RcfServer >, std::shared_ptr< VideoserverSvrImp > > spServers;
	static std::recursive_mutex sMutexReleaseServers;
	static std::map< std::shared_ptr< RCF::RcfServer >, std::shared_ptr< VideoserverSvrImp > > spRleaseServers;
	videoserver *m_pServer;
	int32_t mServerPort;
	static void add(std::shared_ptr< RCF::RcfServer >, std::shared_ptr< VideoserverSvrImp >);
public:
	static int create(videoserver *pServer);
	static int create(videoserverFactory*  f);
	static void release( VideoserverSvrImp* p);
    static videoserver* getVideoServerByPort(int32_t Port);
	static int32_t getPortByVideoServer(videoserver *pServer);
public:
	VideoserverSvrImp(videoserver *pServer, int port);
	~VideoserverSvrImp();

	void destroy( );
	void remove();
	int clone();
	int cloneDerect();
	std::string getLastError();
	bool PlayBackByRecordFile(VideoServer::RecordInfo& vsrf, int64_t hwnd, int64_t& playBackHandle);
	bool SetPlayBack(int64_t playBackHandle, int32_t pos);
	bool StopPlayBack(int64_t playBackHandle, int32_t pause);
	std::string useName();
	std::string passwords();
	std::string ip();
	int32_t port();
	int64_t factory();
	bool logout();
	bool GetRecordFileList(VideoServer::RecordInfoList& vsrflst, std::vector<int>& channels,
		int64_t begTime, int64_t endTime);
	bool GetRecordFileListZone(VideoServer::RecordInfoList& vsrflst, std::vector<int>& channels, 
		int64_t begTime, int64_t endTime);
	bool ClearRecordFileList();
    bool downLoadByRecordFile(std::string filePath, VideoServer::RecordInfo vsri, int64_t& downloaHandle);
    bool stopDownload(int64_t downloaHandle);
	bool stopDownloadAll();
	std::string getChannelName(int32_t channel);
	std::string getFileName(VideoServer::RecordInfo vsri);
    bool login(std::string IP, int32_t port, std::string user,
        std::string password, std::vector< int32_t>& channels, std::vector<std::string > & channelNames);
	void getChannels(std::vector< int32_t>& channelIds, std::vector<std::string > &channelNames);
    bool getPlayBackPos(__int64 playbackHandle, int32_t& pos);
    bool getDownloadPos(int64_t h, int64_t& totalSize, int64_t& currentSize, int32_t& failed);

};

