#include "ProductDialog.h"
#include "ui_ProductDialog.h"
#include "CommonFunc.h"
#include "log.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QApplication>

#include <vector>
#include <string>

#include "settings.h"
#include "Verify.h"



ProductDialog::ProductDialog(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::ProductDialog)
{
    ui->setupUi(this);
	backBtn->hide();
    ui->lineEdit_logo->setText(Settings::getItem(KEY_LOGO_FILE));
    ui->lineEdit_dldir->setText(Verify::downloadDir());
    ui->lineEdit_productName->setText(Settings::getItem(KEY_PRDUCT_NAME));
    ui->lineEdit_productAbout->setText(Settings::getItem(KEY_PRODUCT_INFO));
    ui->lineEdit_productAboutEn->setText(Settings::getItem(KEY_PRODUCT_INFO_EN));
	//QSettings *configIniRead = new QSettings("setting.ini", QSettings::IniFormat);
	//将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型  
	//QString ipResult = configIniRead->value("/AppInfo/AppVersion").toString();
	

    //ui->labelVersion->setText("V1.0");

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onOkBtn()));
    connect(ui->pushButton_dldir, SIGNAL(clicked()), this, SLOT(onEditDlDir()));
    connect(ui->pushButton_logo, SIGNAL(clicked()), this, SLOT(onEditLogoIcon()));
}

ProductDialog::~ProductDialog()
{
    delete ui;
}

void ProductDialog::onOkBtn()
{
    Settings::setItem(KEY_LOGO_FILE, ui->lineEdit_logo->text());
    Settings::setItem(KEY_DOWNLOAD_DIR, ui->lineEdit_dldir->text());
    Settings::setItem(KEY_PRDUCT_NAME, ui->lineEdit_productName->text());
    Settings::setItem(KEY_PRODUCT_INFO, ui->lineEdit_productAbout->text());
    Settings::setItem(KEY_PRODUCT_INFO_EN, ui->lineEdit_productAboutEn->text());
	this->close();
}
void ProductDialog::onEditDlDir(){
    auto dirName = QFileDialog::getExistingDirectory(this,
        QStringLiteral("下载文件夹"), Verify::downloadDir());
    ui->lineEdit_dldir->setText(dirName);
}

void ProductDialog::onEditLogoIcon(){
    auto fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), QApplication::applicationDirPath() + "/image", tr("Image Files (*.png)"));
    ui->lineEdit_logo->setText(fileName);
}

void ProductDialog::onEditProductName(){

}