#include "ipadddlg.h"
#include "ui_ipadddlg.h"

IPAddDlg::IPAddDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IPAddDlg)
{
    ui->setupUi(this);
}

IPAddDlg::~IPAddDlg()
{
    delete ui;
}

void IPAddDlg::changeEvent(QEvent *e)
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
