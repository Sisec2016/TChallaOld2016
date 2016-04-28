#include "PublicsherServer.h"
#include "Service.h"
PublicsherServer* PublicsherServer::s_pInstance = nullptr;

PublicsherServer::PublicsherServer() : m_publishingServer(RCF::TcpEndpoint(PORT_PUBLISH))
{
	m_publishingServer.start();

	// Start publishing.
	m_pubPtr = m_publishingServer.createPublisher<I_ServerCallback>();

}


PublicsherServer::~PublicsherServer()
{
	m_publishingServer.stop();
}
