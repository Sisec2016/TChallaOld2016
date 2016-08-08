#ifndef FORMDEVICEINFO_H
#define FORMDEVICEINFO_H

#include <QWidget>
#include "videoserver.h"
#include "listview.h"
namespace Ui {
class FormDeviceInfo;
}

class FormDeviceInfo : public ListViewItem
{
    Q_OBJECT

public:
    explicit FormDeviceInfo(QWidget *parent = 0);
    ~FormDeviceInfo();
    void init(std::shared_ptr<LoginServerInfo> pInfo);
    std::shared_ptr<LoginServerInfo> getServerInfo()
    {
        return mpInfo;
    }
    virtual void setSelected(bool sel);
private:
    Ui::FormDeviceInfo *ui;
    std::shared_ptr<LoginServerInfo> mpInfo;
};

#endif // FORMDEVICEINFO_H
