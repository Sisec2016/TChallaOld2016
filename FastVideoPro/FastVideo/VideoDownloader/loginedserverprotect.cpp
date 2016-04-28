#include "loginedserverprotect.h"
#include "videoserver.h"
std::recursive_mutex LoginedServerProtect::sMutexEvent;
std::map<QString, std::shared_ptr<LoginedServerProtect> > LoginedServerProtect::sLoginedServers;
LoginedServerProtect::LoginedServerProtect() : mpvsServer(nullptr),
    mpFactory(nullptr), mpIServer(nullptr)
{
}

bool LoginedServerProtect::isLogined(videoserver* p)
{
    if (p == nullptr || !p->mpLoginInfo)
    {
        return false;
    }

    QString sTag = getServerTag(p->mpLoginInfo);
    std::lock_guard<std::recursive_mutex> lock(sMutexEvent);
    return  (sLoginedServers.find(sTag) != sLoginedServers.end()) && sLoginedServers[sTag]->mpvsServer == p;
}


bool LoginedServerProtect::set(videoserver* p)
{
    if (p == nullptr || !p->mpLoginInfo)
    {
        return false;
    }

    QString sTag = getServerTag(p->mpLoginInfo);
    std::lock_guard<std::recursive_mutex> lock(sMutexEvent);
    if (sLoginedServers.find(sTag) == sLoginedServers.end())
    {
         return false;
    }

    if (sLoginedServers[sTag]->mpvsServer == nullptr)
    {
        Log::instance().AddLog(QString("set(: beg"));
        if (p->mpServer != nullptr && p->mpServer != sLoginedServers[sTag]->mpIServer)
        {

            p->mpServer->destroy();
        }
        Log::instance().AddLog(QString("set(: end"));

        p->mpServer = sLoginedServers[sTag]->mpIServer;
        p->mpFactory = sLoginedServers[sTag]->mpFactory;
        p->m_channels = sLoginedServers[sTag]->m_channels;
        sLoginedServers[sTag]->mpvsServer = p;
        return true;
    }

    //return false;
	//如果(sLoginedServers[sTag]->mpvsServer == nullptr)为假,说明已有登录信息了,登录成功
	return true;
}

bool LoginedServerProtect::add(videoserver* p)
{
    if (p == nullptr || !p->mpLoginInfo)
    {
        return false;
    }

    QString sTag = getServerTag(p->mpLoginInfo);
    std::lock_guard<std::recursive_mutex> lock(sMutexEvent);
    if (sLoginedServers.find(sTag) == sLoginedServers.end())
    {
         sLoginedServers[sTag] = std::make_shared<LoginedServerProtect>();
         sLoginedServers[sTag]->mpFactory = p->factory();
         sLoginedServers[sTag]->mpIServer = p->mpServer;
         sLoginedServers[sTag]->m_channels = p->m_channels;
         sLoginedServers[sTag]->mpvsServer = p;
         //Log::instance().AddLog(QString("add(videoserver* p: %1").arg(p->m_channels.size()));
         return true;
    }

    return false;
}

void LoginedServerProtect::release(videoserver* p)
{
    if (p == nullptr || !p->mpLoginInfo)
    {
        return;
    }

    QString sTag = getServerTag(p->mpLoginInfo);
    std::lock_guard<std::recursive_mutex> lock(sMutexEvent);
    if (sLoginedServers.find(sTag) != sLoginedServers.end() && sLoginedServers[sTag]->mpvsServer == p)
    {
        sLoginedServers[sTag]->mpvsServer = nullptr;

    }
    else if (nullptr != p->mpServer)
    {
        p->mpServer->destroy();
    }
}

//用于删除厂商时,清除登录记录
void LoginedServerProtect::remove(videoserver* p)
{
	//Log::instance().AddLog(QString("LoginedServerProtect::remove in"));
	if (p == nullptr || !p->mpLoginInfo)
	{
		return;
	}
	//Log::instance().AddLog(QString("LoginedServerProtect::remove 01"));

	QString sTag = getServerTag(p->mpLoginInfo);
	std::lock_guard<std::recursive_mutex> lock(sMutexEvent);
	if (sLoginedServers.find(sTag) != sLoginedServers.end() && sLoginedServers[sTag]->mpvsServer == p)
	{
		//sLoginedServers[sTag]->mpvsServer = nullptr;
		sLoginedServers.erase(sTag);
		//Log::instance().AddLog(QString("LoginedServerProtect::remove 02"));
	}
	p->mpServer->destroy();
	//Log::instance().AddLog(QString("LoginedServerProtect::remove 03"));
	p->mpServer = nullptr;
}

QString LoginedServerProtect::getServerTag(std::shared_ptr<LoginServerInfo> p)
{
    if (!p)
    {
        return "";
    }
	return QString("%1%2%3%4").arg(p->ip).arg(p->port).arg(p->user).arg(p->password);
}

