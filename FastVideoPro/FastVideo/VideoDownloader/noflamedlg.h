#ifndef NOFLAMEDLG_H
#define NOFLAMEDLG_H
#include <QDialog>
#include <qevent.h>

class NoFlameDlg : public QDialog
{
    Q_OBJECT
public:
    NoFlameDlg(QWidget *parent = 0);
    ~NoFlameDlg();
protected:
    bool mDrag;
    QPoint mDragPosition;
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            mDrag = true;
            mDragPosition = event->globalPos() - this->pos();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (mDrag && (event->buttons() && Qt::LeftButton)) {
            move(event->globalPos() - mDragPosition);
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent *)
    {
        mDrag = false;
    }
};

#endif // NOFLAMEDLG_H
