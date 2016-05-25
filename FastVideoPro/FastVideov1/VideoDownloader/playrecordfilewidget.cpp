#include "playrecordfilewidget.h"
#include "ui_playrecordfilewidget.h"
#include <QThread>
#include <QtCore>
#include "screenadaption.h"

PlayRecordFilewidget::PlayRecordFilewidget(RecordFile &f, std::shared_ptr<videoserver> pServer, QWidget *parent) :
////<<<<<<<<<<<modify window drag by zhangyaofa 2016/5/25
    PlayFlameDlg(parent),
/////////////////////////////////////////////////////
//  NoFlameDlg(parent),
////>>>>>>>>>>>modify end
    mpService(pServer),
    mFile(f),
    ui(new Ui::PlayRecordFilewidget)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->btnPlay->setVisible(true);
    ui->btnStop->setVisible(false);

    connect(&mSliderTimer, SIGNAL(timeout()), this, SLOT(sliderTimeout()));
    timePlay= new QTimer(this);
    connect(timePlay,SIGNAL(timeout()),this,SLOT(initplay()));
    timePlay->start(500);

    ui->labelName->setText(mpService->getChannelName(f.channel));

    ScreenAdaption::instance().showInCenter(this);
}

void PlayRecordFilewidget::initplay()
{
    ui->btnPlay->setVisible(false);
    ui->btnStop->setVisible(true);
    this->ui->Playtime->setEnabled(true);
    mpService->PlayBackByRecordFile(mFile, getPlayWidget(), m_playfile);
    mSliderTimer.start(500);
    if (timePlay->isActive() )
    {
        timePlay->stop();
    }
}

PlayRecordFilewidget::~PlayRecordFilewidget()
{
    if (mSliderTimer.isActive())
    {
        mSliderTimer.stop();
    }
    if (timePlay->isActive() )
    {
        timePlay->stop();
    }
    delete ui;
}

QWidget& PlayRecordFilewidget::getPlayWidget()
{
    return *ui->mdiArea;
}


void PlayRecordFilewidget::on_CloseButton_clicked()
{   
    if (mSliderTimer.isActive() )
    {
        mSliderTimer.stop();
    }
    mpService->StopPlayBack(m_playfile, 0);
    this->close();
}

void PlayRecordFilewidget::on_btnPlay_clicked()
{
    initplay();
}

void PlayRecordFilewidget::on_btnStop_clicked()
{
    if (mSliderTimer.isActive() )
    {
        mSliderTimer.stop();
    }
    ui->btnPlay->setVisible(true);
    ui->btnStop->setVisible(false);
    this->ui->Playtime->setEnabled(false);
    mpService->StopPlayBack(m_playfile, 0);
}


void PlayRecordFilewidget::on_Playtime_sliderReleased()
{
    mpService->SetPlayBack(m_playfile, this->ui->Playtime->value());
    mSliderTimer.start();
}

void PlayRecordFilewidget::sliderTimeout()
{
    qint32 pos = 0;
    if (mpService->getPlayBackPos(m_playfile, pos))
    {
        ui->Playtime->setValue(pos);
        qDebug()<<QString("PlayPos:%1").arg(pos);
        if (pos == 100)
        {
            on_btnStop_clicked();
        }
    }

}

void PlayRecordFilewidget::on_Playtime_sliderPressed()
{
    if (mSliderTimer.isActive() )
    {
        mSliderTimer.stop();
    }
}
