#ifndef usermodifypassword_H
#define usermodifypassword_H

#include <QDialog>

namespace Ui {
class usermodifypassword;
}

class usermodifypassword : public QDialog
{
    Q_OBJECT

public:
    explicit usermodifypassword(QWidget *parent = 0);
    ~usermodifypassword();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::usermodifypassword *ui;
};

#endif // usermodifypassword_H
