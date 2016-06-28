#ifndef SERVICE_UTILS_H
#define SERVICE_UTILS_H
#include "RecordInfo.pb.h"
#include "VideoServer.h"

class ServiceUtils
{
public:
	static void PBRecordInfoToRecordFile(const VideoServer::RecordInfo& from, RecordFile& to){
		to.beginTime = from.begintime();
		to.channel = from.channel();
		to.endTime = from.endtime();
		to.name = from.name();
		to.setPrivateData((void*)from.pprivatedata().c_str(), from.pprivatedata().size());
		to.size = from.size();
	}

	static void RecordFileToPBRecordInfo(const RecordFile& from, VideoServer::RecordInfo&to){
		to.set_begintime(from.beginTime);
		to.set_channel(from.channel);
		to.set_endtime(from.endTime);
		to.set_name(from.name);
		to.set_pprivatedata(std::string(from.pPrivateData, from.PrivateDataDataSize));
		to.set_size(from.size);
	}

	static void PBLoginInfoToLoginServerInfo(const VideoServer::LoginInfo& from, LoginServerInfo& to){
		to.factory = (DeviceFactory)from.factory();
		to.id = from.id().c_str();
		to.ip = from.ip().c_str();
		to.macAddress = from.macaddress().c_str();
		to.name = QString::fromLocal8Bit(from.name().c_str());
		to.password = from.password().c_str();
		to.port = from.port();
		to.user = from.user().c_str();
	}

	static void LoginServerInfoToPBLoginInfo(const LoginServerInfo& from, VideoServer::LoginInfo &to){
		to.set_factory(from.factory);
		to.set_id(from.id.toLocal8Bit().data());
		to.set_ip(from.ip.toLocal8Bit().data());
		to.set_macaddress(from.macAddress.toLocal8Bit().data());
		to.set_name(from.name.toLocal8Bit().data());
		to.set_password(from.password.toLocal8Bit().data());
		to.set_port(from.port);
		to.set_user(from.user.toLocal8Bit().data());
	}
    static void PBDeviceInfoToDeviceInfo(const VideoServer::DeviceInfo& from, DeviceInfo& to){
        to.Factory = (DeviceFactory)from.factory();
        to.nPort = from.nport();
        to.szIP = from.szip();
    }

    static void DeviceInfoToPBDeviceInfo(const DeviceInfo& from, VideoServer::DeviceInfo&to){
        to.set_factory(from.Factory);
        to.set_nport(from.nPort);
        to.set_szip(from.szIP.c_str(), from.szIP.size());
    }
private:

};
#endif //SERVICE_UTILS_H