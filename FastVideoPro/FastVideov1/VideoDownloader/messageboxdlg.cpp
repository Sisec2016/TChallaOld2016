#include "messageboxdlg.h"
#include "ui_messageboxdlg.h"
#include <QPainter>
#include <QFontMetrics>
#include <qDebug>
#include "screenadaption.h"

MessageBoxDlg::MessageBoxDlg(const QString& mMessage, MsgButton buttons, MsgButton defaultButton, const QString& sTitle, QWidget *parent) :
    QDialog(parent),
    mMessage(mMessage),
    mConfirm(No),
    ui(new Ui::MessageBoxDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btnCancel->setVisible(false);
    if(defaultButton != NoButton)
    {
        ui->btnOK->setGeometry(35,ui->btnOK->geometry().y(),83,34);
        ui->btnCancel->setVisible(true);
    }

    ui->lblTitle->setAlignment(Qt::AlignVCenter);
    ui->lblTitle->setText(sTitle.trimmed());
    ui->lblTitle->adjustSize();

    ui->lblMessage->setAlignment(Qt::AlignVCenter);
    ui->lblMessage->setText(mMessage.trimmed());
    ui->lblMessage->adjustSize();
    if(ui->lblMessage->width()>600)
    {
       ui->lblMessage->setGeometry(60, 38, 600,60);
    }
    else
    {
        ui->lblMessage->setGeometry(60,38,ui->lblMessage->width(),60);
    }
    if(ui->lblMessage->width() > 160)
    {
        int iAddWidth = ui->lblMessage->width() - 160;
        ui->btnOK->setGeometry(ui->btnOK->geometry().x() + iAddWidth/2 , ui->btnOK->geometry().y(),83,34);
//        ui->closeButton->setGeometry(ui->closeButton->geometry().x() + iAddWidth , ui->closeButton->geometry().y(),24,24);
        if(defaultButton != NoButton)
        {
            ui->btnCancel->setGeometry(ui->btnCancel->geometry().x() + iAddWidth/2 , ui->btnCancel->geometry().y(),83,34);
        }

        this->setGeometry(0,0,ui->widget->geometry().width() + iAddWidth,ui->widget->geometry().height());
        ui->widget->setGeometry(0,0,ui->widget->geometry().width() + iAddWidth,ui->widget->geometry().height());
    }
//    ui->closeButton->hide();
    ScreenAdaption::instance().showInCenter(this);
}

MessageBoxDlg::~MessageBoxDlg()
{
    delete ui;
}

void MessageBoxDlg::on_closeButton_clicked()
{
    this->close();
}

void MessageBoxDlg::on_btnOK_clicked()
{
    mConfirm = Yes;
    this->close();
}

void MessageBoxDlg::on_btnCancel_clicked()
{
    this->close();
}

void MessageBoxDlg::setBtnText(const QString& sYes, const QString& sNo){
    ui->btnOK->setText(sYes);
    ui->btnCancel->setText(sNo);
}