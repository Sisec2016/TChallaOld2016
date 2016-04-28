#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include <QDialog>
#include <QTime>
#include <QLabel>
#include <noflamedlg.h>

namespace Ui {
class timeDialog;
}

class timeDialog : public NoFlameDlg
{
    Q_OBJECT

public:
    explicit timeDialog(QWidget *parent = 0);
    ~timeDialog();    
    const QTime& getTime()
    {
        return mTime;
    }

    void setTime(const QTime& t);

protected:
    QTime mTime;
    void updateUI();
    void nextLabel();
    void focusOutEvent(QFocusEvent *);
    bool event(QEvent *);
    void onPush(int number);
private slots:


    void on_pushButton_seven_clicked();

    void on_pushButton_eight_clicked();

    void on_pushButton_six_clicked();

    void on_pushButton_nine_clicked();

    void on_pushButton_four_clicked();

    void on_pushButton_five_clicked();

    void on_pushButton_one_clicked();

    void on_pushButton_two_clicked();

    void on_pushButton_three_clicked();

    void on_pushButton_zero_clicked();

    void on_pushButton_conon_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_save_clicked();

private:
    QLabel* mpCurrent;
    Ui::timeDialog *ui;
};

#endif // TIMEDIALOG_H
