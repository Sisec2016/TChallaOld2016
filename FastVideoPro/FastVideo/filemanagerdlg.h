#ifndef FILEMANAGERDLG_H
#define FILEMANAGERDLG_H

#include <QDialog>
#include "MyBaseDialog.h"


namespace Ui {
    class FileManagerDlg;
}

class FileManagerDlg : public MyBaseDialog {
    Q_OBJECT
public:
    FileManagerDlg(QWidget *parent = 0);
    ~FileManagerDlg();

protected:
    void changeEvent(QEvent *e);
protected:
	Ui::FileManagerDlg *ui;

};

#endif // FILEMANAGERDLG_H
