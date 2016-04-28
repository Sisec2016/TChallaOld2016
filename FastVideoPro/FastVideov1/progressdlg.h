#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>

namespace Ui {
    class ProgressDlg;
}

class ProgressDlg : public QDialog {
    Q_OBJECT
public:
    ProgressDlg(QWidget *parent = 0);
    ~ProgressDlg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ProgressDlg *ui;
};

#endif // PROGRESSDLG_H
