#include "timedialog.h"
#include "ui_timedialog.h"
#include <qdebug.h>
#include "screenadaption.h"

timeDialog::timeDialog(QWidget *parent) :
    NoFlameDlg(parent),
    ui(new Ui::timeDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    mpCurrent = nullptr;
    nextLabel();
    ScreenAdaption::instance().showInCenter(this);
}

timeDialog::~timeDialog()
{
    delete ui;
}


void timeDialog::updateUI()
{
    ui->lbHourLeft->setText(QString::number(mTime.hour() / 10));
    ui->lbHourRight->setText(QString::number(mTime.hour() % 10));
    ui->lbMinuteLeft->setText(QString::number(mTime.minute() / 10));
    ui->lbMinuteRight->setText(QString::number(mTime.minute() % 10));
}

void timeDialog::nextLabel()
{
    if (nullptr != mpCurrent)
    {
        mpCurrent->setStyleSheet("QLabel{font-size: 70px;}");
    }
    if (mpCurrent == ui->lbHourLeft)
    {
        mpCurrent = ui->lbHourRight;
    }
    else if (mpCurrent == ui->lbHourRight)
    {
        mpCurrent = ui->lbMinuteLeft;
    }
    else if (mpCurrent == ui->lbMinuteLeft)
    {
        mpCurrent = ui->lbMinuteRight;
    }
    else
    {
        mpCurrent = ui->lbHourLeft;
    }

    bool bEnable = !(mpCurrent == ui->lbHourLeft || mpCurrent == ui->lbMinuteLeft);
    ui->pushButton_eight->setEnabled(bEnable);
    ui->pushButton_nine->setEnabled(bEnable);
    ui->pushButton_seven->setEnabled(bEnable);
    ui->pushButton_six->setEnabled(bEnable);

    bEnable = !(mpCurrent == ui->lbHourLeft);
    ui->pushButton_five->setEnabled(bEnable);
    ui->pushButton_four->setEnabled(bEnable);
    ui->pushButton_three->setEnabled(bEnable);

    mpCurrent->setStyleSheet("QLabel{font-size: 75px;}");
}

void timeDialog::setTime(const QTime& t)
{    
    mTime = t;
    updateUI();
}


void timeDialog::focusOutEvent(QFocusEvent *e)
{
    QDialog::focusOutEvent(e);
    this->deleteLater();

}

bool timeDialog::event(QEvent *e)
{

    qDebug()<<(int)e->type();
    return QDialog::event(e);
}

void timeDialog::onPush(int number)
{
    if (mpCurrent == ui->lbHourLeft)
    {
        mTime.setHMS(10*number + mTime.hour() % 10, mTime.minute(), 0);
    }
    else if (mpCurrent == ui->lbHourRight)
    {
        mTime.setHMS(mTime.hour()/10 * 10 + number, mTime.minute(), 0);
    }
    else if (mpCurrent == ui->lbMinuteLeft)
    {
        mTime.setHMS(mTime.hour(), 10*number + mTime.minute() % 10, 0);
    }
    else
    {
        mTime.setHMS(mTime.hour(), mTime.minute()/10 * 10 + number, 0);
    }
    updateUI();
    nextLabel();
}


void timeDialog::on_pushButton_seven_clicked()
{
    onPush(7);
}

void timeDialog::on_pushButton_eight_clicked()
{
    onPush(8);
}

void timeDialog::on_pushButton_six_clicked()
{
    onPush(6);
}

void timeDialog::on_pushButton_nine_clicked()
{
    onPush(9);
}

void timeDialog::on_pushButton_four_clicked()
{
    onPush(4);
}

void timeDialog::on_pushButton_five_clicked()
{
    onPush(5);
}

void timeDialog::on_pushButton_one_clicked()
{
    onPush(1);
}

void timeDialog::on_pushButton_two_clicked()
{
    onPush(2);
}

void timeDialog::on_pushButton_three_clicked()
{
    onPush(3);
}

void timeDialog::on_pushButton_zero_clicked()
{
    onPush(0);
}

void timeDialog::on_pushButton_conon_clicked()
{
    mpCurrent->setStyleSheet("QLabel{font-size: 70px;}");
    mpCurrent = ui->lbHourRight;
    nextLabel();
}

void timeDialog::on_pushButton_reset_clicked()
{
    mTime.setHMS(0, 0, 0);
    updateUI();
    mpCurrent->setStyleSheet("QLabel{font-size: 70px;}");
    mpCurrent = nullptr;
    nextLabel();
}

void timeDialog::on_pushButton_save_clicked()
{
    this->close();
}
