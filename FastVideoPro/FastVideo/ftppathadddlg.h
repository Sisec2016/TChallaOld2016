#ifndef FTPPATHADDDLG_H
#define FTPPATHADDDLG_H

#include <QDialog>

namespace Ui {
    class FTPPathAddDlg;
}

struct T_FTPPath{
    QString strFtpHost;
    QString strFtpPort;
    QString strUser;
    QString strPwd;
};

class FTPPathAddDlg : public QDialog {
    Q_OBJECT
public:
    FTPPathAddDlg(QWidget *parent = 0);
    ~FTPPathAddDlg();
public:
    void getFTPPath(T_FTPPath& tFTPPath ){ tFTPPath = m_FTPPath;}
    void setCurFTPPath(T_FTPPath& tFTPPath );
    void setFTPListPath(QList<T_FTPPath> *plistFTPPath ){ m_plistFTPPath = plistFTPPath;}
protected:
    void changeEvent(QEvent *e);

protected slots:
    void onOKBtn();
    void onCancelBtn();

private:
    Ui::FTPPathAddDlg *ui;
private:
     T_FTPPath m_FTPPath;
     QList<T_FTPPath> *m_plistFTPPath;
};

#endif // FTPPATHADDDLG_H
