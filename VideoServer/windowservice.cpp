#undef UNICODE

#include <QApplication>

#include <qdebug.h>
#include <QProcess>


#include "windowservice.h"
#include <RCF/RCF.hpp>
#include "Service.h"
#include "VideoserverFactorySvrImp.h"
#include "PublicsherServer.h"
#include "singleapllication.h"
#include <QUdpSocket>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"Advapi32.lib")

SERVICE_STATUS WindowService::m_ServiceStatus;
SERVICE_STATUS_HANDLE WindowService::m_ServiceStatusHandle;
bool WindowService::bDebug;




class VideoServiceImp
{
public:
    // Reverses the order of strings in the vector.
    std::string reverse(std::vector<std::string> &v)
    {
        std::cout << "Reversing a vector of strings...\n";
        std::vector<std::string> w;
        std::copy(v.rbegin(), v.rend(), std::back_inserter(w));
        v.swap(w);

        return "test";
    }
};

void DisableSetUnhandledExceptionFilter()
{
    void *addr = (void*)GetProcAddress(LoadLibraryA("kernel32.dll"),
        "SetUnhandledExceptionFilter");
    if (addr)
    {
        unsigned char code[16];
        int size = 0;
        code[size++] = 0x33;
        code[size++] = 0xC0;
        code[size++] = 0xC2;
        code[size++] = 0x04;
        code[size++] = 0x00;

        DWORD dwOldFlag, dwTempFlag;
        VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
        WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
        VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
    }
}
#define PORT_VIDEO_SERVER		99999
void WindowService::StartVideoServer(DWORD argc, LPTSTR *argv){
    DisableSetUnhandledExceptionFilter();
	int arg = argc;
	SingleApplication a(arg, argv);
	QUdpSocket udp;
    if (!udp.bind(PORT_VIDEO_SERVER, QAbstractSocket::DontShareAddress))
	{
		return;
	}
    Log::instance().AddLog(QObject::tr("StartVideoServer Is Starting"));
	Log::instance().CheckDirectory();
	RCF::RcfInitDeinit rcfInit;

	// Start a TCP server on port 50001, and expose MyServiceImpl.
	//std::make_share<>
	videoserverFactory::getFactorys();
	VideoserverFactorySvrImp myVideoserverFactorySvr;
	RCF::RcfServer server(RCF::TcpEndpoint("0.0.0.0", PORT_FACTORY));
	server.bind<VideoserverFactorySvr>(myVideoserverFactorySvr);
	server.start();
	PublicsherServer::instance();

	while (true)
	{
		Sleep(500);
	}
}

void WINAPI WindowService::ServiceMain(DWORD argc, LPTSTR *argv)
{
    int arg = 0;
	SingleApplication a(arg, argv, true);
    Log::instance().CheckDirectory();
    Log::instance().AddLog(QObject::tr("VideoService Is Starting"));
    if (a.isRunning())
    {
        return;
    }


    while (true)
    {
		QUdpSocket udp;
        if (!udp.bind(PORT_VIDEO_SERVER, QAbstractSocket::DontShareAddress))
		{
			::Sleep(5000);
		}
		else{   
			udp.close();
			QProcess::startDetached(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + " -d");
			::Sleep(2000);
		}
		
    }


    return;
}
