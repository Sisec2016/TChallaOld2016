#ifndef HelpDialog_H
#define HelpDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"

namespace Ui {
    class HelpDialog;
}

class HelpDialog : public MyBaseDialog {
    Q_OBJECT
public:
    HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

protected slots:
    void onOkBtn();

signals:

protected:

private:
    Ui::HelpDialog *ui;
};

#endif // DISKDLG_H
