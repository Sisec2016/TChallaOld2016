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

        }, bpCancel);


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
        std::shared_ptr<std::recursive_mutex> mtLoginResult = std::shared_ptr<std::recursive_mutex>(new std::recursive_mutex());;
        mResults.clear();
        ui->pushButtonConnect->setEnabled(false);
        std::shared_ptr<bool> bpCancel = std::make_shared<bool>(false);
        CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在初始化..."), [=, this]()
        {
            DeviceInfo& d = mDeviceInfos[row];
            auto pFactory = videoserverFactory::getFactory(d.Factory);
            auto pServer = pFactory->create();
            if (!pServer)
            {
                qDebug() << "nullptr == pServer";
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
                std::lock_guard<std::recursive_mutex>  lockLoginResult(*mtLoginResult);

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
            ui->pushButtonConnect->setEnabled(true);

        }, bpCancel);
    }

}

void FoundDeviceDialog::onPushButtonOtherClicked(){

    LogindDeviceDialog dlg(this);
    dlg.exec();
    this->mResults = dlg.getLoginServerInfo();
    this->accept();
}