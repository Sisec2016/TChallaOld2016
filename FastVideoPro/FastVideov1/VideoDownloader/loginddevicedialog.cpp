#include "PING.h"
#include "loginddevicedialog.h"
#include "ui_loginddevicedialog.h"
#include "videoserver.h"
#include <QCollator>
#include <QNetworkConfigurationManager>

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
#include "Iphlpapi.h"

#pragma comment(lib,"Iphlpapi")

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

    ui->checkBoxDefaultPort->setChecked(true);
    ui->checkBoxSearchIp->setChecked(true);
    initNetCombobox();
    ScreenAdaption::instance().showInCenter(this);

    ui->pushButtonDirect->hide();
    ipConfigGuide();
    this->setPage(1);
}

LogindDeviceDialog::~LogindDeviceDialog()
{
    delete ui;
}

void LogindDeviceDialog::ipConfigGuide(){
    QNetworkConfigurationManager mgr;
    if (!WindowUtils::isOnLine())
    {
        UIUtils::showTip(*this,
            QString::fromLocal8Bit("本地连接断开，请插好网线或开启本地连接！"));
        return;
    }
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
                *bResult = WindowUtils::getDirectDevice(*pIP, *pNetGate);
                if (*bpCancel)
                {
                    return;
                }
                if (*bResult)
                {
                    if (!WindowUtils::setNetConfig(WindowUtils::getLoacalNetName(), *pIP, "255.255.255.0", *pNetGate, true))
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
            if (!WindowUtils::setNetConfig(WindowUtils::getLoacalNetName(), *pIP, "255.255.255.0", *pNetGate, true))
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
    
    std::lock_guard<std::recursive_mutex> lock(mmtPages);
    ui->listViewServers->removeAllItems();
    const std::deque<videoserverFactory *>& Factorys = videoserverFactory::getFactorys();
    std::deque<videoserverFactory *> fs;
    QString sFilter = ui->lineEditFactory->text().toLower();
    for (int i = 0; i < Factorys.size(); i++)
    {
        if (sFilter.isEmpty() || Utils::getChineseSpell(Factorys[i]->name()).toLower().startsWith(sFilter))
        {
            if (nullptr != Factorys[i])
            {
                fs.push_back(Factorys[i]);
            }
            
        }
    }
    
    FormFactoryItem* pFirstItem = NULL;
	for (int i = (mCurrentPage - 1) * NUM_OF_ONEPAGE; i < fs.size() && i < mCurrentPage * NUM_OF_ONEPAGE; ++i)
    {
        FormFactoryItem* pItem = new FormFactoryItem(ui->listViewServers);
        pItem->setFactory(fs[i]);
        ui->listViewServers->addWidgetItem(pItem);
        
        mmpPort[pItem] = fs[i]->port();
        if (NULL == pFirstItem)
        {
            pFirstItem = pItem;
            this->on_factory_Selected(pFirstItem);
        }
    }


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
    if (!WindowUtils::isOnLine())
    {
        UIUtils::showTip(*ui->listViewServers,
            QString::fromLocal8Bit("本地连接断开，请插好网线或开启本地连接！"));
        return;
    }

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

    qDebug()<<pFactory->name()<<pFactory->port();
    QString port(ui->lineEditPort->text());
    if (ui->checkBoxDefaultPort->isChecked())
    {
        port = QString::number(pFactory->port());
    }

    port = port.trimmed();
    qDebug()<<port<<" toUInt():"<<port.toUInt();
    if (port.toStdString().find_first_not_of("1234567890") != std::string::npos || port.isEmpty())
    {
        UIUtils::showTip(*ui->lineEditPort, QString::fromLocal8Bit("请输入正确的端口号！"));
        return;
    }

    qDebug()<<"port:"<<port<<" toUnInt "<<port.toUInt();
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

    this->getIps();
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
    qDebug()<<"正在登陆中...";
    std::shared_ptr<bool> bLock = std::shared_ptr<bool>(new bool(false));
    mResults.clear();
	ui->pushButtonConnect->setEnabled(false);
	ui->closeButton->setEnabled(false);
    std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
    CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在初始化..."), [=]()
    {
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
                    qDebug()<<"nullptr == pServer";
                    return;
                }

                std::shared_ptr<LoginServerInfo> pInfo = std::shared_ptr<LoginServerInfo>(new LoginServerInfo());
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

                

                if (pServer->login(pInfo, bpCancel.get()))
                {
                    qDebug()<<"login succeed!";
                    std::lock_guard<std::recursive_mutex>  lockLoginResult(*mtLoginResult);

                    if (!*bpCancel)
                    {
                        *login_IP = sIP;
                        this->mResults.push_back(pInfo);
                    }
                    qDebug()<<"mResults.push_back";
                }
                else
                {
					//***Modified by ZHQ:20160606***
					//***Error information
					logErrorFact = pInfo->name.trimmed();
					logErrorInfo = pServer->getLastError().trimmed();

					if (logErrorInfo.left(4) == QString::fromLocal8Bit("句柄无效"))
						logErrorInfo = QString::fromLocal8Bit("");
					if (logErrorInfo.left(4) == QString::fromLocal8Bit("没有错误"))
						logErrorInfo = QString::fromLocal8Bit("");
					if (logErrorInfo.left(4) == QString::fromLocal8Bit("未知错误"))
						logErrorInfo = QString::fromLocal8Bit("");

					if (logErrorInfo.isEmpty())
						logErrorInfo = QString::fromLocal8Bit("（可能不是指定厂商/设备！）");
					else
						logErrorInfo = QString::fromLocal8Bit("（%1 或 不是指定厂商/设备！）").arg(logErrorInfo);

                    qDebug()<<"login failed:"<<pServer->getLastError()<<pServer->factory()->name();
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

         qDebug()<<"login end";
	}, [=, this](bool bCancel){
        qDebug()<<"if (!*login_result)";
        if (*bpCancel)
        {
            m_bStop = true;
            mResults.clear();
        }
		else
		{
			if (mResults.size() == 0)
			{
				//***Modified by ZHQ:20160606***
				if (logErrorFact.left(4) == QString::fromLocal8Bit(UNDEFIN_DEVICE_STR))
				{
					logErrorInfo = QString::fromLocal8Bit("(请指定厂商或指定IP地址！)");
				}
								
				MessageBoxDlg msgDlg(QString::fromLocal8Bit("登陆失败！%1").arg(logErrorInfo));

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
            QString sName = WindowUtils::getLoacalNetName();
            WindowUtils::setNetConfig(sName, strIP, "255.255.255.0", strGate, true);
            ui->lineEditIP->setText(strGate);
            ui->checkBoxSearchIp->setChecked(false);
        }
    },[=, this](bool bCancel){
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
    std::lock_guard<std::recursive_mutex> lock(mmtPages);
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

    int maxPage = fs.size() / NUM_OF_ONEPAGE;
    if (fs.size() % NUM_OF_ONEPAGE)
    {
        maxPage++;
    }
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
    __try{

        setPage(++mCurrentPage);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        mCurrentPage--;
        
    }
	
}

void LogindDeviceDialog::on_pushButtonPre_clicked()
{
    __try{
        setPage(--mCurrentPage);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
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
    std::lock_guard<std::recursive_mutex> lock(mmtPages);
    if (ui->checkBoxDefaultPort->isChecked() && mmpPort.find(item) != mmpPort.end())
    {
        ui->lineEditPort->setText(QString::number(mmpPort[item]));
    }
    
}

void LogindDeviceDialog::on_txtSearchFactory_textChanged(const QString &arg1)
{
    __try{
        setPage(1);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {

    }
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