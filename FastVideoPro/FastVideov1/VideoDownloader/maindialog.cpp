#include "maindialog.h"
#include "ui_maindialog.h"
#include "windowutils.h"
#include <QApplication>
#include "devicewidget.h"
#include "channelwidget.h"
#include <QMessageBox>
#include "uiutils.h"
#include <QCalendarWidget>
#include <QDesktopWidget>
#include "cwaitdlg.h"
#include "messageboxdlg.h"
#include "screenadaption.h"
#include "loginddevicedialog.h"
#include "dialogdownloadfiles.h"
#include "qss.h"
#include "./VideoDownloader/singleapllication.h"
#include <QScrollBar>
#include "Verify.h"
#include "TaskLogRecordDialog.h"


#pragma comment(lib, "SearchDevices.lib")

#define REFRESH_SECONDS   10
MainDialog::MainDialog(QWidget *parent) :
MyBaseDialog(parent),
ui(new Ui::MainDialog),
mStop(false)

{

    ui->setupUi(this);
    //  this->setWindowFlags(Qt::FramelessWindowHint );//| Qt::WindowStaysOnTopHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    ui->hideButton->hide();
    backBtn->hide();
    closeBtn->hide();
    title_label->raise();
    ui->head_widget->hide();

    m_backBtn2 = new QPushButton(this);
    m_backBtn2->setObjectName(QString::fromUtf8("backBtn"));
    m_backBtn2->setGeometry(QRect(10, 10, 32, 32));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/back.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_backBtn2->setIcon(icon);
    m_backBtn2->setIconSize(QSize(32, 32));

    m_closeBtn2 = new QPushButton(this);
    m_closeBtn2->setObjectName(QString::fromUtf8("closeBtn"));
    m_closeBtn2->setGeometry(QRect(970, 4, 45, 45));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_closeBtn2->setIcon(icon2);
    m_closeBtn2->setIconSize(QSize(45, 45));

    m_backBtn2->setStyleSheet(transparentBtn_StyleSheet);
    m_closeBtn2->setStyleSheet(transparentBtn_StyleSheet);

    ui->listWidgetDevices->horizontalScrollBar()->hide();
    ui->listWidgetDevices->verticalScrollBar()->hide();

    ui->listWidgetChannels->setAttribute(Qt::WA_TranslucentBackground);
    ui->listWidgetDevices->init(this);

    ui->beginDateEdit->setDate(QDateTime::currentDateTime().date());
    ui->endDateEdit->setDate(QDateTime::currentDateTime().date());
    ui->beginDateEdit->calendarWidget()->setFixedSize(400, 400);
    ui->endDateEdit->calendarWidget()->setFixedSize(400, 400);
    ui->beginTimeEdit->setTime(QTime(0, 0, 0));
    ui->timeEditPlus->setTime(QTime(0, 0, 0));
    ui->timeEditSub->setTime(QTime(0, 0, 0));

    ui->beginDateEdit_time->setDate(QDateTime::currentDateTime().date());
    ui->endDateEdit_time->setDate(QDateTime::currentDateTime().date());
    ui->beginDateEdit_time->calendarWidget()->setFixedSize(400, 400);
    ui->endDateEdit_time->calendarWidget()->setFixedSize(400, 400);
    ui->beginTimeEdit_time->setTime(QTime(0, 0, 0));
    ui->rb_queryAll->setChecked(true);
    this->on_rb_queryTime_clicked(false);
    connect(ui->rb_queryAll, SIGNAL(toggled(bool)), this, SLOT(on_rb_queryAll_clicked(bool)));
    connect(ui->rb_queryTime, SIGNAL(toggled(bool)), this, SLOT(on_rb_queryTime_clicked(bool)));
    connect(ui->timeEditPlus, SIGNAL(TimeSet(TimeEdit*)), ui->timeEditSub, SLOT(reset()));
    connect(ui->timeEditSub, SIGNAL(TimeSet(TimeEdit*)), ui->timeEditPlus, SLOT(reset()));
    ui->endTimeEdit->setTime(QTime(23, 59, 59));

    connect(m_backBtn2, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(m_closeBtn2, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(ui->listWidgetDevices, SIGNAL(onSelected(DeviceWidget*)),
        this, SLOT(onSelected(DeviceWidget*)));

    connect(ui->listWidgetDevices, SIGNAL(onRemoveChannels()),
        this, SLOT(onRemoveChannels()));
    ui->taskTreeWidget->setFrameStyle(QFrame::NoFrame);
    // ScreenAdaption::instance().init(this->geometry().width(), this->geometry().height());
    //  ScreenAdaption::instance().adpte(this);

	//<<<<<<<<<<<<<add by zhangyaofa
	m_pSearch = CreateSearchObj();
	//>>>>>>>>>>>>>add end

    CWaitDlg::waitForDoing(this->parentWidget(), QString::fromLocal8Bit("正在加载数据中..."), [=]()
    {
        videoserverFactory::getFactorys();

    }, [this](bool bCancel){load(); });


    mDownloadTimerThread = std::shared_ptr<std::thread>(new std::thread([&]()
    {
        int seconds = 0;
        while (!mStop)
        {
            ::Sleep(1000);
            if (seconds++ < REFRESH_SECONDS)
            {
                continue;
            }
            else
            {
                seconds = 0;
            }
            try
            {
                ui->listWidgetDevices->heartbeat();
            }
            catch (...)
            {

            }
        }
    }));


    CWaitDlg::setMainDlg(this);
    // ScreenAdaption::instance().showInCenter(this);
}



MainDialog::~MainDialog()
{
    this->saveForExit();

	//<<<<<<<<<<<<<<add by zhangyaofa
	DestroySearchObj(m_pSearch);
	//>>>>>>>>>>>>>>>add end

    exit(1);
    mStop = true;
	
    CWaitDlg::waitForDoing(this->parentWidget(), QString::fromLocal8Bit("正在退出中..."), [this]()
    {
        if (mDownloadTimerThread)
        {
            mDownloadTimerThread->join();
            mDownloadTimerThread.reset();
        }
        ui->listWidgetDevices->setAllTaskCancel();
        ui->listWidgetDevices->setQuiting();

    }, [this](bool bCancel){
    });


    ui->listWidgetDevices->releaseAll();
    
    qDebug() << "delete ui beg";
//    m_backBtn2->deleteLater();
//    delete m_backBtn2;
//    m_closeBtn2->deleteLater();
    delete ui;



    Verify::uninit();
    CWaitDlg::setMainDlg(this->parentWidget());
    // exit(1);
}

DeviceWidget* MainDialog::createDeviceWidget(std::shared_ptr<videoserver> pServer)
{
    DeviceWidget* p = new DeviceWidget(pServer, *ui->taskTreeWidget);
    //p->login();//此处登录多余,本函数是DeviceListWidget类回调创建DeviceWidget对象使用的,在DeviceListWidget类中已有调用
    return p;
}

QDateTime MainDialog::getGPSBeginDateTime()
{
    QDateTime t;
    t.setDate(ui->beginDateEdit->date());
    t.setTime(ui->beginTimeEdit->getTime());
    t = t.addSecs(QTime(0, 0, 0).secsTo(ui->timeEditPlus->getTime()));
    t = t.addSecs(-QTime(0, 0, 0).secsTo(ui->timeEditSub->getTime()));
    return t;
}

QDateTime MainDialog::getGPSEndDateTime()
{
    QDateTime t;
    t.setDate(ui->endDateEdit->date());
    t.setTime(ui->endTimeEdit->getTime());
    t = t.addSecs(QTime(0, 0, 0).secsTo(ui->timeEditPlus->getTime()));
    t = t.addSecs(-QTime(0, 0, 0).secsTo(ui->timeEditSub->getTime()));
    return t;
}

QDateTime MainDialog::getBeginDateTime()
{
    QDateTime t;
    t.setDate(ui->beginDateEdit->date());
    t.setTime(ui->beginTimeEdit->getTime());
    return t;
}

QDateTime MainDialog::getEndDateTime()
{
    QDateTime t;
    t.setDate(ui->endDateEdit->date());
    t.setTime(ui->endTimeEdit->getTime());
    return t;
}
QDateTime MainDialog::getGPSBeginDateTime_time()
{
    QDateTime t;
    t.setDate(ui->beginDateEdit_time->date());
    t.setTime(ui->beginTimeEdit_time->getTime());
    t = t.addSecs(QTime(0, 0, 0).secsTo(ui->timeEditPlus->getTime()));
    t = t.addSecs(-QTime(0, 0, 0).secsTo(ui->timeEditSub->getTime()));
    return t;
}

QDateTime MainDialog::getGPSEndDateTime_time()
{
    QDateTime t;
    t.setDate(ui->endDateEdit_time->date());
    t.setTime(ui->endTimeEdit_time->getTime());
    t = t.addSecs(QTime(0, 0, 0).secsTo(ui->timeEditPlus->getTime()));
    t = t.addSecs(-QTime(0, 0, 0).secsTo(ui->timeEditSub->getTime()));
    return t;
}

QDateTime MainDialog::getBeginDateTime_time()
{
    QDateTime t;
    t.setDate(ui->beginDateEdit_time->date());
    t.setTime(ui->beginTimeEdit_time->getTime());
    return t;
}

QDateTime MainDialog::getEndDateTime_time()
{
    QDateTime t;
    t.setDate(ui->endDateEdit_time->date());
    t.setTime(ui->endTimeEdit_time->getTime());
    return t;
}
#define MAX_FILES_NUM    6000
#define MAX_DOWNLOAD_HOURS  24*8
#define MAX_DOWNLOAD_SECONDS  (MAX_DOWNLOAD_HOURS*3600)
bool MainDialog::isOverTime(int channelNum)
{
    if ((getBeginDateTime().secsTo(getEndDateTime()) * channelNum) > MAX_DOWNLOAD_SECONDS)
    {
        return true;
    }

    return false;
}

bool MainDialog::isOverZoneTime(int channelNum)
{
    QDateTime timeStart(getBeginDateTime());
    QDateTime timeEnd(getEndDateTime());
    quint64 seconds = 0;
    for (QDate start(timeStart.date()); start <= timeEnd.date(); start = start.addDays(1))
    {
        seconds += timeStart.time().secsTo(timeEnd.time());
    }

    if (seconds * channelNum > MAX_DOWNLOAD_SECONDS)
    {
        return true;
    }
    return false;
}

void MainDialog::onDownloadTask(std::shared_ptr<DownloadTask> pDownloadTask)
{
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    DeviceWidget* pDevice = ui->listWidgetDevices->cuurentDevice();
    if (nullptr == pDevice)
    {
        ui->widgetDisable->lower();
        return;
    }
    pDevice->initTaskWidget(pDownloadTask);
    CWaitDlg::waitForDoing(NULL, QString::fromLocal8Bit("正在加载下载通道中..."), [=]()
    {
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        pDownloadTask->save();
        pDevice->save(false);
        pDevice->addTask(pDownloadTask);
        pDevice->save(false);
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    }, [=](bool bCancel){ui->widgetDisable->lower(); });

    ui->widgetDisable->lower();
}

void MainDialog::onDownloadFindEnd(std::shared_ptr< std::vector<RecordFile> > pFileAllRows)
{
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    if (pFileAllRows.get() == nullptr || pFileAllRows->size() > MAX_FILES_NUM)
    {
        UIUtils::showTip(*ui->downloadButton, QString::fromLocal8Bit("单次搜索的文件过多，请缩短下载时段或者减少下载通道。"));
        ui->widgetDisable->lower();
        return;
    }

    DeviceWidget* pDevice = ui->listWidgetDevices->cuurentDevice();
    if (nullptr == pDevice)
    {
        ui->widgetDisable->lower();
        return;
    }

    if (pFileAllRows->size() > 0)
    {
        DialogDownloadFiles filedlg(pDevice->getService(), *pFileAllRows);

        if (filedlg.exec() == QDialog::Rejected)
        {
            ui->widgetDisable->lower();
            return;
        }
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        std::shared_ptr< std::vector<RecordFile*> > pFiles = std::make_shared< std::vector<RecordFile*> >();
        filedlg.getSelectedFiles(*pFiles);

        std::shared_ptr<DownloadTask> pDownloadTask = std::make_shared<DownloadTask>();

        QString timeString = QString("%1-%2").arg(this->getGPSBeginDateTime().toString("yyMMddHHmm"))
            .arg(this->getGPSEndDateTime().toString("yyMMddHHmm"));

        if (ui->rb_queryTime->isChecked())
        {
            auto timeBeg = getGPSBeginDateTime_time();
            auto timeEnd = getGPSEndDateTime_time();
            timeString = QString("%1-%2_%3-%4").arg(timeBeg.toString("yyMMdd")).arg(timeEnd.toString("yyMMdd")).arg(timeBeg.toString("HHmm")).arg(timeEnd.toString("HHmm"));
        }

        pDownloadTask->setFilePath(pDevice->getSaveDirName() + "/" + timeString);
        pDownloadTask->setName(QString("%1(%2)").arg(pDevice->getLoginInfo()->name).arg(timeString));

        CWaitDlg::waitForDoing(NULL, QString::fromLocal8Bit("正在加载下载通道中..."), [=]()
        {
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
            for (int i = 0; i < pFiles->size(); i++)
            {
                pDownloadTask->addRow(std::make_shared<DownloadRow>(i, *((*pFiles)[i])));
            }
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        }, [pDownloadTask, this](bool bCancel){
            onDownloadTask(pDownloadTask);
        });

        TaskLogRecordDialog taskLogRecordDlg(pDownloadTask->getName(), pDevice->getLoginInfo()->ip);
        taskLogRecordDlg.exec();
    }
    else
    {
        MessageBoxDlg msgDlg(QString::fromLocal8Bit("视频文件未找到！"));
        msgDlg.exec();
        ui->widgetDisable->lower();
    }

}

void MainDialog::on_downloadButton_clicked()
{
    if (ui->rb_queryTime->isChecked())
    {
        on_zonedownloadBtn_clicked();
        return;
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    DeviceWidget* pDevice = ui->listWidgetDevices->cuurentDevice();
    if (pDevice == nullptr)
    {
        UIUtils::showTip(*ui->downloadButton,
            QString::fromLocal8Bit("请选择一个设备！"));
        return;
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    std::vector<int> channels;
    ui->listWidgetChannels->getSelectedChannels(channels);
    if (channels.size() == 0)
    {
        UIUtils::showTip(*ui->downloadButton, QString::fromLocal8Bit("请选择一个通道！"));
        return;
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    ui->widgetDisable->raise();
    std::shared_ptr< std::vector<RecordFile> > pFileAllRows = std::make_shared< std::vector<RecordFile> >();
    CWaitDlg::waitForDoing(NULL, QString::fromLocal8Bit("正在搜索通道文件中..."), [channels, pFileAllRows, this, pDevice]()
    {
        qDebug() << "正在搜索通道文件中";
        std::vector<RecordFile> fileRows;
        pDevice->getService()->ClearRecordFileList();

        fileRows.clear();
        qDebug() << getGPSBeginDateTime().toString() << " GetRecordFileList " << getGPSEndDateTime().toString();
        std::vector<int> tempchannels;
        tempchannels = channels;
        if (pDevice->getService()->GetRecordFileList(fileRows, tempchannels,
            getGPSBeginDateTime(), getGPSEndDateTime()))
        {
            for (std::vector<RecordFile>::iterator it = fileRows.begin();
                it != fileRows.end(); it++)
            {
                pFileAllRows->push_back(*it);
            }
        }
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        //         for (int i = 0; i < channels.size(); i++)
        //         {
        //             fileRows.clear();
        //             qDebug()<<getGPSBeginDateTime().toString()<<" GetRecordFileList "<<getGPSEndDateTime().toString();
        //             if ( pDevice->getService().GetRecordFileList(fileRows, channels[i],
        //                 getGPSBeginDateTime(), getGPSEndDateTime()))
        //             {
        //                 for (std::vector<RecordFile>::iterator it = fileRows.begin();
        //                      it != fileRows.end(); it++)
        //                 {
        //                     pFileAllRows->push_back(*it);
        //                 }
        //             }
        //         }

    }, [pFileAllRows, this](bool bCancel){
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        onDownloadFindEnd(pFileAllRows);
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    });
}

void MainDialog::on_closeButton_clicked()
{
    this->reject();
}

void MainDialog::on_zonedownloadBtn_clicked()
{
    DeviceWidget* pDevice = ui->listWidgetDevices->cuurentDevice();
    if (pDevice == nullptr)
    {
        UIUtils::showTip(*ui->downloadButton,
            QString::fromLocal8Bit("请选择一个设备！"));
        return;
    }

    std::vector<int> channels;
    ui->listWidgetChannels->getSelectedChannels(channels);
    if (channels.size() == 0)
    {
        UIUtils::showTip(*ui->downloadButton, QString::fromLocal8Bit("请选择一个通道！"));
        return;
    }
    std::shared_ptr< std::vector<RecordFile> > pFileAllRows = std::make_shared< std::vector<RecordFile> >();
    CWaitDlg::waitForDoing(NULL, QString::fromLocal8Bit("正在搜索通道文件中..."), [channels, pFileAllRows, this, pDevice]()
    {
        qDebug() << "正在搜索通道文件中";
        std::vector<RecordFile> fileRows;
        pDevice->getService()->ClearRecordFileList();

        fileRows.clear();
        std::vector<int> tempchannels;
        tempchannels = channels;
        qDebug() << getGPSBeginDateTime_time().toString() << " GetRecordFileList " << getGPSEndDateTime_time().toString();
        if (pDevice->getService()->GetRecordFileListZone(fileRows, tempchannels,
            getGPSBeginDateTime_time(), getGPSEndDateTime_time()))
        {
            for (std::vector<RecordFile>::iterator it = fileRows.begin();
                it != fileRows.end(); it++)
            {
                pFileAllRows->push_back(*it);
            }
        }

    }, [pFileAllRows, this](bool bCancel){
        onDownloadFindEnd(pFileAllRows);
    });
}

void MainDialog::on_hideButton_clicked()
{
    this->showMinimized();
}

void MainDialog::onSelected(DeviceWidget *d)
{
    if (d != nullptr)
    {
        ui->listWidgetChannels->showServer(*d->getService());
    }
}

void MainDialog::onRemoveChannels()
{
    ui->listWidgetChannels->clear();
}

void MainDialog::on_btnAddDevice_clicked()
{
    ui->widgetDisable->raise();

    LogindDeviceDialog dlg(this);
    dlg.exec();
    std::vector< std::shared_ptr<LoginServerInfo> > DeviceVec = dlg.getLoginServerInfo();
    std::shared_ptr<LoginServerInfo> pInfo;

    // 	std::shared_ptr<LoginServerInfo> pInfo = dlg.getLoginInfo();
    // 	if (pInfo)
    // 	{
    // 		videoserver *pServer = videoserverFactory::getFactory(pInfo->factory)->create();
    // 		if (pServer != nullptr)
    // 		{
    // 			ui->listWidgetDevices->addDevice(*pServer, pInfo, false);
    // 		}
    // 
    // 	}

    for (int i = 0; i < DeviceVec.size(); i++)
    {
        pInfo = DeviceVec[i];
        if (pInfo)
        {
            auto pServer = videoserverFactory::getFactory((DeviceFactory)pInfo->factory)->create();
            if (pServer)
            {
                ui->listWidgetDevices->addDevice(pServer, pInfo, false);
                //Log::instance().AddLog(pInfo->name + " " + pInfo->ip + ", id:" + pInfo->id);
                QThread::msleep(10);
            }

        }
    }

    ui->widgetDisable->lower();
}

void MainDialog::on_checkBoxChannelAll_toggled(bool checked)
{
    ui->listWidgetChannels->setAllChecked(checked);
}

void MainDialog::load()
{
    ui->listWidgetDevices->load();
}
void MainDialog::save()
{
    ui->listWidgetDevices->save();
}
void MainDialog::saveForExit(){
    std::shared_ptr<bool> bpSave = std::make_shared<bool>(false);
    std::shared_ptr<std::recursive_mutex> lockMutex = std::make_shared<std::recursive_mutex>();

 //   ui->listWidgetDevices->setAllTaskCancel();
 //   ui->listWidgetDevices->setQuiting();
	
    CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("正在保存数据中..."), [=]()
    {
        int time = 0;

    BeginSave:
        __try{
            save();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            std::cout << "  save(); unkonw error!" << std::endl;
            if (time++ > 4)
            {
                return;
            }
            else
            {
                QThread::sleep(2);
                goto BeginSave;
            }
        }

        *bpSave = true;
    }, [this, lockMutex](bool bCancel){
        lockMutex->unlock(); });

        lockMutex->lock();
        if (*bpSave)
        {

        }
        else
        {
            //UIUtils::showTip(*this, QString::fromLocal8Bit("保存下载数据失败！请稍候再试..."));
        }
}
void MainDialog::on_leftBtn_clicked()
{
    ui->listWidgetDevices->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
}

void MainDialog::on_rightBtn_clicked()
{
    ui->listWidgetDevices->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
}
void MainDialog::on_rb_queryAll_clicked(bool checked){
    ui->beginDateEdit->setEnabled(checked);
    ui->endDateEdit->setEnabled(checked);
    ui->beginTimeEdit->setEnabled(checked);
    ui->endTimeEdit->setEnabled(checked);
}

void MainDialog::on_rb_queryTime_clicked(bool checked){
    ui->beginDateEdit_time->setEnabled(checked);
    ui->endDateEdit_time->setEnabled(checked);
    ui->beginTimeEdit_time->setEnabled(checked);
    ui->endTimeEdit_time->setEnabled(checked);
}