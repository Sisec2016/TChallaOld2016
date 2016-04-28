#include "HelpDialog.h"
#include "ui_HelpDialog.h"
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


HelpDialog::HelpDialog(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
	backBtn->hide();

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onOkBtn()));
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::onOkBtn()
{
	this->close();
}