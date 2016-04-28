#include "logdata.h"
#include <QDateTime>
#include "User.h"

SERIAL_MEMMBER_6(Logdata, mUser, mTime, mOperation, mSrcDir,
    mDstDir, mDescribe)
Logdata::Logdata()
{
}

bool Logdata::WriteLog(const QString& operation, const QString& describe,
    const QString& srcDir, const QString& dstDir){
    Logdata newLog;
    newLog.mDescribe = describe;
    newLog.mDstDir = dstDir;
    newLog.mOperation = operation;
    newLog.mSrcDir = srcDir;
    newLog.mUser = User::current().mName;
    newLog.mTime = QDateTime::currentDateTime().toString(LOG_DATA_TIME_FORMAT);
    return newLog.save();
}
