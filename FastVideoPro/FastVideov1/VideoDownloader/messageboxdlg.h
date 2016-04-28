#ifndef MESSAGEBOXDLG_H
#define MESSAGEBOXDLG_H

enum MsgButton {
    NoButton           = 0x00000000,
    Yes                = 0x00004000,
    No                 = 0x00010000
};
typedef MsgButton Button;

#include <QDialog>

namespace Ui {
class MessageBoxDlg;
}

class MessageBoxDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MessageBoxDlg(const QString& mMessage, MsgButton buttons = Yes, MsgButton defaultButton = NoButton, const QString& sTitle = QStringLiteral("提示"), QWidget *parent = 0);
    ~MessageBoxDlg();
    MsgButton isConfirm()
    {
        return mConfirm;
    }
    void setBtnText(const QString& sYes, const QString& sNo);
private slots:
    void on_closeButton_clicked();
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    QString mMessage;
    MsgButton mConfirm;
    Ui::MessageBoxDlg *ui;
};

#endif // MESSAGEBOXDLG_H
