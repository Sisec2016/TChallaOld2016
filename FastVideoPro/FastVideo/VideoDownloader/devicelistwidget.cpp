#include "devicelistwidget.h"
#include <qpushbutton>
#include <QApplication>
#include "uiutils.h"
#include "messageboxdlg.h"
#include "utils.h"

DeviceListWidget::DeviceListWidget(QWidget *parent) : QListWidget(parent),
    mCuurrentDevice(nullptr),
    mCallBack(nullptr),
    mStop(false)
{
    Utils::CreateIfNotExist(getSaveDatasDir());
}

void DeviceListWidget::heartbeat()
{
    callForEachDevice([&](DeviceWidget* d){
        d->dealFailedDownloadRow();
    });
}
DeviceListWidget::~DeviceListWidget()
{
    mStop = true;
    releaseAll();
}
void DeviceListWidget::releaseAll()
{
    callForEachDevice([&](DeviceWidget* d){
        d->deleteLater();
    });
}

void DeviceListWidget::addDevice(std::shared_ptr<videoserver> pServer, std::shared_ptr<LoginServerInfo> pServerInfo, bool bLogin)
{
    if (mCallBack == nullptr)
    {
        return;
    }
    std::shared_ptr<LoginServerInfo> pOld = find(pServerInfo);
    if (!pOld)
    {
        addLoginServerInfo(pServerInfo);
        DeviceWidget* pDeviceWidget = mCallBack->createDeviceWidget(pServer);
        addDeviceWidget(pDeviceWidget, pServerInfo, bLogin);
    }
    else
    {
        UIUtils::showTip(*this, QString::fromLocal8Bit("该设备已经添加！名称为：%1").arg(pOld->name));
    }
}

void DeviceListWidget::on_exit(DeviceWidget *p)
{
    if (nullptr != p)
    {
        p->removeSaveFile();
        this->removeLoginServerInfo(p->getLoginInfo());
    }
}

void DeviceListWidget::onSel(DeviceWidget* pDevice)
{
    if (mCuurrentDevice == pDevice)
    {
        return;
    }


    if (nullptr != mCuurrentDevice)
    {
        mCuurrentDevice->setSelected(false);
    }
    mCuurrentDevice = pDevice;
    mCuurrentDevice->setSelected(true);
    emit onSelected(pDevice);
}

void DeviceListWidget::onLogin(DeviceWidget* pDevice)
{
    std::lock_guard<std::recursive_mutex> lock(mMutexDeviceUI);
    if (mCuurrentDevice == pDevice)
    {
        emit onSelected(pDevice);
    }
}

void DeviceListWidget::setAllTaskCancel()
{
    callForEachDevice([&](DeviceWidget* d){
        d->cancelTask();
    });
}


void DeviceListWidget::setQuiting()
{
    mStop = true;
    callForEachDevice([&](DeviceWidget* d){
        d->setQuiting();
    });
}

void DeviceListWidget::on_delDeviceButton_clicked(DeviceWidget* pDevice)
{
    if (pDevice == nullptr)
    {
        UIUtils::showTip(*this, QString::fromLocal8Bit("请选择一个设备！"));
        return;
    }
    else if (pDevice->currentTask().get() != nullptr)
    {
        UIUtils::showTip(*this, QString::fromLocal8Bit("请等待任务完成!"));
        return;
    }

    MessageBoxDlg msgDlg(QString::fromLocal8Bit("是否删除选中设备?") , MsgButton::Yes, MsgButton::No);
    msgDlg.exec();
    if (msgDlg.isConfirm() != MsgButton::Yes)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(mMutexDeviceUI);
    if (this->mCuurrentDevice == pDevice)
    {
        emit onRemoveChannels();
        mCuurrentDevice = nullptr;
    }
    for (int i = 0; i < count() && !mStop; i++)
    {
        QListWidgetItem* pItem = this->item(i);
        if (pItem == nullptr)
        {
            continue;
        }

        DeviceWidget* d = dynamic_cast<DeviceWidget *>
                (this->itemWidget(pItem));

        if (d == pDevice)
        {
            removeLoginServerInfo(pDevice->getLoginInfo());
            this->removeItemWidget(pItem);
			pDevice->RemoveTask();
            pDevice->deleteLater();
            delete pItem;
            pDevice = nullptr;
        }

    }
}
QString DeviceListWidget::getSaveDatasDir()
{
    return QApplication::applicationDirPath() + "/datas";
}

QString DeviceListWidget::getSaveDatasFile()
{
    return getSaveDatasDir() + "/devices.dat";
}

void DeviceListWidget::saveLoginInfo()
{
    qDebug()<<"saveLoginInfo: "<<mLoginInfos.size();
    for (int i = 0; i < mLoginInfos.size(); i++)
    {
        mLoginInfos[i]->save();
    }
}

void DeviceListWidget::loadLoginInfo()
{
    mLoginInfos = LoginServerInfo::query(std::make_pair("1", 1));
}
void DeviceListWidget::save()
{
    saveLoginInfo();
    callForEachDevice([&](DeviceWidget* d){
        d->save();
    });
}

void DeviceListWidget::load()
{
    loadLoginInfo();
    const std::deque<videoserverFactory *>& Factorys = videoserverFactory::getFactorys();
    for (int i = 0; i < mLoginInfos.size(); i++)
    {
        LoginServerInfo& info = *mLoginInfos[i];
        videoserverFactory* factory = videoserverFactory::getFactory((DeviceFactory)info.factory);
        if (factory == nullptr)
        {
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << "factory == nullptr" << info.factory;
            continue;
        }

        auto pService = factory->create();
        if (pService)
        {
            DeviceWidget* p = mCallBack->createDeviceWidget(pService);
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__ ;
            addDeviceWidget(p, mLoginInfos[i], false);
            p->login();
            p->load();
        }
        else{
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << "pService == nullptr";
            continue;
        }
    }
}

void DeviceListWidget::addDeviceWidget(DeviceWidget* pDeviceWidget, std::shared_ptr<LoginServerInfo> pServerInfo, bool bLogin)
{
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    {
        std::lock_guard<std::recursive_mutex> lock(mMutexDeviceUI);
        UIUtils::addToListWidget(*this, *pDeviceWidget);
    }
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    connect(pDeviceWidget, SIGNAL(onSel(DeviceWidget*)), this, SLOT(onSel(DeviceWidget*)));
    connect(pDeviceWidget, SIGNAL(onLogin(DeviceWidget*)), this, SLOT(onLogin(DeviceWidget*)));
    connect(pDeviceWidget, SIGNAL(onClose(DeviceWidget*)), this, SLOT(on_delDeviceButton_clicked(DeviceWidget*)));
    pDeviceWidget->setLoginInfo(pServerInfo);
	pDeviceWidget->login();

	
	//以下多余,在创建一个新的DeviceWidget时,传入的pServerInfo是没有登录过的,bLogin是false
//     pDeviceWidget->setConnected(bLogin);
// 
//     if (bLogin)
//     {
//         onLogin(pDeviceWidget);
//     }
//     else
//     {
//         pDeviceWidget->login();
//     }
}
