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
    bool isMannualConfig(){
        return m_bMannual;
    }
protected slots:
    void onOkBtn();
    void onMannualConfigBtn();
signals:

protected:
    bool m_bMannual;
private:
    Ui::IPConfigSucessDialog *ui;
};

#endif // DISKDLG_H
