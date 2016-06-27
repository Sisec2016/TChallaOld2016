#include "videoserversSvr.h"
#include "RCF/RCF.hpp"
#include "QString"
#include <QUdpSocket>
#include <QApplication>
#include <QProcess>
#include "log.h"

#include "ServiceUtils.h"
#include "Service.h"
RCF::RcfInitDeinit rcfInit;

#define VF_BEGIN()	\
if (init_service()) \
\
	{	\
		try	\
		{	\
        std::lock_guard<std::recursive_mutex> lock(sMutexService); \


#define VF_END()	\
		}	\
		catch (const RCF::Exception & e)	\
		{	\
			Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)	\
				.arg(__FUNCTION__).arg(__LINE__).arg(e.getError().getErrorString().c_str())); \
		}	\
	}


#define VDS_BEGIN()	\
if (init_service()) \
    \
{	\
    try	\
{	\
    std::lock_guard<std::recursive_mutex> lock(mMutexService); \
    Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)	\
    .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("beg"));    \


#define VDS_END()	\
    Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)	\
    .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("end"));    \
}	\
    catch (const RCF::Exception & e)	\
{	\
    Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, error:%5").arg(__FILE__)	\
    .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg(e.getError().getErrorString().c_str()));    \
}	\
}

void SvrFactory::startSver(){
    QUdpSocket udp;
    if (!udp.bind(PORT_FACTORY, QAbstractSocket::DontShareAddress))
    {
        return;
    }
    else{
        udp.close();
        QProcess::startDetached(QApplication::applicationDirPath() + "/VideoService.exe");
        Sleep(1000);
    }
}

std::recursive_mutex SvrFactory::sMutexService;
std::shared_ptr< RcfClient<VideoserverFactorySvr> > SvrFactory::spService;
bool SvrFactory::init_service(){
	if (spService.get() == nullptr)
	{   
		try{
            
            std::lock_guard<std::recursive_mutex> lock(sMutexService);
            startSver();
            spService = std::make_shared< RcfClient<VideoserverFactorySvr> >(RCF::TcpEndpoint("127.0.0.1", PORT_FACTORY));
            spService->getClientStub().setConnectTimeoutMs(5 * 1000);
            spService->getClientStub().setRemoteCallTimeoutMs(1000 * 1000);
		}
		catch (const RCF::Exception & e)
		{
			Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
				.arg(__FUNCTION__).arg(__LINE__).arg(e.getError().getErrorString().c_str()));
            std::lock_guard<std::recursive_mutex> lock(sMutexService);
			spService.reset();
			return false;	
		}
	}
    
    return true;
}



int SvrFactory::getByIndex(int index)
{
	VF_BEGIN()
        return spService->getByIndex(index);
	VF_END()
	return SISC_IPC_UNDEFINE;
}
int SvrFactory::getByName(std::string sName)
{
	    VF_BEGIN()
           return spService->getByName(sName);
        VF_END()
        return SISC_IPC_UNDEFINE;
}

void SvrFactory::getFactorys(std::vector< int >& vcFactorys)
{
	VF_BEGIN()
        spService->getFactorys(vcFactorys);
	VF_END()
}

bool  SvrFactory::getRefreshPort(int& newProt, int32_t factory, int32_t oldPort){
    VF_BEGIN()
        newProt = spService->KeepServerRunning(factory, oldPort);
        return (newProt != PORT_NONE);
    VF_END()
    
    return true;
}



SvrFactory::SvrFactory(int f) : mFactory(f){
    mPort = PORT_NONE;
}

SvrFactory::~SvrFactory(){
}

const char* SvrFactory::name()
{
    if (mName.empty())
    {
        VF_BEGIN()
            mName = spService->name(mFactory);
        VF_END()
    }

    return mName.c_str();
}

int SvrFactory::defaultPort()
{
    if (mPort != PORT_NONE)
    {
        return mPort;
    }
    VF_BEGIN()
        if (spService)
        {
            mPort = spService->defaultPort(mFactory);
            return mPort;
        }
        
    VF_END()
    
    return PORT_NONE;
}
const char* SvrFactory::defaultUser()
{

    if (mDefaultUser.empty())
    {
        VF_BEGIN()
            mDefaultUser = spService->defaultUser(mFactory);
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(QString::fromLocal8Bit(mDefaultUser.c_str())));

        VF_END()
    }


    return mDefaultUser.c_str();
}

const char* SvrFactory::defaultPasswords()
{

    if (mDefaultPasswords.empty())
    {
        VF_BEGIN()
            mDefaultPasswords = spService->defaultPasswords(mFactory);
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(QString::fromLocal8Bit(mDefaultPasswords.c_str())));

        VF_END()
    }


    return mDefaultPasswords.c_str();
}
bool SvrFactory::init()
{
    return true;
}
void SvrFactory::clean(){

}
DeviceFactory SvrFactory::factory()
{
    return (DeviceFactory)mFactory;
}

void SvrFactory::videoFileExterns(std::vector<std::string>& externs)
{
    VF_BEGIN()
        spService->videoFileExterns(mFactory, externs);
    VF_END()
}

IVideoServer* SvrFactory::create(){
    VF_BEGIN()
        int port = spService->create(mFactory);
        if (port != PORT_NONE)
        {
            return new SvrVideoserver(port, mFactory);
        }
    VF_END()
    return nullptr;
}

bool  SvrFactory::searchDevice(std::vector<DeviceInfo>& dvcInfos){
    VF_BEGIN()
        VideoServer::DeviceInfoList dviList;

    if (spService->searchDevice(mFactory, dviList))
    {
        dvcInfos.resize(dviList.deviceinfos_size());
        for (int i = 0; i < dviList.deviceinfos_size(); i++)
        {
            ServiceUtils::PBDeviceInfoToDeviceInfo(dviList.deviceinfos(i), dvcInfos[i]);
        }

        return true;
    }

    VF_END()


        return false;
}

std::vector<SvrVideoserver*> SvrVideoserver::sServers;
std::recursive_mutex SvrVideoserver::sMtServers;
SvrVideoserver* SvrVideoserver::getServerByPort(int port){
    std::lock_guard<std::recursive_mutex> lock(SvrVideoserver::sMtServers);
    for (auto it = sServers.begin(); it != sServers.end(); it++)
    {
        if ((*it)->mPort == port)
        {
            return *it;
        }
    }

    return nullptr;
}



bool SvrVideoserver::init_service(){
    if (mpService.get() == nullptr)
    {
        if (!SvrFactory::getRefreshPort(mPort, mFactory, mPort))
        {
            Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
                .arg(__FUNCTION__).arg(__LINE__).arg("getRefreshPort failed"));
            return false;
        }
        
        try{
             mpService = std::make_shared< RcfClient<VideoserverSvr> >(RCF::TcpEndpoint("127.0.0.1", mPort));
             mpService->getClientStub().setConnectTimeoutMs(5 * 1000);
			 switch (mFactory)
			 {
			 case SISC_IPC_HANGJINGKEJI:
				 mpService->getClientStub().setConnectTimeoutMs(3 * 1000);
				 mpService->getClientStub().setRemoteCallTimeoutMs(120 * 3 * 1000);
				 mpService->getClientStub().setMaxBatchMessageLength(100000000);
				 break;
			 default:
				 mpService->getClientStub().setConnectTimeoutMs(5 * 1000);
				 mpService->getClientStub().setRemoteCallTimeoutMs(120 * 1000);
				 mpService->getClientStub().setMaxBatchMessageLength(100000000);
				 break;
			 }            
        }
        catch (const RCF::Exception & e)
        {
            Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
                .arg(__FUNCTION__).arg(__LINE__).arg(e.getError().getErrorString().c_str()));
            mpService.reset();
            return false;
        }
    }
    
    return true;
}

SvrVideoserver::SvrVideoserver(int port, int factory) : mPort(port), mFactory(factory)
{
    std::lock_guard<std::recursive_mutex> lock(SvrVideoserver::sMtServers);
    sServers.push_back(this);
}

SvrVideoserver::~SvrVideoserver()
{
    std::lock_guard<std::recursive_mutex> lock(SvrVideoserver::sMtServers);
    for (int i = 0; i < sServers.size(); i++)
    {
        if (sServers[i] == this)
        {
            sServers.erase(sServers.begin() + i);
            break;
        }
    }
}
void SvrVideoserver::destroy()
{
    logout();
    VDS_BEGIN()
    mpService->destroy();
    VDS_END()
    delete this;
}
IVideoServer* SvrVideoserver::clone()
{
    VDS_BEGIN()
        int port = mpService->clone();
        if (port != PORT_NONE)
        {
            Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)	\
                .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("clone true end"));    \
            return new SvrVideoserver(port, mFactory);
        }
    VDS_END()
    return nullptr;
}




bool SvrVideoserver::login(const char* IP, __int32 port, const char* user,
    const char* password, std::map<__int32, std::string>& channels)
{

    VDS_BEGIN()
        std::vector<int32_t> vcchannels;
        std::vector<std::string> vcchannelNames;
        if (mpService->login(IP, port, user, password, vcchannels, vcchannelNames))
        {
            for (int i = 0; i < vcchannels.size() && i < vcchannelNames.size(); i++)
            {
                channels[vcchannels[i]] = vcchannelNames[i];
            }
            Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
                .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end")); 
            qDebug() << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "true";
            return true;
        }
        else{
            qDebug() << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "false";
        }
    VDS_END()

    return false;
}

bool SvrVideoserver::logout()
{
    VDS_BEGIN()
        bool r = mpService->logout();
        if (r)
        {
            Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
                .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
            return true;
        }
    VDS_END()
    
    return false;
}






void SvrVideoserver::ClearRecordFileList()
{
}

bool SvrVideoserver::GetRecordFileList(std::vector<RecordFile>& files, const std::vector<int>& channelVec, __time64_t timeStart,
    __time64_t timeEnd){
   
    VDS_BEGIN()
    VideoServer::RecordInfoList vsriList;
        
    if (mpService->GetRecordFileList(vsriList, channelVec, timeStart, timeEnd))
    {
        files.resize(vsriList.recordinfos_size());
        for (int i = 0; i < vsriList.recordinfos_size(); i++)
        {
            ServiceUtils::PBRecordInfoToRecordFile(vsriList.recordinfos(i), files[i]);
         }
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }

    VDS_END()


    return false;
}

bool SvrVideoserver::downLoadByRecordFile(const char* saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    VDS_BEGIN()
    VideoServer::RecordInfo vsri;
    ServiceUtils::RecordFileToPBRecordInfo(file, vsri);
    if (mpService->downLoadByRecordFile(saveFileName, vsri, hdl))
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }


    VDS_END()
    

    return false;
}




bool SvrVideoserver::stopDownload(download_handle_t h)
{
    VDS_BEGIN()

    if (mpService->stopDownload(h))
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }
    VDS_END()
    return false;
}

bool SvrVideoserver::PlayBackByRecordFile(const RecordFile& file, HWND hwnd, play_handle_t& playbackHandle)
{
    Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, hwnd:%4").arg(__FILE__)
        .arg(__FUNCTION__).arg(__LINE__).arg((int64_t)hwnd));
    VDS_BEGIN()
    VideoServer::RecordInfo vsri;
    ServiceUtils::RecordFileToPBRecordInfo(file, vsri);
    if (mpService->PlayBackByRecordFile(vsri, (int64_t)hwnd, playbackHandle))
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }
    VDS_END()
   
    return false;
}

bool SvrVideoserver::SetPlayBack(__int64 playbackHandle, __int32 pos)
{
    VDS_BEGIN()
    if (mpService->SetPlayBack(playbackHandle, pos))
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }
    VDS_END()
    return false;
}

bool SvrVideoserver::getPlayBackPos(__int64 playbackHandle, __int32* pos)
{
    VDS_BEGIN()
    if (mpService->getPlayBackPos(playbackHandle, *pos))
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }
    VDS_END()
    return false;
}


bool SvrVideoserver::StopPlayBack(__int64 playbackHandle, __int32 mPause)
{
    VDS_BEGIN()
    if (mpService->StopPlayBack(playbackHandle, mPause))
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }
    VDS_END()
    return false;

}

const char* SvrVideoserver::getLastError(){
    VDS_BEGIN()
    m_sLastError = mpService->getLastError();

    Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, msg:%4").arg(__FILE__)
        .arg(__FUNCTION__).arg(__LINE__).arg(QString::fromLocal8Bit(m_sLastError.c_str())));
    VDS_END()
        return m_sLastError.c_str();
}

bool SvrVideoserver::getDownloadPos(download_handle_t h, __int64* totalSize, __int64* currentSize, bool* failed){
    bool b = false;
    VDS_BEGIN()
    int32_t nFailed = 0;
    if (mpService->getDownloadPos(h, *totalSize, *currentSize, nFailed))
    {
        *failed = (bool)nFailed;
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, port:%4, msg:%5").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(mPort).arg("true end"));
        return true;
    }
    VDS_END()
        return b;
}