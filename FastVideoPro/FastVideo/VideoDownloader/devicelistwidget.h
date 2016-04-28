#ifndef DEVICELISTWIDGET_H
#define DEVICELISTWIDGET_H

#include <QListWidget>
#include <devicewidget.h>
struct DeviceListWidgetCallback
{
    virtual DeviceWidget* createDeviceWidget(std::shared_ptr<videoserver> pServer) = 0;

};

class DeviceListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit DeviceListWidget(QWidget *parent = 0);
    ~DeviceListWidget();
    void init(DeviceListWidgetCallback* pCallback)
    {
        mCallBack = pCallback;
    }

    void setAllTaskCancel();
    void setQuiting();
    void heartbeat();
    void releaseAll();
    void addDevice(std::shared_ptr<videoserver> pServer, std::shared_ptr<LoginServerInfo> pServerInfo, bool bLogin);
    DeviceWidget* cuurentDevice()
    {
        return mCuurrentDevice;
    }

    void save();
    void load();
protected:
    void addDeviceWidget(DeviceWidget* pDeviceWidget, std::shared_ptr<LoginServerInfo> pServerInfo, bool bLogin);
    std::shared_ptr<LoginServerInfo> find(std::shared_ptr<LoginServerInfo> pInfo)
    {
        std::lock_guard<std::recursive_mutex> lock(mMutexLoginInfos);
        if (pInfo.get() == nullptr)
        {
            return std::shared_ptr<LoginServerInfo>();
        }

        for (int i = 0; i < mLoginInfos.size(); i++)
        {
            if ((*mLoginInfos[i]) == (*pInfo))
            {
                return mLoginInfos[i];
            }
        }

        return std::shared_ptr<LoginServerInfo>();
    }
    bool addLoginServerInfo(std::shared_ptr<LoginServerInfo> pInfo)
    {
		if (pInfo.get() == nullptr)
		{
			return false;
		}
        std::lock_guard<std::recursive_mutex> lock(mMutexLoginInfos);
		if (find(pInfo) == nullptr)
        {
            mLoginInfos.push_back(pInfo);
            return true;
        }

        return false;
    }
    void removeLoginServerInfo(std::shared_ptr<LoginServerInfo> pInfo)
    {

        if (pInfo.get() == nullptr)
        {
            return;
        }
        std::lock_guard<std::recursive_mutex> lock(mMutexLoginInfos);
        for (int i = 0; i < mLoginInfos.size(); i++)
        {
            if (mLoginInfos[i].get() == pInfo.get())
            {
                pInfo->erase();
                mLoginInfos.erase(mLoginInfos.begin() + i);
                break;
            }
        }
    }

    template<class FunCallback>
    void callForEachDevice(FunCallback f)
    {
        std::lock_guard<std::recursive_mutex> lock(mMutexDeviceUI);
        for (int i = 0; i < count() && !mStop; i++)
        {
            QListWidgetItem* pItem = this->item(i);
            if (pItem == nullptr)
            {
                continue;
            }

            DeviceWidget* d = dynamic_cast<DeviceWidget *>
                    (this->itemWidget(pItem));
            if (d == nullptr)
            {
                continue;
            }

            f(d);
        }
    }

signals:
    void onSelected(DeviceWidget *d);
    void onRemoveChannels();
public slots:
    void on_exit(DeviceWidget *q);
    void onSel(DeviceWidget* pDevice);
    void onLogin(DeviceWidget* pDevice);
    void on_delDeviceButton_clicked(DeviceWidget* pDevice);
    void saveLoginInfo();
    void loadLoginInfo();

private:
    QString getSaveDatasDir();
    QString getSaveDatasFile();
protected:
    DeviceListWidgetCallback *mCallBack;
    ServerInfoList_t mLoginInfos;
    std::recursive_mutex mMutexLoginInfos;
    DeviceWidget* mCuurrentDevice;
    std::recursive_mutex mMutexDeviceUI;

    bool mStop;
};

#endif // DEVICELISTWIDGET_H
