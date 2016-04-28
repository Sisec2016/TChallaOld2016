#include "sharedlg.h"
#include "ui_sharedlg.h"
#include "sharepathadddlg.h"
#include "CommonFunc.h"

#include <QFile>
#include <QTextStream>

#include <QMessageBox>
#include <qdebug.h>

#include "cwaitdlg.h"
#include "Verify.h"
#pragma comment(lib, "mpr.lib")
#pragma comment(lib, "ShareModule.lib")

#define SharePathListFile "file/SharePathListAddress.txt"

ShareDlg::ShareDlg(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::ShareDlg)
{
	m_bLogin = false;

    ui->setupUi(this);
    ui->sourcefileWidget->setFileCheckedModel(true);
    ui->sourcefileWidget->setMyRootPath(Verify::downloadDirPath());
    ui->sourcePath_label->setText(Verify::downloadDirPath());

    ui->targetfileWidget->setFileCheckedModel(false);

	ui->sharePath_tableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->sharePath_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui->sharePath_tableWidget->setAlternatingRowColors(true);
	ui->sharePath_tableWidget->setFocusPolicy(Qt::NoFocus);

    readSharePathListFile();

	m_progressDialog = new QProgressDialog(this);
	m_progressDialog->setModal(true);

	connect(m_progressDialog, SIGNAL(canceled()), this, SLOT(onProgressDialogCancel()));
	connect(this, SIGNAL(updateProgressBar(int, int)), this, SLOT(onuUpdateProgressBar(int, int)));

   connect(ui->AddSharePathBtn, SIGNAL(clicked()), this, SLOT(onAddSharePathBtn()));
    connect(ui->ModifySharePathBtn, SIGNAL(clicked()), this, SLOT(onModifySharePathBtn()));
   connect(ui->DelSharePathBtn, SIGNAL(clicked()), this, SLOT(onDelSharePathBtn()));
   connect(ui->OutputShareBtn, SIGNAL(clicked()), this, SLOT(onOutputShareBtn()));

  // connect(ui->sharePath_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem * )), this, SLOT(onItemDoubleClicked(QTableWidgetItem*)));
     connect(ui->sharePath_tableWidget, SIGNAL(itemClicked(QTableWidgetItem * )), this, SLOT(onItemClicked(QTableWidgetItem*)));

}

ShareDlg::~ShareDlg()
{
    delete ui;
}

void ShareDlg::changeEvent(QEvent *e)
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
void ShareDlg::closeEvent(QCloseEvent * e )
{
    QDialog::closeEvent(e);
    writeSharePathListFile();
}

void ShareDlg::onProgressDialogCancel()
{
	share_Stop(m_iHandle);
	ui->targetfileWidget->setMyRootPath(m_curSharePath.strSharePath);
}

void ShareDlg::onuUpdateProgressBar(int iCurPercent, int iTotalPercent)
{
	m_progressDialog->setRange(0, 100);
	m_progressDialog->setValue(iTotalPercent);
	qDebug() << iCurPercent << "   " << iTotalPercent;
	if (100 == iTotalPercent)
	{
		share_Stop(m_iHandle);
	}
	ui->targetfileWidget->setMyRootPath(m_curSharePath.strSharePath);
}

void ShareDlg::onCopyError(T_ErrInfo *pErrorInfo)
{
	ui->targetfileWidget->setMyRootPath(m_curSharePath.strSharePath);
	m_mutex.lock();

	int iErr = pErrorInfo->iErr;

	pErrorInfo->bIsCover = m_bCover;

	char szPathTo[MAX_PATH];
	ZeroMemory(szPathTo, MAX_PATH);
	MbToUtf8(szPathTo, pErrorInfo->szPath);

	if (iErr == ERR_EXIST && m_bQuestion)
	{
		bool bIsCover = false;
		QMessageBox::StandardButtons buttonRet = QMessageBox::question(this, QStringLiteral("提示"),
			QStringLiteral("存在相同的 %1，是否要覆盖？").arg(pErrorInfo->szPath), QMessageBox::YesToAll | QMessageBox::NoToAll | QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
		{
			bIsCover = true;
		}
		if (buttonRet == QMessageBox::Yes)
		{
			bIsCover = true;
		}
		else if (buttonRet == QMessageBox::YesToAll)
		{
			m_bQuestion = false;
			bIsCover = true;
		}
		else if (buttonRet == QMessageBox::NoToAll)
		{
			m_bQuestion = false;
			bIsCover = false;
		}
		pErrorInfo->bIsCover = bIsCover;
		m_bCover = pErrorInfo->bIsCover;

	}
	else if (iErr == ERR_UNIMPORTANT || iErr == ERR_UNKNOWN)
	{
		QMessageBox::information(this, QStringLiteral("提示"),
			QStringLiteral("未知错误！"));
	}

	m_waitCondition.wakeAll();

	m_mutex.unlock();
}

void ShareDlg::readSharePathListFile()
{
   // m_listHostIPAddress.a
    QFile file(SharePathListFile);
    if(file.open(QIODevice::ReadOnly|QFile::Text))//QIODevice ReadOnly
    {  
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QString str = stream.readLine();
            QStringList strlistSharePath = str.split(" ");
            int count = strlistSharePath.count();
            T_SharePath tSharePath;
            for(int i=0;i<count;i++)
            {
                if(i==0)
                {
                    tSharePath.strName = strlistSharePath.at(0);
                }
                else if(i==1)
                {
                    tSharePath.strSharePath = strlistSharePath.at(1);
                }
                else if(i==2)
                {
                    tSharePath.strUser = strlistSharePath.at(2);
                }
                else if(i==3)
                {
                    tSharePath.strPwd = strlistSharePath.at(3);
                }

            }
            m_listSharePath.append(tSharePath);
            addToTableWidget(&tSharePath);
        }

       file.close();
    }

}

void ShareDlg::writeSharePathListFile()
{
    QFile file(SharePathListFile);//QIODevice::WriteOnly
    if (file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);

        int count = m_listSharePath.count();
        for(int i = 0;i < count;i++)
        {
            out <<m_listSharePath.at(i).strName<<" "<<m_listSharePath.at(i).strSharePath<<" "
                    <<m_listSharePath.at(i).strUser<<m_listSharePath.at(i).strPwd<<"\n";


        }
        file.close();
     }
}

void ShareDlg::addToTableWidget(T_SharePath *pSharePath)
{
    int row = ui->sharePath_tableWidget->rowCount();
    ui->sharePath_tableWidget->insertRow(row);

    QTableWidgetItem *pItem = new QTableWidgetItem();
    pItem->setText(pSharePath->strName);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->sharePath_tableWidget->setItem(row,0,pItem);

    pItem = new QTableWidgetItem();
    pItem->setText(pSharePath->strSharePath);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->sharePath_tableWidget->setItem(row,1,pItem);

}


void ShareDlg::onAddSharePathBtn()
{
    SharePathAddDlg dlg;
    if(QDialog::Accepted==dlg.exec())
    {
        T_SharePath tSharePath;
        dlg.getSharePath(tSharePath);
        m_listSharePath.append(tSharePath);
        addToTableWidget(&tSharePath);
    }
}

void ShareDlg::onModifySharePathBtn()
{
    int row = ui->sharePath_tableWidget->currentRow();
    if(row>-1)
    {
        SharePathAddDlg dlg;
		dlg.setWindowTitle(QStringLiteral("修改共享路径"));
        T_SharePath tCurSharePath = m_listSharePath.at(row);
        dlg.setCurSharePath(tCurSharePath);

        if(QDialog::Accepted==dlg.exec())
        {
            T_SharePath tSharePath;
            dlg.getSharePath(tSharePath);
            m_listSharePath[row].strName = tSharePath.strName;
            m_listSharePath[row].strSharePath = tSharePath.strSharePath;
            m_listSharePath[row].strUser = tSharePath.strUser;
             m_listSharePath[row].strPwd = tSharePath.strPwd;

          ui->sharePath_tableWidget->item(row,0)->setText(m_listSharePath[row].strName);
          ui->sharePath_tableWidget->item(row,1)->setText(m_listSharePath[row].strSharePath);
        }
    }
}

void ShareDlg::onDelSharePathBtn()
{
    int row = ui->sharePath_tableWidget->currentRow();
    if(row>-1)
    {
		if (QMessageBox::No == QMessageBox::question(this, QStringLiteral("提示"),
			QStringLiteral("确定要删除 %1 ?").arg(m_listSharePath.at(row).strSharePath), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
		{
			return;
		}
        m_listSharePath.removeAt(row);
        ui->sharePath_tableWidget->removeRow(row);
    }
}

static void PercentCallback(unsigned int iHandle, unsigned int iUserData, int iCurPercent, int iTotalPercent, int iType, void *pParam)
{
	ShareDlg *pThis = (ShareDlg *)iUserData;
	pThis->PercentCallback2(iHandle, iCurPercent, iTotalPercent, iType, pParam);
}

void ShareDlg::onOutputShareBtn()
{
    //读勾选的文件
   std::vector<std::string> fileVector1;
   std::string strPathFrom;
   bool bRet = ui->sourcefileWidget->getCheckedFile1(fileVector1, strPathFrom);

    if(!bRet)
     {
        return;
    }
    int row = ui->sharePath_tableWidget->currentRow();
    if(row <0)
    {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请选择共享路径目录！"));
        return;
    }

    T_SharePath tSharePath = m_listSharePath.at(row);
    if(QMessageBox::No == QMessageBox::question(this, QStringLiteral("提示"),
                                 QStringLiteral("确定导出到 %1？").arg(tSharePath.strSharePath),QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
    {
        return;
	}
	if (!m_bLogin)
	{
        NETRESOURCEA nr;
        memset(&nr, 0, sizeof (NETRESOURCE));
        std::string s(tSharePath.strSharePath.toLocal8Bit().data());
        nr.dwType = RESOURCETYPE_ANY;
        nr.lpRemoteName = (LPSTR)s.c_str();//"\\\\192.168.1.112\\shread"
        WNetCancelConnection2A(nr.lpRemoteName, CONNECT_UPDATE_PROFILE, true);
        DWORD dwRetVal = WNetAddConnection2A(&nr, (char *)tSharePath.strPwd.toLatin1().constData(), (char *)tSharePath.strUser.toLatin1().constData(), CONNECT_UPDATE_PROFILE);
        if (dwRetVal != NO_ERROR)
        {
            QMessageBox::information(this, QStringLiteral("提示"),
                QStringLiteral("登录共享主机失败！%1").arg(dwRetVal));
            return;
        }

		m_bLogin = true;
	}

    CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在拷贝中，请稍等..."), [=, this]()
    {
        std::string dirDirect(tSharePath.strSharePath.toLocal8Bit().data());
        for (auto itr = fileVector1.begin(); itr != fileVector1.end(); itr++)
        {
            CWaitDlg::setShowMsg(QString::fromLocal8Bit("正在拷贝:") + itr->c_str());
            CopyFileA(itr->c_str(), (dirDirect + "/" + itr->substr(itr->rfind('\\') + 1)).c_str(), false);
        }


    }, [this](bool bCancel){
        ui->targetfileWidget->setMyRootPath(m_curSharePath.strSharePath);
    });

// 	m_progressDialog->setLabelText(QStringLiteral("正在导出..."));
// 	m_progressDialog->setRange(0, 100);
// 	m_progressDialog->setValue(0);
// 	m_progressDialog->show();
// 	m_bQuestion = true;
// 	m_bCover = false;
//     //fileVector1 copyto tSharePath.strSharePath
// 	//add by liyongxing
// 	char szPathTo[MAX_PATH];
// 	ZeroMemory(szPathTo, MAX_PATH);
// 	Utf8ToMb(szPathTo, tSharePath.strSharePath.toUtf8().constData());
// 	char szPathFrom[MAX_PATH];
// 	ZeroMemory(szPathFrom, MAX_PATH);
// 	Utf8ToMb(szPathFrom, strPathFrom.c_str());
// 	std::vector<std::string> vecFilesTmp;
// 	vecFilesTmp.reserve(fileVector1.size());
// 	for (std::vector<std::string>::iterator itr = fileVector1.begin(); itr != fileVector1.end(); itr++)
// 	{
// 		char szPath[MAX_PATH];
// 		ZeroMemory(szPath, MAX_PATH);
// 		Utf8ToMb(szPath, itr->c_str());
// 		std::string strPath = szPath;
// 		vecFilesTmp.push_back(strPath);
// 	}
// 	m_iHandle = share_MoveFiles_2(vecFilesTmp, szPathFrom,
// 		szPathTo, PercentCallback, (unsigned int)this);
	//用定时器定期判断拷贝进度，然后销毁拷贝进程
	//share_Stop(iHandle);

}

void ShareDlg::PercentCallback2(unsigned int iHandle, int iCurPercent, int iTotalPercent, int iType, void *pParam)
{
	if (iType == 0)//进度条报告
	{
		/*
		if (iTotalPercent == 100)
		{
		//导出完成
		qDebug() << " finish";
		return;
		}*/
		emit updateProgressBar(iCurPercent, iTotalPercent);
	}
	else if (iType == 1)//错误报告或文件已存在
	{
		T_ErrInfo *pInfo = (T_ErrInfo *)pParam;

		//导出过程遇到错误
		//ERR_UNKNOWN 致命错误
		emit copyError(pInfo);

		m_mutex.lock();
		m_waitCondition.wait(&m_mutex);
		m_mutex.unlock();
		//qDebug() << " wait";

		//onCopyError(pInfo);
	}
}

void ShareDlg::onItemDoubleClicked(QTableWidgetItem * item )
{
    int row = ui->sharePath_tableWidget->currentRow();
    if(row <0)
    {
        return;
    }

}

void ShareDlg::onItemClicked(QTableWidgetItem * item )
{
    int row = ui->sharePath_tableWidget->currentRow();
    if(row <0)
    {
        return;
    }
 //add by liyongxing
    //登陆共享路径,成功之后显示目录内容
	T_SharePath tSharePath = m_listSharePath.at(row);
	if (!m_bLogin)
	{
        NETRESOURCEA nr;
        memset(&nr, 0, sizeof (NETRESOURCE));
        std::string s(tSharePath.strSharePath.toLocal8Bit().data());
        nr.dwType = RESOURCETYPE_ANY;
        nr.lpRemoteName = (LPSTR)s.c_str();//"\\\\192.168.1.112\\shread"
        WNetCancelConnection2A(nr.lpRemoteName, CONNECT_UPDATE_PROFILE, true);
        DWORD dwRetVal = WNetAddConnection2A(&nr, (char *)tSharePath.strPwd.toLatin1().constData(), (char *)tSharePath.strUser.toLatin1().constData(), CONNECT_UPDATE_PROFILE);
        if (dwRetVal != NO_ERROR)
		{
			QMessageBox::information(this, QStringLiteral("提示"),
				QStringLiteral("登录共享主机失败！%1").arg(dwRetVal));
			return;
		}

		m_bLogin = true;
	}
    ui->targetfileWidget->setMyRootPath(tSharePath.strSharePath);
	m_curSharePath = tSharePath;
}
