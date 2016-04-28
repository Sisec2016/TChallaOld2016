#ifndef MYBASEDIALOG_H
#define MYBASEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QLabel>
#include <qpushbutton.h>


class MyBaseDialog : public QDialog
{
        Q_OBJECT
public:
    MyBaseDialog(QWidget *parent = 0);
    ~MyBaseDialog();
public:
    void setTitleName(QString name);
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
	void showEvent(QShowEvent* event);
public slots:
    void onCloseClicked();
    void onBackClicked();
    void onMinClicked();
private:
    QPoint mLastMousePosition;
    bool mMoving;

protected:
    QPushButton *closeBtn;
    QLabel *title_label;
    QPushButton *minBtn;
    QPushButton *backBtn;
};

#endif // MYBASEDIALOG_H
