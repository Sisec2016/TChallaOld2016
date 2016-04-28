#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "downloadcontrol.h"
QT_BEGIN_NAMESPACE
class QSslError;
QT_END_NAMESPACE

QT_USE_NAMESPACE


class DownloadManager: public QObject
{
    Q_OBJECT

    QList<QNetworkReply *> currentDownloads;

public:
    DownloadManager();
    void doDownload(const QUrl &url);
    QString mStrFilename;
    QString mMd5;
    DownloadControl *control;
public slots:
    void execute();
    void finishedSlot(int index);
    void errorSlot(int index, QString errorString);
    void progressChangeSlot(int index, qint64 startPoint, qint64 endPoint, qint64 readySize);
private:
    bool isRightFile();
    QString getTempFile();
};

#endif // DOWNLOADMANAGER_H
