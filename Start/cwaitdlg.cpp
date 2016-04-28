#include "cwaitdlg.h"
#include <QDesktopWidget>
#include "ui_cwaitdlg.h"
#include <qdebug.h>
#include <QApplication>
#include <qnamespace.h>
#include "singleapllication.h"
#include "customEvent.h"

#define WIDTH_MAIN 1024
#define HEIGHT_MAIN 768

CWaitDlg *CWaitDlg::sCwaitdlg = nullptr;
std::recursive_mutex CWaitDlg::mtDlg;
std::set<CWaitDlg*> CWaitDlg::spDlg;

void CWaitDlg::on_cancelBtn_clicked()
{
	ui->cancelBtn->hide();
	ui->info->setText(QString::fromLocal8Bit("正在取消中..."));
	mFinishCall(true);
}

CWaitDlg &CWaitDlg::instanceCwaitdlg(QWidget *parent)
{
    if (nullptr == sCwaitdlg)
    {
        if (nullptr == parent)
        {
            parent = QApplication::desktop();
        }
        sCwaitdlg = new CWaitDlg(parent);
    }

    return *sCwaitdlg;
}
CWaitDlg* CWaitDlg::create(QWidget *parent, bool bHideCancel)
{
    if (parent == nullptr)
    {
        if (nullptr != spMainDlg)
        {
            parent = spMainDlg;
        }
        else{
            parent = new QDesktopWidget();
        }
        
    }
	return new CWaitDlg(parent, bHideCancel);;
}

void CWaitDlg::setShowMsg(const QString& msg)
{
    QCoreApplication::postEvent(sCwaitdlg, new TextEvent(msg));
}

QWidget* CWaitDlg::spMainDlg = nullptr;
void CWaitDlg::setMainDlg(QWidget *parent){
    spMainDlg = parent;
}

CWaitDlg::CWaitDlg(QWidget *parent, bool bHideCancel) :
    QDialog(parent),
    ui(new Ui::CWaitDlg)
{
    ui->setupUi(this);
   this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_SetWindowModality/*WA_TranslucentBackground*/);//setAttribute(Qt::WA_ShowModal, true);
	this->setAttribute(Qt::WA_TranslucentBackground);
    installEventFilter(this);

    ui->label->loadGif();
    mThread.reset();

    int nW = parent->width();
    int nH = parent->height();
    this->setGeometry(nW / 2 - geometry().width() / 2, nH / 2 - this->geometry().height() / 2,
                      this->geometry().width(), this->geometry().height());
    connect(this, SIGNAL(onFinished()), this, SLOT(dealFinished()));
	if (bHideCancel)
	{
		ui->cancelBtn->hide();
	}
	else
	{
		ui->cancelBtn->show();
		connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(on_cancelBtn_clicked()));
	}
}


CWaitDlg::~CWaitDlg()
{
    if (mThread.get() != nullptr)
    {
        mThread->wait();
    }
    delete ui;
}


void CWaitDlg::ShowWaitDlg(const QString& text)
{
    ui->info->setText(text);
    if (SingleApplication::instance() != nullptr &&
            SingleApplication::instance()->mainWidget() != nullptr && 
			this->mbHideCancel)
    {
        SingleApplication::instance()->mainWidget()->setEnabled(false);
    }
	//this->setWindowModality(Qt::ApplicationModal);
    this->exec();
}


void  CWaitDlg::HideWaitDlg()
{
	this->hide();
	if (SingleApplication::instance() != nullptr &&
		SingleApplication::instance()->mainWidget() != nullptr && 
		this->mbHideCancel)
	{
		SingleApplication::instance()->mainWidget()->setEnabled(true);
	}
    QCoreApplication::postEvent(this, new FinishEvent());
}

bool CWaitDlg::eventFilter(QObject *b, QEvent *e)
{
    if (this == b && dynamic_cast<FinishEvent *> (e) != nullptr)
    {
        this->accept();
        dealFinished();
        this->deleteLater();
//         if (SingleApplication::instance() != nullptr &&
//                 SingleApplication::instance()->mainWidget() != nullptr)
//         {
//             SingleApplication::instance()->mainWidget()->setEnabled(true);
//         }
    }
    else if (this == b && dynamic_cast<TextEvent *> (e) != nullptr)
    {
        this->ui->info->setText(((TextEvent *)e)->mText);
    }

    return true;
}

void CWaitDlg::dealFinished()
{
    mFinishCall(false);
}
