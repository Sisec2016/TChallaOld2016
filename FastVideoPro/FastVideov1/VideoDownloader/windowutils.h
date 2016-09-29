#ifndef WINDOWUTILS_H
#define WINDOWUTILS_H
#include <Windows.h>
#include <QString>
#include <tchar.h>
#include <QTextCodec>
#include <qdebug.h>
#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <set>
#include <memory>

class WindowUtils
{
public:
    static bool isValidNetMacaddress(const QString& macaddress);
	static void GetIPfromLocalNIC(std::vector<QString> &IPs);
	static void getLocalIPs(std::vector<QString> &IPs);
    static void getLocalIPs(const QString& sHostName, std::vector<QString> &IPs);
    static bool findProcessByName(const char* szFileName);
    static void terminateProcess(const char* szFileName);
    static void copy(const QFileInfo& source, const QDir& dest, const QString& destName = "");
    static bool setNetConfig(const QString& sName, const QString& sIP, const QString& sMask = "255.255.255.0",
        const QString& sGate = "", bool bWait = false, std::shared_ptr<bool> bpCancel = std::shared_ptr<bool>());
    static bool setNetDhcp(const QString& sName);

    static bool isConnecteTo(const QString& IP, int millSeconds = 500);
    static bool getDirectDevice(QString& ip, QString& netGate, std::shared_ptr<bool> bpCancel = std::shared_ptr<bool>());
    static bool getDirectDevice(QString& ip, QString& netGate, std::set<QString>& otherIPS, int secondsWait = 60, std::shared_ptr<bool> bpCancel = std::shared_ptr<bool>());
    static bool setIPByDHCP(QString& ip, QString& mask, QString& netGate, std::shared_ptr<bool> bpCancel = std::shared_ptr<bool>());
    static const QString& getLoacalNetName();
    static bool isOnLine();
    static void disableWindowMsg();
    static void sleep(int milliSeconds, std::shared_ptr<bool> bpCancel = std::shared_ptr<bool>());
private:
    WindowUtils();
};

#endif // WINDOWUTILS_H
