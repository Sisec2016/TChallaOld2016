#undef UNICODE
#ifndef LOGW_H
#define LOGW_H

#include <QTextCodec>
#include <QString>
#include "Windows.h"
#include <boost/log/support/date_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
using namespace logging::trivial;

class Log
{
    /*
     * 单例模式
     */
    static Log *pInstance;
public:
    static Log &instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new Log();
        }

        return *pInstance;
    }

    static void add(const char* sLog, severity_level s = trace){
        instance().AddLog(QString::fromLocal8Bit(sLog, s));
    }

    static void initFileName(const QString& name)
    {


        if (pInstance != nullptr)
        {
            if (pInstance->mLastFileName == name)
            {
                return;
            }
            delete pInstance;
        }
        pInstance = new  Log(name);
        pInstance->mLastFileName = name;
    }
    Log(const QString& fileName);
    ~Log();
private:
    Log();

    void init(const QString& fileName);

    QString mLastFileName;
public:
    void AddLog(QString msg, severity_level s = trace);
    void AddLog(std::string msg, severity_level s = trace){
        AddLog(QString::fromLocal8Bit(msg.c_str()), s);
    }
    void AddLog(const char* msg, severity_level s = trace){
        AddLog(QString::fromLocal8Bit(msg), s);
    }
    void CheckDirectory();

};

#endif // LOGW_H
