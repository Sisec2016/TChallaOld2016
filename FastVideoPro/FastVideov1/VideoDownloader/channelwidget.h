#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class ChannelWidget;
}

class ChannelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelWidget(const std::pair<qint32,QString>& channel, QWidget *parent = 0);
    ~ChannelWidget();
    bool isCheck();
    void setCheck(bool bChecked);
    int getChannel()
    {
        return mChannel;
    }
protected:
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::ChannelWidget *ui;
    qint32 mChannel;
};

#endif // CHANNELWIDGET_H
