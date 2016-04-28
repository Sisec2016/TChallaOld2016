#include "usermodifypassword.h"
#include "ui_usermodifypassword.h"
#include <QMessageBox>
#include "User.h"

usermodifypassword::usermodifypassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usermodifypassword)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    setMouseTracking( true );
}

usermodifypassword::~usermodifypassword()
{
    delete ui;
}

void usermodifypassword::on_pushButtonOK_clicked()
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

    if (!User::current().isCollectPasswords(oldPasswd)){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("密码不对！"));
        return;
    }

    User::current().setPassword(newPasswd);
    QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("修改密码成功！"));
    this->accept();
}

void usermodifypassword::on_pushButton_cancel_clicked()
{
    this->close();
}
