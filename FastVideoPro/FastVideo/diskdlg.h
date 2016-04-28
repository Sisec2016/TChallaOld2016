#ifndef DISKDLG_H
#define DISKDLG_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>
#include <QProcess>
#include "DiskModuleApi.h"

#include "MyBaseDialog.h"

namespace Ui {
    class DiskDlg;
}

class DiskDlg : public MyBaseDialog {
    Q_OBJECT
public:
    DiskDlg(QWidget *parent = 0);
    ~DiskDlg();

	void PercentCallback2(unsigned int iHandle, int iCurPercent, int iTotalPercent, int iType, void *pParam);
protected slots:
    void onDiskDirectoryBtn();
    void onDiskOutputBtn();
	void onProgressDialogCancel();
	void onuUpdateProgressBar(int iCurPercent, int iTotalPercent);
	void onCopyError(T_ErrInfo *pErrorInfo);
    void readOutput();

signals:
	void updateProgressBar(int iCurPercent, int iTotalPercent);
	void copyError(T_ErrInfo *pErrorInfo);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::DiskDlg *ui;
private:
    QString m_diskDirectoryName;
	QProgressDialog *m_progressDialog;
	unsigned int m_iHandle;//¿½±´½ø³Ì¾ä±ú
	bool m_bQuestion;
	bool m_bCover;
    QProcess* cmd;
	QWaitCondition m_waitCondition;
	QMutex m_mutex;
};

#endif // DISKDLG_H
