#include "dialogdownloadfiles.h"
#include "ui_dialogdownloadfiles.h"
#include "cwaitdlg.h"
#include "singleapllication.h"
#include "formdownloadfile.h"
#include "uiutils.h"
#include "screenadaption.h"
#include "qss.h"

DialogDownloadFiles::DialogDownloadFiles(std::shared_ptr<videoserver> pServer, std::vector<RecordFile>& files, QWidget *parent) :
    NoFlameDlg(parent),
    ui(new Ui::DialogDownloadFiles),
    mvcFiles(files),
    mpServer(pServer),
    mIndex(0)
{
    ui->setupUi(this);
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->closeButton->setIcon(icon);
	ui->closeButton->setIconSize(QSize(32, 32));
	ui->closeButton->setText("");
	ui->closeButton->setStyleSheet(transparentBtn_StyleSheet);
	connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));

    ui->listViewFiles->init(ui->widgetHeader);
    ScreenAdaption::instance().showInCenter(this);
    QCoreApplication::postEvent(this, new AddDownloadRowEvent());
    ui->checkBoxAll->setChecked(true);
    CWaitDlg::waitForDoing(SingleApplication::instance()->mainWidget(), QString::fromLocal8Bit("正在加载数据中..."), [this]()
    {
        while (mIndex < mvcFiles.size())
        {
            QThread::msleep(200);
        }

    }, [this](bool bCancel){});
}

DialogDownloadFiles::~DialogDownloadFiles()
{
    delete ui;
}

void DialogDownloadFiles::getSelectedFiles(std::vector<RecordFile*>& files)
{
    files.clear();
    for (int i = 0; i < ui->listViewFiles->itemSize(); i++)
    {
        FormDownloadFile* p = dynamic_cast<FormDownloadFile*> (ui->listViewFiles->getItem(i));
        if (p != nullptr && p->isChecked())
        {
            files.push_back(p->getData());
        }
    }
}

void DialogDownloadFiles::customEvent(QEvent* event)
{

    AddDownloadRowEvent* edownload = dynamic_cast<AddDownloadRowEvent *> (event);
    if (edownload != NULL)
    {
        if (mIndex < mvcFiles.size())
        {
            FormDownloadFile* p = new FormDownloadFile(this);
            p->init(&mvcFiles[mIndex], mpServer);
            p->setChecked(true);
            ui->listViewFiles->addWidgetItem(p);
            mIndex++;
            QCoreApplication::postEvent(this, new AddDownloadRowEvent());
        }

    }
}

void DialogDownloadFiles::on_closeButton_clicked()
{
    this->reject();
}

void DialogDownloadFiles::on_pushButtonConnect_clicked()
{
    std::vector<RecordFile *> Files;
    getSelectedFiles(Files);
    if (Files.size() > 0)
    {
        this->accept();
    }
    else
    {
        UIUtils::showTip(*ui->widgetFiles, QString::fromLocal8Bit("请至少选择一个文件下载！"));
    }
}

void DialogDownloadFiles::on_checkBoxAll_toggled(bool checked)
{
    for (int i = 0; i < ui->listViewFiles->itemSize(); i++)
    {
        FormDownloadFile* p = dynamic_cast<FormDownloadFile*> (ui->listViewFiles->getItem(i));
        if (p != nullptr)
        {
            p->setChecked(checked);
        }

    }
}
