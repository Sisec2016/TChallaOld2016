#ifndef VIDEOSERVER_H
#define VIDEOSERVER_H
#include <qdatetime.h>
#include <QString>
#include <vector>
#include <deque>

#include <memory>
#include <map>
#include <QEvent>
#include <QObject>
#include <thread>
#include <mutex>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QWidget>
#include "../../VideoServer/IVideoServer.h"
#include "customEvent.h"
#include <excpt.h>
#include <iostream>
#include <string>
#include "log.h"
#include "SqlUtils.h"
#include "SqlTableMembers.h"
using namespace std;

#define UNDEFIN_DEVICE_STR "智能识别"
#define UNDEFIN_DEVICE_DEFAULT_USER "UNDEFIN_DEVICE_DEFAULT_USER"
#define UNDEFIN_DEVICE_DEFAULT_PASSWORD "UNDEFIN_DEVICE_DEFAULT_PASSWORD"

#define BIT_ONE_BYTE 8
#define BYTES_ONE_KB 1024
#define KBS_ONE_M 1024

QDataStream & operator << (QDataStream &dataStream, RecordFile &d);
QDataStream & operator >> (QDataStream &dataStream, RecordFile &d);

typedef std::map<std::string, unsigned int> OEMFacMap;

struct LoginServerInfo : public SqlTable<LoginServerInfo>
{
    SERIAL_MEMMBER_HEAD()
    QString name;
    QString ip;
    int port;
    QString user;
    QString password;
    QString macAddress;
    int factory;
    QString id;
    bool operator == (const LoginServerInfo& other)
    {
        if (this == &other)
        {
            return true;
        }

        if (!macAddress.isEmpty())
        {
            //return macAddress == other.macAddress && factory == other.factory;
        }

        return ip == other.ip && port == other.port &&
                user == other.user && password == other.password && factory == other.factory;
    }
};
typedef std::vector< std::shared_ptr<LoginServerInfo> > ServerInfoList_t;

QDataStream & operator << (QDataStream &dataStream, LoginServerInfo &d);
QDataStream & operator >> (QDataStream &dataStream, LoginServerInfo &d);

class videoserver;
class downloadEvent : public QEvent
{
public:
    downloadEvent(videoserver* pSvr, qint64 totalSize, qint64 size, bool failed);
    videoserver* m_pSvr;
    qint64 m_totalSize;
    qint64 m_size;
    bool m_failed;
};
class heartbeatEvent : public QEvent
{
public:
    heartbeatEvent(videoserver* pSvr) :
       QEvent(SERVICE_CALLBACK_EVENT), m_pSvr(pSvr)
    {

    }

    videoserver* m_pSvr;
};
class disconnectEvent : public QEvent
{
public:
    disconnectEvent(videoserver* pSvr) :
         QEvent(SERVICE_CALLBACK_EVENT), m_pSvr(pSvr)
    {

    }

    videoserver* m_pSvr;
};

class reconnectEvent : public QEvent
{
public:
    reconnectEvent(videoserver* pSvr) :
         QEvent(SERVICE_CALLBACK_EVENT), m_pSvr(pSvr)
    {

    }
    videoserver* m_pSvr;
};

class videoserver;

class ServerExternFuns
{
    std::map<std::string, pfExternFun> mMpFuns;
public:
    void add(const std::string& funName, pfExternFun f)
    {
        if (nullptr != f)
        {
            mMpFuns[funName] = f;
        }
    }

    bool have(const std::string& fun) const
    {
        return mMpFuns.find(fun) != mMpFuns.end();
    }

    template<class R>
    std::shared_ptr<R> call(const char* fun, IVideoServer* server)
    {
        if (!have(fun))
        {
            return std::shared_ptr<R>();
        }

        R* r = (R*)sheCall(mMpFuns[fun], server, nullptr);
        return std::shared_ptr<R>(r);
    }

    template<class R, class Params>
    std::shared_ptr<R> call(const std::string& fun, IVideoServer* server, Params* pprms)
    {
        if (!have(fun))
        {
            return std::shared_ptr<R>();
        }


        R* r = (R*)sheCall(mMpFuns[fun], server, pprms);

        return std::shared_ptr<R>(r);
    }

    void addLog(const char* sLog, int nLine)
    {

        Log::instance().AddLog(QString("%1:%2  %4").arg(__FILE__)
                      .arg(nLine).arg(sLog));
    }

private:
    void* sheCall(pfExternFun f, IVideoServer* server, void* pprms)
    {
       SHE_BEGING
       return f(server, pprms);
       SHE_END_RETURN(nullptr)
    }
};

class videoserverFactory
{
    static std::deque<videoserverFactory *> s_Factorys;
    static std::recursive_mutex s_mutexFactorys;
    static std::vector<std::string> s_vcExternFunStrings;
    std::recursive_mutex m_mutexService;
    std::vector< std::shared_ptr<videoserver> > m_vcServices;
protected:
    bool init()
    {
        SHE_BEGING
        if (nullptr != mpFactory)
        {
            if (!mpFactory->init())
            {
                addLog("init failed", __LINE__);
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
        SHE_END_RETURN_FALSE
    }
    void clean()
    {
        SHE_BEGING
        if (nullptr != mpFactory)
        {
            mpFactory->clean();
        }

        SHE_END
    }
    bool mInit;
public:
    static const std::deque<videoserverFactory *>& getFactorys();
    static videoserverFactory* get(int index)
    {
        getFactorys();
        if (index < s_Factorys.size() && index >= 0)
        {
            return s_Factorys[index];
        }
        else
        {
            return NULL;
        }
    }
    static videoserverFactory* get(const QString& name)
    {
        getFactorys();
        for (int i = 0; i < s_Factorys.size(); i++)
        {
            if (s_Factorys[i]->name() == name)
            {
                return s_Factorys[i];
            }
        }

        return NULL;
    }
    static videoserverFactory* getFactory(DeviceFactory f);
    static void releaseVideoServerFactory();
	static void addFakeFactory(IVideoServerFactory *pFactory);
public:
    videoserverFactory(IVideoServerFactory *p);
    ~videoserverFactory();
public:
    DeviceFactory factory()
    {
        if (nullptr != mpFactory)
        {
            return mpFactory->factory();
        }
        else
        {
            return SISC_IPC_UNDEFINE;
        }
    }

    std::shared_ptr<videoserver> create(bool nullSver = false);
    void destroy(videoserver* p);
     IVideoServer* createDerect();

    QString name()
    {
        if (nullptr != mpFactory)
        {
            return QString::fromLocal8Bit(mpFactory->name());
        }
        else
        {
            return QString::fromLocal8Bit(UNDEFIN_DEVICE_STR);
        }
    }

	bool IsOEMFac()
	{
		if (nullptr != mpFactory)
		{
			return mpFactory->IsOEMFac();
		}
		else
		{
			return false;
		}
	}

    QString getLastError()
    {
        if (nullptr != mpFactory)
        {
            return QString::fromLocal8Bit(mpFactory->getLastError());
        }

        return "";
    }

    void videoFileExterns(std::vector<QString>& externs)
    {
        if (nullptr != mpFactory)
        {
            std::vector<std::string> e;
            mpFactory->videoFileExterns(e);
            externs.clear();
            for (int i = 0; i < e.size(); i++)
            {
                externs.push_back(QString::fromLocal8Bit(e[i].c_str()));
            }
        }

    }

    int port()
    {
        __try{
            if (nullptr != mpFactory)
            {
                return mpFactory->defaultPort();
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {

        }
        

        return 0;
    }

    QString defaultUser()
    {
        if (nullptr != mpFactory)
        {
            return QString::fromLocal8Bit(mpFactory->defaultUser());
        }
        return UNDEFIN_DEVICE_DEFAULT_USER;
    }

    QString defaultPasswords()
    {
        if (nullptr != mpFactory)
        {
            return QString::fromLocal8Bit(mpFactory->defaultPasswords());
        }

        return UNDEFIN_DEVICE_DEFAULT_PASSWORD;
    }

    void addServerExterFun(const std::string& name, pfExternFun f)
    {
        mServerExternFuns.add(name, f);
    }

    ServerExternFuns& serverExterFuns()
    {
        return mServerExternFuns;
    }

    bool searchDevice(std::vector<DeviceInfo>& devices){
        if (nullptr != mpFactory)
        {
            return mpFactory->searchDevice(devices);
        }
        return false;
    }
	void initOEMFacList();

protected:
    IVideoServerFactory* mpFactory;
    ServerExternFuns mServerExternFuns;
    bool sheInit()
    {
        SHE_BEGING
        if (nullptr != mpFactory)
        {
            bool r = mpFactory->init();
            if (!r)
            {
                addLog("init failed", __LINE__);
            }

            std::cout<<"she try end"<<std::endl;
            return r;
        }

        return true;
        SHE_END_RETURN_FALSE
    }

    void addLog(const char* sLog, int nLine)
    {
        if (nullptr != mpFactory)
        {
            Log::instance().AddLog(QString("%1:%2-%3  %4").arg(__FILE__)
                      .arg(nLine).arg(mpFactory->name()).arg(sLog));
        }
        else
        {
            Log::instance().AddLog(QString("%1:%2-%3  %4(%5)").arg(__FILE__)
                      .arg(nLine).arg("null factory").arg(sLog).arg(this->getLastError()));
        }
    }

public:
	static OEMFacMap m_OEMXMFacMap;   //雄迈OEM系列
	static OEMFacMap m_OEMHIKFacMap;  //海康OEM系列
	static OEMFacMap m_OEMDHFacMap;   //大华OEM系列
    static OEMFacMap m_OEMBXSFacMap;  //宝欣盛OEM系列
	static OEMFacMap m_OEMJiuAnFacMap;  //九安OEM系列
	static OEMFacMap m_OEMDongYangFacMap; //东阳OEM系统
	static OEMFacMap m_OEMZhongWeiFacMap; //中维OEM系列
    static OEMFacMap m_OEMJXJMap; //佳信捷OEM系列
};

#define TIME_FORMAT "yyyy-MM-dd hh:mm:ss"

class PlayBackPosCaculator
{
public:
    PlayBackPosCaculator();
    void setPlaySeconds(__time64_t seconds)
    {
        mPlaySeconds = seconds;
    }
    int getPos();
    void setPos(unsigned int pos);
private:
    __time64_t mStartPlayTime;
    __time64_t mPlaySeconds;
};


class DownloadPosCaculator
{
public:
    DownloadPosCaculator();
    void init(__int64 size, const std::string& sFile)
    {
        mTotalSize = size;
        mSaveFile = sFile;
    }
    static __int64 getFileSize(const std::string& sFile);
    int getPos(__int64& totalSize, __int64& currentSize);

private:
    __int64 mTotalSize;
    std::string mSaveFile;
};

class videoserver
{
    virtual videoserver* cloneDerect(); 

	void remove();//用于删除厂商时登录和析构
    
public:
    static videoserver* getServerByPort(int port);
public:
    ~videoserver();
    videoserver(IVideoServer *p, videoserverFactory *f);
    void setRelease(bool b){
        m_bRelease = b;
    }
    void destroy();
    bool isRelease(){
        return m_bRelease;
    }
    bool isNull(){
        return mpServer == nullptr;
    }
public:
    virtual std::shared_ptr<videoserver>  clone();


    virtual bool PlayBackByRecordFile(RecordFile& file, QWidget &w, play_handle_t& playbackHandle);
    virtual bool SetPlayBack(play_handle_t playbackHandle, qint32 pos);
    virtual bool getPlayBackPos(play_handle_t playbackHandle, qint32& pos);
    virtual bool StopPlayBack(play_handle_t playbackHandle, int mPause);

    virtual QString getLastError()
    {
        return QString::fromLocal8Bit(mLastError.c_str());
    }

    virtual QString useName()
    {
        if (mpLoginInfo)
        {
            return  mpLoginInfo->user;
        }
        else
        {
            return "";
        }
    }

    virtual QString passwords()
    {
        if (mpLoginInfo)
        {
            return  mpLoginInfo->password;
        }
        else
        {
            return "";
        }
    }

    virtual QString ip()
    {
        if (mpLoginInfo)
        {
            return  mpLoginInfo->ip;
        }
        else
        {
            return "";
        }
    }

    virtual int port()
    {
        if (mpLoginInfo)
        {
            return  mpLoginInfo->port;
        }
        else
        {
            return 0;
        }
    }

    virtual videoserverFactory *factory()
    {
        return mpFactory;
    }

    virtual void videoFileExterns(std::vector<QString>& externs)
    {
        mpFactory->videoFileExterns(externs);
    }

    virtual bool logout();

	virtual bool GetRecordFileList(std::vector<RecordFile>& files, /*int nChannelId*/std::vector<int>& channelVec, const QDateTime& timeStart, const QDateTime& timeEnd);

	virtual bool GetRecordFileListZone(std::vector<RecordFile>& files, /*int nChannelId*/std::vector<int>& channelVec, const QDateTime& timeStart, const QDateTime& timeEnd);
    void ClearRecordFileList()
    {
        SHE_BEGING
        if (nullptr != mpServer)
        {
        //    mpServer->ClearRecordFileList();
        }

        std::cout<<"she try end"<<std::endl;
        SHE_END
    }

    virtual bool downLoad(const QString& saveFileName, const RecordFile& file, QObject* eventReceiver);
    virtual bool stopDownload(QObject* eventReceiver);
    virtual bool stopDownloadAll();

    virtual QString getChannelName(int channel);
    virtual QString getFileName(const RecordFile &f);
    virtual const std::map<qint32, std::string>& channels() const
    {
       return m_channels;
    }

    virtual bool login(std::shared_ptr<LoginServerInfo> p, bool *pbStop);
    bool reLogin();
    bool canPlayback()
    {
        if (nullptr == mpFactory)
        {
            return false;
        }


        std::shared_ptr<bool> r = this->mpFactory->serverExterFuns().call<bool>(EXTERN_FUN_CAN_PLAY_BACK, this->mpServer);

        if (r)
        {
            return *r;
        }
        else
        {
            return true;
        }
    }

protected:
    bool shedownLoadByRecordFile(const std::string& saveFileName, const RecordFile& file, download_handle_t& hdl);
    bool shegetDownloadPos(download_handle_t h, qint64* totalSize, qint64* currentSize, bool* failed);
    bool shestopDownload(download_handle_t h);

    bool sheLogin(IVideoServer* pServer, const std::string& IP, int port, const std::string& user, const std::string& password);
protected:
    void DealDownLoadCallback(download_handle_t h, qint64 totalSize, qint64 size, bool failed);
    void SendDownLoadHeartbeat(download_handle_t h);
    void DealDisconnectCallback();
    void DealReconnectCallback();
    void addLog(const char* sLog, int nLine);


protected:
    std::recursive_mutex mMutexThread;
    std::thread* mpThrDowload;
    bool mStop;
protected:
    IVideoServer *mpServer;
    videoserverFactory *mpFactory;
    std::map<qint32, std::string> m_channels;
    std::map<play_handle_t, PlayBackPosCaculator> mMpPlayBackPosCaculators;
    std::recursive_mutex mMutexEventRecievers;
    std::map<download_handle_t, QObject*> mEventReceivers;
    std::map<download_handle_t, DownloadPosCaculator> mMpDownloadPosCaculators;
    std::string mLastError;
    std::shared_ptr<LoginServerInfo> mpLoginInfo;
    bool m_bRelease;
};

struct OEMFactoryInfo
{
	char *Name[32];
	DeviceFactory FacID;
	DeviceFactory isOem;
};

enum Enum_OEM_XM
{
	OEM_FAC_JF = 0,
	OEM_XM_END,
};
class OEMFactory : public IVideoServerFactory
{
public:
	OEMFactory();
	~OEMFactory(){};

	OEMFactory(DeviceFactory FacID, bool bOEMFlag, char *FacName, IVideoServerFactory *pFactory);

	bool init(){ return true; }
	void clean(){ return; }

	virtual const char* name();

	virtual int defaultPort()
	{
        if (m_port == 0 && !m_pFactory)
		{
			return m_pFactory->defaultPort();
		}
		else
		{
			return m_port;
		}
	}
	virtual const char* defaultUser()
	{
        if (m_usr.length() == 0 && !m_pFactory)
		{
			return m_pFactory->defaultUser();
		}
		else
		{
			return m_usr.c_str();
		}
	}

	virtual const char* defaultPasswords()
	{
        if (m_pass.length() == 0 && !m_pFactory)
		{
			return m_pFactory->defaultPasswords();
		}
		else
		{
            return m_pass.c_str();
		}
	}

	virtual DeviceFactory factory();

	virtual void videoFileExterns(std::vector<std::string >& externs)
	{
		//externs.push_back("h264");
        if (!m_pFactory)
        {
            m_pFactory->videoFileExterns(externs);
        }

	}

	virtual IVideoServer* create(){return m_pFactory->create(); }
	
	virtual bool IsOEMFac()
	{
		return m_OemFlag;
	}

private:

	std::string m_name;
	DeviceFactory m_FacID;
	bool m_OemFlag;

    std::string m_usr;
	int m_port;
    std::string m_pass;

	IVideoServerFactory *m_pFactory;
};

#endif // VIDEOSERVER_H
