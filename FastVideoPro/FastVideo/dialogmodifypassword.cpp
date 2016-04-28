#include "dialogmodifypassword.h"
#include "ui_dialogmodifypassword.h"
#include "safedisk.h"
#include <QMessageBox>

DialogModifyPassword::DialogModifyPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModifyPassword)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    setMouseTracking( true );
}

DialogModifyPassword::~DialogModifyPassword()
{
    delete ui;
}

void DialogModifyPassword::on_pushButtonOK_clicked()
{
    QString oldPasswd(ui->lineEditOldPasswords->text());
    QString newPasswd(ui->lineEdit_newPasswords->text());
    if (newPasswd.isEmpty() || oldPasswd.isEmpty()){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("输入的密码不能为空！"));
        return;
    }

    if (newPasswd != ui->lineEdit_newPassword2->text()){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("两次输入的密码不一致！"));
        return;
    }

    if (!SafeDisk::instance().verifyPasswd(oldPasswd)){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("密码不对！"));
        return;
    }

    if (!SafeDisk::instance().modifyPasswd(newPasswd)){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("修改密码失败！"));
        return;
    }

    QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("修改密码成功！"));
    this->accept();
}

void DialogModifyPassword::on_pushButton_cancel_clicked()
{
    this->close();
}
