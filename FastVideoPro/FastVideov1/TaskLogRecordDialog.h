#ifndef TaskLogRecordDialog_H
#define TaskLogRecordDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"
#include "TaskLog.h"
namespace Ui {
    class TaskLogRecordDialog;
}

class TaskLogRecordDialog : public MyBaseDialog {
    Q_OBJECT
public:
    TaskLogRecordDialog(const QString& taskName, const QString& deviceIP, QWidget *parent = 0);
    ~TaskLogRecordDialog();
    QString caseDir();
protected slots:
    void onOkBtn();
signals:

protected:
    TaskLog mTaskLog;
    QString mCaseDir;
private:
    Ui::TaskLogRecordDialog *ui;
};

#endif // DISKDLG_H
