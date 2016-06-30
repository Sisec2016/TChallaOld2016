#ifndef NOFLAMEDLG_H
#define NOFLAMEDLG_H
#include <QDialog>
#include <qevent.h>
#include <qapplication.h>

class PlayFlameDlg : public QDialog
{
    Q_OBJECT
public:
    PlayFlameDlg(QWidget *parent = 0);
    ~PlayFlameDlg();
protected:
    bool mDrag;
    QPoint mDragPosition;
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void showEvent(QShowEvent* event);
private:
	QPoint mLastMousePosition;
	bool mMoving;
   /* void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            mDrag = true;
            mDragPosition = event->globalPos() - this->pos();
            event->accept();
        }
    }*/

	/*void mouseMoveEvent(QMouseEvent *event)
    {
        if (mDrag && (event->buttons() && Qt::LeftButton)) {
            move(event->globalPos() - mDragPosition);
            event->accept();
        }
    }*/

	/*void mouseReleaseEvent(QMouseEvent *)
    {
        mDrag = false;
    }*/
};

#endif // NOFLAMEDLG_H
