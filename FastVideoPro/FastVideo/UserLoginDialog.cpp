#include "UserLoginDialog.h"
#include "ui_UserLoginDialog.h"


#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <QTime>
#include <vector>
#include <string>
#include <memory>
#include "uiutils.h"
#include "User.h"


#include "usermodifypassword.h"

UserLoginDialog::UserLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    setMouseTracking( true );
    ui->radioButtonCollector->setChecked(true);
}

UserLoginDialog::~UserLoginDialog()
{

    delete ui;
}

bool UserLoginDialog::isLogined(){
    return User::current().isLogined();
}

bool  UserLoginDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{

    return QDialog::nativeEvent(eventType, message, result);
}

void UserLoginDialog::on_pushButtonOK_clicked()
{
    if (!User::login(getSelectUserType(), ui->lineEdit_passwords->text()))
    {
        UIUtils::showTip(*ui->lineEdit_passwords, QStringLiteral("ÃÜÂë´íÎó"));
        return;
    }

    this->accept();
}

void UserLoginDialog::on_pushButtonPasswd_clicked()
{
    User::setUserType(getSelectUserType());
    usermodifypassword dlg(this);
    dlg.exec();
}

int UserLoginDialog::getSelectUserType(){
    if (ui->radioButtonCollector->isChecked())
    {
        return USER_TYPE_COLLECT;
    }
    else if (ui->radioButtonExport->isChecked())
    {
        return USER_TYPE_EXPORT;
    }
    else if (ui->radioButtonAdmin->isChecked()){
        return USER_TYPE_ADMIN;
    }
    
    return USER_TYPE_NULL;
}