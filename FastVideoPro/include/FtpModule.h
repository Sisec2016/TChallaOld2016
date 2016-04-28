
#ifndef _FTPMODULE_H
#define _FTPMODULE_H

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "dllexport.h"
#include "Poco/Types.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Net/FTPClientSession.h"



namespace Poco 
{

class FtpUpload : Runnable
{
public:
	FtpUpload();
	virtual ~FtpUpload();
	Int32 SetUpLoadFileInfo(Poco::Net::FTPClientSession *session, char* filename, UInt64 filesize);
	Int32 GetPercent();

	void start();
	void stop();
	void join();
	void run();

public:
	Int32 RunImpl();	
	void DoFtpUpload();
	Int32 StopFtpUpLoad();
	bool GetThreadStatus();
	
private:
	Poco::Net::FTPClientSession *m_ftpSession;
	char m_filename[256];
	Int64 m_fileSize;
	std::streamsize m_upLen;;

	Thread	  m_thread;
	bool	  m_bStop;
	bool      m_bStopUpLoad;
	FastMutex m_mutex;	
	
};


struct FtpServerInfo
{
	char host[16];	    //服务器地址
	char username[128]; //登录用户名
	char password[128]; //登录密码
}FTP_SERVER_INFO;

typedef std::map<std::string, Poco::Net::FTPClientSession*> FtpSessionMap;
typedef std::map<std::string, FtpUpload*> FtpUpLoadMap;

#define DefaultFtpManagerInterface (FtpManager::DefaultFtpManager)
class DLLEXPORT_API FtpManager
{
public:
	FtpManager();
	virtual ~FtpManager();
	static FtpManager& DefaultFtpManager();
	Int32 Login(FtpServerInfo *FtpSvrInfo);
	Int32 LogOut(FtpServerInfo *FtpSvrInfo);
	Int32 GetSeverFileList(FtpServerInfo *FtpSvrInfo);
	Int32 UpLoadFile(FtpServerInfo *FtpSvrInfo, char* filename, UInt64 filesize);
	Int32 GetPercent(char* filename, UInt64 filesize);
	Int32 StopUpLoad(char* filename);

private:
	FtpSessionMap m_ftpSessionMap;
	FtpUpLoadMap m_ftpUploadMap;
};
}

#endif
