#pragma once
#include <stdint.h>
#include <RCF/RCF.hpp>
#include <memory>

class ServerCallback
{
	static ServerCallback* sInstance;
	ServerCallback();
	~ServerCallback();
	std::shared_ptr<RCF::RcfServer> mpSubscriptServer;
	RCF::SubscriptionPtr mSubPtr;
public:
	static ServerCallback& instance(){
		if (nullptr == sInstance)
		{
			sInstance = new ServerCallback();
		}

		return *sInstance;
	}
	bool init();
	void onDownloadPos(int64_t receiver, int64_t port, int64_t totalSize, int64_t size, bool failed);
	void onDisconnet(int64_t receiver, int64_t port);
	void onReconnet(int64_t receiver, int64_t port);
	void onHeartbeat(int64_t receiver, int64_t port);
};

