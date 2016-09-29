#include "FoundDeviceDialog.h"
#include "ui_FoundDeviceDialog.h"
#include "qss.h"
#include "PING.h"
#include <QMessageBox>
#include "dialoglogineddevices.h"
#include "loginddevicedialog.h"
#include "messageboxdlg.h"
#include "cwaitdlg.h"
#include "uiutils.h"
#include "windowutils.h"
#include "utils.h"
#include "netdlg.h"
#include "IPConfigSucessDialog.h"



#define     IP_CONFIG_GUIDE_TITLE  QStringLiteral("IP自动匹配向导")
FoundDeviceDialog::FoundDeviceDialog(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::FoundDeviceDialog)
{
    ui->setupUi(this);
    ui->ip_tableWidget->horizontalHeader()->setSectionsClickable(false);

    ui->ip_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->ip_tableWidget->setFocusPolicy(Qt::NoFocus);
    title_label->setStyleSheet("QLabel"
        "{"
        "font-size:28px;"
        "color: rgb(255, 255, 255);"
        "border-color: rgba(255, 255, 255, 0);"
        "background-color: rgba(255, 255, 255, 0);"
        "font-family:Microsoft Yahei;"
        "}");
    title_label->setText(QStringLiteral("发现设备"));
    connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
    connect(ui->pushButtonOther, SIGNAL(clicked()), this, SLOT(onPushButtonOtherClicked()));
    this->init();

}

FoundDeviceDialog::~FoundDeviceDialog()
{
    delete ui;
}

void FoundDeviceDialog::addToTableWidget(const DeviceInfo& d){
    int row = ui->ip_tableWidget->rowCount();
    ui->ip_tableWidget->insertRow(row);

    QTableWidgetItem *pItem = new QTableWidgetItem();
    pItem->setText(d.szIP.c_str());
    pItem->setTextAlignment(Qt::AlignHCenter);
    ui->ip_tableWidget->setItem(row, 0, pItem);

    pItem = new QTableWidgetItem();
    pItem->setText(QString::number(d.nPort));
    pItem->setTextAlignment(Qt::AlignHCenter);
    ui->ip_tableWidget->setItem(row, 1, pItem);

    pItem = new QTableWidgetItem();
    auto p = videoserverFactory::getFactory(d.Factory);
    if (p)
    {
        pItem->setText(p->name());

    }
    pItem->setTextAlignment(Qt::AlignHCenter);
    ui->ip_tableWidget->setItem(row, 2, pItem);
}


void FoundDeviceDialog::init(){
    qDebug() << "FoundDeviceDialog::init";
    mDeviceInfos.clear();
    std::deque<videoserverFactory *> allFacs;
    allFacs.push_back(videoserverFactory::getFactory(SISC_IPC_DIZHIPU));
    allFacs.push_back(videoserverFactory::getFactory(SISC_IPC_JXJ));
    allFacs.push_back(videoserverFactory::getFactory(SISC_IPC_DH));
    std::shared_ptr< std::map<std::string, DeviceInfo> > pMpDIs = std::make_shared< std::map<std::string, DeviceInfo> >();
    std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
    CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("发现设备中..."), [=, this]()
    {
        for (int i = 0; i < allFacs.size(); i++)
        {
            auto p = allFacs[i];
            if (p == nullptr || p->IsOEMFac())
            {
                continue;
            }
            qDebug() << p->name() << (int)p->factory();
            std::vector<DeviceInfo> vcDI;
            if (p->searchDevice(vcDI))
            {
                qDebug() << "p->searchDevice";
                for (int j = 0; j < vcDI.size(); j++)
                {
                    (*pMpDIs)[vcDI[j].szIP] = vcDI[j];
                }
            }
        }
    },[=, this](bool bCancel){
            for (auto it = pMpDIs->begin(); it != pMpDIs->end(); it++)
            {
                this->addToTableWidget(it->second);
                mDeviceInfos.push_back(it->second);
            }
            if (pMpDIs->size() == 0)
            {
                UIUtils::showTip(*this->ui->pushButtonOther, QStringLiteral("未发现到设备，请点击“其它设备”按钮进行设备搜索"));
            }

        }, bpCancel);


}

bool setNetwork(const QString& ipDevice, std::shared_ptr<bool> bpCancel){

    QString sNet(ipDevice.mid(0, ipDevice.lastIndexOf(".") + 1));
    std::vector<QString> ips;
    WindowUtils::getLocalIPs(ips);
    for (int i = 0; i < ips.size(); i++)
    {
        if (ips[i].mid(0, ips[i].lastIndexOf(".") + 1) == sNet)
        {
            return true;
        }
    }

    QString ip;
    QString mask;
    QString netGate;
    if (WindowUtils::setIPByDHCP(ip, mask, netGate, bpCancel)){
        if (ip.mid(0, ip.lastIndexOf(".") + 1) == sNet)
        {
            return true;
        }
    }
    if (bpCancel && *bpCancel)
    {
        return false;
    }
    QString sName = WindowUtils::getLoacalNetName();
    QString setIP;
    for (int i = 254; i > 1; i--)
    {
        setIP = sNet + QString::number(i);
        if (setIP != ipDevice)
        {
            if (WindowUtils::setNetConfig(sName, setIP, "255.255.255.0", sNet + "1", true, bpCancel)){
                return true;
            }
        }
    }

    
    return false;
}

void FoundDeviceDialog::onLoginClicked()
{
    if (!WindowUtils::isOnLine())
    {
        UIUtils::showTip(*this,
            QString::fromLocal8Bit("本地连接断开，请插好网线或开启本地连接！"));
        return;
    }
    

    int row = ui->ip_tableWidget->currentRow();
    if (row > -1 && row < mDeviceInfos.size())
    {

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

        std::shared_ptr<int> login_result = std::shared_ptr<int>(new int());
        *login_result = 0;
        mResults.clear();
        this->enableButton(false);
        
        std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
        CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在初始化..."), [=, this]()
        {
            DeviceInfo& d = this->mDeviceInfos[row];
            bool b = setNetwork(d.szIP.c_str(), bpCancel);
            if (*bpCancel)
            {
                return;
            }
            if (!b)
            {
                b = setNetwork(d.szIP.c_str(), bpCancel);
                if (*bpCancel)
                {
                    return;
                }
            }
            if (!b)
            {
                UIUtils::showTip(*this,
                    QString::fromLocal8Bit("与设备不在同一网络中，请检查一下！"));
                return;
            }

            auto pFactory = videoserverFactory::getFactory(d.Factory);
            auto pServer = pFactory->create();
            if (!pServer)
            {
                qDebug() << "nullptr == pServer";
                return;
            }
            if (*bpCancel)
            {
                qDebug() << __FUNCTION__<<__LINE__;
                return;
            }
            std::shared_ptr<LoginServerInfo> pInfo = std::shared_ptr<LoginServerInfo>(new LoginServerInfo());
            pInfo->factory = d.Factory;
            pInfo->ip = d.szIP.c_str();
            pInfo->id = pInfo->ip + QString::number(QDateTime::currentDateTime().toTime_t());
            pInfo->name = QString("%1(%2)").arg(pFactory->name()).arg(pInfo->ip);
            pInfo->port = d.nPort;
            if (pInfo->port == 0)
            {
                pInfo->port = pServer->factory()->port();
            }

            pInfo->password = password;
            pInfo->user = user;
            if (pServer->login(pInfo, bpCancel.get()))
            {
                if (!*bpCancel)
                {
                    mResults.push_back(pInfo);
                }
            }
            else
            {
                qDebug() << "login failed:" << pServer->getLastError() << pServer->factory()->name();
            }
        }, [=, this](bool bCancel){
            qDebug() << "if (!*login_result)";
            if (*bpCancel)
            {
                qDebug() << __FUNCTION__ << __LINE__;
                mResults.clear();
            }
            else
            {
                if (mResults.size() == 0)
                {
                    MessageBoxDlg msgDlg(QString::fromLocal8Bit("登陆失败！"));
                    msgDlg.exec();
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
            this->enableButton(true);
        }, bpCancel);
    }

}
void FoundDeviceDialog::startLoginDlg(){
    LogindDeviceDialog dlg(this);
    qDebug() << __FUNCTION__ << __LINE__;
    dlg.exec();
    this->mResults = dlg.getLoginServerInfo();
    this->accept();
}
void FoundDeviceDialog::onPushButtonOtherClicked(){
    this->enableButton(false);
    ipConfigGuide();
    this->enableButton(true);
}


void FoundDeviceDialog::mannulConfigNet(){
    netDlg netDlg_(this->parentWidget());
    netDlg_.setTitleName(QStringLiteral("网络配置"));
    netDlg_.exec();
}
void FoundDeviceDialog::configOldNet()
{
    if (this->mIPs.size() > 0)
    {
        QString sNet(this->mIPs[0].mid(0, this->mIPs[0].lastIndexOf(".") + 1));
        qDebug() << __FUNCTION__ << __LINE__ << this->mIPs[0];
        WindowUtils::setNetConfig(WindowUtils::getLoacalNetName(), this->mIPs[0], "255.255.255.0", sNet + "1", true);
    }
}
void FoundDeviceDialog::intelligentConfig(){
    std::shared_ptr<QString> pIP = std::make_shared<QString>();
    std::shared_ptr<QString> pNetGate = std::make_shared<QString>();
    std::shared_ptr<QString> pMask = std::make_shared<QString>("255.255.255.0");
    std::shared_ptr<bool> bResult = std::make_shared<bool>(false);
    std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
    CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在智能匹配，请稍等...."), [=, this]()
    {
        *bResult = WindowUtils::setIPByDHCP(*pIP, *pMask, *pNetGate, bpCancel);
        if (*bpCancel)
        {
            qDebug() << __FUNCTION__ << __LINE__;
            this->configOldNet();
            return;
        }
        if (!*bResult)
        {
            qDebug() << __FUNCTION__ << __LINE__;
            *bResult = WindowUtils::getDirectDevice(*pIP, *pNetGate, bpCancel);
            if (*bpCancel)
            {
                qDebug() << __FUNCTION__ << __LINE__;
                this->configOldNet();
                return;
            }

        }
        this->configOldNet();
    }, [=, this](bool bCancel){
        if (*bpCancel)
        {
            qDebug() << __FUNCTION__ << __LINE__ << "sleep 1000";
            this->startLoginDlg();
            return;
        }
        qDebug() << __FUNCTION__ << __LINE__;
        if (*bResult)
        {
            IPConfigSucessDialog dlg(*pIP, "255.255.255.0", *pNetGate);
            dlg.exec();
            if (dlg.isMannualConfig())
            {
                
                this->mannulConfigNet();
            }
            else{
                CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在设置IP中...."), [=]()
                {
                    WindowUtils::setNetConfig(WindowUtils::getLoacalNetName(), *pIP, "255.255.255.0", *pNetGate, true);
                }, [](bool bCancel){});
            }
        }
        else{
            if (UIUtils::showQuetionBox(IP_CONFIG_GUIDE_TITLE,
                QStringLiteral("智能识别网段失败！重新匹配或手工配置？"), QStringLiteral("重新匹配"),
                QStringLiteral("手工配置")))
            {
                this->intelligentConfig();
                return;
            }
            else{

                this->mannulConfigNet();
            }

        }

        this->startLoginDlg();
    }, bpCancel);
}

void FoundDeviceDialog::ipConfigGuide(){

    //this->hide();
    if (!WindowUtils::isOnLine())
    {
        UIUtils::showTip(*this,
            QString::fromLocal8Bit("本地连接断开，请插好网线或开启本地连接！"));
        return;
    }

    WindowUtils::getLocalIPs(mIPs);
    qDebug()<<__FUNCTION__<<__LINE__<<mIPs.size();
    this->intelligentConfig();
}

void FoundDeviceDialog::deepConfig(){
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
            
        }
        else{
            UIUtils::showTip(*this,
                QString::fromLocal8Bit("智能识别网段失败！请手动设置！"));
            netDlg netDlg_(nullptr);
            netDlg_.setTitleName(QStringLiteral("网络配置"));
            netDlg_.exec();
            
        }

    }, bpCancel);

}

void FoundDeviceDialog::enableButton(bool b){

    closeBtn->setEnabled(b);
    minBtn->setEnabled(b);
    backBtn->setEnabled(b);
    ui->pushButtonConnect->setEnabled(b);
    ui->pushButtonOther->setEnabled(b);
}