#include "formdownloadfile.h"
#include "ui_formdownloadfile.h"
#include "playrecordfilewidget.h"

FormDownloadFile::FormDownloadFile(QWidget *parent) :
    ListViewItem(parent),
    ui(new Ui::FormDownloadFile),
    mpFile(nullptr),
    mpServer(nullptr)
{
    ui->setupUi(this);
}

FormDownloadFile::~FormDownloadFile()
{
    delete ui;
}

void FormDownloadFile::init(RecordFile* pFile, std::shared_ptr<videoserver> pServer)
{
    if (nullptr != pFile && pServer)
    {
        mpFile = pFile;
        mpServer = pServer;
        ui->labelBeginTime->setText(QDateTime::fromTime_t(mpFile->beginTime).toString(TIME_FORMAT));
        ui->labelChannel->setText(pServer->getChannelName(mpFile->channel));
        ui->labelEndTime->setText(QDateTime::fromTime_t(mpFile->endTime).toString(TIME_FORMAT));
        ui->labelName->setText(QString::fromLocal8Bit(mpFile->name.c_str()));
		ui->labelSize->setText(QString::number(mpFile->size / 1024) + " KB");

    }
}
void FormDownloadFile::setChecked(bool b)
{
    ui->checkBox->setChecked(b);
}

bool FormDownloadFile::isChecked()
{
    return ui->checkBox->isChecked();
}

void FormDownloadFile::on_pushButtonPlay_clicked()
{
    if (nullptr != mpFile && nullptr != mpServer)
    {
        PlayRecordFilewidget playrecrodfile(*mpFile, mpServer);
        playrecrodfile.exec();
    }
}
