#include "ServerCallback.h"
#include <QCoreApplication>
#include "customEvent.h"
#include "videoserver.h"
#include "Service.h"


ServerCallback* ServerCallback::sInstance = nullptr;

ServerCallback::ServerCallback()
{
}


ServerCallback::~ServerCallback()
{
	mSubPtr->close();
}

bool ServerCallback::init(){
	if (mpSubscriptServer.get() == nullptr)
	{
		mpSubscriptServer = std::make_shared<RCF::RcfServer>(RCF::TcpEndpoint());
		mpSubscriptServer->start();
		mSubPtr = mpSubscriptServer->createSubscription<I_ServerCallback>(
			*this,
			RCF::TcpEndpoint(PORT_PUBLISH));
	}

	return mpSubscriptServer.get() != nullptr;
}

void ServerCallback::onDownloadPos(int64_t receiver, int64_t port, int64_t totalSize, int64_t size, bool failed)
{
	QCoreApplication::postEvent((QObject*)receiver, new downloadEvent(videoserver::getServerByPort(port), totalSize, size, failed));
}

void ServerCallback::onDisconnet(int64_t receiver, int64_t port){
	QCoreApplication::postEvent((QObject*)receiver, new disconnectEvent(videoserver::getServerByPort(port)));
}

void ServerCallback::onReconnet(int64_t receiver, int64_t port){
	QCoreApplication::postEvent((QObject*)receiver, new reconnectEvent(videoserver::getServerByPort(port)));
}

void ServerCallback::onHeartbeat(int64_t receiver, int64_t port){
	QCoreApplication::postEvent((QObject*)receiver, new heartbeatEvent(videoserver::getServerByPort(port)));
}