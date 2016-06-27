#ifndef SERVICE_H
#define SERVICE_H
#include <string>
#include <vector>
#include <map>

#include <RCF/Idl.hpp>
#include <SF/vector.hpp>
#include <SF/string.hpp> 
#include <SF/map.hpp>
#include "LoginInfo.pb.h"
#include "RecordInfo.pb.h"
#include "DeviceInfo.pb.h"

#define PORT_NONE				0
#define PORT_FACTORY			50001
#define PORT_PUBLISH			40001
#define PORT_VIDEOS_SERVER		60000


RCF_BEGIN(VideoserverFactorySvr, "VideoserverFactorySvr")
	RCF_METHOD_R1(int, getByIndex, int);
	RCF_METHOD_R1(int, getByName, std::string);
	RCF_METHOD_V1(void, getFactorys, std::vector< int >&);
	RCF_METHOD_R1(int, create, int);
	RCF_METHOD_R1(std::string, name, int);
	RCF_METHOD_R1(bool, IsOEMFac, int);
	RCF_METHOD_V2(void, videoFileExterns, int, std::vector< std::string >&);
	RCF_METHOD_R1(std::string, getLastError, int);
	RCF_METHOD_R1(int, defaultPort, int);
	RCF_METHOD_R1(std::string, defaultUser, int);
	RCF_METHOD_R1(std::string, defaultPasswords, int);
    RCF_METHOD_R2(int, KeepServerRunning, int, int);
RCF_END(VideoserverFactorySvr);

RCF_BEGIN(VideoserverSvr, "VideoserverSvr")

	RCF_METHOD_V0(void, destroy);
	RCF_METHOD_V0(void, remove);
	RCF_METHOD_R0(int, clone);
	RCF_METHOD_R0(int, cloneDerect);
	RCF_METHOD_R0(std::string, getLastError);
	RCF_METHOD_R3(bool, PlayBackByRecordFile, VideoServer::RecordInfo, int64_t, int64_t&);
	RCF_METHOD_R2(bool, SetPlayBack, int64_t, int32_t);
	RCF_METHOD_R2(bool, StopPlayBack, int64_t, int32_t);
	RCF_METHOD_R0(std::string, useName);
	RCF_METHOD_R0(std::string, passwords);
	RCF_METHOD_R0(std::string, ip);
	RCF_METHOD_R0(int32_t, port);
	RCF_METHOD_R0(int64_t, factory);
	RCF_METHOD_R0(bool, logout);
	RCF_METHOD_R4(bool, GetRecordFileList, VideoServer::RecordInfoList&, std::vector<int>, int64_t, int64_t);
	RCF_METHOD_R4(bool, GetRecordFileListZone, VideoServer::RecordInfoList&, std::vector<int>&, int64_t, int64_t);
	RCF_METHOD_R0(bool, ClearRecordFileList);
    RCF_METHOD_R3(bool, downLoadByRecordFile, std::string, VideoServer::RecordInfo, int64_t&);
	RCF_METHOD_R1(bool, stopDownload, int64_t);
	RCF_METHOD_R0(bool, stopDownloadAll);
	RCF_METHOD_R1(std::string, getChannelName, int32_t);
	RCF_METHOD_R1(std::string, getFileName, VideoServer::RecordInfo);
    RCF_METHOD_R6(bool, login, std::string, int32_t, std::string,
        std::string, std::vector< int32_t>&, std::vector<std::string > &);
	RCF_METHOD_V2(void, getChannels, std::vector< int32_t>&, std::vector<std::string > &);
    RCF_METHOD_R2(bool, getPlayBackPos, int64_t, int32_t&);
    RCF_METHOD_R4(bool, getDownloadPos, int64_t, int64_t&, int64_t&, int32_t&);
RCF_END(VideoserverSvr);

RCF_BEGIN(I_ServerCallback, "I_ServerCallback")
RCF_METHOD_V5(void, onDownloadPos, int64_t /*receiver*/, int64_t /*port*/, int64_t /*totalSize*/, int64_t /*size*/, bool /*failed*/);
RCF_METHOD_V2(void, onDisconnet, int64_t /*receiver*/, int64_t /*port*/);
RCF_METHOD_V2(void, onReconnet, int64_t /*receiver*/, int64_t /*port*/);
RCF_METHOD_V2(void, onHeartbeat, int64_t /*receiver*/, int64_t /*port*/);
RCF_END(I_ServerCallback)


#endif // SERVICE_H
