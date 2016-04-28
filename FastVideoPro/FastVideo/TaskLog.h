#ifndef TASK_LOG_H
#define TASK_LOG_H
#include "SqlUtils.h"
#include "SqlTableMembers.h"
class TaskLog : public SqlTable<TaskLog>
{
    SERIAL_MEMMBER_HEAD()
public:
    TaskLog();
    ~TaskLog();
    QString mName;
    QString mTime;
    QString mAddress;
    QString mMen;
    QString mDesc;
    QString mDeviceIP;
    QString mText;
};

#endif // TASK_LOG_H