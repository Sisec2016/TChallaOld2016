/**
 * @copyright (C),1999-2014,福建省伊时代科技股份有限公司.
 * @file     Log.h(文件名)
 * @authors  李乃茂
 * @version  v1.0(版本)
 * @date      2014-05-05 (日期)
 * @details   日志处理\n
 *
 *
 * @pre Windows
 * @note
 **/
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
    Log(const QString& fileName);
    ~Log();
private:
    Log();

    void init(const QString& fileName);

    QString mLastFileName;
public:
    void AddLog(const QString& msg, severity_level s = trace);
    void AddLog(const std::string& msg, severity_level s = trace);
    void CheckDirectory();

};

#endif // LOGW_H
