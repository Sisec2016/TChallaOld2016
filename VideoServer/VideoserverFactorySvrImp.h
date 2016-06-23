#pragma once
#include <vector>
#include <string>
#include <RCF/RCF.hpp>
#include <memory>
#include "VideoserverSvrImp.h"

class VideoserverFactorySvrImp
{

public:
	VideoserverFactorySvrImp();
	~VideoserverFactorySvrImp();
	int getByIndex(int index);
	int getByName(std::string name);
	void getFactorys(std::vector<int>& factory);
	int create(int nFactory);
	std::string name(int nFactory);
	void videoFileExterns(int nFactory, std::vector< std::string >& vcExterns);
	std::string getLastError(int nFactory);
	int defaultPort(int nFactory);
	std::string defaultUser(int nFactory);
	std::string defaultPasswords(int nFactory);
	bool IsOEMFac(int nFactory);
    int KeepServerRunning(int nFactory, int port);
    bool searchDevice(int nFactory, VideoServer::DeviceInfoList& devices);
};

