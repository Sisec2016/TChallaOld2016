#ifndef UserLoginDialog_H
#define UserLoginDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>


namespace Ui {
    class UserLoginDialog;
}

class UserLoginDialog : public QDialog {
    Q_OBJECT
public:
    UserLoginDialog(QWidget *parent = 0);
    ~UserLoginDialog();
    bool isLogined();
signals:

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonPasswd_clicked();

private:
    Ui::UserLoginDialog *ui;
private:
    int getSelectUserType();

};

#endif // DISKDLG_H
