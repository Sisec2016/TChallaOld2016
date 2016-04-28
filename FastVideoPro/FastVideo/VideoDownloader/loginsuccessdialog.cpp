#include "loginsuccessdialog.h"
#include "ui_loginsuccessdialog.h"
#include "qss.h"

loginSuccessDialog::loginSuccessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginSuccessDialog)
{
    ui->setupUi(this);

	QIcon icon;
	icon.addFile(QString::fromUtf8(":/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->closeButton->setIcon(icon);
	ui->closeButton->setIconSize(QSize(45, 45));
	ui->closeButton->setText("");
	ui->closeButton->setStyleSheet(transparentBtn_StyleSheet);
	//connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
}

loginSuccessDialog::~loginSuccessDialog()
{
    delete ui;
}
