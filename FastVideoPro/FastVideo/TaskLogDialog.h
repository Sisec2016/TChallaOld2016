#ifndef TaskLogDialog_H
#define TaskLogDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"
#include <QSqlQueryModel>

namespace Ui {
    class TaskLogDialog;
}

class TaskLogDialog : public MyBaseDialog {
    Q_OBJECT
public:
    TaskLogDialog(QWidget *parent = 0);
    ~TaskLogDialog();
    void refreshTime();
protected slots:
    void onFindBtn();
signals:

protected:

private:
    Ui::TaskLogDialog *ui;
    QSqlQueryModel m_queryModel;
    bool mbHeadSetted;

    void setModelHeadData();
};

#endif // DISKDLG_H
