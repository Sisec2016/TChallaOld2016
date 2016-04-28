#ifndef IPADDDLG_H
#define IPADDDLG_H

#include <QDialog>

namespace Ui {
    class IPAddDlg;
}

class IPAddDlg : public QDialog {
    Q_OBJECT
public:
    IPAddDlg(QWidget *parent = 0);
    ~IPAddDlg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::IPAddDlg *ui;
};

#endif // IPADDDLG_H
