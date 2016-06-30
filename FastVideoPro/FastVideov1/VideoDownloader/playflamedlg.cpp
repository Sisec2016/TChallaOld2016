#include "playflamedlg.h"
#include "screenadaption.h"

PlayFlameDlg::PlayFlameDlg(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window );

}

PlayFlameDlg::~PlayFlameDlg()
{

}

void PlayFlameDlg::mousePressEvent(QMouseEvent* event)
{
    QDialog::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}

void PlayFlameDlg::mouseMoveEvent(QMouseEvent* event)
{
    QDialog::mouseMoveEvent(event);
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
      //  this->move(this->pos() + (event->globalPos() - mLastMousePosition));
     //   mLastMousePosition = event->globalPos();
    }
}

void PlayFlameDlg::mouseReleaseEvent(QMouseEvent* event)
{
    QDialog::mouseReleaseEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void PlayFlameDlg::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    QWidget* pParent = NULL;// this->parentWidget();
    if (pParent == NULL)
    {
        pParent = (QWidget*)QApplication::desktop();
    }
    this->move((pParent->width() -this->width()) / 2, (pParent->height() - this->height()) / 2);
    
}