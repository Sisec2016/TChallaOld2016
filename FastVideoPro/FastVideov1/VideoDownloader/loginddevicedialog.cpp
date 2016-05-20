#include "PING.h"
#include "loginddevicedialog.h"
#include "ui_loginddevicedialog.h"
#include "videoserver.h"
#include <QCollator>

#include "utils.h"
#include "uiutils.h"
#include "windowutils.h"
#include "videoserver.h"
#include "messageboxdlg.h"
#include "windowutils.h"
#include "cwaitdlg.h"
#include "dialoglogineddevices.h"
#include "formfactoryitem.h"
#include "screenadaption.h"
#include "qss.h"
#include "utils.h"
#include "netdlg.h"
#include "IPConfigSucessDialog.h"

#include "maindialog.h"






#define     NET_IP_DEAFAULT     QStringLiteral("默认")
#define     IP_CONFIG_GUIDE_TITLE  QStringLiteral("IP自动匹配向导")
LogindDeviceDialog::LogindDeviceDialog(QWidget *parent) :
NoFlameDlg(parent),
ui(new Ui::LogindDeviceDialog),
mCurrentPage(1)
{
	ui->setupUi(this);

	QIcon icon;
	icon.addFile(QString::fromUtf8(":/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->closeButton->setIcon(icon);
	ui->closeButton->setIconSize(QSize(45, 45));
	ui->closeButton->setText("");
	ui->closeButton->setStyleSheet(transparentBtn_StyleSheet);
	ui->lineEditDeviceName->hide();
	ui->label_8->hide();

	connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
	connect(ui->pushButtonDirect, SIGNAL(clicked()), this, SLOT(on_pushButtonDirect_clicked()));
	connect(ui->lineEditFactory, SIGNAL(textChanged(const QString &)), this, SLOT(on_txtSearchFactory_textChanged(const QString &)));
	connect(ui->listViewServers, SIGNAL(onSelected(ListViewItem*)), this, SLOT(on_factory_Selected(ListViewItem*)));
	ui->listViewServers->init(ui->widgetHeader);
	this->setPage(1);
	ui->checkBoxDefaultPort->setChecked(true);
	ui->checkBoxSearchIp->setChecked(true);
	initNetCombobox();
	ScreenAdaption::instance().showInCenter(this);

	ui->pushButtonDirect->hide();
	ipConfigGuide();

	//<<<<<<<<<<<<<<add by zhangyaofa 
	MainDialog *pMainDlg = (MainDialog *)parent;
	m_pSearch = pMainDlg->m_pSearch;
	//>>>>>>>>>>>>>add end
}

LogindDeviceDialog::~LogindDeviceDialog()
{
	delete ui;
	
}

void LogindDeviceDialog::ipConfigGuide(){
	this->hide();
	if (UIUtils::showQuetionBox(IP_CONFIG_GUIDE_TITLE, QStringLiteral("是否进行下载器IP智能匹配？")))
	{

		std::shared_ptr<QString> pIP = std::make_shared<QString>();
		std::shared_ptr<QString> pNetGate = std::make_shared<QString>();
		std::shared_ptr<QString> pMask = std::make_shared<QString>("255.255.255.0");
		std::shared_ptr<bool> bResult = std::make_shared<bool>(false);
		std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
		CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("正在智能匹配，请稍等...."), [=, this]()
		{

			*bResult = WindowUtils::setIPByDHCP(*pIP, *pMask, *pNetGate);
			if (*bpCancel)
			{
				return;
			}
			if (!*bResult)
			{
				*bResult = WindowUtils::getDirectDevice(*pIP, *pNetGate, msetIps);
				if (*bpCancel)
				{
					return;
				}
				if (*bResult)
				{
					if (!WindowUtils::setNetConfig(QStringLiteral("本地连接"), *pIP, "255.255.255.0", *pNetGate, true))
					{
						*bResult = false;
					}
				}
			}

		}, [=, this](bool bCancel){
			if (bCancel)
			{
				return;
			}
			if (*bResult)
			{
				IPConfigSucessDialog dlg(*pIP, "255.255.255.0", *pNetGate);
				dlg.exec();
				this->show();
			}
			else{
				if (UIUtils::showQuetionBox(IP_CONFIG_GUIDE_TITLE, QStringLiteral("智能识别网段失败！是否进行深度匹配？")))
				{
					deepConfig();
				}

			}

		}, bpCancel);
	}
	else{
		netDlg netDlg_(nullptr);
		netDlg_.setTitleName(QStringLiteral("网络配置"));
		netDlg_.exec();
		this->show();
	}
}

void LogindDeviceDialog::deepConfig(){
	std::shared_ptr<bool> bResult = std::make_shared<bool>(false);
	std::shared_ptr<QString> pIP = std::make_shared<QString>();
	std::shared_ptr<QString> pNetGate = std::make_shared<QString>();
	std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
	CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在深度匹配，请稍等..."), [=, this](){
		for (int i = 0; i < 255; i++)
		{
			*pNetGate = QString("192.168.%1.1").arg(i);
			*pIP = QString("192.168.%1.44").arg(i);
			if (*bpCancel)
			{
				return;
			}
			if (!WindowUtils::setNetConfig(QString::fromLocal8Bit("本地连接"), *pIP, "255.255.255.0", *pNetGate, true))
			{
				continue;
			}


			if (CPing::instance().instance().ScanOneIP(*pNetGate, *pIP, false))
			{
				*bResult = true;
				break;
			}
		}
	}, [=, this](bool bCancel){
		if (*bpCancel)
		{
			return;
		}
		if (*bResult)
		{
			IPConfigSucessDialog dlg(*pIP, "255.255.255.0", *pNetGate);
			dlg.exec();
			this->show();
		}
		else{
			UIUtils::showTip(*this,
				QString::fromLocal8Bit("智能识别网段失败！请手动设置！"));
			netDlg netDlg_(nullptr);
			netDlg_.setTitleName(QStringLiteral("网络配置"));
			netDlg_.exec();
			this->show();
		}

	}, bpCancel);

}

void LogindDeviceDialog::initFactory()
{
	ui->listViewServers->removeAllItems();
	const std::deque<videoserverFactory *>& Factorys = videoserverFactory::getFactorys();
	std::deque<videoserverFactory *> fs;
	QString sFilter = ui->lineEditFactory->text().toLower();
	for (int i = 0; i < Factorys.size(); i++)
	{
		if (sFilter.isEmpty() || Utils::getChineseSpell(Factorys[i]->name()).toLower().startsWith(sFilter))
		{
			fs.push_back(Factorys[i]);
		}
	}

	FormFactoryItem* pFirstItem = NULL;
	for (int i = (mCurrentPage - 1) * NUM_OF_ONEPAGE; i < fs.size() && i < NUM_OF_ONEPAGE + (mCurrentPage - 1) * NUM_OF_ONEPAGE; ++i)
	{
		FormFactoryItem* pItem = new FormFactoryItem(ui->listViewServers);
		//set factory name
		pItem->setFactory(fs[i]);
		ui->listViewServers->addWidgetItem(pItem);
		if (NULL == pFirstItem)
		{
			pFirstItem = pItem;
		}
	}

	//<<<<<<<<<add init factory  string by zhangyaofa 2016/5/18
    m_DHFactorys.clear();
	QString sFactory = QString::fromLocal8Bit("大华");
	m_DHFactorys.push_back(sFactory);

    m_DZPFactorys.clear();
	sFactory = QString::fromLocal8Bit("迪智浦");
	m_DZPFactorys.push_back(sFactory);
	OEMFacMap DZPMap = videoserverFactory::GetFakeFactory(SISC_IPC_DIZHIPU);
	OEMFacMap::iterator itr;
	for (itr = DZPMap.begin(); itr != DZPMap.end(); itr++)
	{
		sFactory = QString::fromLocal8Bit((char *)itr->first.c_str());
		m_DZPFactorys.push_back(sFactory);
	}

    m_JxjFactorys.clear();
	sFactory = QString::fromLocal8Bit("佳信捷");
	m_JxjFactorys.push_back(sFactory);
	//>>>>>>>> add end

	this->on_factory_Selected(pFirstItem);
}

void LogindDeviceDialog::on_btnCloseX_clicked()
{
	emit onClose();
}

void LogindDeviceDialog::on_lineEditPort_textChanged(const QString &arg1)
{
	FormFactoryItem* pItem = (FormFactoryItem*)ui->listViewServers->getSelectedItem();
	if (nullptr == pItem)
	{
		return;
	}
	videoserverFactory* pFactory = pItem->getFactory();
	if (pFactory == NULL)
	{
		return;
	}

	ui->checkBoxDefaultPort->setChecked(arg1 == QString::number(pFactory->port()));
}

void LogindDeviceDialog::on_pushButtonConnect_clicked()
{

	FormFactoryItem* pItem = (FormFactoryItem*)ui->listViewServers->getSelectedItem();
	if (nullptr == pItem)
	{
		UIUtils::showTip(*ui->listViewServers, QString::fromLocal8Bit("请选择一个厂商！"));
		return;
	}
	videoserverFactory* pFactory = pItem->getFactory();
	if (pFactory == NULL)
	{
		UIUtils::showTip(*ui->listViewServers, QString::fromLocal8Bit("请选择一个厂商！"));
		return;
	}

	qDebug() << pFactory->name() << pFactory->port();
	QString port(ui->lineEditPort->text());
	if (ui->checkBoxDefaultPort->isChecked())
	{
		port = QString::number(pFactory->port());
	}

	port = port.trimmed();
	qDebug() << port << " toUInt():" << port.toUInt();
	if (port.toStdString().find_first_not_of("1234567890") != std::string::npos || port.isEmpty())
	{
		UIUtils::showTip(*ui->lineEditPort, QString::fromLocal8Bit("请输入正确的端口号！"));
		return;
	}

	qDebug() << "port:" << port << " toUnInt " << port.toUInt();
	QString user(ui->lineEditAccount->text());
	QString password(ui->lineEditPasswords->text());
	user = user.trimmed();
	password = password.trimmed();
	if (user.isEmpty() && (!(password.isEmpty())))
	{
		UIUtils::showTip(*ui->lineEditAccount, QString::fromLocal8Bit("请输入用户名！"));
		return;
	}

	//如果用户名为空，则用户名与密码都取厂商默认
	if (user.isEmpty())
	{
		user = UNDEFIN_DEVICE_DEFAULT_USER;
		password = UNDEFIN_DEVICE_DEFAULT_PASSWORD;
	}

	//<<<<<<<<<<<<modify  search device by zhangyaofa 2016/5/18

	bool bCheckBroadcast = FALSE;
	vector <QString>::iterator itrFactory;

    if (ui->checkBoxSearchIp->isChecked())
    {
        for (itrFactory = m_DHFactorys.begin(); itrFactory != m_DHFactorys.end(); itrFactory++)
        {
            if ((*itrFactory) == pFactory->name())
            {
                bCheckBroadcast = TRUE;
                checkDeviceByBroadcast(DH_SDK);
                break;
            }
        }

		for (itrFactory = m_DZPFactorys.begin(); itrFactory != m_DZPFactorys.end(); itrFactory++)
		{
			if ((*itrFactory) == pFactory->name())
			{
				bCheckBroadcast = TRUE;
				checkDeviceByBroadcast(DZP_SDK);
				break;
			}
		}

        for (itrFactory = m_JxjFactorys.begin(); itrFactory != m_JxjFactorys.end(); itrFactory++)
        {
            if ((*itrFactory) == pFactory->name())
            {
                bCheckBroadcast = TRUE;
                checkDeviceByBroadcast(JXJ_SDK);
                break;
            }
        }
    }
	

	if (!bCheckBroadcast)
	{
		this->getIps();
	}
	///////////////////////////////
	//this->getIps();


	//>>>>>>>>>>>>modify end


	if (mvcIps.size() == 0)
	{
		return;
	}

	std::shared_ptr<int> login_result = std::shared_ptr<int>(new int());
	*login_result = 0;
	std::shared_ptr<QString> login_IP = std::shared_ptr<QString>(new QString());
	std::shared_ptr<std::recursive_mutex> mtLoginResult = std::shared_ptr<std::recursive_mutex>(new std::recursive_mutex());;

	connectThreads.clear();
	m_bStop = false;
	qDebug() << "正在登陆中...";
	std::shared_ptr<bool> bLock = std::shared_ptr<bool>(new bool(false));
	mResults.clear();
	ui->pushButtonConnect->setEnabled(false);
	ui->closeButton->setEnabled(false);
	std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
	CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在初始化..."), [=]()
	{
		//<<<<<<<<<<<<<<<<<<add intelligent search device   by zhangyaofa 2016/5/17 
		if (!bCheckBroadcast)
		{
			autoCheckDeviceByBroadcast(bLock, pFactory, port, user, password, mtLoginResult);
		}
		//>>>>>>>>>>>>>>>>>>add end

		for (int i = 0; i < mvcIps.size() && (!*bpCancel); i++)
		{
			*bLock = true;
			connectThreads.push_back(new std::thread([=](){
				if (*bpCancel)
				{
					return;
				}
				QString sIP(mvcIps[i]);
				auto pServer = pFactory->create();
				*bLock = false;
				if (!pServer)
				{
					qDebug() << "nullptr == pServer" << sIP;
					return;
				}

				std::shared_ptr<LoginServerInfo> pInfo = std::shared_ptr<LoginServerInfo>(new LoginServerInfo());
				//set factory 
				pInfo->factory = pServer->factory()->factory();
				//pInfo->id = QString::number(QDateTime::currentDateTime().toTime_t());
				//用时间做id在线程并发时取值一样,造成下载异常
				pInfo->id = sIP + QString::number(QDateTime::currentDateTime().toTime_t());
				pInfo->ip = sIP;
				pInfo->name = ui->lineEditDeviceName->text();
				if (pInfo->name.trimmed().isEmpty())
				{
					pInfo->name = QString("%1(%2)").arg(pServer->factory()->name()).arg(sIP);
				}
				if (port.toInt() == 0)
				{
					pInfo->port = pServer->factory()->port();
				}
				else
				{
					pInfo->port = port.toInt();
				}
				pInfo->password = password;
				pInfo->user = user;
				if (pServer->login(pInfo, &m_bStop))
				{
					qDebug() << "login succeed!";
					std::lock_guard<std::recursive_mutex>  lockLoginResult(*mtLoginResult);

					if (!*bpCancel)
					{
						*login_IP = sIP;
						this->mResults.push_back(pInfo);
					}
					qDebug() << "mResults.push_back";
				}
				else
				{
					qDebug() << "login failed:" << pInfo->ip << pServer->getLastError() << pServer->factory()->name();
				}
			}));

			::Sleep(1000);
			//             while(*bLock)
			//             {
			//                 ::Sleep(1);
			//             }

		}
		if (!*bpCancel)
		{
			CWaitDlg::setShowMsg(QString::fromLocal8Bit("正在智能登录中..."));
		}

		// 		char threadsize[16] = {0};
		// 		sprintf_s(threadsize, "connectThreads.size():%d", connectThreads.size());
		// 		Log::instance().AddLog(QString("正在智能登录中...") );
		for (int i = 0; i < connectThreads.size(); i++)
		{
			connectThreads[i]->join();
			delete connectThreads[i];
		}

		qDebug() << "login end";
	}, [=, this](bool bCancel){
		qDebug() << "if (!*login_result)";
		if (*bpCancel)
		{
			m_bStop = true;
			mResults.clear();
		}
		else
		{
			if (mResults.size() == 0)
			{
				MessageBoxDlg msgDlg(QString::fromLocal8Bit("登陆失败！"));
				msgDlg.exec();
				qDebug() << "pServer->getLastError() end";
			}
			else
			{
				ui->lineEditPasswords->clear();
				DialogLoginedDevices* pDlg = new DialogLoginedDevices(this);
				pDlg->init(mResults);
				if (QDialog::Accepted == pDlg->exec()){
					//this->mpLoginInfo = pDlg->getLoginServerInfo();
					mResults = pDlg->getLoginServerInfos();
					this->accept();
				}
				else{
					mResults.clear();
				}
			}


		}
		ui->pushButtonConnect->setEnabled(true);
		ui->closeButton->setEnabled(true);

	}, bpCancel);
}

void LogindDeviceDialog::on_pushButtonDirect_clicked(){
	if (!ui->pushButtonDirect->isEnabled())
	{
		return;
	}
	ui->pushButtonDirect->setEnabled(false);
	std::shared_ptr<bool> bResult = std::make_shared<bool>(false);

	CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在智能识别，请稍等..."), [=, this]()
	{
		QString strIP;
		QString strGate;
		if (*bResult = WindowUtils::getDirectDevice(strIP, strGate))
		{
			QString sName = QString::fromLocal8Bit("本地连接");
			WindowUtils::setNetConfig(sName, strIP, "255.255.255.0", strGate, true);
			ui->lineEditIP->setText(strGate);
			ui->checkBoxSearchIp->setChecked(false);
		}
	}, [=, this](bool bCancel){
		if (*bResult)
		{
			UIUtils::showTip(*ui->pushButtonDirect,
				QString::fromLocal8Bit("直连设置成功！"));
		}
		else{
			UIUtils::showTip(*ui->pushButtonDirect,
				QString::fromLocal8Bit("直连设置失败！请检查网络再重试，或者手工进行配置。"));
		}
		ui->pushButtonDirect->setEnabled(true);
	});
}


void LogindDeviceDialog::getIps()
{
	mvcIps.clear();
	//     if (msetIps.size() > 0)
	//     {
	//         for (auto it = msetIps.begin(); it != msetIps.end(); it++)
	//         {
	//             mvcIps.push_back(*it);
	//         }
	// 
	//         return;
	//     }


	if (ui->checkBoxSearchIp->isChecked())
	{
		QString netip(ui->comboBoxNet->currentText());
		if (netip.isEmpty() || (netip != NET_IP_DEAFAULT && !Utils::isIpV4(netip)))
		{
			UIUtils::showTip(*ui->comboBoxNet,
				QString::fromLocal8Bit("请输入或选择有效IP网段！"));
			return;
		}
		std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
		CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在搜索设备，请稍等..."), [=, this]()
		{
			if (netip != NET_IP_DEAFAULT)
			{
				CPing::instance().ScanIPs(mvcIps, netip, false, bpCancel);
			}
			else
			{
				CPing::instance().ScanIp(mvcIps, false, bpCancel);
			}



		}, [=, this](bool bCancel){
			if (*bpCancel)
			{
				mvcIps.clear();
				return;
			}
			if (mvcIps.size() == 0)
			{
				UIUtils::showTip(*ui->checkBoxSearchIp,
					QString::fromLocal8Bit("未找到设备！"));
			}
		}, bpCancel);
	}
	else
	{
		QString ip(ui->lineEditIP->text());
		if (!ip.isEmpty() && Utils::isIpV4(ip))
		{
			mvcIps.push_back(ip);
		}
		else
		{
			UIUtils::showTip(*ui->lineEditIP,
				QString::fromLocal8Bit("请输入有效IP！"));
		}
	}
}

void LogindDeviceDialog::on_closeButton_clicked()
{
	this->accept();
}

void LogindDeviceDialog::setPage(int num)
{
	const std::deque<videoserverFactory *>& Factorys = videoserverFactory::getFactorys();
	std::deque<videoserverFactory *> fs;
	QString sFilter = ui->lineEditFactory->text().toLower();
	for (int i = 0; i < Factorys.size(); i++)
	{
		if (sFilter.isEmpty() || Utils::getChineseSpell(Factorys[i]->name()).toLower().startsWith(sFilter))
		{
			fs.push_back(Factorys[i]);
		}
	}

	int maxPage = fs.size() / NUM_OF_ONEPAGE + 1;
	if (num < 1)
	{
		num = 1;
	}

	if (num > maxPage)
	{
		num = maxPage;
	}

	ui->pushButtonPre->setEnabled(num > 1);
	ui->pushButtonNext->setEnabled(num < maxPage);
	ui->labelPages->setText(QString("%1/%2").arg(num).arg(maxPage));
	mCurrentPage = num;
	initFactory();

}

void LogindDeviceDialog::on_lineEditIP_textChanged(const QString &arg1)
{
	ui->checkBoxSearchIp->setChecked(arg1.isEmpty());
}

void LogindDeviceDialog::on_pushButtonNext_clicked()
{
	setPage(++mCurrentPage);
}

void LogindDeviceDialog::on_pushButtonPre_clicked()
{
	setPage(--mCurrentPage);
}

void LogindDeviceDialog::on_checkBoxSearchIp_stateChanged(int state)
{
	if (state == Qt::Checked)
	{
		ui->lineEditIP->clear();

	}
	ui->comboBoxNet->setEnabled(state == Qt::Checked);
}

void LogindDeviceDialog::on_checkBoxDefaultPort_stateChanged(int state)
{
	if (state == Qt::Checked)
	{
		FormFactoryItem* pItem = (FormFactoryItem*)ui->listViewServers->getSelectedItem();
		if (nullptr == pItem)
		{
			return;
		}
		videoserverFactory* pFactory = pItem->getFactory();
		if (pFactory == NULL)
		{
			return;
		}

		ui->lineEditPort->setText(QString::number(pFactory->port()));
	}
}

void LogindDeviceDialog::on_factory_Selected(ListViewItem* item){
	if (ui->checkBoxDefaultPort->isChecked())
	{
		FormFactoryItem* pItem = (FormFactoryItem*)(item);
		if (pItem != NULL)
		{
			ui->lineEditPort->setText(QString::number(pItem->getFactory()->port()));
		}
	}

}

void LogindDeviceDialog::on_txtSearchFactory_textChanged(const QString &arg1)
{
	setPage(1);
}

void LogindDeviceDialog::initNetCombobox(){
	ui->comboBoxNet->clear();
	ui->comboBoxNet->addItem(NET_IP_DEAFAULT);
	std::vector<QString> vcIps;
	WindowUtils::getLocalIPs(vcIps);
	for (int i = 0; i < vcIps.size(); i++)
	{
		QString& ip = vcIps[i];
		ui->comboBoxNet->addItem(ip.replace(ip.lastIndexOf("."), ip.size() - ip.lastIndexOf("."), ".0"));
	}
}

//<<<<<<<add by zhangyaofa 2016/5/18
void LogindDeviceDialog::checkDeviceByBroadcast(int nFactoryType)
{

	qDebug() << "check device by broadcast start" << QString(nFactoryType);
	mvcIps.clear();

	

	//set DLL path
	//m_pSearch->SetDllPath("factorys\\");	

	int nDeviceLen = sizeof(NET_DEVICE_INFO);
	char *pDevice = new char[nDeviceLen * 512];
	int nRet = 0;
	memset(pDevice, 0, nDeviceLen * 512);	
	std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
	CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在搜索设备，请稍等..."), [=, this]()
	{
	bool bRet = m_pSearch->GetDevice(pDevice, nDeviceLen * 512, (int *)&nRet);
		if (bRet)
		{
			int i;
			for (i = 0; i < nRet / nDeviceLen; i++)
			{
				NET_DEVICE_INFO *ndiTmp = (NET_DEVICE_INFO *)(pDevice + i*nDeviceLen);

				switch (nFactoryType)
				{
				case DH_SDK:
					if (ndiTmp->nSDKType == DH_SDK)
					{
						QString qIp = ndiTmp->szIp;
						qDebug() << "da hua" << qIp;
						mvcIps.push_back(qIp);
					}
					break;
				case DZP_SDK:
					if (ndiTmp->nSDKType == DZP_SDK)
					{
						QString qIp = ndiTmp->szIp;
						qDebug() << "dzp" << qIp;
						mvcIps.push_back(qIp);
					}
					break;
				case JXJ_SDK:
					if (ndiTmp->nSDKType == JXJ_SDK)
					{
						QString qIp = ndiTmp->szIp;
						qDebug() << "jxj" << qIp;
						mvcIps.push_back(qIp);
					}
					break;
				default:
					break;
				}
			}
		}

		
		delete pDevice;

	}, [=, this](bool bCancel){
		if (*bpCancel)
		{
			mvcIps.clear();
			return;
		}
		if (mvcIps.size() == 0)
		{
			UIUtils::showTip(*ui->checkBoxSearchIp,
				QString::fromLocal8Bit("未找到设备！"));
		}
	}, bpCancel);

	return;


}

void LogindDeviceDialog::autoCheckDeviceByBroadcast(std::shared_ptr<bool> bLock, videoserverFactory* pFactory, 
	QString port, QString user, QString password, std::shared_ptr<std::recursive_mutex> mtLoginResult)
{
	qDebug() << "auto check start";
	SearchDeviceInterface *pSearch = CreateSearchObj();

	//set DLL path
	pSearch->SetDllPath("factorys\\");

	int nDeviceLen = sizeof(NET_DEVICE_INFO);
	char *pDevice = new char[nDeviceLen * 512];
	int nRet = 0;
	memset(pDevice, 0, nDeviceLen * 512);
	std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
	

	bool bRet = pSearch->GetDevice(pDevice, nDeviceLen * 512, (int *)&nRet);

	if (bRet)
	{
		int i;
		for (i = 0; i < nRet / nDeviceLen; i++)
		{
			NET_DEVICE_INFO *ndiTmp = (NET_DEVICE_INFO *)(pDevice + i*nDeviceLen);
			*bLock = true;
			connectThreads.push_back(new std::thread([=](){
				if (*bpCancel)
				{
					return;
				}
 				//QString sIP("192.168.0.15");
				QString sIP(ndiTmp->szIp);
				auto pServer = pFactory->create();
				*bLock = false;
				if (!pServer)
				{
					qDebug() << "auto nullptr == pServer " << sIP;
					return;
				}

				std::shared_ptr<LoginServerInfo> pInfo = std::shared_ptr<LoginServerInfo>(new LoginServerInfo());
				//pInfo->factory = SISC_IPC_DIZHIPU;
				//set factory 
				switch (ndiTmp->nSDKType)
				{
				case DH_SDK:

				{
					pInfo->factory = SISC_IPC_DH;					
				}
				break;
				case DZP_SDK:

					pInfo->factory = SISC_IPC_DIZHIPU;

					break;
				case JXJ_SDK:
					if (ndiTmp->nSDKType == JXJ_SDK)
					{
						pInfo->factory = SISC_IPC_JXJ;					
						
					}
					break;
				default:
					break;
				}

				std::vector<QString>::iterator itrIp;
				for (itrIp = mvcIps.begin(); itrIp != mvcIps.end(); itrIp++)
				{
					QString sIp = ndiTmp->szIp;
					if ((*itrIp) == sIp)
					{
						mvcIps.erase(itrIp);
						break;
					}
						
				}			
				
				//用时间做id在线程并发时取值一样,造成下载异常
				pInfo->id = sIP + QString::number(QDateTime::currentDateTime().toTime_t());
				pInfo->ip = sIP;
				
				
				if (port.toInt() == 0)
				{
					pInfo->port = pServer->factory()->port();
				}
				else
				{
					pInfo->port = port.toInt();
				}
				
				pInfo->password = password;
				pInfo->user = user;
				if (pServer->loginByBroadcast(pInfo->factory, pInfo, &m_bStop))
				{
					qDebug() << "login succeed!";
					std::lock_guard<std::recursive_mutex>  lockLoginResult(*mtLoginResult);

					if (!*bpCancel)
					{						
						this->mResults.push_back(pInfo);
					}
					qDebug() << "mResults.push_back";
				}
				else
				{
					qDebug() << "auto check login failed:" << pInfo->ip << pServer->getLastError() << pServer->factory()->name();
				}
			}));

			::Sleep(1000);

			
		}
	}

	DestroySearchObj(pSearch);
	delete pDevice;
}

//>>>>>>>>>>>>>>add end