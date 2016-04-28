#include "channelwidget.h"
#include "ui_channelwidget.h"
#include <qdebug.h>
#include "screenadaption.h"

ChannelWidget::ChannelWidget(const std::pair<qint32,QString>& channel, QWidget *parent) :
    QWidget(parent),
    mChannel(channel.first),
    ui(new Ui::ChannelWidget)
{
    ui->setupUi(this);
    if (channel.second.trimmed().isEmpty())
    {
        ui->checkBox->setText(tr("channel%1").arg(mChannel));
    }
    else
    {
        ui->checkBox->setText(channel.second);
    }

    ScreenAdaption::instance().adpte(this);
}

ChannelWidget::~ChannelWidget()
{
    delete ui;
}

bool ChannelWidget::isCheck()
{
    return ui->checkBox->isChecked();
}
void ChannelWidget::setCheck(bool bChecked)
{
    ui->checkBox->setChecked(bChecked);
}

void ChannelWidget::mouseReleaseEvent(QMouseEvent *)
{
    ui->checkBox->setChecked(!ui->checkBox->isChecked());
}
