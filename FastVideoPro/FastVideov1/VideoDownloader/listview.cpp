#include "listview.h"
#include <QVBoxLayout>
#include <deque>
#include <uiutils.h>
#include <algorithm>

ListViewItem::ListViewItem(QWidget *parent) : QWidget(parent)
{

}

void ListViewItem::initListViewItem()
{
    QString sStyleSheet(this->styleSheet());
    sStyleSheet.replace(" ", "");
    int begin = sStyleSheet.indexOf("selection-border-image:url");
    if (begin != -1)
    {
        begin += strlen("selection-");
        int end = sStyleSheet.indexOf(";", begin);
        mSelectedBordthImage = sStyleSheet.mid(begin, end - begin + 1);
        qDebug() << "mSelectedBordthImage:" << mSelectedBordthImage;
    }

    begin = sStyleSheet.indexOf(QRegExp("[^-]border-image:\\s*url\\s*\\(:.*\\);"));
    if (begin != -1)
    {
        begin = sStyleSheet.indexOf("border-image:", begin);
        int end = sStyleSheet.indexOf(";", begin);
        mBordthImage = sStyleSheet.mid(begin, end - begin + 1);
    }


}

void ListViewItem::setSelected(bool sel)
{
    QString sStyleSheet(this->styleSheet());
    if (sel)
    {
        if (this->mBordthImage.isEmpty() && !this->mSelectedBordthImage.isEmpty())
        {
            int begin = sStyleSheet.indexOf("selection-border-image");
            if (begin != -1)
            {

                int end = sStyleSheet.indexOf(";", begin);
                sStyleSheet = sStyleSheet.insert(end + 1, QString(" ") + mSelectedBordthImage);
            }
        }
        else
        {
            sStyleSheet.replace(QRegExp("[^-;]border-image:\\s*url\\s*\\(:.*\\);"), QString(" ") + mSelectedBordthImage);
        }
    }
    else {
        sStyleSheet.replace(QRegExp("[^-]border-image:\\s*url\\s*\\(:.*\\);"), QString(" ") + mBordthImage);
    }

    this->setStyleSheet(sStyleSheet);
}

void ListViewItem::mousePressEvent(QMouseEvent *)
{
    setSelected(true);
    emit onSelected(this);
}


ListView::ListView(QWidget *parent) :
QScrollArea(parent), mInit(false), mpSelectedItem(nullptr), mMultedSetect(false)
{

    setAttribute(Qt::WA_TranslucentBackground);

}

void ListView::init(QWidget* pHead)
{

    if (nullptr != pHead)
    {
        UIUtils::getChildrenSortByX(*pHead, mvcHeadWidgets);
    }
    if (!mInit)
    {

        if (this->widget() == nullptr)
        {
            this->setWidget(new QWidget(this));
        }
        QVBoxLayout *DevicesLayout = new QVBoxLayout();
        DevicesLayout->setSizeConstraint(QLayout::SetNoConstraint);
        DevicesLayout->setContentsMargins(0, 0, 0, 0);
        DevicesLayout->setSpacing(0);
        this->widget()->setLayout(DevicesLayout);
        mInit = true;

    }
}



void ListView::addWidgetItem(ListViewItem *item)
{
    if (nullptr == item)
    {
        return;
    }
    qDebug() << "item->initListViewItem();";
    item->initListViewItem();
    connect(item, SIGNAL(onSelected(ListViewItem*)), this, SLOT(onItemSelected(ListViewItem*)));
    init();
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;


    std::vector<QWidget*> pvcWidgets;
    UIUtils::getChildrenSortByX(*item, pvcWidgets);
    if (pvcWidgets.size() > 0)
    {
        UIUtils::getChildrenSortByX(*pvcWidgets[0], pvcWidgets);
    }
    for (int i = 0; i < pvcWidgets.size(); i++)
    {
        if (this->mvcHeadWidgets.size() > i)
        {
            QWidget* pWidget = pvcWidgets[i];
            const QRect& rHeader(mvcHeadWidgets[i]->geometry());
            const QRect& rWidget(pWidget->geometry());
            pWidget->setFixedWidth(mvcHeadWidgets[i]->geometry().width());
            pWidget->setGeometry(rHeader.x(), rWidget.y(), rHeader.width(), rWidget.height());
        }
    }

    QRect r(this->geometry());
    r.setHeight(item->geometry().height());

    if (widget()->layout()->count() == 0)
    {
        r.setHeight(item->geometry().height());
    }
    else
    {
        r.setHeight(widget()->geometry().height() + item->geometry().height());
    }

    widget()->setFixedHeight(r.height());
    widget()->layout()->addWidget(item);
    this->setAlignment(Qt::AlignTop);

    if (mpSelectedItem == nullptr)
    {
        mpSelectedItem = item;
        mpSelectedItem->setSelected(true);
    }

    qDebug() << "item->initListViewItem() end" << __FILE__ << __FUNCTION__ << __LINE__;
}


void ListView::removeItem(int index)
{
    init();
    if (index < widget()->layout()->count() && index >= 0)
    {
        QWidget *item = widget()->layout()->itemAt(index)->widget();
        if (item != nullptr)
        {
            QRect r(this->geometry());
            widget()->layout()->removeWidget(item);
            r.setHeight(widget()->geometry().height() - item->geometry().height());
            item->deleteLater();
            // widget()->hide();
            // widget()->setFixedHeight(r.height());
            // widget()->layout()->setGeometry(r);
            // widget()->show();
        }
        if (mMultedSetect)
        {

            for (int i = 0; i < mpSelectedItems.size(); i++)
            {
                if (mpSelectedItems[i] == item)
                {
                    mpSelectedItems.erase(mpSelectedItems.begin() + i);
                    break;
                }
            }
        }
        else if (item == this->mpSelectedItem)
        {
            if (widget()->layout()->count() > 0)
            {
                ListViewItem *item = (ListViewItem *)widget()->layout()->itemAt(0)->widget();
                mpSelectedItem = item;
                mpSelectedItem->setSelected(true);
            }
            else
            {
                mpSelectedItem = nullptr;
            }
        }

    }
}

void ListView::removeItem(ListViewItem *item)
{
    init();
    removeItem(widget()->layout()->indexOf(item));
}

void ListView::removeAllItems()
{
    init();
    mpSelectedItems.clear();
    for (int i = widget()->layout()->count() - 1; i >= 0; i--)
    {
        removeItem(i);
    }
}


int ListView::itemSize()
{
    init();
    return  widget()->layout()->count();
}

ListViewItem *ListView::getItem(int index)
{
    init();
    if (index < widget()->layout()->count())
    {
        return (ListViewItem *)widget()->layout()->itemAt(index)->widget();
    }

    return nullptr;
}

void ListView::onItemSelected(ListViewItem *pItem)
{
    if (mMultedSetect)
    {
        auto r = std::find(mpSelectedItems.begin(), mpSelectedItems.end(), pItem);
        if (r == mpSelectedItems.end())
        {
            pItem->setSelected(true);
            mpSelectedItems.push_back(pItem);
            emit onSelected(pItem);
        }
        else{
            pItem->setSelected(false);
            mpSelectedItems.erase(r);
        }

    }
    else if (mpSelectedItem != pItem)
    {
        if (nullptr != mpSelectedItem)
        {
            mpSelectedItem->setSelected(false);
        }

        mpSelectedItem = pItem;
        emit onSelected(pItem);
    }
}
