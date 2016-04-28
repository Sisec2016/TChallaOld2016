#include "timeedit.h"
#include "qdatetime.h"
#include "timedialog.h"

TimeEdit::TimeEdit(QWidget *parent) :
    QLineEdit(parent)
{
    mTime = QDateTime::currentDateTime().time();
    updateUI();
}

void TimeEdit::updateUI()
{
    this->setText(mTime.toString("HH:mm"));
}

void TimeEdit::mouseReleaseEvent(QMouseEvent *e)
{
    timeDialog dlg;
    dlg.setTime(this->mTime);
    dlg.exec();
    mTime = dlg.getTime();
    updateUI();
    emit TimeSet(this);
}

void TimeEdit::reset()
{
    mTime.setHMS(0, 0, 0);
    updateUI();
}
