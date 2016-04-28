#include "filemanagerdlg.h"
#include "ui_filemanagerdlg.h"
#include "Verify.h"

FileManagerDlg::FileManagerDlg(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::FileManagerDlg)
{
    ui->setupUi(this);

	ui->sourcefileWidget->setFileCheckedModel(true);
    ui->sourcefileWidget->setMyRootPath(Verify::downloadDirPath());
    ui->sourcePath_label->setText(Verify::downloadDirPath());

	ui->diskBtn->setVisible(false);
	ui->shareBtn->setVisible(false);
	ui->ftpBtn->setVisible(false);
	ui->treeView->setVisible(false);
	ui->deleteBtn->setVisible(false);
	ui->fileplayBtn->setVisible(false);

}

FileManagerDlg::~FileManagerDlg()
{
    delete ui;
}

void FileManagerDlg::changeEvent(QEvent *e)
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

