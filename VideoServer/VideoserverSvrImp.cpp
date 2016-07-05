#include "VideoserverSvrImp.h"
#include <QDateTime>
#include "Service.h"
#include "ServiceUtils.h"


int VideoserverSvrImp::sMaxPort = PORT_VIDEOS_SERVER;
std::map< std::shared_ptr< RCF::RcfServer >, std::shared_ptr< VideoserverSvrImp > > VideoserverSvrImp::spServers;
std::recursive_mutex VideoserverSvrImp::sMutexServers;
std::recursive_mutex VideoserverSvrImp::sMutexReleaseServers;
std::map< std::shared_ptr< RCF::RcfServer >, std::shared_ptr< VideoserverSvrImp > > VideoserverSvrImp::spRleaseServers;

void VideoserverSvrImp::add(std::shared_ptr< RCF::RcfServer > rcfSvr, std::shared_ptr< VideoserverSvrImp > impSvr){
	std::lock_guard<std::recursive_mutex> lock(sMutexServers);
	spServers[rcfSvr] = impSvr;
}

int VideoserverSvrImp::create(videoserver *pServer){
	if (pServer == nullptr)
	{
		return PORT_NONE;
	}


	auto pRcfServer = std::make_shared<RCF::RcfServer>(RCF::TcpEndpoint("0.0.0.0", ++sMaxPort));
	auto pServerImp = std::make_shared<VideoserverSvrImp>(pServer, sMaxPort);
	pRcfServer->bind<VideoserverSvr>(*pServerImp);
	pRcfServer->start();
	VideoserverSvrImp::add(pRcfServer, pServerImp);

//	Log::instance().AddLog(QString("VideoserverSvrImp::create %1").arg(sMaxPort));
	return sMaxPort;
}

int VideoserverSvrImp::create(videoserverFactory*  f){
	if (f == nullptr)
	{
		return PORT_NONE;
	}

	std::lock_guard<std::recursive_mutex> lock(sMutexServers);
	for (auto it = spRleaseServers.begin(); it != spRleaseServers.end(); it++)
	{
		if (it->second->m_pServer->factory() == f)
		{
			spServers[it->first] = it->second;
			int port = it->second->mServerPort;
			spRleaseServers.erase(it);
			return port;
		}
	}

	return create(f->create());
}

void VideoserverSvrImp::release(VideoserverSvrImp* p){
	std::lock_guard<std::recursive_mutex> lock(sMutexServers);
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg((int)p));
	for (auto it = spServers.begin(); it != spServers.end(); it++)
	{
		if (it->second.get() == p)
		{
			spRleaseServers[it->first] = it->second;
			spServers.erase(it);
//             Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//                 .arg(__FUNCTION__).arg(__LINE__).arg(QString::fromLocal8Bit("it->second.get() == p")));
			return;
		}
	}
}
videoserver* VideoserverSvrImp::getVideoServerByPort(int32_t Port){
    std::lock_guard<std::recursive_mutex> lock(sMutexServers);
    for (auto it = spServers.begin(); it != spServers.end(); it++)
    {
        if (it->second->mServerPort == Port)
        {
//             Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, %4").arg(__FILE__)
//                 .arg(__FUNCTION__).arg(__LINE__).arg(it->second->mServerPort));
            return it->second->m_pServer;
        }
    }

//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, nullptr:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(Port));
    return nullptr;
}
int32_t VideoserverSvrImp::getPortByVideoServer(videoserver *pServer){
	std::lock_guard<std::recursive_mutex> lock(sMutexServers);
	for (auto it = spServers.begin(); it != spServers.end(); it++)
	{
		if (it->second->m_pServer == pServer)
		{
//             Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, %4").arg(__FILE__)
//                 .arg(__FUNCTION__).arg(__LINE__).arg(it->second->mServerPort));
			return it->second->mServerPort;
		}
	}

//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, %4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("PORT_NONE"));
	return PORT_NONE;
}

VideoserverSvrImp::VideoserverSvrImp(videoserver *pServer, int port) : m_pServer(pServer), mServerPort(port)
{
}


VideoserverSvrImp::~VideoserverSvrImp()
{
	if (NULL != m_pServer)
	{
//         Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//             .arg(__FUNCTION__).arg(__LINE__).arg("VideoserverSvrImp::~VideoserverSvrImp"));
		m_pServer->destroy();
	}
}

void VideoserverSvrImp::destroy(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("VideoserverSvrImp::~destroy"));
	release(this);
}

void VideoserverSvrImp::remove(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("VideoserverSvrImp::~release"));
	release(this);
}

int VideoserverSvrImp::clone(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("clone beg"));
	return create(this->m_pServer->clone());
}

int VideoserverSvrImp::cloneDerect(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("VideoserverSvrImp::~cloneDerect"));
	return create(this->m_pServer->cloneDerect());
}

std::string VideoserverSvrImp::getLastError(){
	return this->m_pServer->getLastError().toLocal8Bit().data();
}


bool VideoserverSvrImp::PlayBackByRecordFile(VideoServer::RecordInfo& vsrf, int64_t hwnd, int64_t& playBackHandle){
	RecordFile f;
	play_handle_t handle;
// 	Log::instance().AddLog(QString::fromLocal8Bit("%1, %2, %3").arg(__FUNCTION__).arg(__LINE__).
//         arg(vsrf.pprivatedata().size()));
	ServiceUtils::PBRecordInfoToRecordFile(vsrf, f);
	if (this->m_pServer->PlayBackByRecordFile(f, (HWND)hwnd, handle)){
		ServiceUtils::RecordFileToPBRecordInfo(f, vsrf);
		playBackHandle = handle;
//         Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//             .arg(__FUNCTION__).arg(__LINE__).arg("PlayBackByRecordFile:: scceed"));
		return true;
	}
	playBackHandle = NULL;
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(this->m_pServer->getLastError()));
	return false;
}


bool VideoserverSvrImp::SetPlayBack(int64_t playBackHandle, int32_t pos){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(pos));
	return this->m_pServer->SetPlayBack(playBackHandle, pos);
}


bool VideoserverSvrImp::StopPlayBack(int64_t playBackHandle, int32_t pause){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(playBackHandle));
	return this->m_pServer->StopPlayBack(playBackHandle, pause);
}

std::string VideoserverSvrImp::useName(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(this->m_pServer->useName()));
	return this->m_pServer->useName().toLocal8Bit().data();
}
std::string VideoserverSvrImp::passwords(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(this->m_pServer->passwords()));
	return this->m_pServer->passwords().toLocal8Bit().data();
}
std::string VideoserverSvrImp::ip(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(this->m_pServer->ip()));
	return this->m_pServer->ip().toLocal8Bit().data();
}
int32_t VideoserverSvrImp::port(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(this->m_pServer->port()));
	return this->m_pServer->port();
}
int64_t VideoserverSvrImp::factory(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(this->m_pServer->factory()->factory()));
	return this->m_pServer->factory()->factory();
}
bool VideoserverSvrImp::logout(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(mServerPort).arg("beg"));
	bool r = this->m_pServer->logout();
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, end:%5").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(mServerPort).arg(r));
    return r;
}

bool VideoserverSvrImp::GetRecordFileList(VideoServer::RecordInfoList& vsrflst, std::vector<int>& channels, 
	int64_t begTime, int64_t endTime){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("begin"));
    std::vector<RecordFile> rfs;
	vsrflst.clear_recordinfos();
	if (m_pServer->GetRecordFileList(rfs, channels, QDateTime::fromTime_t(begTime), QDateTime::fromTime_t(endTime)))
	{
		for (int i = 0; i < rfs.size(); i++){
			Log::instance().AddLog(QString("%1, %2, %3").arg(__FUNCTION__).arg(__LINE__).
				arg(rfs[i].name.c_str()));
            rfs[i].name = m_pServer->getFileName(rfs[i]).toLocal8Bit().data();
			ServiceUtils::RecordFileToPBRecordInfo(rfs[i], *vsrflst.add_recordinfos());
			Log::instance().AddLog(QString("%1, %2, %3").arg(__FUNCTION__).arg(__LINE__).
			arg(vsrflst.recordinfos(i).name().c_str()));
		}

		return true;
	}

//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("failed"));
	return false;

}
bool VideoserverSvrImp::GetRecordFileListZone(VideoServer::RecordInfoList& vsrflst, std::vector<int>& channels, int64_t begTime, int64_t endTime){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("begin"));
    std::vector<RecordFile> rfs;
	vsrflst.clear_recordinfos();
	if (m_pServer->GetRecordFileListZone(rfs, channels, QDateTime::fromTime_t(begTime), QDateTime::fromTime_t(endTime)))
	{
		for (int i = 0; i < rfs.size(); i++){
            rfs[i].name = m_pServer->getFileName(rfs[i]).toLocal8Bit().data();
			ServiceUtils::RecordFileToPBRecordInfo(rfs[i], *vsrflst.add_recordinfos());
		}
//         Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//             .arg(__FUNCTION__).arg(__LINE__).arg("succeed"));
		return true;
	}
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("failed"));
	return false;
}

bool VideoserverSvrImp::ClearRecordFileList(){
	m_pServer->ClearRecordFileList();
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(""));
	return true;
}

bool VideoserverSvrImp::downLoadByRecordFile(std::string filePath, VideoServer::RecordInfo vsri, int64_t& downloaHandle){
	RecordFile f;
	ServiceUtils::PBRecordInfoToRecordFile(vsri, f);
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, filePath:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(QString::fromLocal8Bit(filePath.c_str())));
    return m_pServer->downLoadByRecordFile(filePath, f, downloaHandle);
}

bool VideoserverSvrImp::stopDownload(int64_t downloaHandle){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(downloaHandle));
    return m_pServer->stopDownload( downloaHandle);
}

bool VideoserverSvrImp::stopDownloadAll(){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg("stopDownloadAll"));
	return m_pServer->stopDownloadAll();
}

std::string VideoserverSvrImp::getChannelName(int32_t channel){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(m_pServer->getChannelName(channel)));
	return m_pServer->getChannelName(channel).toLocal8Bit().data();
}

std::string VideoserverSvrImp::getFileName(VideoServer::RecordInfo vsri){
	RecordFile f;
	ServiceUtils::PBRecordInfoToRecordFile(vsri, f);
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(m_pServer->getFileName(f)));
	return m_pServer->getFileName(f).toLocal8Bit().data();
}

bool VideoserverSvrImp::login(std::string IP, int32_t port, std::string user,
    std::string password, std::vector< int32_t>& channels, std::vector<std::string > & channelNames){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(mServerPort).arg("beg"));
    try
    {
        if (m_pServer->login(IP.c_str(), port, user.c_str(), password.c_str()))
        {
            auto chnnls = m_pServer->channels();
            for (auto it = chnnls.begin(); it != chnnls.end(); it++)
            {
                channels.push_back(it->first);
                channelNames.push_back(it->second);
            }
//             Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
//                 .arg(__FUNCTION__).arg(__LINE__).arg(mServerPort).arg("end true"));
            return true;
        }
    }
     catch (...)
    {
    }
    
    
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(mServerPort).arg("end false"));
    return false;
}

void VideoserverSvrImp::getChannels(std::vector< int32_t>& channelIds, std::vector<std::string > &channelNames){
	auto mpChannel = m_pServer->channels();
	channelIds.clear();
	channelNames.clear();
	for (auto it = mpChannel.begin(); it != mpChannel.end(); it++)
	{
		channelIds.push_back(it->first);
		channelNames.push_back(it->second);
//         Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
//             .arg(__FUNCTION__).arg(__LINE__).arg(QString::fromLocal8Bit(it->second.c_str())));
	}
}

bool VideoserverSvrImp::getPlayBackPos(__int64 playbackHandle, int32_t& pos){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4 beg ").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(playbackHandle));
    bool b = m_pServer->getPlayBackPos(playbackHandle, pos);
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4 end ").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(playbackHandle));
    return b;
}

bool VideoserverSvrImp::getDownloadPos(int64_t h, int64_t& totalSize, int64_t& currentSize, int32_t& failed){
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4 beg ").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(h));
    bool bFailed = true;
    bool b = m_pServer->getDownloadPos(h, &totalSize, &currentSize, &bFailed);
    failed = bFailed;
//     Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4 end ").arg(__FILE__)
//         .arg(__FUNCTION__).arg(__LINE__).arg(h));
    return b;
};
