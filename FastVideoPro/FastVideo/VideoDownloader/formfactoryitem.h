#ifndef FORMFACTORYITEM_H
#define FORMFACTORYITEM_H

#include <QWidget>
#include "listview.h"
#include "videoserver.h"

namespace Ui {
class FormFactoryItem;
}

class FormFactoryItem : public ListViewItem
{
    Q_OBJECT

public:
    explicit FormFactoryItem(QWidget *parent = 0);
    ~FormFactoryItem();
    void setFactory(videoserverFactory *pFactory);
    videoserverFactory *getFactory()
    {
        return mpFactory;
    }

private:
    Ui::FormFactoryItem *ui;
    videoserverFactory *mpFactory;
};

#endif // FORMFACTORYITEM_H
