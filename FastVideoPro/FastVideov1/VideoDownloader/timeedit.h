#ifndef TIMEEDIT_H
#define TIMEEDIT_H

#include <QLineEdit>
#include <QTime>

class TimeEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TimeEdit(QWidget *parent = 0);
    void setTime(const QTime& t)
    {
       mTime = t;
       updateUI();
    }

    QTime getTime()
    {
        return mTime;
    }

signals:
    void TimeSet(TimeEdit* p);
public slots:
    void reset();
protected:
    void updateUI();
    void mouseReleaseEvent(QMouseEvent *);
    QTime mTime;
};

#endif // TIMEEDIT_H
