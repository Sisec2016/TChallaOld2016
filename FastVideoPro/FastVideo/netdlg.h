#ifndef NETDLG_H
#define NETDLG_H

#include <QDialog>
#include <QList>

#include "mybasedialog.h"

#include "myipaddressedit.h"

#include <QNetworkInterface>
#include <QNetworkAddressEntry>

namespace Ui {
    class netDlg;
}

typedef struct T_Host_IPAddress{
    QString strIP;
    QString strMaskIP;
    QString strGateIP;
}Host_IPAddress;

class netDlg : public MyBaseDialog {
    Q_OBJECT
public:
    netDlg(QWidget *parent = 0);
    ~netDlg();

protected:
    void changeEvent(QEvent *e);
    void closeEvent (QCloseEvent * e );
public:
    void getIPInterfaces();
    void refreshIPAddress();
    void readIPListFile();
    void writeIPListFile();
    void addToTableWidget(T_Host_IPAddress *phostIPAddress);
private slots:
    void onSearchClicked();
    void onAddClicked();
    void onDeleteClicked();
    void onConfigClicked();

private:
    Ui::netDlg *ui;

private:
    QList<T_Host_IPAddress> m_listHostIPAddress;

    QNetworkInterface m_netInterface;
    QNetworkAddressEntry m_hostAddressEntry;

	QString m_strIp;
	QString m_strNetMask;
	QString m_strGate;
};

#endif // NETDLG_H
