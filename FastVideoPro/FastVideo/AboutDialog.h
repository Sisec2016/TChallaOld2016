#ifndef AboutDialog_H
#define AboutDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public MyBaseDialog {
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

protected slots:
    void onOkBtn();

signals:

protected:

private:
    Ui::AboutDialog *ui;
};

#endif // DISKDLG_H
