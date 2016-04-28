#include "log.h"

#include "Winsvc.h"
#include "time.h"
#include "stdio.h"
#include "Winreg.h"
#include <QObject>
#include <QDir>
#include <QApplication>
#include <iostream>

Log *Log::pInstance = nullptr;

Log::Log()
{
    init(QApplication::applicationName());
}

Log::Log(const QString& fileName)
{
    init(fileName);
}

void Log::init(const QString& fileName)
{
    CheckDirectory();
    logging::add_file_log
    (
        keywords::file_name = (QApplication::applicationDirPath() + QString("/log/") + fileName + QString("_%N.log")).toLocal8Bit().data(),                                        /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< 日志文件大小最大 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< 在半夜12点日志文件更新 >*/
        keywords::format = "[%TimeStamp%]: %Message%",                                 /*< 日志记录格式 >*/
        keywords::auto_flush = true,
        keywords::open_mode = std::ios::app
    );

    logging::add_common_attributes(); 
}


Log::~Log()
{
}


void Log::CheckDirectory()
{
    QDir d(QApplication::applicationDirPath() + "/log");
    if (!d.exists())
    {
        d.mkpath(QApplication::applicationDirPath() + "/log");
    }
}

void Log::AddLog(QString msg, severity_level s)
{
    src::severity_logger< severity_level > lg;
    BOOST_LOG_SEV(lg, s) << msg.toLocal8Bit().data();
}


