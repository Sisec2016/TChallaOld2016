#ifndef WINDOWSERVICE_H
#define WINDOWSERVICE_H
//服务头文件
#include <log.h>



class WindowService
{
public:
    static void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
	static void StartVideoServer(DWORD argc, LPTSTR *argv);
public:
    static SERVICE_STATUS m_ServiceStatus;
    static SERVICE_STATUS_HANDLE m_ServiceStatusHandle;
    static bool bDebug;
};

#endif // WINDOWSERVICE_H
