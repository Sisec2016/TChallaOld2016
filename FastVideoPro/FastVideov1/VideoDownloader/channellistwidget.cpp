#include "channellistwidget.h"
#include "uiutils.h"
#include "channelwidget.h"


ChannelListWidget::ChannelListWidget(QWidget *parent) : QListWidget(parent)
{
}

ChannelListWidget::~ChannelListWidget()
{

}

void ChannelListWidget::getSelectedChannels(std::vector<int> &channels)
{
    for (int i = 0; i < this->count(); i++)
    {
        QListWidgetItem* pItem = this->item(i);
        if (pItem == nullptr)
        {
            continue;
        }

        ChannelWidget* cw = dynamic_cast<ChannelWidget *>(this->itemWidget(pItem));
        if (cw != nullptr && cw->isCheck())
        {
            channels.push_back(cw->getChannel());
        }
    }
}

void ChannelListWidget::setAllChecked(bool bChecked)
{
    for (int i = 0; i < this->count(); i++)
    {
        QListWidgetItem* pItem = this->item(i);
        if (pItem == nullptr)
        {
            continue;
        }

        ChannelWidget* cw = dynamic_cast<ChannelWidget *>(this->itemWidget(pItem));
        if (cw != nullptr)
        {
            cw->setCheck(bChecked);
        }
    }
}

void ChannelListWidget::showServer(videoserver &s)
{
    this->clear();

    const std::map<qint32, std::string>& chnnls = s.channels();
    for (std::map<qint32, std::string>::const_iterator it = chnnls.begin(); it != chnnls.end(); it++)
    {
        ChannelWidget* pChannelWidget = new ChannelWidget(std::make_pair(it->first, QString::fromLocal8Bit(it->second.c_str())));
        UIUtils::addToListWidget(*this, *pChannelWidget);
    }
}
