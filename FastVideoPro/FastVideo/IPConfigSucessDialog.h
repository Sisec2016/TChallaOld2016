#ifndef IPConfigSucessDialog_H
#define IPConfigSucessDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"

namespace Ui {
    class IPConfigSucessDialog;
}

class IPConfigSucessDialog : public MyBaseDialog {
    Q_OBJECT
public:
    IPConfigSucessDialog(const QString&ip, const QString& subMask, const QString& netGate, QWidget *parent = 0);
    ~IPConfigSucessDialog();

protected slots:
    void onOkBtn();
signals:

protected:

private:
    Ui::IPConfigSucessDialog *ui;
};

#endif // DISKDLG_H
