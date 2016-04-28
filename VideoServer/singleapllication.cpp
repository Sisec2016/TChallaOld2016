#include "singleapllication.h"

#include <QtNetwork/QLocalSocket>
#include <QFileInfo>

#define TIME_OUT                (500)    // 500ms
SingleApplication* SingleApplication::sInstance = nullptr;
SingleApplication::SingleApplication(int &argc, char **argv, bool run)
    : QApplication(argc, argv)
    , w(NULL)
    , _isRunning(false)
    , _localServer(NULL) {


    _serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
	if (run)
	{
		_initLocalConnection();
	}
	else{

	}
    sInstance = this;
}

bool SingleApplication::testOtherInstance(){
	QLocalSocket socket;
	socket.connectToServer(_serverName);
	_isRunning = socket.waitForConnected(TIME_OUT);
	return _isRunning;
}

bool SingleApplication::isRunning() {
    return _isRunning;
}

void SingleApplication::_newLocalConnection() {
    QLocalSocket *socket = _localServer->nextPendingConnection();
    if(socket) {
        socket->waitForReadyRead(2*TIME_OUT);
        delete socket;


        _activateWindow();
    }
}


void SingleApplication::_initLocalConnection() {
	if (!testOtherInstance())
	{
		_newLocalServer();
	}
}


void SingleApplication::_newLocalServer() {
    _localServer = new QLocalServer(this);
    connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
    if(!_localServer->listen(_serverName)) {
        if(_localServer->serverError() == QAbstractSocket::AddressInUseError) {
            QLocalServer::removeServer(_serverName);
            _localServer->listen(_serverName);
        }
    }
}


void SingleApplication::_activateWindow() {
    if(w) {
        w->showMaximized();
        w->raise();
        w->activateWindow();
    }
}
