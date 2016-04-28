#include "dialoglogineddevices.h"
#include "ui_dialoglogineddevices.h"
#include "formdeviceinfo.h"
DialogLoginedDevices::DialogLoginedDevices(QWidget *parent) :
    NoFlameDlg(parent),
    ui(new Ui::DialogLoginedDevices)
{
    ui->setupUi(this);
    ui->listViewDevices->init(ui->widgetHeader);
    ui->listViewDevices->setMultiSelect(true);
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

}

DialogLoginedDevices::~DialogLoginedDevices()
{
    delete ui;
}

void DialogLoginedDevices::init(std::vector< std::shared_ptr<LoginServerInfo> > pDevices)
{
    for (int i = 0; i < pDevices.size(); i++)
    {
        FormDeviceInfo* pDeviceForm = new FormDeviceInfo(this);
        pDeviceForm->init(pDevices[i]);

        ui->listViewDevices->addWidgetItem(pDeviceForm);
        if (i == 0)
        {
            ui->listViewDevices->onItemSelected(pDeviceForm);
        }
    }
}


void DialogLoginedDevices::on_pushButtonConnect_clicked()
{
    mDevices.clear();
    auto selectedItems = ui->listViewDevices->getSelectedItems();
    for (auto it = selectedItems.begin(); it != selectedItems.end(); it++)
    {
        FormDeviceInfo* pInfo = (FormDeviceInfo*)(*it);
        if (pInfo != nullptr)
        {
            mDevices.push_back(pInfo->getServerInfo());
        }
    }

    this->accept();
    
}

void DialogLoginedDevices::on_pushButtonCancel_clicked()
{
    this->reject();
}