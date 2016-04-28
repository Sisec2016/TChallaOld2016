#include "taskwidget.h"
#include "ui_taskwidget.h"
#include "windowutils.h"
#include <QMessageBox>
#include "videoserver.h"
#include "customEvent.h"
#include "messageboxdlg.h"
#include "downloadtask.h"
#include "cwaitdlg.h"
#include "singleapllication.h"
#include "devicewidget.h"
#include "uiutils.h"
#include "screenadaption.h"

TaskWidget::TaskWidget(DeviceWidget *pDevice, std::shared_ptr<DownloadTask> t,  const QString& sources, QWidget *parent) :
    QWidget(parent),
    beg(QDateTime::currentDateTime()),
    mCancel(false),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setTask(pDevice, t);
    ui->statusLabel->setText(QString::fromLocal8Bit("等待"));
    ScreenAdaption::instance().adpte(this);
}


TaskWidget::TaskWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TaskWidget), beg(QDateTime::currentDateTime()), mCancel(false), mpDevice(nullptr)
{
    ui->setupUi(this);
    last = beg;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->statusLabel->setText(QString::fromLocal8Bit("等待"));
    mTask.reset();
    ScreenAdaption::instance().adpte(this);
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

void TaskWidget::setTask(DeviceWidget *pDevice, std::shared_ptr<DownloadTask> t)
{
    mpDevice = pDevice;
    mTask = t;
    if (mTask)
    {
        last = beg;
        ui->nameLabel->setText(mTask->mName);
        ui->nameLabel->setToolTip(mTask->mName);
        int totalM = mTask->mTotalSize / KBS_ONE_M / BYTES_ONE_KB;
        if (totalM > 0)
        {
            ui->sizeLabel->setText(QString("%1M").arg(totalM));
        }
        else
        {
            ui->sizeLabel->setText(QString("%1KB").arg(mTask->mTotalSize / BYTES_ONE_KB));
        }
    }
}
void TaskWidget::setProgress(int p)
{
    if (p >= 0 && p <= 100)
    {
        mTask->mDownloadSize = p * mTask->mTotalSize / 100;
        ui->progressBar->setValue(p);
        if (mTask->mDownloadSize >= mTask->mTotalSize)
        {
            ui->statusLabel->setText(QString::fromLocal8Bit("完成"));
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::green);
            ui->statusLabel->setPalette(pe);
            mTask->mDownloadSize = mTask->mTotalSize;
            mTask->mLastDownloadSize = mTask->mTotalSize;
            ui->timeLabel->setText(QString::fromLocal8Bit("0分0秒"));
        }
    }
}

int TaskWidget::getProgress(){
    return ui->progressBar->value();
}
void TaskWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (mCancel)
    {
        return;
    }
    emit onSel(this);
}

void TaskWidget::customEvent(QEvent* event)
{
    if (mCancel || !mTask)
    {
        return;
    }

    taskEvent* edownload = dynamic_cast<taskEvent *> (event);
    if (edownload != NULL)
    {
        if (!edownload->m_failed && edownload->m_downloadsize < mTask->mTotalSize
                && mTask->mDownloadSize < mTask->mTotalSize)
        {
            QDateTime end(QDateTime::currentDateTime());
            qint64 msecs = last.msecsTo(end);
            mTask->mDownloadSize += edownload->m_downloadsize;
            if (msecs > 1000)
            {
                qint64 v = (mTask->mDownloadSize - mTask->mLastDownloadSize) * 1000 / (msecs * 1.0) / BYTES_ONE_KB;
                int vM = v / KBS_ONE_M;
                if (vM * BIT_ONE_BYTE > 0)
                {
                    ui->speedLabel->setText(QString("%1Mbps").arg(vM * BIT_ONE_BYTE));
                }
                else
                {
                    ui->speedLabel->setText(QString("%1Kbps").arg(v * BIT_ONE_BYTE));
                }
                last = end;
                mTask->mLastDownloadSize = mTask->mDownloadSize;


                if (v > 0)
                {
                    int leftsecs = (mTask->mTotalSize - mTask->mDownloadSize) / v / BYTES_ONE_KB;

                    if (leftsecs / 60 > 60)
                    {
                        ui->timeLabel->setText(QString::fromLocal8Bit("%1时%2分").arg(leftsecs / 3600).arg((leftsecs % 3600) / 60));
                    }
                    else
                    {
                        ui->timeLabel->setText(QString::fromLocal8Bit("%1分%2秒").arg(leftsecs / 60).arg(leftsecs % 60));
                    }
                }
            }

            if (mTask->mDownloadSize < mTask->mTotalSize)
            {
                ui->statusLabel->setText(QString::fromLocal8Bit("下载中"));
            }

            ui->progressBar->setValue(mTask->mDownloadSize / (mTask->mTotalSize * 1.0) * 100);

            if (mTask->mDownloadSize >= mTask->mTotalSize)
            {
                ui->timeLabel->setText(QString::fromLocal8Bit("0分0秒"));

            }
        }

    }

}

void TaskWidget::on_cancelButton_clicked()
{
    if (mCancel)
    {
        UIUtils::showTip(*mpDevice, QString::fromLocal8Bit("已取消此任务！"));
        return;
    }

    if (mpDevice == nullptr)
    {
        UIUtils::showTip(*this, QString::fromLocal8Bit("请等待数据初始化完成！"));
        return;
    }

    if (mpDevice->haveInitTasks())
    {
        UIUtils::showTip(*mpDevice, QString::fromLocal8Bit("请等待此设备所有任务初化完成,再取消此任务！"));
        return;
    }

    MessageBoxDlg msgDlg(QString::fromLocal8Bit("是否确认关闭?") , MsgButton::Yes, MsgButton::No);
    msgDlg.exec();
    if (msgDlg.isConfirm() == MsgButton::Yes)
    {
        mCancel = true;

		Log::instance().AddLog(QString("[0]on_cancelButton_clicked"));
        CWaitDlg::waitForDoing(SingleApplication::instance()->mainWidget(), QString::fromLocal8Bit("正在取消下载任务中..."), [=]()
        {
            if (mTask.get() != nullptr)
            {
               mTask->cancel();
            }


        }, [this](bool bCancel)
        {
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
            emit cancelAll(this);
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
        });
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
}



