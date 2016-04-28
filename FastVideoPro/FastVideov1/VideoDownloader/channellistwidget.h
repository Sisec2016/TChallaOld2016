#ifndef CHANNELLISTWIDGET_H
#define CHANNELLISTWIDGET_H

#include <QListWidget>
#include "videoserver.h"
class ChannelListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ChannelListWidget(QWidget *parent = 0);
    ~ChannelListWidget();
    void getSelectedChannels(std::vector<int>& channels);
    void setAllChecked(bool bChecked);
signals:

public slots:
    void showServer(videoserver& s);
};

#endif // CHANNELLISTWIDGET_H
