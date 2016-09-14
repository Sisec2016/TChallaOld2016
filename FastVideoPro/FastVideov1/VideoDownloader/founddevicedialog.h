#ifndef FoundDeviceDialog_H
#define FoundDeviceDialog_H

#include <QDialog>
#include <QList>

#include "mybasedialog.h"

#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include "videoserver.h"

namespace Ui {
    class FoundDeviceDialog;
}


class FoundDeviceDialog : public MyBaseDialog {
    Q_OBJECT
public:
    FoundDeviceDialog(QWidget *parent = 0);
    ~FoundDeviceDialog();

public:
    std::vector< std::shared_ptr<LoginServerInfo> >  getLoginServerInfo()
    {
        return mResults;
    }
    void ipConfigGuide();
protected:
    void addToTableWidget(const DeviceInfo& d);
    void init();
    void mannulConfigNet();
    void intelligentConfig();
    void deepConfig();
    void startLoginDlg();
    void enableButton(bool b);
private slots:
    void onLoginClicked();
    void onPushButtonOtherClicked();
private:
    Ui::FoundDeviceDialog *ui;
    std::vector<DeviceInfo> mDeviceInfos;
    std::vector< std::shared_ptr<LoginServerInfo> > mResults;
    std::vector<QString> mIPs;
};

#endif // FoundDeviceDialog_H
