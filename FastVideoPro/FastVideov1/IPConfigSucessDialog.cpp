#include "IPConfigSucessDialog.h"
#include "ui_IPConfigSucessDialog.h"
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



IPConfigSucessDialog::IPConfigSucessDialog(const QString& ip, const QString& subMask, const QString& netGate, QWidget *parent) :
MyBaseDialog(parent), m_bMannual(false),
    ui(new Ui::IPConfigSucessDialog)
{
    ui->setupUi(this);
	backBtn->hide();
    ui->label_IP->setText(ip);
    ui->label_submask->setText(subMask);
    ui->label_netgate->setText(netGate);

    connect(ui->pushButtonConfig, SIGNAL(clicked()), this, SLOT(onOkBtn()));
    connect(ui->pushButtonConfigMannual, SIGNAL(clicked()), this, SLOT(onMannualConfigBtn()));
}

IPConfigSucessDialog::~IPConfigSucessDialog()
{
    delete ui;
}

void IPConfigSucessDialog::onOkBtn()
{
	this->close();
}

void IPConfigSucessDialog::onMannualConfigBtn(){
    m_bMannual = true;
    this->close();
}