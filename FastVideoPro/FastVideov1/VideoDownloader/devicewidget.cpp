#include "devicewidget.h"
#include "ui_devicewidget.h"
#include "downloadtasktreewidget.h"
#include <QThread>
#include "cwaitdlg.h"
#include "singleapllication.h"
#include "customEvent.h"
#include <QMessageBox>
#include "Verify.h"
#include "PING.h"
#include "uiutils.h"

DeviceWidget::DeviceWidget(std::shared_ptr<videoserver> pServer, DownloadTaskTreeWidget& treeWidget, QWidget *parent)
    : mpService(pServer), mTreeWidget(treeWidget),
    QWidget(parent), mLogout(false), mNeedSave(true),
    ui(new Ui::DeviceWidget), mLastSaveThread(nullptr), mQuiting(false)
{
	mStatus = UNCONNECTED;
    ui->setupUi(this);
    ui->label_refreshing->loadGif();
}

DeviceWidget::~DeviceWidget()
{
    delete ui;

    if (mLoginThread.get() != nullptr)
    {
        mLoginThread->join();
    }

    //qDebug()<<"DeviceWidget::~DeviceWidget";
	//mService.logout();
    //mService.destroy();
    mpService->setRelease(true);
	Log::instance().AddLog(QString("DeviceWidget::~DeviceWidget"));
}

void DeviceWidget::cancelAllDownloadingTask()
{

}

void DeviceWidget::cancelTask()
{

    while (true)
    {
        QThread::msleep(100);
        std::lock_guard<std::recursive_mutex> lock(mmtInitTask);
        if (mpInitTasks.size() == 0)
        {
            break;
        }
    }

    std::lock_guard<std::recursive_mutex> lock(mmtInitTask);
    std::lock_guard<std::recursive_mutex> lockDownload(mMutexDownloadTask);
    if (mpDownloadTask.get())
    {
        mpDownloadTask->cancel();
    }
}
void DeviceWidget::setSelected(bool b)
{
    if (b)
    {
		/*
        ui->widgetSelect->setStyleSheet("QWidget#widgetSelect{border-color: rgb(199,199,199);"
            "border-width: 1px;"
            "border-style: solid;"
            "border-radius: 0px;"
        "}");
		*/
		ui->widgetSelect->setStyleSheet("QWidget#widgetSelect{background-color: rgb(136,150,199);"
			"border-width: 1px;"
			"border-color:transparent;"
			"border-style: solid;"
			"border-radius: 10px;"
	"}");

	}
    else
    {
       ui->widgetSelect->setStyleSheet("");
    }
}

void DeviceWidget::setLoginInfo(std::shared_ptr<LoginServerInfo> p)
{
    mpLoginInfo = p;
    mStatus = UNCONNECTED;
    if (mpLoginInfo.get() != nullptr)
    {
       ui->lbDeviceName->setText(mpLoginInfo->name);
       ui->lbDeviceName->setToolTip(mpLoginInfo->name);
    }
    else
    {
        ui->lbDeviceName->setText("");
        ui->lbDeviceName->setToolTip("");
    }

    refreshUI();
}

void DeviceWidget::login()
{
    if (mStatus == CONNECTING || mStatus == CONNECTED)
    {
        return;
    }

    mStatus = CONNECTING;
    if (mLoginThread.get() != nullptr)
    {
        mLoginThread->join();
    }

    mLoginThread = std::shared_ptr<std::thread>(new std::thread([=](DeviceWidget* This){
        if (mpLoginInfo.get() != nullptr)
        {
			bool bStop = false;
            if (mpService->login(mpLoginInfo, &bStop))
            {
                mStatus = CONNECTED;
                std::lock_guard<std::recursive_mutex> lock(mMutexDownloadTask);
                if (nullptr != mpDownloadTask.get())
                {
                    mpDownloadTask->initDownloadServer();
                    mpDownloadTask->download(this);
                }
                QCoreApplication::postEvent(this, new loginEvent(This));
            }
            else
            {
                mStatus = CONNECT_FAILED;
            }

        }


      //  QCoreApplication::postEvent(This, new loginEvent(this));
    }, this));

    refreshUI();
}

// void DeviceWidget::logout()
// {
// 	if (mService.logout())
// 	{
// 		mStatus = UNCONNECTED;
// 	}
// }

/*
 * 获取保存的目录名
 *  @return 路径值
 */
QString DeviceWidget::getSaveDirName()
{
   QStringListIterator arg_it( QCoreApplication::arguments() );
   while ( arg_it.hasNext() )
   {
       const QString & a = arg_it.next();
       if( a == "-d" && arg_it.hasNext() )
       {
            return QString(arg_it.next()) + "/";
       }
   }

   return Verify::downloadDirPath();
}
void DeviceWidget::initTaskWidget(std::shared_ptr<DownloadTask> task)
{
    if (task.get() == nullptr)
    {
        return;
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    QString source;
    if (task->mTotalSize == 0)
    {
        std::lock_guard<std::recursive_mutex> lock(task->mMutex);
        for (DownloadRows_t::iterator it = task->readyDownloadRows.begin();
            it != task->readyDownloadRows.end(); it++)
        {
            if (it->second.size() > 0 && source.isEmpty())
            {
                source = this->mpService->getChannelName(it->first);
            }

            for (int i = 0; i < it->second.size(); i++)
            {
                task->mTotalSize += it->second[i]->fileSize();
            }
        }
    }
    

    if (task->readyDownloadRows.size() > 1)
    {
        source += "...";
    }
    if (!task->mpTaskWidget)
    {
        task->mpTaskWidget = new TaskWidget(this, task, source);
    }
    else
    {
        task->mpTaskWidget->setTask(this, task);
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    task->mpService = getService();
    task->mTop = new QTreeWidgetItem();
    mTreeWidget.addTopLevelItem(task->mTop);
    mTreeWidget.setItemWidget(task->mTop, 0, task->widget()); 
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;

//     connect(task->widget(), SIGNAL(cancelAll(TaskWidget *)),
//                      &mTreeWidget, SLOT(dealCancelAll(TaskWidget*)));
    connect(task->widget(), SIGNAL(cancelAll(TaskWidget *)),
                     this, SLOT(dealCancelAll(TaskWidget*)));

    connect(task->widget(), SIGNAL(onSel(TaskWidget *)),
                     &mTreeWidget, SLOT(dealSel(TaskWidget*)));

}




void DeviceWidget::dealDowloadfinished(DownloadWidget *souce, int channel, bool complete, bool closed)
{
    if (mQuiting)
    {
        return;
    }
    try
    {
        std::lock_guard<std::recursive_mutex> lock(mMutexDownloadTask);

        std::shared_ptr<DownloadTask> pCurrentTask =  currentTask();
        if (pCurrentTask.get() != nullptr)
        {
            pCurrentTask->dealFinish(souce, channel, complete);
            if (!complete)
            {
                pCurrentTask->releaseDownloadServer(souce->getService(), channel);
            }
            else
            {
                std::shared_ptr<DownloadRow> r = pCurrentTask->getNeedDownload(channel);

                if (r.get() != nullptr)
                {
                    if (!r->download(this, this->getDownloadPath(*pCurrentTask, r->getChannel()), souce->getService()))
                    {
                        pCurrentTask->addFaileRow(r);
                        pCurrentTask->releaseDownloadServer(souce->getService(), channel);

                    }
                    else
                    {
                        pCurrentTask->addDownloadingRow(r);
                    }
                }
                else
                {
                    pCurrentTask->releaseDownloadServer(souce->getService(), channel);
                }
            }

            if (this->mpDownloadTask->isFinished())
            {
                pCurrentTask->widget()->setProgress(100);
                mpFinishTasks.push_back(pCurrentTask);
                std::thread thrd([&]{
                    nextTask();
                    save(false);
                    if (nullptr != currentTask().get())
                    {
                        currentTask()->download(this);
                    }
                 });
                thrd.detach();
            }



        }
    }
    catch(...)
    {
        qDebug()<<"dealDowloadfinished unknown error";
    }

    qDebug()<<"DeviceWidget::dealDowloadfinished"<<souce;

}


void DeviceWidget::dealFailedDownloadRow()
{
    if (mpService && !mpService->isNull() && !mpService->isRelease())
    {
       if (!CPing::instance().Ping((char *)mpService->ip().toStdString().c_str(), 50))//linux/win7 system
        {
            if (this->mStatus == CONNECTED)
            {
                QCoreApplication::postEvent(this, new DeviceUnconnected());
                this->mStatus = UNCONNECTED;
                this->refreshUI();
            }
            
        }
        else if (this->mStatus != CONNECTED)
        {
            this->login();
        }
    }

    if (this->mStatus != CONNECTED)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(mMutexDownloadTask);
    auto curTask = currentTask();
    if (curTask)
    {
        qDebug()<<"d->dealFailedDownloadRow()";
        curTask->heartBeat();
        curTask->download(this);
    }
}

void DeviceWidget::refreshUI()
{
    if (mpLoginInfo.get() != nullptr)
    {
        ui->lbDeviceName->setText(this->mpLoginInfo->name);
        ui->lbDeviceName->setToolTip(mpLoginInfo->name);
    }
    else
    {
        ui->lbDeviceName->setText("");
        ui->lbDeviceName->setToolTip("");
    }

    ui->btStatus->show();
    ui->label_refreshing->hide();
    switch(mStatus)
    {
    case UNCONNECTED:
        ui->btStatus->setStyleSheet("QPushButton{border-image:url(:/png/broken_link.png); background-color: rgba(255, 255, 255, 0);}");
        break;
    case CONNECTING:
        ui->btStatus->hide();
        ui->label_refreshing->show();
        break;
    case CONNECTED:
        ui->btStatus->setStyleSheet("QPushButton{border-image:url(:/png/link.png); background-color: rgba(255, 255, 255, 0);}");
        break;
    case CONNECT_FAILED:
        ui->btStatus->setStyleSheet("QPushButton{border-image:url(:/png/broken_link.png); background-color: rgba(255, 255, 255, 0);}");
        break;
    }


}

void DeviceWidget::customEvent(QEvent* event)
{
    if (mQuiting)
    {
        return;
    }

    loginEvent* elogin = dynamic_cast<loginEvent *> (event);
    if (elogin != NULL)
    {
        refreshUI();
        if (this->mStatus == CONNECTED)
        {
            if (mLoginThread.get() != nullptr)
            {
                mLoginThread->join();
                mLoginThread.reset();
            }
            emit onLogin(this);

        }

    }
    else if (dynamic_cast<DownloadRowForWidget *> (event) != nullptr)
    {
        try
        {
            DownloadRow* pDownloadRow = ((DownloadRowForWidget *)event)->m_pRow;
            auto pServer = ((DownloadRowForWidget *)event)->m_pServer;
            std::lock_guard<std::recursive_mutex> lock(mMutexDownloadTask);
            if (nullptr != pDownloadRow && pServer != nullptr && this->mpDownloadTask.get() != nullptr)
            {
                qDebug()<<"pDownloadRow->getDownloadWidget()";

                if (pDownloadRow->getDownloadWidget() == nullptr)
                {
                        qDebug()<<"getDownloadWidget() == nullptr";
                    RecordFile& row = pDownloadRow->getRecordFile();
                    QString fileName = pServer->getFileName(row);
                    DownloadWidget* dlg = new DownloadWidget(pServer, this->getDownloadPath(*mpDownloadTask, pDownloadRow->getChannel()), fileName, QDateTime::fromTime_t(row.beginTime).toString("yyyy-MM-dd HH:mm:ss"),
                                                                                   QDateTime::fromTime_t(row.endTime).toString("yyyy-MM-dd HH:mm:ss"),
                                                                                   row.channel);
                    pDownloadRow->setDownloadWidget(dlg);
                }
                connect(pDownloadRow->getDownloadWidget(), SIGNAL(finished(DownloadWidget*,int,bool, bool)),
                        this, SLOT(dealDowloadfinished(DownloadWidget*,int,bool, bool)));
                pDownloadRow->getDownloadWidget()->setTask(mpDownloadTask->widget());

                QTreeWidgetItem* pdownLoadWidget = new QTreeWidgetItem();
                mpDownloadTask->TreeWidgetItem()->addChild(pdownLoadWidget);
                mTreeWidget.setItemWidget(pdownLoadWidget, 0,
                    pDownloadRow->getDownloadWidget());

                pDownloadRow->download(this, mpDownloadTask->getFilePath(), pServer);

            }
        }
        catch(...)
        {

        }
    }
    else if(dynamic_cast<AddDownloadRowEvent *> (event) != nullptr)
    {
        this->addDowloadRow();
    }
    else if (dynamic_cast<DeviceUnconnected *> (event) != nullptr)
    {
        UIUtils::showTip(*this, QStringLiteral("已经离线，请检查网络！"), QPoint(0, 0), 10);
    }
}

void DeviceWidget::dealCancelAll(TaskWidget *task)
{
     mTreeWidget.dealCancelAll(task);
     CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在取消下载任务中..."), [=]()
    {
//        std::lock_guard<std::recursive_mutex> lockInitTasks(mmtInitTask);
        std::lock_guard<std::recursive_mutex> lock(mMutexDownloadTask);
        qDebug()<<"cancelDownloading";
        bool cancelDownloading = (this->mpDownloadTask.get() != nullptr &&
                this->mpDownloadTask->widget() == task);
        if (cancelDownloading)
        {
            nextTask();
            save(false);
            if (nullptr != currentTask().get())
            {
                currentTask()->download(this);
            }
        }
        else
        {
            for (int i = 0; i < mpFinishTasks.size(); i++)
            {
                if (mpFinishTasks[i]->widget() == task)
                {
                    mpFinishTasks.erase(mpFinishTasks.begin() + i);
                    break;
                }
            }

            for (int i = 0; i < this->mpWaitingTasks.size(); i++)
            {
                if (mpWaitingTasks[i]->widget() == task)
                {
                    mpWaitingTasks[i]->cancel();
                    mpWaitingTasks.erase(mpWaitingTasks.begin() + i);
                    break;
                }
            }
            save(false);
        }
        qDebug() << "cancelDownloading end"<<__FILE__<<__FUNCTION__<<__LINE__;
// 		for (int i = 0; i < this->mpWaitingTasksCopy.size(); i++)
// 		{
// 			if (mpWaitingTasksCopy[i]->widget() == task)
// 			{
// 				mpWaitingTasksCopy.erase(mpWaitingTasksCopy.begin() + i);
// 				break;
// 			}
// 		}

    }, [](bool bCancel){


    });

    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
}

void DeviceWidget::RemoveTask()
{
//	mmtInitTask.lock();
	mMutexDownloadTask.lock();
	for (int i = 0; i < this->mpWaitingTasks.size(); i++)
	{
        std::shared_ptr<DownloadTask> task = mpWaitingTasks[i];
		mMutexDownloadTask.unlock();
//		mmtInitTask.unlock();

        dealCancelAll(task->mpTaskWidget);
        mTreeWidget.dealCancelAll(task->mpTaskWidget);
		task->cancel();
	}

    mpWaitingTasks.clear();
}

void DeviceWidget::addDowloadRow()
{
    try
    {
        std::shared_ptr<DownloadRow> pDownloadRow;
        {
            std::lock_guard<std::recursive_mutex> lock(mmtInitTask);
            while (mpInitTasks.size() > 0)
            {
                if (mpInitTasks[0].get() == nullptr || mpInitTasks[0]->TreeWidgetItem() == nullptr)
                {
                    mpInitTasks.pop_front();
                }
                else
                {
                    break;
                }
            }

            if (mpInitTasks.size() == 0)
            {
                return;
            }

            qDebug() << "addDowloadRow";
            pDownloadRow = mpInitTasks[0]->ReadyDownloadNext();
        }
        
        if (pDownloadRow.get() == nullptr)
        {
            qDebug()<<"pDownloadRow.get() == nullptr";
            this->addTask(mpInitTasks[0]);
            mpInitTasks.pop_front();
            if (mpInitTasks.size() > 0)
            {
                QCoreApplication::postEvent(this, new AddDownloadRowEvent());
            }
            else
            {

            }
            return;
        }

        qDebug()<<"pDownloadRow->getDownloadWidget()";

        if (pDownloadRow->getDownloadWidget() == nullptr)
        {
                qDebug()<<"getDownloadWidget() == nullptr";
            RecordFile& row = pDownloadRow->getRecordFile();
            QString fileName = this->mpService->getFileName(row);

            DownloadWidget* dlg = new DownloadWidget(mpService, getDownloadPath(*mpInitTasks[0], pDownloadRow->getChannel()), fileName, QDateTime::fromTime_t(row.beginTime).toString("yyyy-MM-dd HH:mm:ss"),
                                                                           QDateTime::fromTime_t(row.endTime).toString("yyyy-MM-dd HH:mm:ss"),
                                                                           row.channel);
            pDownloadRow->setDownloadWidget(dlg);
        }

        pDownloadRow->getDownloadWidget()->setTask(mpInitTasks[0]->widget());
        QTreeWidgetItem* pdownLoadWidget = new QTreeWidgetItem();
        mpInitTasks[0]->TreeWidgetItem()->addChild(pdownLoadWidget);
        mTreeWidget.setItemWidget(pdownLoadWidget, 0,
            pDownloadRow->getDownloadWidget());
    }

    catch(...)
    {
        qDebug()<<"addDowloadRow unknow error";
    }


    qDebug()<<"pDownloadRow->postEvent()";
    QCoreApplication::postEvent(this, new AddDownloadRowEvent());
}

void DeviceWidget::save(bool IncludeTasks)
{
    if (mpLoginInfo.get() == nullptr)
    {
        return;
    }


    std::lock_guard<std::recursive_mutex> lockDownload(mMutexDownloadTask);
    if (mpDownloadTask.get() != nullptr)
    {
        if (IncludeTasks)
        {
            mpDownloadTask->mLoginInfoID = mpLoginInfo->getLNId();
            mpDownloadTask->mState = DTK_STATE_DOWNLOADING;
            mpDownloadTask->save();
        }
    }

    for (int i = 0; i < mpWaitingTasks.size(); i++)
    {
        if (IncludeTasks)
        {
            mpWaitingTasks[i]->mLoginInfoID = mpLoginInfo->getLNId();
            mpWaitingTasks[i]->mState = DTK_STATE_WAITING;
            mpWaitingTasks[i]->save();
        }
    }

    for (int i = 0; i < mpInitTasks.size(); i++)
    {
        if (IncludeTasks)
        {
            mpInitTasks[i]->mLoginInfoID = mpLoginInfo->getLNId();
            mpInitTasks[i]->mState = DTK_STATE_INIT;
            mpInitTasks[i]->save();
        }

    }
}

void DeviceWidget::load()
{
    if (mpLoginInfo.get() == nullptr)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> lockDownload(mMutexDownloadTask);

    login();
    auto pTasks = DownloadTask::query(std::make_pair("mLoginInfoID", mpLoginInfo->getLNId()));
    for (int i  = 0; i < pTasks.size(); i++)
    {
        auto pDownloadTask = pTasks[i];
        if (pDownloadTask->mState != DTK_STATE_NULL && pDownloadTask->mState != DTK_STATE_FINISHED)
        {
            pDownloadTask->loadData();
            initTaskWidget(pDownloadTask);
            addTask(pDownloadTask);
        }
        else{
            pDownloadTask->erase();
        }
    }
}

void DeviceWidget::removeSaveFile()
{
    if (mpLoginInfo.get() == nullptr)
    {
        return;
    }

    QFile file(getSaveFile());
    file.remove();
}

void DeviceWidget::mouseReleaseEvent(QMouseEvent *)
{
    this->login();
    emit onSel(this);
}


void DeviceWidget::on_closeButton_clicked()
{
    emit onClose(this);
}

QString DeviceWidget::getSaveFile()
{
    return QApplication::applicationDirPath() + "/datas/" + getLoginInfo()->id;
}
