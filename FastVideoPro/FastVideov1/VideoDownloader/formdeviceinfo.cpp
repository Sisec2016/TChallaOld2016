#include "formdeviceinfo.h"
#include "ui_formdeviceinfo.h"
#include "videoserver.h"

FormDeviceInfo::FormDeviceInfo(QWidget *parent) :
    ListViewItem(parent),
    ui(new Ui::FormDeviceInfo)
{
    ui->setupUi(this);
}

FormDeviceInfo::~FormDeviceInfo()
{
    delete ui;
}

void FormDeviceInfo::init(std::shared_ptr<LoginServerInfo> pInfo)
{
    if (pInfo)
    {
        videoserverFactory* pVF = videoserverFactory::getFactory((DeviceFactory)pInfo->factory);
        if (pVF != nullptr)
        {
            ui->labelFactory->setText(pVF->name());
        }

        ui->labelIP->setText(pInfo->ip);
        ui->labelPort->setText(QString::number(pInfo->port));
        ui->labelType->setText("DVR");

        this->mpInfo = pInfo;
    }


}
