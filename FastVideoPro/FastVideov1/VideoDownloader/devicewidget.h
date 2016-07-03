#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include "videoserver.h"
#include "downloadtask.h"
#include <QTreeWidget>
#include <algorithm>

typedef std::unique_lock<std::recursive_timed_mutex> device_lock_t;
#define  DEFALUT_WAIT_TIME  200
namespace Ui {
class DeviceWidget;
}

class DownloadRowForWidget : public QEvent
{
public:
    DownloadRowForWidget(DownloadRow_t pRow, std::shared_ptr<videoserver> pServer) :
       QEvent(CUSTOM_DOWNLOAD_FOR_WIDGET_EVENT), m_pRow(pRow), m_pServer(pServer)
    {

    }

    DownloadRow_t m_pRow;
    std::shared_ptr<videoserver> m_pServer;
};
class DeviceUnconnected : public QEvent
{
public:
    DeviceUnconnected() :
        QEvent(CUSTOM_DEVICE_UNCONNECTED_EVENT)
    {

    }
};
class DownloadTaskTreeWidget;
class DeviceWidget : public QWidget
{
    Q_OBJECT

    SERIAL_MEMMBER_HEAD()
    friend class DownloadTask;
    enum statusTip{
        UNCONNECTED,
        CONNECTING,
        CONNECTED,
        CONNECT_FAILED,
    };

    statusTip mStatus;
public:
    explicit DeviceWidget(std::shared_ptr<videoserver> pServer, DownloadTaskTreeWidget& treeWidget, QWidget *parent = 0);
    ~DeviceWidget();
    QString getDownloadPath(DownloadTask& task, channelid_t channel)
    {
        if (getLoginInfo()->factory == SISC_IPC_YUSHIKEJI)
        {
            return QString("%1/YuShiKeJi(%2)/%3").arg(task.getFilePath()).arg(getLoginInfo()->ip)
                .arg(getService()->getChannelName(channel));
        }

        return QString("%1/%2/%3").arg(task.getFilePath()).arg(getLoginInfo()->name)
            .arg(getService()->getChannelName(channel));
    }
    void setLoginInfo(std::shared_ptr<LoginServerInfo> p);
    void cancelAllDownloadingTask();
    void cancelTask();
    bool isConnected()
    {
        return mStatus == CONNECTED;
    }
    void setSelected(bool b);
    std::shared_ptr<LoginServerInfo> getLoginInfo( )
    {
        return mpLoginInfo;
    }
    bool needSave()
    {
        return mNeedSave;
    }
    void setConnected(bool b)
    {
        if (b)
        {
            mStatus = CONNECTED;
        }
        else
        {
            mStatus = UNCONNECTED;
        }

        refreshUI();
    }
    std::shared_ptr<videoserver> getService()
    {
        return mpService;
    }


    std::shared_ptr<DownloadTask> currentTask()
    {
        device_lock_t lock(mMutexDownloadTask, std::chrono::milliseconds(DEFALUT_WAIT_TIME));
        return mpDownloadTask;
    }

    std::shared_ptr<DownloadTask> nextTask()
    {
        device_lock_t lock(mMutexDownloadTask, std::chrono::milliseconds(DEFALUT_WAIT_TIME));
        if (mpDownloadTask.get() != nullptr)
        {
            mpDownloadTask->mState = DTK_STATE_FINISHED;
            mpDownloadTask->save();
            mpDownloadTask->clearDownloadData();
        }

        if (mpWaitingTasks.size() > 0)
        {
            mpDownloadTask = mpWaitingTasks[0];
            mpDownloadTask->mState = DTK_STATE_DOWNLOADING;
            mpWaitingTasks.pop_front();
            mpDownloadTask->initDownloadServer();
        }
        else
        {
            mpDownloadTask.reset();
        }

        return mpDownloadTask;
    }

    void addTask(std::shared_ptr<DownloadTask> task)
    {
        if (!task)
        {
            return;
        }
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        device_lock_t lock(mMutexDownloadTask, std::chrono::milliseconds(DEFALUT_WAIT_TIME));
        task->mState = DTK_STATE_WAITING;
		mpWaitingTasks.push_back(task);

        if (this->currentTask().get() == nullptr)
        {
            nextTask()->download(this);
        }
    }

	void RemoveTask();

    void setQuiting()
    {
        mQuiting = true;
    }

    void refreshUI();
    void login();
	//void logout();
    QString getSaveDirName();
    void initTaskWidget(std::shared_ptr<DownloadTask> task);
   
    bool haveInitTasks()
    {
        device_lock_t lock(mmtInitTask);
        return mpInitTasks.size() != 0;
    }
    bool haveFinshedTasks()
    {
        return mpFinishTasks.size() != 0;
    }
    void save(bool IncludeTasks = true);
    void load();
    void removeSaveFile();
Q_SIGNALS:
    void onSel(DeviceWidget* pDevice);
    void onLogin(DeviceWidget* pDevice);
    void onClose(DeviceWidget* pDevice);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void customEvent(QEvent* event);
protected:
    DownloadTaskTreeWidget& mTreeWidget;
    std::shared_ptr<videoserver> mpService;
    std::shared_ptr<std::thread> mLoginThread;
protected:
    bool mLogout;
    bool mNeedSave;
    bool mQuiting;
    std::shared_ptr<LoginServerInfo> mpLoginInfo;
    std::recursive_timed_mutex  mMutexDownloadTask;
    std::shared_ptr<DownloadTask> mpDownloadTask;
    std::deque< std::shared_ptr<DownloadTask> > mpFinishTasks;
	std::deque< std::shared_ptr<DownloadTask> > mpWaitingTasks;
    std::recursive_timed_mutex mmtInitTask;
    std::deque< std::shared_ptr<DownloadTask> > mpInitTasks;
public slots:
    void dealDowloadfinished(DownloadWidget *souce, int channel, bool complete, bool close);
    void dealFailedDownloadRow();
    void dealCancelAll(TaskWidget *task);
    void addDowloadRow();
    void on_closeButton_clicked();
private:

    void startDownload();
    QString getSaveFile();
private:
    Ui::DeviceWidget *ui;
    std::thread* mLastSaveThread;
};

#endif // DEVICEWIDGET_H
