#undef UNICODE
#include "../../VideoServer/log.h"

//QT头文件
#include <QCoreApplication>
#include <QApplication>
#include <QTextCodec>
#include <QList>
#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QTextCodec>
#include "windowservice.h"
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

void Addlog(const char* sLog){
	Log::instance().AddLog(QString::fromLocal8Bit(sLog));
}

void sheStartVideoServer(DWORD arg, char *argv[]){
	__try{
		WindowService::StartVideoServer(arg, argv);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		Addlog("sheStartVideoServer unkonw error!");
		exit(-1);
	}
}

#ifndef _M_IX86
#error "The following code only works for x86!"
#endif




int main(int argc, char *argv[])
{
	int arg = argc;

    WindowService::bDebug = false;
    if (argc > 1)
    {
        if (strcmp(argv[1], "-d") == 0) //调试模式
        {
			WindowService::StartVideoServer(arg, argv);
        }
        else
        {
            QApplication a(arg, argv);
			WindowService::bDebug = true;
			WindowService::ServiceMain(0, nullptr);
        }
    }
    else
    {
		WindowService::bDebug = true;
		WindowService::ServiceMain(arg, argv);
		return 0;
    }

    return 0;
}



