
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

private:
    Log();
    Log(const QString& fileName);
    void init(const QString& fileName);
    ~Log();
    QString mLastFileName;
public:
    void AddLog(QString msg, severity_level s = trace);
    void CheckDirectory();

};

#endif // LOGW_H
