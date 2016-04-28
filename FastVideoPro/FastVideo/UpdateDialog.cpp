#include "UpdateDialog.h"
#include "ui_UpdateDialog.h"
#include "CommonFunc.h"
#include "log.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

#include <vector>
#include <string>

#include "settings.h"

#pragma comment(lib, "version.lib")


UpdateDialog::UpdateDialog(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
	backBtn->hide();

	//QSettings *configIniRead = new QSettings("setting.ini", QSettings::IniFormat);
	//将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型  
	//QString ipResult = configIniRead->value("/AppInfo/AppVersion").toString();
	

	QString stVersion;// "V1.0";
	ui->labelVersion->setText(stVersion);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onOkBtn()));
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::onOkBtn()
{
	this->close();
}