#ifndef DOWNLOADTASK_H
#define DOWNLOADTASK_H
#include <qevent.h>
#include <map>
#include <deque>
#include <set>
#include <thread>
#include <mutex>
#include <QTreeWidget>
#include <algorithm>
#include "videoserver.h"
#include "downloadwidget.h"
#include "taskwidget.h"
#include "SqlUtils.h"
#include "SqlTableMembers.h"

typedef qint32 channelid_t;
typedef qint32 rowIndex_t;
typedef std::map<std::shared_ptr<videoserver>, std::set<channelid_t> > downloadServers_t;

#define MAX_DOWNLOAD_SERVER_NUM     5
#define MAX_DOWNLOAD_THRED         20

class DeviceWidget;

struct RecordFileInfo : public SqlTable<RecordFileInfo>
{
    SERIAL_MEMMBER_HEAD()
    
    int channel;      //通道
    qlonglong size;         //文件大小(byte)
    QString  name;    //文件名称
    qlonglong beginTime; //本地时间
    qlonglong endTime;   //本地时间
    QByteArray mPrivateData;   //私有数据
    void setID(int nDownloadID){
        this->mLNId = nDownloadID;
    }
    virtual bool insert()
    {
        QSqlQuery query;
        query.clear();
        if (mLNId != ID_NULL)
        {
            query.prepare(sPreparedIDInsert);
        }
        else{
            query.prepare(sPreparedInsert);
        }

        bindValues(query);
        if (mLNId != ID_NULL)
        {
            query.bindValue(":"ID_COLUMN, mLNId);
        }
        if (exec(query))
        {
            if (mLNId != ID_NULL){
                return true;
            }

            if (exec(query, std::string("SELECT MAX(mLNId) id FROM ") + sTableName))
            {
                if (query.next())
                {
                    mLNId = query.value(0).toInt();
                    return true;
                }
            }
        }

        return false;
    }
};


struct DownloadRow : public SqlTable<DownloadRow>
{
    SERIAL_MEMMBER_HEAD()
    DownloadRow() : row(0), pDownloadWidget(nullptr)
    {
        mCancel = false;
        mThread.reset();
    }

    DownloadRow(int r,  const RecordFile& otherf) : pDownloadWidget(nullptr), f(otherf)
    {
        mCancel = false;
        row = r;
    }

    DownloadRow(const DownloadRow& other)
    {
        mCancel = false;
        f = other.f;
        row = other.row;
        pDownloadWidget = other.pDownloadWidget;
        mThread.reset();
    }
    ~DownloadRow();
    DownloadRow& operator= (const DownloadRow& other)
    {
        if (this != &other)
        {
            f = other.f;
            row = other.row;
            pDownloadWidget = other.pDownloadWidget;
        }
        return *this;
    }
    bool save();
    virtual void loaded();
    virtual bool erase();
    channelid_t getChannel()
    {
        return f.channel;
    }

    void setDownloadWidget(DownloadWidget* p)
    {
        pDownloadWidget = p;
    }
    DownloadWidget* getDownloadWidget()
    {
        return pDownloadWidget;
    }
    RecordFile& getRecordFile()
    {
        return f;
    }
    quint64 fileSize()
    {
        return f.size;
    }

    bool download(DeviceWidget* pWidget, const QString& strFilePath, std::shared_ptr<DownloadRow> selfP, std::shared_ptr<videoserver> pServer);
public:
    int taskID;

    qint32 row;
    QString mFileFullName;
    QString mRFPath;

    DownloadWidget* pDownloadWidget;
    std::shared_ptr<std::thread> mThread;

    void setCancel();
    bool isCancel(){
        return mCancel;
    }
private:
    RecordFile f;

    bool mCancel;
};



QDataStream & operator << (QDataStream &dataStream, DownloadRow &d);
QDataStream & operator >> (QDataStream &dataStream, DownloadRow &d);

typedef std::map<channelid_t, std::deque<std::shared_ptr<DownloadRow> > > DownloadRows_t;
typedef std::shared_ptr<DownloadRow> DownloadRow_t;

#define  DTK_STATE_NULL         0
#define  DTK_STATE_INIT         1
#define  DTK_STATE_WAITING      2
#define  DTK_STATE_DOWNLOADING  3
#define  DTK_STATE_FINISHED     4

class DownloadTask : public SqlTable<DownloadTask>
{
    SERIAL_MEMMBER_HEAD()

    friend class DeviceWidget;

    DownloadRows_t readyDownloadRows;
    DownloadRows_t downloadingRows;
    DownloadRows_t failedDownloadRows;
    std::recursive_mutex mMutex;

    std::recursive_mutex mMutexDownloadServers;
    downloadServers_t mDownloadServers;
    std::shared_ptr<videoserver>  mpService;
    std::shared_ptr<videoserver> getDownloadServer(channelid_t c);
    QTreeWidgetItem *mTop;

    TaskWidget* mpTaskWidget;
public:
    int mId;
    int mRowIndex;
    QString mstrFilePath;
    QString mName;
    int mHaveWidget;
    int mLoginInfoID;
    int mState;

    QString msTotalSize;
    QString msLastDownloadSize;
    QString msDownloadSize;
    int mnprogressBar;
public:
    qint64 mTotalSize;
    //下载大小
    qint64  mLastDownloadSize;
    qint64 mDownloadSize;
public:
    QTreeWidgetItem *TreeWidgetItem()
    {
        return mTop;
    }

    void initDownloadServer();
    void destroyDownloadServers();
    void releaseDownloadServer(std::shared_ptr<videoserver> pServer, channelid_t c)
    {
        std::lock_guard< std::recursive_mutex> lock(mMutexDownloadServers);
        mDownloadServers[pServer].erase(c);
    }
    void heartBeat();
    bool isFinished();

    void setFilePath(const QString& path)
    {
        mstrFilePath = path;
    }
    void setName(const QString& s)
    {
        int index = s.indexOf("\\");
        if (index >= 0)
        {
            mName = s.right(s.length() - index - 1);
        }
        else{
            mName = s;
        }

    }
    const QString& getName()
    {
        return mName;
    }

    const QString& getFilePath()
    {
        return mstrFilePath;
    }
public:
    friend QDataStream & operator << (QDataStream &dataStream, DownloadTask &d);
    friend QDataStream & operator >> (QDataStream &dataStream, DownloadTask &d);
    DownloadTask() : mpService(nullptr), mHaveWidget(0), mpTaskWidget(nullptr), mCancel(false)
    {
        mId = QDateTime::currentDateTime().toTime_t();
        mRowIndex = 0;
        mLoginInfoID = NULL;
        mState = DTK_STATE_NULL;
        mLastDownloadSize = 0;
        mDownloadSize = 0;
        mTotalSize = 0;
    }

    ~DownloadTask()
    {
        destroyDownloadServers();
    }

    std::shared_ptr<DownloadRow> getNeedDownload(channelid_t c);
    void download(DeviceWidget* pWidget);
    void addFaileRow(std::shared_ptr<DownloadRow> r)
    {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        failedDownloadRows[r->getChannel()].push_back(r);
    }

    void addDownloadingRow(std::shared_ptr<DownloadRow> r)
    {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        downloadingRows[r->getChannel()].push_back(r);
    }

    void dealFinish(DownloadWidget *souce, int channel, bool complete)
    {
        if (mCancel)
        {
            return;
        }
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        if (downloadingRows.find(channel) != downloadingRows.end())
        {
            for (int i = 0; i < downloadingRows[channel].size(); i++)
            {
                if (downloadingRows[channel][i]->getDownloadWidget() == souce)
                {
                    if (!complete)
                    {
                        addFaileRow(downloadingRows[channel][i]);
                        qDebug()<<"dealFinish add file row";
                    }
                    else{
                        downloadingRows[channel][i]->erase();
                    }

                    downloadingRows[channel].erase(downloadingRows[channel].begin() + i);
                    if (downloadingRows[channel].size() == 0)
                    {
                        downloadingRows.erase(channel);
                    }
                    break;
                }
            }

        }

    }

    void addRow(std::shared_ptr<DownloadRow> r)
    {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        readyDownloadRows[r->getChannel()].push_back(r);
    }

    void clear()
    {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        readyDownloadRows.clear();
        failedDownloadRows.clear();
        this->setReadyDownloadBegin();

    }

    int channelNum()
    {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        return readyDownloadRows.size();
    }

    int getDownRowNum();

    bool hasRow();

    TaskWidget* widget()
    {
        return mpTaskWidget;
    }

    void setReadyDownloadBegin()
    {
        std::lock_guard<std::recursive_mutex> lock(mMutex);
        mItNow = readyDownloadRows.begin();
        mRowIndex = 0;
    }

    std::shared_ptr<DownloadRow> ReadyDownloadNext();
    void cancel();
    void subDownloadSize(qint64 size);
    bool save();
    void loadData();
    void removeSaveFile();
    void clearDownloadData();
private:
    QString getSaveFile();
protected:
    DownloadRows_t::iterator mItNow;
    bool mCancel;
};


#endif // DOWNLOADTASK_H
