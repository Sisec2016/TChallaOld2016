#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <qevent.h>
#include <mutex>
#include <memory>
#include "videoserver.h"
#include "devicelistwidget.h"
//#include "noflamedlg.h"
#include "../mybasedialog.h"

#include "SearchDevicesImpl.h"

namespace Ui {
class MainDialog;
}

class DownloadTask;
class DeviceWidget;
class MainDialog : public MyBaseDialog, public DeviceListWidgetCallback
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    virtual DeviceWidget* createDeviceWidget(std::shared_ptr<videoserver> pServer);
protected:
    std::recursive_mutex mMutex;

public:
    bool isOverTime(int channelNum);
    bool isOverZoneTime(int channelNum);

    void load();
    void save();
    void saveForExit();

    QDateTime getGPSBeginDateTime();
    QDateTime getGPSEndDateTime();
    QDateTime getBeginDateTime();
    QDateTime getEndDateTime();

    QDateTime getGPSBeginDateTime_time();
    QDateTime getGPSEndDateTime_time();
    QDateTime getBeginDateTime_time();
    QDateTime getEndDateTime_time();
    void onDownloadFindEnd(std::shared_ptr< std::vector<RecordFile> > pFileAllRows);
    void onDownloadTask(std::shared_ptr<DownloadTask> pDownloadTask);

	//<<<<<<<<<<<<add by zhangyaofa 2016/5/20	
	SearchDeviceInterface *m_pSearch;
	//>>>>>>>>>>>>>>>>add end
public:
    QString getSaveDatasDir();
private slots:
    void on_downloadButton_clicked();
    void on_closeButton_clicked();
    void on_zonedownloadBtn_clicked();
    void on_hideButton_clicked();

    void on_btnAddDevice_clicked();
    void onSelected(DeviceWidget* d);
    void onRemoveChannels();
    void on_checkBoxChannelAll_toggled(bool checked);

	void on_leftBtn_clicked();
	void on_rightBtn_clicked();

    void on_rb_queryAll_clicked(bool checked);
    void on_rb_queryTime_clicked(bool checked);
private:
    Ui::MainDialog *ui;
    bool mStop;
    std::shared_ptr<std::thread> mDownloadTimerThread;
	QPushButton *m_backBtn2;
	QPushButton *m_closeBtn2;

};

#endif // MAINDIALOG_H
