
#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QDialog>
#include <qevent.h>
#include <QDateTime>
#include <QString>
#include "videoserver.h"

namespace Ui {
class DownloadWidget;
}

class DownloadWidget : public QWidget
{
    Q_OBJECT

    friend QDataStream & operator << (QDataStream &dataStream, DownloadWidget &d);
    friend QDataStream & operator >> (QDataStream &dataStream, DownloadWidget &d);
public:
    explicit DownloadWidget(std::shared_ptr<videoserver> pServer, const QString& filePath, const QString& name, const QString& startTime,
                            const QString& endTime, const int& channel, QWidget *parent = 0);
    ~DownloadWidget();

    bool isFished()
    {
        return !mDownloading;
    }

    void setTask(QObject*  task)
    {
        mTask = task;
    }

    void setStatus(const QString& s);
    void setSource(const QString& s);
    std::shared_ptr<videoserver>  getService()
    {
        return mpSvr;
    }

    void setVideoServer(std::shared_ptr<videoserver> pServer)
    {
        mpSvr = pServer;
    }

    qint64 getDownloadSize()
    {
        return mDownloadSize;
    }

    void heartBeat();
signals:
    void finished(DownloadWidget *pSource,int channel, bool isComplete, bool close = false);
protected:
    bool dealHeartbeat(QEvent* event);
    void customEvent(QEvent* event);

    QObject* mTask;
protected:
    QDateTime beg;
    QDateTime last;
    qint64  mLastDownloadSize;
    qint64  mLastFailedDownloadSize;
    qint64 mDownloadSize;
    qint64 mTotalSize;
    bool mDownloading;
    std::shared_ptr<videoserver> mpSvr;
    QString strfilePath;
    quint32 mBeatTime;
    std::recursive_mutex mMutexHeartBeat;
public:
    void cancel();
public slots:
    void on_cancelButton_clicked();

private:
    int  iChannel;
    Ui::DownloadWidget *ui;
};

QDataStream & operator << (QDataStream &dataStream, DownloadWidget &d);
QDataStream & operator >> (QDataStream &dataStream, DownloadWidget &d);

#endif // DOWNLOADWIDGET_H
