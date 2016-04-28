#ifndef DIALOGLOGINEDDEVICES_H
#define DIALOGLOGINEDDEVICES_H

#include <QDialog>
#include "videoserver.h"
#include <vector>
#include "noflamedlg.h"

namespace Ui {
class DialogLoginedDevices;
}

class DialogLoginedDevices : public NoFlameDlg
{
    Q_OBJECT

public:
    explicit DialogLoginedDevices(QWidget *parent = 0);
    ~DialogLoginedDevices();
    void init(std::vector< std::shared_ptr<LoginServerInfo> > pDevices);
    const std::vector< std::shared_ptr<LoginServerInfo> >& getLoginServerInfos(){
        return mDevices;
    }
private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonCancel_clicked();
private:
    Ui::DialogLoginedDevices *ui;
    std::vector< std::shared_ptr<LoginServerInfo> > mDevices;
};

#endif // DIALOGLOGINEDDEVICES_H
