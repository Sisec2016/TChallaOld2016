#ifndef LOGINSUCCESSDIALOG_H
#define LOGINSUCCESSDIALOG_H

#include <QDialog>

namespace Ui {
class loginSuccessDialog;
}

class loginSuccessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginSuccessDialog(QWidget *parent = 0);
    ~loginSuccessDialog();

private:
    Ui::loginSuccessDialog *ui;
};

#endif // LOGINSUCCESSDIALOG_H
