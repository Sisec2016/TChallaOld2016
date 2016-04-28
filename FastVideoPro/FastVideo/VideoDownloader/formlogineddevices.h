#ifndef FORMLOGINEDDEVICES_H
#define FORMLOGINEDDEVICES_H

#include <QWidget>
#include "videoserver.h"
#include <vector>

namespace Ui {
class FormLoginedDevices;
}

class FormLoginedDevices : public QWidget
{
    Q_OBJECT

public:
    explicit FormLoginedDevices(QWidget *parent = 0);
    void init(std::vector< std::shared_ptr<LoginServerInfo> > pDevices);
    ~FormLoginedDevices();

private slots:
    void on_pushButtonConnect_clicked();

private:
    Ui::FormLoginedDevices *ui;
};

#endif // FORMLOGINEDDEVICES_H
