#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    auto md5Byte = QCryptographicHash::hash(QString("dwsfdajfaiierueiur%1adkfjaofdlasdfl").arg(ui->lineEditApply->text()).toLatin1(), QCryptographicHash::Md5);
    QString md5(md5Byte.toHex());
    ui->lineEditActivity->setText(md5);
}
