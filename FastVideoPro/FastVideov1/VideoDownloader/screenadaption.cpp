#include "screenadaption.h"
#include <QDesktopWidget>
#include <QApplication>

ScreenAdaption* ScreenAdaption::pInstance;
ScreenAdaption& ScreenAdaption::instance()
{
    if (nullptr == pInstance)
    {
        pInstance = new ScreenAdaption();
    }
    return *pInstance;
}

ScreenAdaption::ScreenAdaption() :
    mWidthScaleFactor(1), mHeightScaleFactor(1), mNeedAdapt(false)
{
}

void ScreenAdaption::init(int devWidth, int devHeight)
{
    QDesktopWidget *pDesk = QApplication::desktop();
    int screenW = pDesk->screenGeometry().width();
    int screenH = pDesk->screenGeometry().height();

    if ((screenW == devWidth) && (screenH == devHeight))
    {
        return ;
    }

    mNeedAdapt = true;
    mWidthScaleFactor = screenW / (devWidth * 1.0);
    mHeightScaleFactor = screenH / (devHeight * 1.0);
}

void ScreenAdaption::adpte(QWidget* p)
{
    if (nullptr == p || !mNeedAdapt)
    {
        return;
    }

    p->setGeometry(p->geometry().x() * mWidthScaleFactor, p->geometry().y() * mHeightScaleFactor,
                   p->geometry().width() * mWidthScaleFactor, p->geometry().height() * mHeightScaleFactor);
    QFont font = p->font();
    font.setPointSize(font.pointSize()*(mWidthScaleFactor < mHeightScaleFactor ? mWidthScaleFactor : mHeightScaleFactor));
    p->setFont(font);
    QObjectList list = p->children();
    foreach(QObject * obj, list)
    {
       if (!obj->isWidgetType())
       {
           continue;
       }

       adpte((QWidget*)obj);
    }

}


void ScreenAdaption::showInCenter(QWidget* p)
{
    if (p == nullptr)
    {
        return;
    }
    const QWidget* pParent = p->parentWidget();
    if (pParent == nullptr)
    {
        pParent = QApplication::desktop();
    }
    p->move((pParent->width() - p->width()) / 2 + pParent->x(), (pParent->height() - p->height()) / 2 + pParent->y());
}
