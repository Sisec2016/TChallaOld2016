#ifndef ProductDialog_H
#define ProductDialog_H

#include <QDialog>
#include <QString>
#include <QProgressDialog>
#include <QWaitCondition>
#include <QMutex>

#include "MyBaseDialog.h"

namespace Ui {
    class ProductDialog;
}

class ProductDialog : public MyBaseDialog {
    Q_OBJECT
public:
    ProductDialog(QWidget *parent = 0);
    ~ProductDialog();

protected slots:
    void onOkBtn();
    void onEditDlDir();
    void onEditLogoIcon();
    void onEditProductName();
signals:

protected:

private:
    Ui::ProductDialog *ui;
};

#endif // DISKDLG_H
