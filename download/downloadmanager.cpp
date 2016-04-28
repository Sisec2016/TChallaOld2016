#include "downloadmanager.h"

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QStringList>
#include <QUrl>
#include <QDebug>
#include <stdio.h>
#include <QLibrary>
#include <QCoreApplication>
#include <iostream>

DownloadManager::DownloadManager()
{
    control = new DownloadControl(this);
    connect(control, SIGNAL(finished(int)), SLOT(finishedSlot(int)));
    connect(control, SIGNAL(error(int, QString)), SLOT(errorSlot(int, QString)));
    connect(control, SIGNAL(progressChange(int, qint64, qint64, qint64)), SLOT(progressChangeSlot(int, qint64, qint64, qint64)));
//     connect(&manager, SIGNAL(finished(QNetworkReply*)),
//             SLOT(downloadFinished(QNetworkReply*)));
}


void DownloadManager::doDownload(const QUrl &url)
{
    std::cout << "doDownload" << std::endl;
   
}

void DownloadManager::finishedSlot(int index)
{
    qDebug() << "finish : " << index;
    if (index == 0 && control->getState() == DownloadControl::Finished)
    {
        if (isRightFile())
        {   
            QFile::remove(mStrFilename);
            if (QFile::rename(getTempFile(), mStrFilename)){
            }
        }
        QCoreApplication::instance()->quit();
    }
}
void DownloadManager::errorSlot(int index, QString errorString)
{
    std::cout <<  index << " "<<errorString.toLocal8Bit().data();
    QCoreApplication::instance()->quit();
}

void DownloadManager::progressChangeSlot(int index, qint64 startPoint, qint64 endPoint, qint64 readySize)
{
    std::cout << index << " startPoint:" << startPoint << " endPoint:" << endPoint << " readySize:" << readySize <<std::endl;
}
void DownloadManager::execute()
{
    QStringList args = QCoreApplication::instance()->arguments();

    if (args.length() < 2 )
    {
        QCoreApplication::instance()->quit();
        return;
    }

    args.takeFirst();           // skip the first argument, which is the program's name
    if (args.isEmpty()) {
        QCoreApplication::instance()->quit();
        return;
    }
    
    if (args.length() > 2)
    {
        mMd5 = args[2];
    }

    mStrFilename = args[1];
    control->downloadFile(args[0], getTempFile(), 4);

}


bool DownloadManager::isRightFile(){
    if (mMd5.isEmpty())
    {
        return true;
    }

    QFile theFile(getTempFile());
    theFile.open(QIODevice::ReadOnly);
    QByteArray ba = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
    theFile.close();
    std::cout << "md5  " << mMd5.toStdString().c_str() << "  " << ba.toHex().constData();
    return  (mMd5 == ba.toHex().constData());
}

QString DownloadManager::getTempFile(){
    return mStrFilename + "_tmp";
}
