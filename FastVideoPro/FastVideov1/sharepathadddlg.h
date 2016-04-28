#ifndef SHAREPATHADDDLG_H
#define SHAREPATHADDDLG_H

#include <QDialog>

namespace Ui {
    class SharePathAddDlg;
}

struct T_SharePath {
    QString strName;
    QString strSharePath;
    QString strUser;
    QString strPwd;
};
class SharePathAddDlg : public QDialog {
    Q_OBJECT
public:
    SharePathAddDlg(QWidget *parent = 0);
    ~SharePathAddDlg();
public:
    void getSharePath(T_SharePath& tSharePath ){ tSharePath = m_sharePath;}
    void setCurSharePath(T_SharePath& tSharePath );
protected:
    void changeEvent(QEvent *e);

protected slots:
    void onOKBtn();
    void onCancelBtn();
    void onTestConnBtn();

private:
    Ui::SharePathAddDlg *ui;

private:
    T_SharePath m_sharePath;
};

#endif // SHAREPATHADDDLG_H
