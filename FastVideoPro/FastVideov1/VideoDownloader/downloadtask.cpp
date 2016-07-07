#include "downloadtask.h"
#include "devicewidget.h"
#include "downloadtasktreewidget.h"
#include <QCoreApplication>
#include <QApplication>
#include <QDir>

SERIAL_MEMMBER_4(DownloadRow, row, mFileFullName, taskID, mRFPath)

void DownloadRow::setCancel(){
    mCancel = true;
    if (nullptr != pDownloadWidget)
    {
        pDownloadWidget->cancel();
    }
}
bool DownloadRow::download(DeviceWidget* pWidget,
    const QString& strFilePath, std::shared_ptr<DownloadRow> selfP, std::shared_ptr<videoserver> pServer)
{
    if (mCancel || selfP.get() != this)
    {
        return false;
    }
    
    if (!pWidget->isConnected())
    {
        qDebug()<<"DownloadRow::download !pWidget->isConnected()";
        return false;
    }
    if (!pServer)
    {
        return false;
    }
//     if (mThread.get() != nullptr)
//     {
//         mThread->join();
//     }

    if (mFileFullName.isEmpty())
    {
        mFileFullName = (strFilePath + "/" + pServer->getFileName(f)).trimmed();
    }

    if (nullptr == pDownloadWidget)
    {
        QCoreApplication::postEvent(pWidget, new DownloadRowForWidget(selfP, pServer));
        return true;
    }
//    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    pDownloadWidget->setSource(pServer->getChannelName(f.channel));
//     mThread = std::shared_ptr<std::thread>(new std::thread([&]{
    std::vector<QString> externs;
    pServer->videoFileExterns(externs);
    pDownloadWidget->setVideoServer(pServer);
    if (!pServer->downLoad(mFileFullName, f, pDownloadWidget) && !mCancel)
    {
        QCoreApplication::postEvent(pDownloadWidget, new downloadEvent(nullptr, 0, 0, true));
    }
//     }));
//    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    return true;
}

DownloadRow::~DownloadRow()
{
//     if (mThread.get() != nullptr)
//     {
//         mThread->join();
//     }
}

QDataStream & operator << (QDataStream &dataStream, DownloadRow &d)
{
    d.save();
    dataStream<<d.f;
    return dataStream;
}

QDataStream & operator >> (QDataStream &dataStream, DownloadRow &d)
{
    dataStream>>d.f;
    d.pDownloadWidget = nullptr;
    return dataStream;
}

SERIAL_MEMMBER_11(DownloadTask, mId, mRowIndex, mstrFilePath, mName, mHaveWidget, mLoginInfoID, mState,
    msTotalSize, msLastDownloadSize, msDownloadSize, mnprogressBar)

bool DownloadTask::isFinished()
{
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    for (DownloadRows_t::iterator it = readyDownloadRows.begin(); it != readyDownloadRows.end(); it++)
    {
        if (it->second.size() > 0)
        {
            return false;
        }
    }

    for (DownloadRows_t::iterator it = downloadingRows.begin(); it != downloadingRows.end(); it++)
    {
        if (it->second.size() > 0)
        {
            return false;
        }
    }

    for (DownloadRows_t::iterator it = failedDownloadRows.begin(); it != failedDownloadRows.end(); it++)
    {
        if (it->second.size() > 0)
        {
            return false;
        }
    }

    return true;
}



std::shared_ptr<DownloadRow> DownloadTask::getNeedDownload(channelid_t c)
{
    std::lock_guard<std::recursive_mutex> lock(mMutex);
    if (readyDownloadRows[c].size() > 0)
    {
        std::shared_ptr<DownloadRow> r = readyDownloadRows[c][0];
        readyDownloadRows[c].pop_front();
        return r;
    }
    else if (failedDownloadRows[c].size() > 0)
    {
        std::shared_ptr<DownloadRow> r = failedDownloadRows[c][0];
        failedDownloadRows[c].pop_front();
        return r;
    }

    return std::shared_ptr<DownloadRow>();
}

void DownloadTask::download(DeviceWidget* pWidget)
{
    if (mCancel)
    {
        return;
    }
    std::lock_guard<std::recursive_mutex> lock(mMutex);
    std::shared_ptr<videoserver> pServer;
    for (DownloadRows_t::iterator it = readyDownloadRows.begin();
         it != readyDownloadRows.end(); it++)
    {
        if (it->second.size() == 0 && failedDownloadRows[it->first].size() > 0)
        {
            it->second = failedDownloadRows[it->first];
            failedDownloadRows[it->first].clear();
        }
    }

    for (DownloadRows_t::iterator it = readyDownloadRows.begin();
         it != readyDownloadRows.end(); it++)
    {

        QString downloadPath(pWidget->getDownloadPath(*this, it->first));
        QDir dir;
        dir.mkpath(downloadPath);
        while (it->second.size() > 0 &&
               (pServer = getDownloadServer(it->first)))
        {

            std::shared_ptr<DownloadRow> pRow = it->second[0];;
            it->second.pop_front();

            qDebug()<<"pRow->download beg";
            if (pRow.get() != nullptr)
            {
                if (!pRow->download(pWidget, downloadPath, pRow, pServer))
                {
                    failedDownloadRows[it->first].push_back(pRow);
                    releaseDownloadServer(pServer, it->first);
                    qDebug()<<"releaseDownloadServer";
                }
                else
                {
                    downloadingRows[it->first].push_back(pRow);
                }
            }
            else
            {
                releaseDownloadServer(pServer, it->first);
            }
        }

    }
}

bool DownloadTask::hasRow()
{
    std::lock_guard<std::recursive_mutex> lock(mMutex);
    for (DownloadRows_t::iterator it = readyDownloadRows.begin();
         it != readyDownloadRows.end(); it++)
    {
        if (it->second.size() > 0 )
        {
            return true;
        }
    }
    for (DownloadRows_t::iterator it = downloadingRows.begin();
         it != downloadingRows.end(); it++)
    {
        if (it->second.size() > 0 )
        {
            return true;
        }
    }
    for (DownloadRows_t::iterator it = failedDownloadRows.begin();
         it != failedDownloadRows.end(); it++)
    {
        if (it->second.size() > 0 )
        {
            return true;
        }
    }
    return false;
}

int DownloadTask::getDownRowNum()
{
    std::lock_guard<std::recursive_mutex> lock(mMutex);
    int num = 0;

    for (DownloadRows_t::iterator it = readyDownloadRows.begin(); it != readyDownloadRows.end(); it++)
    {
        num += it->second.size();
    }

    for (DownloadRows_t::iterator it = downloadingRows.begin(); it != downloadingRows.end(); it++)
    {
        num += it->second.size();
    }

    for (DownloadRows_t::iterator it = failedDownloadRows.begin(); it != failedDownloadRows.end(); it++)
    {
        num += it->second.size();
    }

    return num;
}


std::shared_ptr<videoserver> DownloadTask::getDownloadServer(channelid_t c)
{
    std::lock_guard< std::recursive_mutex> lock(mMutexDownloadServers);
    for (downloadServers_t::iterator it = mDownloadServers.begin();
         it != mDownloadServers.end(); it++)
    {
        if (it->second.find(c) == it->second.end())
        {
            qDebug()<<"return it->first"<<c;
            it->second.insert(c);
            return it->first;
        }
    }

    return std::shared_ptr<videoserver>();
}

void DownloadTask::initDownloadServer()
{
    std::lock_guard< std::recursive_mutex> lock(mMutexDownloadServers);
    if (mDownloadServers.size() == 0 && mpService != nullptr)
    {
        mDownloadServers[mpService];
        for (int i = 1; i < MAX_DOWNLOAD_SERVER_NUM && channelNum() > 0 &&
             i < MAX_DOWNLOAD_THRED / channelNum(); i++)
        {
            auto pServer = mpService->clone();
            if (nullptr != pServer)
            {
                mDownloadServers[pServer];
            }
            else
            {
                break;
            }
        }
    }
}

void DownloadTask::destroyDownloadServers()
{
    std::lock_guard< std::recursive_mutex> lock(mMutexDownloadServers);
    for (downloadServers_t::iterator it = mDownloadServers.begin();
         it != mDownloadServers.end(); it++)
    {
        if (it->first != mpService)
        {
            it->first->setRelease(true);
        }
    }
    mDownloadServers.clear();
}

void DownloadTask::heartBeat()
{
    if (mCancel)
    {
        qDebug() << __FUNCTION__ << __LINE__;
        return;
    }
    std::lock_guard<std::recursive_mutex> lock(mMutex);
    for (DownloadRows_t::iterator it = downloadingRows.begin();
         it != downloadingRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            if (it->second[i]->getDownloadWidget() != nullptr)
            {
                qDebug() << __FUNCTION__ << __LINE__;
                it->second[i]->getDownloadWidget()->heartBeat();
            }
        }
    }

}
std::shared_ptr<DownloadRow> DownloadTask::ReadyDownloadNext()
{
    std::lock_guard<std::recursive_mutex> lock(mMutex);

    if (mItNow != readyDownloadRows.end())
    {
        if (mRowIndex < mItNow->second.size())
        {
            return mItNow->second[mRowIndex++];
        }
        else
        {
            mItNow++;
            mRowIndex = 0;
            return ReadyDownloadNext();
        }
    }

    return std::shared_ptr<DownloadRow>(nullptr);
}

void DownloadTask::cancel()
{
    qDebug() << "DownloadTask::cancel" << __FILE__ << __FUNCTION__ << __LINE__;
    if (mCancel)
    {
        return;
    }
    mLastDownloadSize = 0;
    mCancel = true;

    qDebug() << "DownloadTask beg" << __FILE__ << __FUNCTION__ << __LINE__;
    if (mpTaskWidget)
    {
        qDebug() << "DownloadTask" << __FILE__ << __FUNCTION__ << __LINE__;
        mpTaskWidget->setCancel();
    }
    qDebug() << "DownloadTask" << __FILE__ << __FUNCTION__ << __LINE__;
    {
        qDebug() << "DownloadTask mMutex" << __FILE__ << __FUNCTION__ << __LINE__;
        for (DownloadRows_t::iterator it = downloadingRows.begin();
            it != downloadingRows.end(); it++)
        {
            for (int i = 0; i < it->second.size(); i++)
            {
                it->second[i]->setCancel();
            }
        }
    }

    qDebug() << "DownloadTask end" << __FILE__ << __FUNCTION__ << __LINE__;

    //clearDownloadData();
    //mpTaskWidget.reset();
}

QString DownloadTask::getSaveFile()
{
    return QString("%1/datas/t%2").
                   arg(QApplication::applicationDirPath()).arg(mId);
}
void DownloadTask::subDownloadSize(qint64 size)
{
    if (mLastDownloadSize > size)
    {
        mLastDownloadSize -= size;
    }
    else
    {
        mLastDownloadSize = 0;
    }

    if (mDownloadSize > size)
    {
        mDownloadSize -= size;
    }
    else
    {
        mDownloadSize = 0;
    }
}
bool DownloadTask::save()
{

    QFile file(getSaveFile());
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream out(&file);

    std::lock_guard<std::recursive_mutex> lock(mMutex);

    for (DownloadRows_t::iterator it =  readyDownloadRows.begin();
        it !=  readyDownloadRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            it->second[i]->taskID = this->mLNId;
            out << *it->second[i];
        }
    }

    for (DownloadRows_t::iterator it = downloadingRows.begin();
        it != downloadingRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            if (mpTaskWidget)
            {
                qDebug() << "downloading size:" << it->second[i]->getDownloadWidget()->getDownloadSize();
                subDownloadSize(it->second[i]->getDownloadWidget()->getDownloadSize());
            }
            it->second[i]->taskID = this->mLNId;
            out << *it->second[i];
        }
    }

    for (DownloadRows_t::iterator it = failedDownloadRows.begin();
        it != failedDownloadRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            it->second[i]->taskID = this->mLNId;
            out << *it->second[i];
        }
    }

    file.close();
    
    msTotalSize = QString::number(mTotalSize);
    msLastDownloadSize = QString::number(mLastDownloadSize);
    msDownloadSize = QString::number(mDownloadSize);

    if (mpTaskWidget)
    {
        mnprogressBar = mpTaskWidget->getProgress();
    }
    
    return SqlTable<DownloadTask>::save();  
}

void DownloadTask::loadData()
{
    QFile file(getSaveFile());;
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    
    std::lock_guard<std::recursive_mutex> lock(mMutex);
    auto downloadRows = DownloadRow::query(std::make_pair("taskID", mLNId));
    for (DownloadRows_t::size_type i = 0; i < downloadRows.size(); i++)
    {
        std::shared_ptr<DownloadRow> dr = downloadRows[i];
        in >> *dr;
        readyDownloadRows[dr->getChannel()].push_back(dr);
    }
    file.close();

    mTotalSize = msTotalSize.toULongLong();
    mLastDownloadSize = msLastDownloadSize.toULongLong();
    mDownloadSize = msDownloadSize.toULongLong(); 
    mpTaskWidget = new TaskWidget();


    setReadyDownloadBegin();

    
}

void DownloadTask::removeSaveFile()
{
    QFile file(getSaveFile());
    file.remove();
}

void DownloadTask::clearDownloadData(){
    //std::lock_guard<std::recursive_mutex> lock(mMutex);

    for (DownloadRows_t::iterator it = readyDownloadRows.begin();
        it != readyDownloadRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            it->second[i]->erase();
        }
    }

    readyDownloadRows.clear();

    for (DownloadRows_t::iterator it = downloadingRows.begin();
        it != downloadingRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            it->second[i]->erase();
        }
    }

    downloadingRows.clear();

    for (DownloadRows_t::iterator it = failedDownloadRows.begin();
        it != failedDownloadRows.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            it->second[i]->erase();
        }
    }
    failedDownloadRows.clear();
    removeSaveFile();
    this->erase();
}



