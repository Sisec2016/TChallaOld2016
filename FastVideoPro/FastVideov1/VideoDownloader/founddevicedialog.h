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
protected:
    void addToTableWidget(const DeviceInfo& d);
    void init();
private slots:
    void onLoginClicked();
    void onPushButtonOtherClicked();
private:
    Ui::FoundDeviceDialog *ui;
    std::vector<DeviceInfo> mDeviceInfos;
    std::vector< std::shared_ptr<LoginServerInfo> > mResults;
};

#endif // FoundDeviceDialog_H
