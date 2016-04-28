#include "progressdlg.h"
#include "ui_progressdlg.h"

ProgressDlg::ProgressDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDlg)
{
    ui->setupUi(this);
}

ProgressDlg::~ProgressDlg()
{
    delete ui;
}

void ProgressDlg::changeEvent(QEvent *e)
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
