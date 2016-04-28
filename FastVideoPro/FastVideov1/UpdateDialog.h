#ifndef UpdateDialog_H
#define UpdateDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"

namespace Ui {
    class UpdateDialog;
}

class UpdateDialog : public MyBaseDialog {
    Q_OBJECT
public:
    UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();

protected slots:
    void onOkBtn();

signals:

protected:

private:
    Ui::UpdateDialog *ui;
};

#endif // DISKDLG_H
