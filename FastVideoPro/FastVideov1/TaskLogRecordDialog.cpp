#include "TaskLogRecordDialog.h"
#include "ui_TaskLogRecordDialog.h"
#include "CommonFunc.h"
#include "log.h"
#include "logdata.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QApplication>

#include <vector>
#include <string>
#include <QDateTime>




TaskLogRecordDialog::TaskLogRecordDialog(const QString& taskName, const QString& deviceIP, QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::TaskLogRecordDialog)
{
    ui->setupUi(this);
	backBtn->hide();
    
    ui->lineEdit_taskName->setText(taskName);
    ui->lineEdit_tasktime->setText(QDateTime::currentDateTime().toString(SQL_UTIL_TIME_FORMAT));
    ui->lineEdit_tasktime->setEnabled(false);
    ui->lineEdit_taskDeviceIP->setText(deviceIP);
    ui->comboBox_taskDir->addItem(QStringLiteral("案件一"));
    ui->comboBox_taskDir->addItem(QStringLiteral("案件二"));
    ui->comboBox_taskDir->addItem(QStringLiteral("案件三"));
    ui->comboBox_taskDir->addItem(QStringLiteral("案件四"));
    ui->comboBox_taskDir->addItem(QStringLiteral("案件五"));
    ui->comboBox_taskDir->setCurrentText("");
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onOkBtn()));

}

TaskLogRecordDialog::~TaskLogRecordDialog()
{
    delete ui;
}
QString TaskLogRecordDialog::caseDir(){
    return ui->comboBox_taskDir->currentText();
}
void TaskLogRecordDialog::onOkBtn()
{
    mTaskLog.mName = ui->lineEdit_taskName->text();
    mTaskLog.mAddress = ui->lineEdit_taskAddress->text();
    mTaskLog.mDesc = ui->lineEdit_taskDescript->text();
    mTaskLog.mDeviceIP = ui->lineEdit_taskDeviceIP->text();

    mTaskLog.mMen = ui->lineEdit_taskCollectMan->text();
    mTaskLog.mText = ui->lineEdit_taskText->text();
    mTaskLog.mTime = ui->lineEdit_tasktime->text();
    
    mTaskLog.save();
	this->close();
}
