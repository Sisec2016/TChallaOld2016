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
    MyBaseDialog(parent),
    ui(new Ui::IPConfigSucessDialog)
{
    ui->setupUi(this);
	backBtn->hide();
    ui->label_IP->setText(ip);
    ui->label_submask->setText(subMask);
    ui->label_netgate->setText(netGate);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onOkBtn()));
}

IPConfigSucessDialog::~IPConfigSucessDialog()
{
    delete ui;
}

void IPConfigSucessDialog::onOkBtn()
{
    
	this->close();
}
