#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QDialog>
#include <QThread>
#include "mybasedialog.h"
#include "logdata.h"


namespace Ui {
    class logManagerDlg;
}

#define LOGNUM_OF_ONE_PAGE 20


class logManagerDlg : public MyBaseDialog {
    Q_OBJECT
public:
    logManagerDlg(QWidget *parent = 0);
    ~logManagerDlg();
	friend class LogSearchThread;
protected:
    void changeEvent(QEvent *e);
	int conVertTime(int iyear, int imon, int iday, int ihour, int imin, int isec);
	void clearLogList();
	void showLogList(int pageNum);
private slots:
    void onSearchClicked();
    void onOutputClicked();
	void onPastPageClicked();
	void onNextPageClicked();
    void onTaskLogClicked();
protected:
    Ui::logManagerDlg *ui;
	int m_curpage;
    std::vector< std::shared_ptr<Logdata> > m_logList;

};

#endif // LOGMANAGER_H
