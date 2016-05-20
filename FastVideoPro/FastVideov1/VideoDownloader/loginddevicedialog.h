#ifndef LOGINDDEVICEDIALOG_H
#define LOGINDDEVICEDIALOG_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include <QStringListModel>
#include "videoserver.h"
#include <vector>
#include <set>
#include "listview.h"
#include "noflamedlg.h"
#include "SearchDevicesImpl.h"

namespace Ui {
class LogindDeviceDialog;
}
#define NUM_OF_ONEPAGE   7
class LogindDeviceDialog : public NoFlameDlg
{
    Q_OBJECT

public:
    explicit LogindDeviceDialog(QWidget *parent = 0);
    ~LogindDeviceDialog();
	std::vector< std::shared_ptr<LoginServerInfo> >  getLoginServerInfo()
    {
		return mResults;
    }

signals:
    void onClose();
    void onPreStep();
    void onNextStep();
protected:
    void ipConfigGuide();
    void deepConfig();
    void initFactory();
    void getIps();
private slots:
    void on_btnCloseX_clicked();
    void on_lineEditPort_textChanged(const QString &arg1);
    void on_pushButtonConnect_clicked();
    void on_pushButtonDirect_clicked();
    void on_closeButton_clicked();
    void on_lineEditIP_textChanged(const QString &arg1);
	void on_pushButtonNext_clicked();
	void on_pushButtonPre_clicked();
	void on_checkBoxSearchIp_stateChanged(int state);
	void on_checkBoxDefaultPort_stateChanged(int state);
    void on_txtSearchFactory_textChanged(const QString &arg1);
    void on_factory_Selected(ListViewItem* item);
	void checkDeviceByBroadcast(int nFactoryType);
	void autoCheckDeviceByBroadcast(std::shared_ptr<bool> bLock, videoserverFactory* pFactory, 
		QString port, QString user, QString password, std::shared_ptr<std::recursive_mutex> mtLoginResult);
private:
    void setPage(int num);
    void initNetCombobox();
protected:
	std::vector<std::thread*> connectThreads;
	bool m_bStop;
    std::set<QString> msetIps;
    std::vector<QString> mvcIps;
    std::vector< std::shared_ptr<LoginServerInfo> > mResults;
    int mCurrentPage;
	//<<<<<<<<<<<<add by zhangyaofa 2016/5/20
	std::vector<QString> m_DHFactorys;
	std::vector<QString> m_DZPFactorys;
	std::vector<QString> m_JxjFactorys;
	SearchDeviceInterface *m_pSearch;
	//>>>>>>>>>>>>>>>>add end
private:
    Ui::LogindDeviceDialog *ui;
};

#endif // LOGINDDEVICEDIALOG_H
