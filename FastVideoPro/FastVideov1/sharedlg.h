#ifndef SHAREDLG_H
#define SHAREDLG_H

#include <QDialog>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"

#include"sharepathadddlg.h"

#include "ShareModuleApi.h"

class QTableWidgetItem;

namespace Ui {
    class ShareDlg;
}

class ShareDlg : public MyBaseDialog {
    Q_OBJECT
public:
    ShareDlg(QWidget *parent = 0);
    ~ShareDlg();

	void PercentCallback2(unsigned int iHandle, int iCurPercent, int iTotalPercent, int iType, void *pParam);
protected slots:
    void onAddSharePathBtn();
    void onModifySharePathBtn();
    void onDelSharePathBtn();
    void onOutputShareBtn();
    void onItemDoubleClicked ( QTableWidgetItem * item );
    void onItemClicked ( QTableWidgetItem * item );
	void onProgressDialogCancel();
	void onuUpdateProgressBar(int iCurPercent, int iTotalPercent);
	void onCopyError(T_ErrInfo *pErrorInfo);
signals:
	void updateProgressBar(int iCurPercent, int iTotalPercent);
	void copyError(T_ErrInfo *pErrorInfo);
protected:
    void changeEvent(QEvent *e);
    void closeEvent (QCloseEvent * e );
private:
    void readSharePathListFile();
    void writeSharePathListFile();
    void addToTableWidget(T_SharePath *pSharePath);
private:
    Ui::ShareDlg *ui;
private:
     QList<T_SharePath> m_listSharePath;
	 bool m_bLogin;
	T_SharePath m_curSharePath;

	 QProgressDialog *m_progressDialog;
	 unsigned int m_iHandle;//¿½±´½ø³Ì¾ä±ú
	 bool m_bQuestion;
	 bool m_bCover;

	 QWaitCondition m_waitCondition;
	 QMutex m_mutex;
};

#endif // SHAREDLG_H
