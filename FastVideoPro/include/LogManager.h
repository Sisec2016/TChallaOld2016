#ifndef _LOGMANAGER_H_
#define _LOGMANAGER_H_

#include <list>

#include "dllexport.h"
#include "LogHeader.h"
#include "Log.h"
#include "LogSearch.h"
#include "FileDisk.h"


#include "Poco/Types.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"

namespace Poco 
{

#define DefaultLogManagerInterface (LogManager::DefaultLogManager)

class DLLEXPORT_API LogManager : public Runnable
{
public:
	LogManager();
	virtual ~LogManager();

public:
	static LogManager& DefaultLogManager();
	Int32 LogManagerInit();

	Int32 WriteLog(LogInfo* pRecInfo);
	Int32 StartSearchLog(UInt32 uiStartTime, UInt32 uiEndTime, UInt32 uiType);
	Int32 StopSearchLog();
	Int32 LoadPuLog(Int32 iNum, LogInfo* pLog);
	Int32 Destory();

private:
	int WriteLogToLogFile();
	void CheckRepairLog(CFileDisk* pFileDisk);

private:
	void start();
	void stop();
	void join();
	void run();

private:
	Thread m_thread;
	FastMutex m_threadMutex;
	FastMutex m_logListMutex;
	Event m_Event;

	bool m_bStop;
	
	typedef std::list<LogInfo* > LogList;
	LogList m_pTempLogList;
	
	CLog m_Log;
	CLogSearch m_LogSearch;
};

}
#endif

