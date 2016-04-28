#ifndef MYIPADDRESSEDIT_H
#define MYIPADDRESSEDIT_H

#include <QWidget>

#include <QLineEdit>


namespace Ui {
    class MyIPAddressEdit;
}

class QWidget;
class QFocusEvent;
class QKeyEvent;
class QLabel;

class MyIpPartLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyIpPartLineEdit(QWidget *parent = 0);
    ~MyIpPartLineEdit(void);

    void set_nexttab_edit(QLineEdit *nexttab) { next_tab_ = nexttab; }

protected:
    virtual void focusInEvent(QFocusEvent *e);
    virtual    void keyPressEvent(QKeyEvent *event);

private slots:
    void text_edited(const QString& text);

private:
    QLineEdit *next_tab_;
};

class MyIPAddressEdit : public QWidget {
    Q_OBJECT
public:
    MyIPAddressEdit(QWidget *parent = 0);
    ~MyIPAddressEdit();

protected:
    void changeEvent(QEvent *e);

public:
    void settext(const QString &text);
    QString text();
    void setStyleSheet(const QString &styleSheet);
    void setDefaultText(QString text);
signals:
    void textchanged(const QString& text);
    void textedited(const QString &text);

private slots:
    void textchangedslot(const QString& text);
    void texteditedslot(const QString &text);

private:
    Ui::MyIPAddressEdit *ui;
};

#endif // MYIPADDRESSEDIT_H
