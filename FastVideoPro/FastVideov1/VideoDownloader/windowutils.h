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
    static bool setNetConfig(const QString& sName, const QString& sIP, const QString& sMask = "255.255.255.0", const QString& sGate = "", bool bWait = false);
    static bool setNetDhcp(const QString& sName);

    static bool isConnecteTo(const QString& IP, int millSeconds = 500);
    static bool getDirectDevice(QString& ip, QString& netGate);
    static bool getDirectDevice(QString& ip, QString& netGate, std::set<QString>& otherIPS, int secondsWait = 60);
    static bool setIPByDHCP(QString& ip, QString& mask, QString& netGate);
    static const QString& getLoacalNetName();
    static bool isOnLine();
    static void disableWindowMsg();
private:
    WindowUtils();
};

#endif // WINDOWUTILS_H
