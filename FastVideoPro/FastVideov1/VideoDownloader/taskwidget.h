#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <qevent.h>
#include <QDateTime>
#include <QString>
#include <memory>
#include "SqlUtils.h"
#include "SqlTableMembers.h"

namespace Ui {
class TaskWidget;
}
class DeviceWidget;
class DownloadTask;
class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(DeviceWidget *pDevice,std::shared_ptr<DownloadTask> t, const QString& sources, QWidget *parent = 0);
    TaskWidget(QWidget *parent = 0);
    void setTask(DeviceWidget *pDevice, std::shared_ptr<DownloadTask> t);

    ~TaskWidget();
    void setProgress(int p);
    int getProgress();
    
	void setSpeed(int nSpeed);

    void setCancel()
    {
        mCancel = true;
    }

Q_SIGNALS:
    void onSel(TaskWidget* task);
    void cancelAll(TaskWidget *task);	

protected:
    virtual void mouseReleaseEvent(QMouseEvent *);
    void customEvent(QEvent* event);
    std::shared_ptr<DownloadTask> mTask;
    DeviceWidget* mpDevice;
private:
    Ui::TaskWidget *ui;

    //开始时间
    QDateTime beg;
    //结束时间
    QDateTime last;


    bool mCancel;
private slots:
    void on_cancelButton_clicked();

private:
	DWORD getMaxDownloadSpeed();
	
};


#endif // TASKWIDGET_H
