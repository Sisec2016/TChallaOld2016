
#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QScrollArea>
#include <QWidget>
#include <QLayout>
#include <qdebug.h>

class ListViewItem : public QWidget
{
    Q_OBJECT
public:
    explicit ListViewItem(QWidget *parent = 0);
    void initListViewItem();
    virtual void setSelected(bool sel);
protected:

    virtual void mousePressEvent(QMouseEvent *);
signals:
    void onSelected(ListViewItem* item);
private:
    QString mSelectedBordthImage;
    QString mBordthImage;
};

class ListView : public QScrollArea
{
    Q_OBJECT
public:

    explicit ListView(QWidget *parent = 0);
    void addWidgetItem(ListViewItem *item);
    void removeItem(int index);

    void removeItem(ListViewItem *item);
    void removeAllItems();
    int itemSize();
    ListViewItem *getItem(int index);
    void init(QWidget* pHead = nullptr);
    ListViewItem *getSelectedItem()
    {
        return mpSelectedItem;
    }
    void setMultiSelect(bool b){
        mMultedSetect = b;
    }
    const std::vector<ListViewItem *>& getSelectedItems(){
        return mpSelectedItems;
    }

signals:
    void onSelected(ListViewItem* item);
public slots:
    void onItemSelected(ListViewItem *pItem);
private:
    bool mInit;
    ListViewItem *mpSelectedItem;
    std::vector<QWidget*> mvcHeadWidgets;
    bool mMultedSetect;
    std::vector<ListViewItem *> mpSelectedItems;
};

#endif // LISTVIEW_H
