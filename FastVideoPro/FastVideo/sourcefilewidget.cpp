#include "sourcefilewidget.h"
#include "ui_sourcefilewidget.h"

#include <QMessageBox>
#include <QInputDialog>

#include <Windows.h>
#include <tchar.h>
#include <shellapi.h>
#include <qdebug.h>

#include <QTextCodec>
#include <QLineEdit>

#include "cwaitdlg.h"

SourcefileWidget::SourcefileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SourcefileWidget)
{
    ui->setupUi(this);
    m_myModel = NULL;

  // ui->treeView->header()->setFixedHeight(15);
   ui->treeView->setAnimated(false);
   ui->treeView->setSortingEnabled(true);//自动排序
    ui->treeView->setDragEnabled(false);//不可拖放
    ui->treeView->header()->setStretchLastSection(true);
//	ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
   // ui->treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    ui->treeView->header()->setSortIndicatorShown(true);
	ui->treeView->header()->setSectionsClickable(true);

	//ui->treeView->setAnimated(false);
	//ui->treeView->setIndentation(100);


    connect(ui->filePlayBtn, SIGNAL(clicked()), this, SLOT(onFilePlayBtn()));
    connect(ui->fileDelBtn, SIGNAL(clicked()), this, SLOT(onFileDelBtn()));
    connect(ui->createDirectoryBtn, SIGNAL(clicked()), this, SLOT(onCreateDirectoryBtn()));

}

SourcefileWidget::~SourcefileWidget()
{
    delete ui;
    if(m_myModel)
    {
        //delete m_myModel;
    }
}

void SourcefileWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SourcefileWidget::setFileCheckedModel(bool bCheck)
{
    if(bCheck)
    {
        m_myModel = new MyFileCheckDirModel;
        ui->createDirectoryBtn->hide();

    }
    else
    {
        m_myModel = new MyFileDirModel;

    }

    m_myModel->setReadOnly(false);
  //  m_myModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
   // ui->treeView->setModel(m_myModel);


}

void SourcefileWidget::setMyRootPath(QString pathName)
{
  // QModelIndex index = m_myModel->index(QDir::currentPath());
	m_myModel->refresh();
	//m_myModel->setRootPath(pathName);
//	m_myModel->setRootPath(QDir::currentPath());
//	QModelIndex index = m_myModel->setRootPath(pathName);
//	QModelIndex index = m_myModel->index(pathName);
	ui->treeView->setModel(m_myModel);
   QModelIndex index = m_myModel->index(pathName);
	ui->treeView->setRootIndex(index);
	//m_myModel->sort(0);
   // ui->treeView->expand(index);
 //   ui->treeView->scrollTo(index);
    ui->treeView->resizeColumnToContents(0);
}

void SourcefileWidget::onFilePlayBtn()
{
    std::vector<std::string> fileVector;
    std::string strPathFrom;
    bool bRet = getCheckedFile1(fileVector, strPathFrom);
    if (fileVector.size() == 0)
    {
        return;
    }
    if (fileVector.size() > 1)
    {
        QMessageBox::information(this, QStringLiteral("提示"),
            QStringLiteral("只能选择一个文件来播放！"), QStringLiteral("确定"));
        return;
    }
    
    
	
    QString strFile = QString::fromLocal8Bit(fileVector[0].c_str());
    strFile ="\""+ strFile+"\"";

    ShellExecute(GetDesktopWindow(), _T("open"), _T("C:\\Program Files (x86)\\OVPlayer\\OVPlayer.exe"), (LPTSTR)strFile.unicode(), NULL, SW_SHOWNORMAL);

}

void SourcefileWidget::onCreateDirectoryBtn()
{
	QModelIndex mkIndex = ui->treeView->currentIndex();
	if (!mkIndex.isValid())
	{
		mkIndex = ui->treeView->rootIndex();
	}
	if (!mkIndex.isValid())
	{
		return;
	}  

	QString dirName = QInputDialog::getText(this, QStringLiteral("新建文件夹"), QStringLiteral("文件夹名称:"), QLineEdit::Normal, QStringLiteral("新建文件夹"));

	if (!m_myModel->fileInfo(mkIndex).isDir())
	{
		mkIndex = mkIndex.parent();
	}

	if (!dirName.isEmpty() && !m_myModel->mkdir(mkIndex, dirName).isValid()) {
	//	if (!dirName.isEmpty() && !m_myModel->mkdir(index, dirName.toUtf8().constData()).isValid()) {
		//QMessageBox::information(this, QStringLiteral("新建文件夹"),
		//	QStringLiteral("Failed to create the directory"));
    }
}

void SourcefileWidget::onFileDelBtn()
{


//     CWaitDlg::waitForDoing(this, QString::fromLocal8Bit("正在删除中，请稍等..."), [=, this]()
//     {
        
        QModelIndex rooIndex = ui->treeView->rootIndex();
        if (!rooIndex.isValid())
        {
            QMessageBox::information(nullptr, QStringLiteral("提示"),
                QStringLiteral("请选择文件"), QStringLiteral("确定"));
            return;
        }

        int row = m_myModel->rowCount(rooIndex);
        std::vector<QString> delIndexs;
        readCheck(rooIndex, delIndexs);
        if (delIndexs.size() == 0)
        {
            QMessageBox::information(nullptr, QStringLiteral("提示"),
                QStringLiteral("请选择文件"), QStringLiteral("确定"));
            return;
        }

        if (1 == QMessageBox::question(NULL, QStringLiteral("提示"),
            QStringLiteral("确定要删除?"), QStringLiteral("是"), QStringLiteral("否")))
        {
            return;
        }
        bool ok = true;
        qDebug() << row;
        for (int i = 0; i < delIndexs.size(); i++)
        {
            ok = deletePath(m_myModel->index(delIndexs[i]));
        }
        qDebug() << "out";
// 
//     }, [this](bool bCancel){
        qDebug() << "refresh beg";
        m_myModel->refresh();
        qDebug() << "refresh end";
/*    });*/
    

   
    
}


//递归删除
bool SourcefileWidget::deletePath(const QModelIndex &parentIndex)
{
    qDebug() << "deletePath()";
    if (!parentIndex.isValid())
    {
        qDebug() << "!isValid()";
        return true;
    }
    
    QFileInfo fileInfo = m_myModel->fileInfo(parentIndex);
    if (!fileInfo.isDir())//文件夹
    {
        qDebug() << "isFile()";
        return m_myModel->remove(parentIndex);
    }
    
    
    
   
    qDebug() << "isDir():";
	bool ok = false;
	int row = m_myModel->rowCount(parentIndex);
    qDebug() << "isDir():" << row;
    while (row > 0){

        QModelIndex index = m_myModel->index(0, 0, parentIndex);
        if (!index.isValid())
        {
            break;
        }
        ok = deletePath(index);
        if (!ok)
        {
            return false;
        }

        row = m_myModel->rowCount(parentIndex);
    }
    
	ok = m_myModel->rmdir(parentIndex);
	return ok;
}

std::vector<std::string>&  SourcefileWidget::getCheckedFile()
{       
    //清除上次勾选的文件
    m_fileVector.clear();


    //读勾选的文件
	QModelIndex rooIndex = ui->treeView->rootIndex ();
	QFileInfo fileInfo = m_myModel->fileInfo(rooIndex);
	QString strFile = fileInfo.filePath();
	m_strPathRoot = std::string(strFile.toLocal8Bit().data());

    readCheckFile(rooIndex);

    return m_fileVector;
}


bool SourcefileWidget::getCheckedFile1(std::vector<std::string> &fileVector, std::string &strPathRoot)
{
    //清除上次勾选的文件
	if (0 != m_fileVector.size())
	{
		m_fileVector.clear();
	}

    //读勾选的文件
	QModelIndex rooIndex = ui->treeView->rootIndex ();
    if (!rooIndex.isValid())
    {
        QMessageBox::information(nullptr, QStringLiteral("提示"),
            QStringLiteral("请选择文件"), QStringLiteral("确定"));
        return false;
    }
	QFileInfo fileInfo = m_myModel->fileInfo(rooIndex);
	QString strFile = fileInfo.filePath();
#ifdef WIN32
	strFile.replace('/', "\\");
#endif
	m_strPathRoot = std::string(strFile.toLocal8Bit().data());

    readCheckFile(rooIndex);

    fileVector = m_fileVector;
	strPathRoot = m_strPathRoot;

    //判断是否有要拷贝的文件
    int size = fileVector.size();
    //qDebug()<<"file count:"<<size;
    if(0==size)
    {
        QMessageBox::information(nullptr, QStringLiteral("提示"),
                                 QStringLiteral("请选择文件"), QStringLiteral("确定"));
        return false;
    }

    return true;
}

//递归
void SourcefileWidget::readCheckFile(QModelIndex &parentIndex)
{
    int row = m_myModel->rowCount(parentIndex);
    for(int i = 0;i<row;i++)
    {
        QModelIndex index = m_myModel->index(i,0,parentIndex);
        Qt::CheckState state = (Qt::CheckState)index.data(Qt::CheckStateRole).toInt();
        if(index.isValid() && state!=Qt::Unchecked)
        {
			QFileInfo fileInfo = m_myModel->fileInfo(index);

			//qDebug()<<fileInfo.filePath()<<"\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                xx,m....................................                                                                                                       jm                                                                                                                                  
			QString strFile = fileInfo.filePath();
#ifdef WIN32
			strFile.replace('/', "\\");
#endif
          
            if(fileInfo.isDir())//文件夹
            {
                 if(m_myModel->hasChildren(index) == true)//含子文件
                 {
                     readCheckFile(index);
					 continue;
                 }
				 else//空文件夹
				 {
					 strFile = "DIR:" + strFile;
				 }
				 
            }

			std::string c_strFile = std::string(strFile.toLocal8Bit().data());
			m_fileVector.push_back(c_strFile);

         }
    }

}

void SourcefileWidget::readCheck(QModelIndex &parentIndex, std::vector<QString>& vcIndexs)
{
    Qt::CheckState pstt = (Qt::CheckState)parentIndex.data(Qt::CheckStateRole).toInt();
    if (pstt == Qt::Unchecked)
    {
        return;
    }
    int row = m_myModel->rowCount(parentIndex);
    std::vector<QString> indexs;
    bool all = true;
    for (int i = 0; i < row; i++)
    {
        QModelIndex index = m_myModel->index(i, 0, parentIndex);
        Qt::CheckState state = (Qt::CheckState)index.data(Qt::CheckStateRole).toInt();
        if (state == Qt::Checked)
        {
            indexs.push_back(m_myModel->filePath(index));
        }
        else if (state == Qt::PartiallyChecked)
        {
            readCheck(index, indexs);
            all = false;
        }
        else{
            all = false;
        }
    }

    if (all)
    {
        vcIndexs.push_back(m_myModel->filePath(parentIndex));
    }
    else{
        for (int i = 0; i < indexs.size(); i++)
        {
            vcIndexs.push_back(indexs[i]);
        }
    }
}
