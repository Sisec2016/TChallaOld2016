#include "formlogineddevices.h"
#include "ui_formlogineddevices.h"
#include "formdeviceinfo.h"

FormLoginedDevices::FormLoginedDevices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLoginedDevices)
{
    ui->setupUi(this);
}

void FormLoginedDevices::init(std::vector< std::shared_ptr<LoginServerInfo> > pDevices)
{
    for (int i = 0; i < pDevices.size(); i++)
    {
        FormDeviceInfo* pDeviceForm = new FormDeviceInfo(this);
        if (i == 0)
        {
            pDeviceForm->setFocus();
        }

        pDeviceForm->init(pDevices[i]);
        ui->listViewDevices->addWidgetItem(pDeviceForm);
    }
}

FormLoginedDevices::~FormLoginedDevices()
{
    delete ui;
}

void FormLoginedDevices::on_pushButtonConnect_clicked()
{

}
