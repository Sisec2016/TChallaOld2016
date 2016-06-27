#include "VideoserverFactorySvrImp.h"
#include "videoserver.h"
#include "Service.h"
#include "VideoserverSvrImp.h"
#include "ServiceUtils.h"
VideoserverFactorySvrImp::VideoserverFactorySvrImp()
{

}


VideoserverFactorySvrImp::~VideoserverFactorySvrImp()
{
}

int VideoserverFactorySvrImp::getByIndex(int index){
	videoserverFactory*  f = videoserverFactory::get(index);
	if (f != nullptr)
	{
		return f->factory();
	}

	return SISC_IPC_UNDEFINE;
}

int VideoserverFactorySvrImp::getByName(std::string name){
	videoserverFactory*  f = videoserverFactory::get(name.c_str());
	if (f != nullptr)
	{
		return f->factory();
	}

	return SISC_IPC_UNDEFINE;
}

void VideoserverFactorySvrImp::getFactorys(std::vector<int>& factory){
	factory.clear();
	auto fs = videoserverFactory::getFactorys();
	Log::instance().AddLog(QString("getFactorys : %1").arg(fs.size()));
	for (int i = 0; i < fs.size(); i++){
		factory.push_back(fs[i]->factory());
	}
}

int VideoserverFactorySvrImp::create(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f == nullptr)
	{
		Log::instance().AddLog(" VideoserverFactorySvrImp::create f == nullptr");
		return PORT_NONE;
	}
	Log::instance().AddLog(" VideoserverSvrImp::create");
	return VideoserverSvrImp::create(f);
}

std::string VideoserverFactorySvrImp::name(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
		return f->name().toLocal8Bit().data();
	}

	Log::instance().AddLog(" VideoserverFactorySvrImp::name f == nullptr");
	return "";
}

void VideoserverFactorySvrImp::videoFileExterns(int nFactory, std::vector< std::string >& vcExterns){
	vcExterns.clear();
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
		std::vector<QString> vcExtersQ;
		f->videoFileExterns(vcExtersQ);
		for (int i = 0; i < vcExtersQ.size(); i++){
			vcExterns.push_back(vcExtersQ.at(i).toStdString());
		}

	}

}
std::string VideoserverFactorySvrImp::getLastError(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
		return f->getLastError().toLocal8Bit().data();
	}

	return "";
}
int VideoserverFactorySvrImp::defaultPort(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
		return f->port();
	}

	return 0;
}

std::string VideoserverFactorySvrImp::defaultUser(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
		return f->defaultUser().toStdString();
	}

	return "";
}

std::string VideoserverFactorySvrImp::defaultPasswords(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
		return f->defaultPasswords().toStdString();
	}

	return "";
}

bool VideoserverFactorySvrImp::IsOEMFac(int nFactory){
	videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
	if (f != nullptr)
	{
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, %4").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(f->IsOEMFac()));
		return f->IsOEMFac();
	}
    Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
        .arg(__FUNCTION__).arg(__LINE__).arg("f == nullptr"));
	return false;
}

int VideoserverFactorySvrImp::KeepServerRunning(int nFactory, int port){
    videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
    if (f == nullptr)
    {
        Log::instance().AddLog(" KeepServerRunning::create f == nullptr");
        return PORT_NONE;
    }
    videoserver *pVideoServer = VideoserverSvrImp::getVideoServerByPort(port);
    if (pVideoServer != nullptr && pVideoServer->factory() == f)
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, find:%4").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(nFactory));
        return port;
    }

    Log::instance().AddLog(" KeepServerRunning::create");
    return VideoserverSvrImp::create(f);
}

bool VideoserverFactorySvrImp::searchDevice(int nFactory, VideoServer::DeviceInfoList& devices){
    videoserverFactory*  f = videoserverFactory::getFactory((DeviceFactory)nFactory);
    std::vector<DeviceInfo> dvcInfos;
    devices.clear_deviceinfos();
    if (f != nullptr)
    {
        if (f->searchDevice(dvcInfos))
        {
            for (int i = 0; i < dvcInfos.size(); i++){
                ServiceUtils::DeviceInfoToPBDeviceInfo(dvcInfos[i], *devices.add_deviceinfos());
            }

            return true;
        }
    }


    return false;
}