#pragma once
#include <RCF/RCF.hpp>
#include "Service.h"
typedef boost::shared_ptr< RCF::Publisher<I_ServerCallback> > ServerPublisherPtr;

class PublicsherServer
{
	static PublicsherServer* s_pInstance;
	PublicsherServer();
	~PublicsherServer();
	RCF::RcfServer m_publishingServer;
	ServerPublisherPtr m_pubPtr;
public:
	static PublicsherServer& instance(){
		if (nullptr == s_pInstance)
		{
			s_pInstance = new PublicsherServer();
		}

		return *s_pInstance;
	}

	ServerPublisherPtr get(){
		return m_pubPtr;
	}
};

