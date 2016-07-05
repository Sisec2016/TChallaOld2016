#ifndef CWAITDLG_H
#define CWAITDLG_H

#include <QDialog>

#include <memory>
#include <thread>
#include <mutex>
#include <QThread>
#include <functional>
#include <set>
#include <qdebug.h>
#include <memory>

namespace Ui
{
    class CWaitDlg;
}



template<class Fn>
class DoingThread : public QThread
{
    Fn mF;
public:
    DoingThread(Fn f) : mF(f)
    {

    }

    virtual void run()
    {
        mF();
    }
};

template<class Fn>
std::shared_ptr < QThread > CreateFnThread(Fn f)
{
    return std::shared_ptr< QThread >(new DoingThread<Fn>(f));
}

class CWaitDlg : public QDialog
{
    Q_OBJECT
    static CWaitDlg *sCwaitdlg;
    static QWidget* spMainDlg;
    std::function<void (bool)> mFinishCall;
    std::shared_ptr <QThread> mThread;
	bool mbHideCancel;
    std::shared_ptr<bool> mbCancel;
public:
    static void setMainDlg(QWidget *parent);
	explicit CWaitDlg(QWidget *parent = 0, bool bHideCancel=true);
    ~CWaitDlg();
    static std::recursive_mutex mtDlg;
    static std::set<CWaitDlg*> spDlg;
public:
    template<class Fn>
    static void waitForDoing(QWidget *parent, QString s, Fn F, std::function<void(bool)> OFF, std::shared_ptr<bool> bCancel = std::shared_ptr<bool>())
    {
        CWaitDlg* pDlg = CWaitDlg::create(parent, !bCancel);
        pDlg->mbCancel = bCancel;
        pDlg->mbHideCancel = !bCancel;
        pDlg->enableMainWidget(false);
        sCwaitdlg = pDlg;
        spDlg.insert(pDlg);
        pDlg->mFinishCall = OFF;
        pDlg->mThread = CreateFnThread([=]()
        {
            F();
            QThread::msleep(100);
            pDlg->HideWaitDlg();
        });
        pDlg->mThread->start();
        pDlg->ShowWaitDlg(s);
		pDlg->setEnabled(true);
    }

    static CWaitDlg &instanceCwaitdlg(QWidget *parent = 0);
	static CWaitDlg* create(QWidget *parent, bool bHideCancel = true);
    static void setShowMsg(const QString& msg);
    bool eventFilter(QObject *, QEvent *);
signals:
    void onFinished();
private slots:
	void dealFinished();
	void on_cancelBtn_clicked();

public:
    void ShowWaitDlg(const QString& text);
    void HideWaitDlg();
private:
    void enableMainWidget(bool enable);
private:
    Ui::CWaitDlg *ui;
};

#endif // CWAITDLG_H
