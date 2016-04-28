#ifndef LOGDATA_H
#define LOGDATA_H
#include <QString>
#include "SqlUtils.h"
#include "SqlTableMembers.h"

#define  LOG_DATA_TIME_FORMAT "yyyy-MM-dd hh:mm:ss"

#define  LOG_Download_STR  QStringLiteral("文件下载")
#define  LOG_FtpUpload_STR QStringLiteral("FTP上传")
#define  LOG_ShareExpt_STR QStringLiteral("共享导出")
#define  LOG_DiskExpt_STR  QStringLiteral("硬盘导出")
#define  LOG_ScreenRec_STR QStringLiteral("屏幕录制")
#define  LOG_NetConfig_STR QStringLiteral("网络配置")
#define  LOG_FileDel_STR   QStringLiteral("文件删除")
#define  LOG_NoDefine_STR   QStringLiteral("未知操作")

class Logdata : public SqlTable<Logdata>
{
    SERIAL_MEMMBER_HEAD()
public:
    static bool WriteLog(const QString& operation, const QString& describe,
        const QString& mSrcDir = "", const QString& mDstDir = "");
public:
    Logdata();
    QString mUser;
    QString mTime;
    QString mOperation;
    QString mSrcDir;
    QString mDstDir;
    QString mDescribe;
};

#endif // EMPLOYEE_H
