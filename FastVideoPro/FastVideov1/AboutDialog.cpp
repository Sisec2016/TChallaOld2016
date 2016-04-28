#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "CommonFunc.h"
#include "log.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <vector>
#include <string>

#include "settings.h"
#include "Verify.h"
#pragma comment(lib, "version.lib")
QString GetFileVersion()
{
    QString version = Settings::getItem(KEY_CURVERSION);
    if (version.isEmpty())
    {
        version = Verify::version();
    }

    return QString("V") + version;
}

AboutDialog::AboutDialog(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
	backBtn->hide();

	//QSettings *configIniRead = new QSettings("setting.ini", QSettings::IniFormat);
	//将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型  
	//QString ipResult = configIniRead->value("/AppInfo/AppVersion").toString();
	

	QString stVersion = GetFileVersion();// "V1.0";
	ui->labelVersion->setText(stVersion);
    if (!Settings::getItem(KEY_PRODUCT_INFO).isEmpty()){
        ui->label_2->setText(Settings::getItem(KEY_PRODUCT_INFO));
    }
    if (!Settings::getItem(KEY_PRODUCT_INFO_EN).isEmpty()){
        ui->label_3->setText(Settings::getItem(KEY_PRODUCT_INFO_EN));
    }
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onOkBtn()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::onOkBtn()
{
	this->close();
}