#ifndef SINGLEAPLLICATION_H
#define SINGLEAPLLICATION_H

#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <QtNetwork/QLocalServer>

class SingleApplication : public QCoreApplication {

        Q_OBJECT
        static SingleApplication* sInstance;
    public:
        SingleApplication(int &argc, char **argv);

        bool isRunning();

        static SingleApplication* instance()
        {
            return sInstance;
        }

protected:

    private slots:
        void _newLocalConnection();

    private:
        void _initLocalConnection();
        void _newLocalServer();
        void _activateWindow();

        bool _isRunning;                // 是否已經有实例在运行
        QLocalServer *_localServer;     // 本地socket Server
        QString _serverName;            // 服务名称
};

#endif // SINGLEAPPLICATION_H

#endif // SINGLEAPLLICATION_H
