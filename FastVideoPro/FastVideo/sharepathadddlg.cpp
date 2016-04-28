#include "sharepathadddlg.h"
#include "ui_sharepathadddlg.h"
#include <QMessageBox>

SharePathAddDlg::SharePathAddDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SharePathAddDlg)
{
    ui->setupUi(this);

	ui->TestConnBtn->hide();

    connect(ui->OKBtn, SIGNAL(clicked()), this, SLOT(onOKBtn()));
    connect(ui->CancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtn()));
    connect(ui->TestConnBtn, SIGNAL(clicked()), this, SLOT(onTestConnBtn()));
}

SharePathAddDlg::~SharePathAddDlg()
{
    delete ui;
}

void SharePathAddDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SharePathAddDlg::onOKBtn()
{
    m_sharePath.strName = ui->name_lineEdit->text().trimmed();
    m_sharePath.strSharePath = ui->sharePath_lineEdit->text().trimmed();
    m_sharePath.strUser = ui->user_lineEdit->text().trimmed();
    m_sharePath.strPwd = ui->pwd_lineEdit->text().trimmed();

    if(m_sharePath.strName.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请输入名称！"));
        return;
    }

    if(m_sharePath.strSharePath.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请输入共享路径目录！"));
        return;
    }


    this->accept();
}

void SharePathAddDlg::setCurSharePath(T_SharePath& tSharePath )
{
    ui->name_lineEdit->setText(tSharePath.strName);
    ui->sharePath_lineEdit->setText(tSharePath.strSharePath);
    ui->user_lineEdit->setText(tSharePath.strUser);
    ui->pwd_lineEdit->setText(tSharePath.strPwd);
}


void SharePathAddDlg::onCancelBtn()
{
    this->reject();
}

void SharePathAddDlg::onTestConnBtn()
{
    m_sharePath.strSharePath = ui->sharePath_lineEdit->text().trimmed();

    if(m_sharePath.strSharePath.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请输入共享路径目录！"));
        return;
    }

    m_sharePath.strUser = ui->user_lineEdit->text().trimmed();
    m_sharePath.strPwd = ui->pwd_lineEdit->text().trimmed();

    //add by liyongxing
	//??????????
}
