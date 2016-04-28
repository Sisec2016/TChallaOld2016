#include "diskdlg.h"
#include "ui_diskdlg.h"
#include "CommonFunc.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>

#include <vector>
#include <string>
#include "cwaitdlg.h"
#include "log.h"
#include "Verify.h"
#pragma comment(lib, "DiskModule.lib")

DiskDlg::DiskDlg(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::DiskDlg)
{
    ui->setupUi(this);

    m_diskDirectoryName = "";
	m_bQuestion = true;
	m_bCover = false;

    ui->sourcefileWidget->setFileCheckedModel(true);
    ui->sourcefileWidget->setMyRootPath(Verify::downloadDirPath());
    ui->sourcePath_label->setText(Verify::downloadDirPath());

	//目标目录
    ui->targetfileWidget->setFileCheckedModel(true);

    cmd = new QProcess;
    connect(cmd, SIGNAL(readyRead()), this, SLOT(readOutput()));

	m_progressDialog = new QProgressDialog(this);
	m_progressDialog->setModal(true);

	connect(m_progressDialog, SIGNAL(canceled()), this, SLOT(onProgressDialogCancel()));
	connect(this, SIGNAL(updateProgressBar(int, int)), this, SLOT(onuUpdateProgressBar(int, int)), Qt::QueuedConnection);
	connect(this, SIGNAL(copyError(T_ErrInfo*)), this, SLOT(onCopyError(T_ErrInfo*)));
    connect(ui->disksSelectDirectoryBtn, SIGNAL(clicked()), this, SLOT(onDiskDirectoryBtn()));
    connect(ui->diskOutputBtn, SIGNAL(clicked()), this, SLOT(onDiskOutputBtn()));
}

DiskDlg::~DiskDlg()
{
	delete m_progressDialog;
    delete ui;
}

void DiskDlg::changeEvent(QEvent *e)
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

void DiskDlg::onProgressDialogCancel()
{
	qDebug() << " onProgressDialogCancel()";
	disk_Stop(m_iHandle);
	ui->targetfileWidget->setMyRootPath(m_diskDirectoryName);
}

void DiskDlg::onuUpdateProgressBar(int iCurPercent, int iTotalPercent)
{
	m_progressDialog->setValue(iTotalPercent);
	qDebug() << iCurPercent << "   " << iTotalPercent;
	if (100 == iTotalPercent)
	{
		disk_Stop(m_iHandle);
	}
	ui->targetfileWidget->setMyRootPath(m_diskDirectoryName);
}

void DiskDlg::onCopyError(T_ErrInfo *pErrorInfo)
{
	ui->targetfileWidget->setMyRootPath(m_diskDirectoryName);
	m_mutex.lock();

	int iErr = pErrorInfo->iErr;

	pErrorInfo->bIsCover = m_bCover;

	//char szPathTo[MAX_PATH];
	//ZeroMemory(szPathTo, MAX_PATH);
	//MbToUtf8(szPathTo, pErrorInfo->szPath);
	
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
		else if(buttonRet == QMessageBox::NoToAll)
		{
			m_bQuestion = false;
			bIsCover = false;
		}
		pErrorInfo->bIsCover = bIsCover;
		m_bCover = pErrorInfo->bIsCover;

		/*
		if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("提示"),
			QStringLiteral("存在相同的 %1，是否要覆盖？").arg(pErrorInfo->szPath), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
		{
			bIsCover = true;
		}
		pErrorInfo->bIsCover = bIsCover;
		m_bCover = pErrorInfo->bIsCover;

		if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("提示"),
			QStringLiteral("以后冲突的文件是否执行同样操作？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
		{
			m_bQuestion = false;
		}*/

	}
	else if (iErr == ERR_UNIMPORTANT )
	{
		QMessageBox::information(this, QStringLiteral("提示"),
			QStringLiteral("导出完成，可能未结束！"));
	}
	else if (iErr == ERR_UNKNOWN)
	{
		QMessageBox::information(this, QStringLiteral("提示"),
			QStringLiteral("未知错误！"));
	}

	m_waitCondition.wakeAll();

	m_mutex.unlock();
}
void DiskDlg::readOutput()
{
    cmd->readAll();

}

void DiskDlg::onDiskDirectoryBtn()
{
    QString foldName = QFileDialog::getExistingDirectory(this,
        QStringLiteral("请选择导出文件夹"), "");


    if (foldName.isEmpty())
    {
        return;
    }

    m_diskDirectoryName = foldName;
    ui->targetfileWidget->setMyRootPath(m_diskDirectoryName);

    ui->diskDirctory_lineEdit->setText(m_diskDirectoryName);
    
}

static void PercentCallback(unsigned int iHandle, unsigned int iUserData, int iCurPercent, int iTotalPercent, int iType, void *pParam)
{
	DiskDlg *pThis = (DiskDlg *)iUserData;
	pThis->PercentCallback2(iHandle, iCurPercent, iTotalPercent, iType, pParam);
}

void DiskDlg::onDiskOutputBtn()
{

 //读勾选的文件
   // std::vector<std::string> &fileVector = ui->sourcefileWidget->getCheckedFile();

    //读勾选的文件
   std::vector<std::string> fileVector1;
   string strPathFrom;
   bool bRet = ui->sourcefileWidget->getCheckedFile1(fileVector1, strPathFrom);

    if(!bRet)
     {
        return;
    }
   //判断是否有要拷贝的文件
/*   int size = fileVector.size();
   qDebug()<<"file count:"<<size;
   if(0==size)
   {
       QMessageBox::information(this, QStringLiteral("提示"),
                                QStringLiteral("请选择文件"));
       return;
   }*/

   if (m_diskDirectoryName.isEmpty())
   {
       QMessageBox::information(this, QStringLiteral("提示"),
                                QStringLiteral("请选择磁盘目录"));
       return;
   }
   if (1 == QMessageBox::question(NULL, QStringLiteral("提示"),
       QStringLiteral("确定导出到 %1？").arg(m_diskDirectoryName), QStringLiteral("是"), QStringLiteral("否")))
   {
	   return;
   }
   
   CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在拷贝中，请稍等..."), [=, this]()
   {
       std::string dirDirect(m_diskDirectoryName.toLocal8Bit().data());
       for (auto itr = fileVector1.begin(); itr != fileVector1.end(); itr++)
       {
           CWaitDlg::setShowMsg(QString::fromLocal8Bit("正在拷贝:") + itr->c_str());
           CopyFileA(itr->c_str(), (dirDirect + "/" + itr->substr(itr->rfind('\\') + 1)).c_str(), false);
       }
      
       
   }, [this](bool bCancel){
       ui->targetfileWidget->setMyRootPath(m_diskDirectoryName);
   });

   /*m_progressDialog->setLabelText(QStringLiteral("正在导出..."));
   m_progressDialog->setRange(0, 100);
   m_progressDialog->setValue(0);
   m_progressDialog->show();
 
   m_bQuestion = true;
   m_bCover = false;
   //add by liyongxing
   QString strPathTo = m_diskDirectoryName;
   strPathTo.replace('/', '\\');

   char szPathTo[MAX_PATH];
   ZeroMemory(szPathTo, MAX_PATH);
   Utf8ToMb(szPathTo, strPathTo.toUtf8().constData());
   char szPathFrom[MAX_PATH];
   ZeroMemory(szPathFrom, MAX_PATH);
   Utf8ToMb(szPathFrom, strPathFrom.c_str());
   std::vector<std::string> vecFilesTmp;
   vecFilesTmp.reserve(fileVector1.size());
   for (std::vector<std::string>::iterator itr = fileVector1.begin(); itr != fileVector1.end(); itr++)
   {
	   char szPath[MAX_PATH];
	   ZeroMemory(szPath, MAX_PATH);
	   Utf8ToMb(szPath, itr->c_str());
	   std::string strPath = szPath;
	   vecFilesTmp.push_back(strPath);
   }
 //  __try
   //{

	  m_iHandle = disk_MoveFiles_2(vecFilesTmp, szPathFrom,
		   szPathTo/*(char *)strPathTo.toUtf8().constData()*, PercentCallback, (unsigned int)this); //toLatin1 toUtf8
  // }
  // __except (EXCEPTION_EXECUTE_HANDLER)
  // {
	//  QDebug()<< "disk copy unkonw error!" ;
   //}
 
   //判断拷贝进度，然后销毁拷贝进程
   //disk_Stop(iHandle);*/
}

void DiskDlg::PercentCallback2(unsigned int iHandle, int iCurPercent, int iTotalPercent, int iType, void *pParam)
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
