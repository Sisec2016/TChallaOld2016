#include "netdlg.h"
#include "ui_netdlg.h"
#include "qss.h"
#include "PING.h"
#include <QMessageBox>
#include <QNetworkInterface>
#include <QFile>
#include <time.h>
#include <QProcess>

#include "NetConfigModuleApi.h"
#include "logdata.h"
#include "cwaitdlg.h"
#include "uiutils.h"
#include "windowutils.h"
#include <Winsock2.h>
#include <Iphlpapi.h>
#include <IPTypes.h>
#include "pcap.h"

#pragma comment(lib, "NetConfigModule.lib")


#define autoRecognizeBtn_StyleSheet "QPushButton {"\
"border-image: url();"\
        "background-color: rgb(175,211,237);"\
        "border-width: 2px;"\
        "border-color: rgb(175,211,237);"\
        "border-style: solid;"\
        "border-radius: 3;"\
        "padding: 3px;"\
        "min-width: 9ex;"\
        "min-height: 2.5ex;}"\
        "QPushButton:hover{background-color: rgb(255,0,0);}"\
        "QPushButton:pressed{background-color: rgb(0,255,0);}"

#define IPListFile "file/ipListAddress.txt"

netDlg::netDlg(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::netDlg)
{
    ui->setupUi(this);
/*
    ui->gateip_label->setVisible(false);
    ui->GateIPEdit->setVisible(false);
    
    ui->gateip_label_2->setVisible(false);
    ui->curgateip_label->setVisible(false);
*/

    ui->groupBox->setStyleSheet("QGroupBox{color:white}");
    ui->groupBox_2->setStyleSheet("QGroupBox{color:white}");
    ui->groupBox_3->setStyleSheet("QGroupBox{color:white}");

   // ui->ip_tableWidget->horizontalHeader()->setFixedHeight(35); //设置表头的高度
    ui->ip_tableWidget->horizontalHeader()->setSectionsClickable(false);

    ui->ip_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui->ip_tableWidget->setAlternatingRowColors(true);
	ui->ip_tableWidget->setFocusPolicy(Qt::NoFocus);

    readIPListFile();

    getIPInterfaces();
    refreshIPAddress();

	QString strText = "192.168.1.";
	ui->IPEdit->setDefaultText(strText);
	strText = "255.255.255.0";
	ui->MaskIPEdit->setDefaultText(strText);
	strText = "192.168.1.1";
	ui->GateIPEdit->setDefaultText(strText);
    connect(ui->searchBtn, SIGNAL(clicked()), this, SLOT(onSearchClicked()));
    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(onAddClicked()));
    connect(ui->deleteBtn,SIGNAL(clicked()),this,SLOT(onDeleteClicked()));
    connect(ui->configBtn,SIGNAL(clicked()),this,SLOT(onConfigClicked()));

}

netDlg::~netDlg()
{
    delete ui;
}

void netDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void netDlg::getIPInterfaces()
{
#if 0
    //获取所有网络接口的列表
    foreach (m_netInterface, QNetworkInterface::allInterfaces())
    {
        //设备名
       // qDebug() << "Device:" << netInterface.name();

        //MAC地址
      //  qDebug() << "HardwareAddress:" << netInterface.hardwareAddress();

        QList<QNetworkAddressEntry> entryList = m_netInterface.addressEntries();

        bool bFind  = false;
        //遍历每一个IP地址(每个包含一个IP地址，一个子网掩码和一个广播地址)
        foreach(QNetworkAddressEntry entry, entryList)
        {
            QHostAddress address = entry.ip();

            if(address.protocol() == QAbstractSocket::IPv4Protocol &&
               address != QHostAddress::Null &&
               address != QHostAddress::LocalHost){
                if (address.toString().contains("127.0.")){
                  continue;
                }
                m_hostAddressEntry = entry;
                bFind = true;
                break;
            }
        }

            //广播地址
           // qDebug() << "Broadcast:" << entry.broadcast().toString();
        if(bFind)
        {
            break;
        }
    }
	
#else
	char szIP[20];
	char szNetMask[20];
	char szGate[20];
	netconfig_GetIP(szIP, szNetMask, szGate, 20);

	m_strIp = szIP;
	m_strNetMask = szNetMask;
	m_strGate = szGate;
#endif
 }

void netDlg::refreshIPAddress()
{
    //IP地址
    ui->curip_label->setText(m_strIp);

    //子网掩码
    ui->curmaskip_label->setText(m_strNetMask);

	//网关  编译不过
 	ui->curgateip_label->setText(m_strGate);

}


void netDlg::closeEvent(QCloseEvent * e )
{
    qDebug()<<" closeEvent";
    writeIPListFile();
}


void netDlg::readIPListFile()
{
   // m_listHostIPAddress.a
    QFile file(IPListFile);
    if(file.open(QIODevice::ReadOnly|QFile::Text))//QIODevice ReadOnly
    {
        qDebug()<<"read open";
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QString str = stream.readLine();
            QStringList stripAddress = str.split(" ");
            int count = stripAddress.count();
            T_Host_IPAddress t_HostIPAddress;
            for(int i=0;i<count;i++)
            {
                if(i==0)
                {
                    t_HostIPAddress.strIP = stripAddress.at(0);
                }
                else if(i==1)
                {
                    t_HostIPAddress.strMaskIP = stripAddress.at(1);
                }
                else if(i==2)
                {
                    t_HostIPAddress.strGateIP = stripAddress.at(2);
                }

            }
            m_listHostIPAddress.append(t_HostIPAddress);
            addToTableWidget(&t_HostIPAddress);
        }

       file.close();
    }

}

void netDlg::writeIPListFile()
{
    QFile file(IPListFile);//QIODevice::WriteOnly
    if (file.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug()<<"write open";

        QTextStream out(&file);

        int count = m_listHostIPAddress.count();
        for(int i = 0;i < count;i++)
        {
            out <<m_listHostIPAddress.at(i).strIP<<" "<<m_listHostIPAddress.at(i).strMaskIP<<" "<<m_listHostIPAddress.at(i).strGateIP<<"\n";


        }
        file.close();
     }
}





void netDlg::onSearchClicked()
{
    std::shared_ptr<bool> bResult = std::make_shared<bool>(false);
    CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在智能识别，请稍等..."), [=, this]()
    {
        CWaitDlg::setShowMsg(QString::fromLocal8Bit("正在识别网关..."));
        *bResult = WindowUtils::setIPByDHCP(m_strIp, m_strNetMask, m_strGate);
        QString sName = QString::fromLocal8Bit("本地连接");

        CWaitDlg::setShowMsg(QString::fromLocal8Bit("正在智能识别..."));
        if ((!*bResult) && WindowUtils::getDirectDevice(m_strIp, m_strGate))
        {
            m_strNetMask = "255.255.255.0";
            WindowUtils::setNetConfig(sName, m_strIp, m_strNetMask, m_strGate);
            *bResult = true;
        }

//         for (int i = 0; i < 255 && (!*bResult); i++)
//         {
//             QString sIP = QString("192.168.%1.1").arg(i);
//             WindowUtils::setNetConfig(sName, sIP, "255.255.255.0", "", true);
// 
//             CWaitDlg::setShowMsg(QString::fromLocal8Bit("正在智能识别直连设备(192.168.%1.0)...").arg(i));
//             if (CPing::instance().ScanOneIP(sRIP, sIP, true))
//             {
//                 WindowUtils::setNetConfig(sName, sIP, "255.255.255.0", sRIP);
//                 m_strIp = sIP;
//                 m_strNetMask = "255.255.255.0";
//                 m_strGate = sRIP;
//                 *bResult = true;
//                 break;
//             }
//         }

    }, [=, this](bool bCancel){
        if (*bResult)
        {
            UIUtils::showTip(*ui->searchBtn,
                QString::fromLocal8Bit("智能识别网段成功！"));
            this->refreshIPAddress();
        }
        else{
            UIUtils::showTip(*ui->searchBtn,
                QString::fromLocal8Bit("智能识别网段失败！请检查网络再重试，或者手工进行配置。"));
        }

    });
}

void netDlg::onAddClicked()
{
    // IP地址验证
    QString strIP = ui->IPEdit->text();
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);
    int nPos = 0;
    QValidator::State state = regexp_validator.validate(strIP, nPos);
    // IP不合法
    if (state != QValidator::Acceptable)
    {
        QMessageBox msg;
        msg.setText("Invalid IPAddress!");
        msg.exec();
        return;
    }
 // 子网掩码验证
    QString strMaskIP = ui->MaskIPEdit->text();
    state = regexp_validator.validate(strMaskIP, nPos);
    if (state != QValidator::Acceptable)
    {
        QMessageBox msg;
        msg.setText("Invalid MaskIPAddress!");
        msg.exec();
        return;
    }


 // 默认网关验证

    QString strGateIP = ui->GateIPEdit->text();
    state = regexp_validator.validate(strGateIP, nPos);
    if (state != QValidator::Acceptable)
    {
        QMessageBox msg;
        msg.setText("Invalid GateIPAddress!");
        msg.exec();
        return;
    }

    //比较是否含有相同的IP地址
    int count = m_listHostIPAddress.count();
    if(count!=0)
    {
        //比较是否含有相同的IP
        for(int i = 0;i<count;i++)
        {
            T_Host_IPAddress t_HostIPAddress = m_listHostIPAddress.at(i);
            if(strIP==t_HostIPAddress.strIP/* && strMaskIP==t_HostIPAddress.strMaskIP
               && strGateIP==t_HostIPAddress.strGateIP*/)
            {
                QMessageBox msg;
                msg.setText("IP Has Existed!");
                msg.exec();
                return;
            }
        }
    }

    T_Host_IPAddress t_HostIPAddress;
    t_HostIPAddress.strIP = strIP;
    t_HostIPAddress.strMaskIP = strMaskIP;
    t_HostIPAddress.strGateIP = strGateIP;

    m_listHostIPAddress.append(t_HostIPAddress);
    addToTableWidget(&t_HostIPAddress);
    writeIPListFile();
    Logdata::WriteLog(LOG_NetConfig_STR, QStringLiteral("添加IP%1成功!").arg(strIP));
}

void netDlg::addToTableWidget(T_Host_IPAddress *phostIPAddress)
{
    int row = ui->ip_tableWidget->rowCount();
    ui->ip_tableWidget->insertRow(row);

    QTableWidgetItem *pItem = new QTableWidgetItem();
    pItem->setText(phostIPAddress->strIP);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->ip_tableWidget->setItem(row,0,pItem);

    pItem = new QTableWidgetItem();
    pItem->setText(phostIPAddress->strMaskIP);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->ip_tableWidget->setItem(row,1,pItem);

    pItem = new QTableWidgetItem();
    pItem->setText(phostIPAddress->strGateIP);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->ip_tableWidget->setItem(row,2,pItem);

}

void netDlg::onDeleteClicked()
{

    int row = ui->ip_tableWidget->currentRow();
    if(row>-1)
    {
		if (QMessageBox::No == QMessageBox::question(this, QStringLiteral("提示"),
			QStringLiteral("确定要删除 %1 ?"  ).arg(m_listHostIPAddress.at(row).strIP), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
		{
			return;
		}

        Logdata::WriteLog(LOG_NetConfig_STR, QStringLiteral("删除IP%1成功!").arg(m_listHostIPAddress.at(row).strIP));

        m_listHostIPAddress.removeAt(row);
        ui->ip_tableWidget->removeRow(row);
    }
}

void netDlg::onConfigClicked()
{
    //liyounxing
    int row = ui->ip_tableWidget->currentRow();
    if(row>-1)
    {
        T_Host_IPAddress t_HostIPAddress = m_listHostIPAddress.at(row);
		
        Logdata::WriteLog(LOG_NetConfig_STR, QStringLiteral("设置IP%1成功!").arg(m_listHostIPAddress.at(row).strIP));
       //add by liyongxing
		bool bRet = netconfig_SetIP((char *)t_HostIPAddress.strIP.toLatin1().constData(),
			(char *)t_HostIPAddress.strMaskIP.toLatin1().constData(),
			(char *)t_HostIPAddress.strGateIP.toLatin1().constData());
        QString addr = QString("addr=%1").arg(t_HostIPAddress.strIP);
        QString mask = QString("mask=%1").arg(t_HostIPAddress.strMaskIP);
        QString gateway = QString("gateway=%1").arg(t_HostIPAddress.strGateIP);
        QString sName = QString("name=\"%1\"").arg(QString::fromLocal8Bit("本地连接"));
        QProcess::execute("netsh", QStringList() <<
            "interface" << "ip" << "set" << "address"
            << sName << "source=static" << addr << mask << gateway);
        //m_hostAddressEntry.setIp(QHostAddress("192.168.10.103"));
		getIPInterfaces();
        refreshIPAddress();
    }

}
