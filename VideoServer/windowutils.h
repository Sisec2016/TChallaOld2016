#ifndef WINDOWUTILS_H
#define WINDOWUTILS_H
#include <Windows.h>
#include <QString>
#include <tchar.h>
#include <QTextCodec>
#include <qdebug.h>
#include <QProcess>


class WindowUtils
{
public:
    static bool isValidNetMacaddress(const QString& macaddress);
    static void getLocalIPs(std::vector<QString> &IPs);
    static bool isConnecteTo(const QString& IP)
    {
        QProcess p;
        QString cammand = QString("ping %1 -n 1").arg(IP);
        p.start(cammand);
        if (!p.waitForStarted(-1))
        {
            qDebug()<<"p.waitForStarted()"<<p.errorString()<<"  "<<p.error();
        }

        if (!p.waitForFinished(-1))
        {
            qDebug()<<"p.waitForFinished()"<<p.errorString()<<"  "<<p.error();
        }

        QString s(QString::fromLocal8Bit(p.readAllStandardOutput().data()));
        qDebug()<<s;
        return s.contains("TTL=");
    }
    static bool findProcessByName(const char* szFileName);
    static void terminateProcess(const char* szFileName);
private:
    WindowUtils();
};

#endif // WINDOWUTILS_H
