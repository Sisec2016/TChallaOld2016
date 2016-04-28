#include "ftpdlg.h"
#include "ui_ftpdlg.h"

#include <time.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "logdata.h"
#include "Verify.h"

#define FTPPathListFile "file/FTPPathListAddress.txt"

/************************************************************************************
								ftpclient 代码
************************************************************************************/

Ftpclient::Ftpclient(QObject *parent):QObject(parent)
{
	m_ftp = NULL;
	currentPath = "";
	UpLoadprogressDialog = new QProgressDialog((QWidget*)parent);	//upload
}

Ftpclient::~Ftpclient()
{

}

int Ftpclient::ftpConnect(T_FTPPath *pFTPPath)
{
	if(m_ftp != NULL)
	{
		ftpDisConnect();
	}

	if(m_ftp == NULL)
	{
		if(pFTPPath == NULL)
		{
			return -1;
		}
		isDirectory.clear();
		DirectoryLatinName.clear();
		m_ftp = new QFtp(this);
		connect(m_ftp, SIGNAL(commandFinished(int ,bool)), this, SLOT(ftpCommandFinished(int,bool)));
		connect(m_ftp, SIGNAL(listInfo(const myQUrlInfo&)), this, SLOT(addToList(const myQUrlInfo&)));
		connect(m_ftp, SIGNAL(dataTransferProgress(qint64,qint64)), this, SLOT(updateDataTransferProgress1(qint64,qint64)));

		currentPath = "";
		m_ftp->connectToHost(pFTPPath->strFtpHost, pFTPPath->strFtpPort.toUShort());
		m_ftp->login(pFTPPath->strUser, pFTPPath->strPwd);
		return 1;
	}
}

int Ftpclient::ftpDisConnect()
{
	m_ftp->abort();
	m_ftp->deleteLater();
	m_ftp = NULL;
	currentPath = "";

	emit cmdConnected(false);
	return 0;
}

void Ftpclient::cdParent()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	//isDirectory.clear();
	//为了设置返回键是否其作用
	currentPath = currentPath.left(currentPath.lastIndexOf('/'));
	if(currentPath.isEmpty())
	{
		m_ftp->cd("/");
		//为了设置返回键是否其作用
		start = true;
	}
	else
	{
		m_ftp->cd(currentPath);
		start = true;
	}
	m_ftp->list();
}

void Ftpclient::cdChild(QString dir)
{
	isDirectory.clear();
	DirectoryLatinName.clear();
	currentPath += "/" +dir;
	m_ftp->cd(dir);
	m_ftp->list();
	start = true;
	QApplication::setOverrideCursor(Qt::WaitCursor);		
}

void Ftpclient::cdDir(QString dir)
{
	isDirectory.clear();
	DirectoryLatinName.clear();
	currentPath = dir;
	m_ftp->cd(currentPath);
	m_ftp->list();
	start = true;
	QApplication::setOverrideCursor(Qt::WaitCursor);	
}

void Ftpclient::ftpCommandFinished(int,bool error)
{
	if (m_ftp->currentCommand() == QFtp::ConnectToHost) 
	{
		if (error) 
		{
			QApplication::restoreOverrideCursor();
			emit cmdConnected(false);
			return;
		}
	}
	if(m_ftp->currentCommand() == QFtp::Login)
	{
		m_ftp->list();
		emit cmdConnected(true);
	}
	if(m_ftp->currentCommand() == QFtp::Get)
	{
		QApplication::restoreOverrideCursor();
		if(error)
		{
			m_file->close();
			//m_file->remove();
			emit cmdGot(false);
		}
		else
		{
			//not ftp->close();否则下载完一个文件后ftp就断开了，
			m_file->close();

			emit cmdGot(true);
		}
		//progressDialog->hide();
		delete m_file;
	}
	if(m_ftp->currentCommand() == QFtp::Put)
	{
		QApplication::restoreOverrideCursor();
		if(error){
			m_file->close();
			//file->remove();
			emit cmdPut(false);
		}
		else
		{
			//not ftp->close();否则下载完一个文件后ftp就断开了，
			m_file->close();
			emit cmdPut(true);
		}
		//假如取消文件传送 delete file 会将本地文件删掉，所以不能使用。
		//progressDialog1->hide();
	}
	else if(m_ftp->currentCommand() == QFtp::List)
	{
		QApplication::restoreOverrideCursor();
		if(isDirectory.empty())
		{
			emit cmdList(true);
		}
	}

}

void Ftpclient::addToList(const myQUrlInfo& urlInfo)
{
	isDirectory[urlInfo.name()] = urlInfo.isDir();
	DirectoryLatinName[urlInfo.name().toLatin1()] = urlInfo.name();
	emit cmdChangeList(urlInfo);
}

void Ftpclient::putFile(QString& fileName, QString& filePath)
{
	fileName.replace('\\', '/');
	filePath.replace('\\', '/');
	if(fileName.isEmpty())
	{
		QMessageBox::information(0,tr("FTP"),
			tr("file: %1 error .").arg(fileName));
		return;
	}
	QString newFilePath = filePath + '/';
	QString newDirFile = fileName.mid(newFilePath.length());
	int num = newDirFile.lastIndexOf('/');
	QString newFile = newDirFile.mid(num + 1);
	// 	if (num != -1)
	// 	{
	// 		QString CreateDir = newDirFile.left(num);
	// 
	// 		int ret = m_ftp->cd(CreateDir);
	// 		cdChild(CreateDir);
	// 		m_ftp->mkdir(CreateDir);
	// 	}

	m_file = new QFile(fileName);
	if(!m_file->open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, QStringLiteral("FTP"),
			QStringLiteral("uploading file: %1 failed: %2").arg(fileName).arg(m_file->errorString()));
		delete m_file;
		return;
	}
	m_ftp->put(m_file, currentPath + "/" + newFile);

	emit cmdUploading();
}

void Ftpclient::updateDataTransferProgress1(qint64 readBytes,qint64 totalBytes)
{
	UpLoadprogressDialog->setMaximum(totalBytes);
	UpLoadprogressDialog->setValue(readBytes);
}

/************************************************************************************
								FTPDlg 代码
************************************************************************************/
FTPDlg::FTPDlg(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::FTPDlg),
	m_ftpClient(new Ftpclient(this))
{
    ui->setupUi(this);

	QIcon icon;
	icon.addFile(QString::fromUtf8(":/images/folderBack.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->ParentDirBtn->setIcon(icon);
	ui->ParentDirBtn->setEnabled(false);

    ui->sourcefileWidget->setFileCheckedModel(true);
    ui->sourcefileWidget->setMyRootPath(Verify::downloadDirPath());
    ui->sourcePath_label->setText(Verify::downloadDirPath());

    ui->FTPPath_tableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->FTPPath_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->FTPPath_tableWidget->setAlternatingRowColors(true);

    readFTPPathListFile();

    connect(ui->AddFTPPathBtn, SIGNAL(clicked()), this, SLOT(onAddFTPPathBtn()));
    connect(ui->ModifyFTPPathBtn, SIGNAL(clicked()), this, SLOT(onModifyFTPPathBtn()));
    connect(ui->DelFTPPathBtn, SIGNAL(clicked()), this, SLOT(onDelFTPPathBtn()));
    connect(ui->OutputFTPBtn, SIGNAL(clicked()), this, SLOT(onOutputFTPBtn()));

    //connect(ui->sharePath_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem * )), this, SLOT(onItemDoubleClicked(QTableWidgetItem*)));
    connect(ui->FTPPath_tableWidget, SIGNAL(itemClicked(QTableWidgetItem * )), this, SLOT(onItemClicked(QTableWidgetItem*)));


	connect(m_ftpClient, SIGNAL(cmdChangeList(const myQUrlInfo &)), this,SLOT(changeList(const myQUrlInfo &)));
	connect(m_ftpClient, SIGNAL(cmdConnected(bool)), this, SLOT(onConnect(bool)));
	connect(m_ftpClient, SIGNAL(cmdGot(bool)), this, SLOT(onGet(bool)));
	connect(m_ftpClient, SIGNAL(cmdPut(bool)), this, SLOT(onPut(bool)));
	connect(m_ftpClient, SIGNAL(cmdList(bool)), this, SLOT(onList(bool)));

	connect(ui->FTP_SERVER_DIR, SIGNAL(itemActivated(QTreeWidgetItem *, int)), this, SLOT(processItem(QTreeWidgetItem *, int)));
	connect(ui->ParentDirBtn, SIGNAL(clicked()),this,SLOT(cdParent()));
}

FTPDlg::~FTPDlg()
{
	delete m_ftpClient;
    delete ui;
}

void FTPDlg::changeEvent(QEvent *e)
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
void FTPDlg::closeEvent(QCloseEvent * e )
{
    QDialog::closeEvent(e);
    writeFTPPathListFile();
}

void FTPDlg::readFTPPathListFile()
{
    // m_listHostIPAddress.a
    QFile file(FTPPathListFile);
    if(file.open(QIODevice::ReadOnly|QFile::Text))//QIODevice ReadOnly
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QString str = stream.readLine();
            QStringList strlistFTPPath = str.split(" ");
            int count = strlistFTPPath.count();
            T_FTPPath tFTPPath;
            for(int i=0;i<count;i++)
            {
                if(i==0)
                {
                    tFTPPath.strFtpHost = strlistFTPPath.at(0);
                }
                else if(i==1)
                {
                    tFTPPath.strFtpPort = strlistFTPPath.at(1);
                }
                else if(i==2)
                {
                    tFTPPath.strUser = strlistFTPPath.at(2);
                }
                else if(i==3)
                {
                    tFTPPath.strPwd = strlistFTPPath.at(3);
                }

            }
            m_listFTPPath.append(tFTPPath);
            addToTableWidget(&tFTPPath);
        }

       file.close();
    }

}

void FTPDlg::writeFTPPathListFile()
{
    QFile file(FTPPathListFile);//QIODevice::WriteOnly
    if (file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);

        int count = m_listFTPPath.count();
        for(int i = 0;i < count;i++)
        {
            out <<m_listFTPPath.at(i).strFtpHost<<" "<<m_listFTPPath.at(i).strFtpPort<<" "
                    <<m_listFTPPath.at(i).strUser<<" "<<m_listFTPPath.at(i).strPwd<<"\n";


        }
        file.close();
     }
}

void FTPDlg::addToTableWidget(T_FTPPath *pFTPPath)
{
    int row = ui->FTPPath_tableWidget->rowCount();
    ui->FTPPath_tableWidget->insertRow(row);

    QTableWidgetItem *pItem = new QTableWidgetItem();
    pItem->setText(pFTPPath->strFtpHost);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->FTPPath_tableWidget->setItem(row,0,pItem);

    pItem = new QTableWidgetItem();
    pItem->setText(pFTPPath->strFtpPort);
	pItem->setTextAlignment(Qt::AlignHCenter);
    ui->FTPPath_tableWidget->setItem(row,1,pItem);

}


void FTPDlg::onAddFTPPathBtn()
{
    FTPPathAddDlg dlg;
    dlg.setFTPListPath(&m_listFTPPath);
    if(QDialog::Accepted==dlg.exec())
    {
        T_FTPPath tFTPPath;
        dlg.getFTPPath(tFTPPath);
        m_listFTPPath.append(tFTPPath);
        addToTableWidget(&tFTPPath);
    }
}

void FTPDlg::onModifyFTPPathBtn()
{
    int row = ui->FTPPath_tableWidget->currentRow();
    if(row>-1)
    {
        FTPPathAddDlg dlg;
		dlg.setWindowTitle(QStringLiteral("修改FTP路径"));
        T_FTPPath tCurFTPPath = m_listFTPPath.at(row);
        dlg.setCurFTPPath(tCurFTPPath);
        dlg.setFTPListPath(&m_listFTPPath);
        if(QDialog::Accepted==dlg.exec())
        {
            T_FTPPath tFTPPath;
            dlg.getFTPPath(tFTPPath);
            m_listFTPPath[row].strFtpHost = tFTPPath.strFtpHost;
            m_listFTPPath[row].strFtpPort = tFTPPath.strFtpPort;
            m_listFTPPath[row].strUser = tFTPPath.strUser;
             m_listFTPPath[row].strPwd = tFTPPath.strPwd;

          ui->FTPPath_tableWidget->item(row,0)->setText(m_listFTPPath[row].strFtpHost);
          ui->FTPPath_tableWidget->item(row,1)->setText(m_listFTPPath[row].strFtpPort);
        }
    }
}

void FTPDlg::onDelFTPPathBtn()
{
    int row = ui->FTPPath_tableWidget->currentRow();
    if(row>-1)
    {
		if (QMessageBox::No == QMessageBox::question(this, QStringLiteral("提示"),
			QStringLiteral("确定要删除 %1 ?").arg(m_listFTPPath.at(row).strFtpHost), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
		{
			return;
		}
        m_listFTPPath.removeAt(row);
        ui->FTPPath_tableWidget->removeRow(row);
    }
}

void FTPDlg::onOutputFTPBtn()
{
    //读勾选的文件
   std::vector<std::string> fileVector;
   std::string strPathFrom;
   bool bRet = ui->sourcefileWidget->getCheckedFile1(fileVector, strPathFrom);

    if(!bRet)
     {
        return;
    }
    int row = ui->FTPPath_tableWidget->currentRow();
    if(row <0)
    {
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请选择FTP服务器！"));
        return;
    }

    T_FTPPath tFTPPath = m_listFTPPath.at(row);
	if (QMessageBox::No == QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("确定导出到 %1 ?").arg(tFTPPath.strFtpHost), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
	{
        return;
    }
    //fileVector1 copyto tSharePath.strSharePath
    //add by tianshixiong

	std::vector<std::string>::iterator iter = fileVector.begin();
	for(iter; iter != fileVector.end(); iter++)
	{
		QString strfileName = QString::fromStdString(*iter);
		m_ftpClient->putFile(strfileName, QString::fromStdString(strPathFrom));
	}
	ui->FTP_SERVER_DIR->clear();
	m_ftpClient->cdDir(m_ftpClient->getPath());
}

void FTPDlg::onItemDoubleClicked(QTableWidgetItem * item )
{
    int row = ui->FTPPath_tableWidget->currentRow();
    if(row <0)
    {
        return;
    }

}

void FTPDlg::onItemClicked(QTableWidgetItem * item )
{
    int row = ui->FTPPath_tableWidget->currentRow();
    if(row <0)
    {
        return;
    }
	//add by tianshixiong
    //登陆FTP服务器,成功之后显示目录内容
	T_FTPPath tFTPPath = m_listFTPPath.at(row);
	if (QMessageBox::No == QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("登录到 %1 ?").arg(tFTPPath.strFtpHost), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
	{
		return;
	}
	m_CurHost = tFTPPath.strFtpHost;
	m_ftpClient->ftpConnect(&tFTPPath);
   
	if((m_ftpClient->getPath()).isEmpty())
	{
		ui->DirEdit->setText("");
		return;
	}

	ui->FTP_SERVER_DIR->clear();
}

void	FTPDlg::changeList(const myQUrlInfo &urlInfo)
{
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, urlInfo.name().toLatin1());
	item->setText(1,QString::number(urlInfo.size()));
	item->setText(2,urlInfo.lastModified().toString("yyyy-MM-dd"));

	QPixmap pixmap(urlInfo.isDir() ? ":/images/isdir.png":":/images/isfile.png");
	item->setIcon(0, pixmap);
	
	ui->FTP_SERVER_DIR->addTopLevelItem(item);
	if (!ui->FTP_SERVER_DIR->currentItem()) 
	{
		ui->FTP_SERVER_DIR->setCurrentItem(ui->FTP_SERVER_DIR->topLevelItem(0));
		ui->FTP_SERVER_DIR->setEnabled(true);
	}
}

void FTPDlg::onConnect(bool isConnect)
{
	if(isConnect)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("登录成功"));
        Logdata::WriteLog(LOG_FtpUpload_STR, QStringLiteral("登陆Ftp服务器%1成功!").arg(m_CurHost));

		ui->FTP_SERVER_DIR->clear();
		ui->FTP_SERVER_DIR->setEnabled(true);
	}
	else
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("登录失败"));
        Logdata::WriteLog(LOG_FtpUpload_STR, QStringLiteral("登陆Ftp服务器%1失败!").arg(m_CurHost));

		ui->FTP_SERVER_DIR->clear();
		ui->FTP_SERVER_DIR->setEnabled(false);
	}
}

void FTPDlg::onGet(bool)
{

}

void	FTPDlg::onPut(bool error)
{
	ui->FTP_SERVER_DIR->clear();
	//m_ftpClient->cdDir(m_ftpClient->getPath());
}

void	FTPDlg::onList(bool error)
{
	if(error)
	{
		ui->FTP_SERVER_DIR->setEnabled(false);
	}
	//ui->DirEdit->setText(m_ftpClient->getPath().toLatin1());
	//ui->DirEdit->setText(m_ftpClient->getPath().toUtf8());
	ui->DirEdit->setText(m_ftpClient->getPath().toLatin1());
}

void	FTPDlg::onTopDir(bool isStop)
{
	if(isStop)
	{

	}
	else
	{

	}

}

void FTPDlg::processItem(QTreeWidgetItem* item, int)
{
	QString name = item->text(0);
	QString oldname = m_ftpClient->GetOldName(name);
	if (m_ftpClient->isDir(oldname))
	{
		ui->FTP_SERVER_DIR->clear();
		m_ftpClient->cdChild(oldname);
		QString curDir = m_ftpClient->getPath();
		ui->DirEdit->setText(curDir.toLatin1());
		ui->ParentDirBtn->setEnabled(true);
		return;
	}
}

void FTPDlg::cdParent()
{
	if((m_ftpClient->getPath()).isEmpty()){
		ui->ParentDirBtn->setEnabled(false);
		return;
	}
	m_ftpClient->cdParent();
	ui->ParentDirBtn->setEnabled(true);
	ui->FTP_SERVER_DIR->clear();
	ui->DirEdit->setText(m_ftpClient->getPath().toLatin1());
}