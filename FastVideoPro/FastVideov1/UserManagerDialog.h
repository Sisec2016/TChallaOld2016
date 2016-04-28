#ifndef UserManagerDialog_H
#define UserManagerDialog_H

#include <QDialog>

namespace Ui {
class UserManagerDialog;
}

class UserManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagerDialog(QWidget *parent = 0);
    ~UserManagerDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::UserManagerDialog *ui;
private:
    int getSelectUserType();
};

#endif // UserManagerDialog_H
