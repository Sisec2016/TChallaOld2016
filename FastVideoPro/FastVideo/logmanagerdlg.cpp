#include "logManagerDlg.h"
#include "ui_logmanagerDlg.h"

#include "qss.h"
#include <time.h>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCalendarWidget>
#include <QList>
#include <QCloseEvent>
#include <QString>
#include <QTextCodec> 
#include <QtWidgets/QApplication>
#include <QProgressDialog>
#include "uiutils.h"
#include "cwaitdlg.h"
#include "logdata.h"
#include "TaskLogDialog.h"


#pragma comment(lib, "LogModule.lib")


logManagerDlg::logManagerDlg(QWidget *parent) :
    MyBaseDialog(parent),
    ui(new Ui::logManagerDlg)
{
	m_curpage = 1;

    ui->setupUi(this);


	/*
    ui->log_tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
     "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
     "QScrollBar::handle:hover{background:gray;}"
     "QScrollBar::sub-line{background:transparent;}"
     "QScrollBar::add-line{background:transparent;}");

    ui->log_tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
     "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
     "QScrollBar::handle:hover{background:gray;}"
     "QScrollBar::sub-line{background:transparent;}"
     "QScrollBar::add-line{background:transparent;}");*/

  //  ui->log_tableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
	ui->log_tableWidget->horizontalHeader()->setSectionsClickable(false);
//	ui->log_tableWidget->setAlternatingRowColors(true);
	ui->log_tableWidget->setFocusPolicy(Qt::NoFocus);

    QDateTime currentDateTime = QDateTime::currentDateTime();

    ui->dateEdit1->setDateTime(currentDateTime);
    ui->dateEdit2->setDateTime(currentDateTime);
    //ui->timeEdit1->setDateTime(currentDateTime);
    ui->timeEdit2->setDateTime(currentDateTime);

	ui->pastPage->setEnabled(false);
	ui->nextPage->setEnabled(false);

    connect(ui->searchBtn,SIGNAL(clicked()),this,SLOT(onSearchClicked()));
    connect(ui->outputBtn,SIGNAL(clicked()),this,SLOT(onOutputClicked()));

	connect(ui->pastPage,SIGNAL(clicked()),this,SLOT(onPastPageClicked()));
	connect(ui->nextPage,SIGNAL(clicked()),this,SLOT(onNextPageClicked()));

    connect(ui->taskLogBtn, SIGNAL(clicked()), this, SLOT(onTaskLogClicked()));
}

logManagerDlg::~logManagerDlg()
{
	clearLogList();
    delete ui;

}

void logManagerDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) 
	{
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void logManagerDlg::onSearchClicked()
{

	//清空上次查询结果
	ui->log_tableWidget->setRowCount(0);

    QDateTime begTime(ui->dateEdit1->date(), ui->timeEdit1->time());
    QDateTime endTime(ui->dateEdit2->date(), ui->timeEdit2->time());
	
    std::shared_ptr<int> iNum = std::make_shared<int>(0);
    clearLogList();
    if (begTime.toTime_t() > endTime.toTime_t())
    {
        return;
    }

    CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("正在查询中..."), [=]()
    {
        m_logList = Logdata::query(std::make_tuple("mTime", ">", begTime.addSecs(-10).toString(LOG_DATA_TIME_FORMAT)),
            std::make_tuple("mTime", "<", endTime.addSecs(10).toString(LOG_DATA_TIME_FORMAT)));

        *iNum = m_logList.size();
 
    }, [=](bool){
        if (*iNum <= 0)
        {
            UIUtils::showTip(*this, QStringLiteral("当前无日志!"));
            return;
        }
        
        showLogList(1);
    });

	

	

	

}

void logManagerDlg::clearLogList()
{
	m_curpage = 0;

    m_logList.clear();
}


int logManagerDlg::conVertTime(int iyear, int imon, int iday, int ihour, int imin, int isec)
{
	struct tm time;
	time.tm_year = iyear-1900;
	time.tm_mon = imon-1;
	time.tm_mday = iday;
	time.tm_hour = ihour;
	time.tm_min = imin;
	time.tm_sec = isec;
	
	if( time.tm_year<0 ||time.tm_mon<0 ||time.tm_mon>11
		||time.tm_mday<1 ||time.tm_mday>31 ||time.tm_hour<0 
		||time.tm_hour>23 ||time.tm_min<0 ||time.tm_min>59
		||time.tm_sec<0 ||time.tm_sec>59)
	{
		return -1;
	}
		
	return mktime(&time);
}

void logManagerDlg::onOutputClicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
		QStringLiteral("Save Log"), "",
		QStringLiteral("*.txt;;All Files (*)"));
    
    
    
    if (fileName.isEmpty())
        return;
    else {
        if (fileName.indexOf(".txt") < 0)
        {
            fileName += ".txt";
        }

        QFile file(fileName);//QIODevice::WriteOnly
        if (!file.open(QFile::WriteOnly|QFile::Text)) {
			QMessageBox::information(this, QStringLiteral("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream out(&file);

        int row = ui->log_tableWidget->rowCount();
        int col = ui->log_tableWidget->columnCount();
        for(int i = 0;i < row;i++)
        {
          for(int j = 0;j < col;j++)
          {
              QTableWidgetItem *pItem = ui->log_tableWidget->item(i,j);
              if(pItem)
              {
                  out <<pItem->text()<<"  ";
              }

           }
          out << "\n";
        }
        file.close();
    }
}
void logManagerDlg::onPastPageClicked()
{
	//清空上次查询结果
	ui->log_tableWidget->setRowCount(0);
	showLogList(-1);
}

void logManagerDlg::onNextPageClicked()
{
	//清空上次查询结果
	ui->log_tableWidget->setRowCount(0);
	showLogList(1);
}


void logManagerDlg::showLogList(int pageNum)
{
	if (m_logList.size() == 0)
	{
		return;
	}
	if(pageNum > 0)
	{
		m_curpage = m_curpage + 1;
	}
	else
	{
		m_curpage = m_curpage - 1;
	}

	if(m_curpage<=0)
	{
		m_curpage = 1;
	}
	int totalPage = 0;

	if ((m_logList.size() % LOGNUM_OF_ONE_PAGE) == 0)
	{
		totalPage = m_logList.size() / LOGNUM_OF_ONE_PAGE;
	}
	else
	{
		totalPage = m_logList.size() / LOGNUM_OF_ONE_PAGE + 1;
	}

	if(totalPage < m_curpage)
	{
		m_curpage = totalPage;
	}
	//当前面显示的日志数
	int templistNum = (m_logList.size() - (m_curpage - 1) * LOGNUM_OF_ONE_PAGE);
	int showlistNum = 0;
	if (templistNum >= LOGNUM_OF_ONE_PAGE)
	{
		showlistNum = LOGNUM_OF_ONE_PAGE;
	} 
	else
	{
		showlistNum = templistNum;
	}
	
	ui->PageLabel->setText(QString("%1/%2").arg(m_curpage).arg(totalPage));
	
	for (int i = 0; i < showlistNum; i++)
	{
		Logdata& log = *(m_logList[m_curpage -1+ i]);

		ui->log_tableWidget->insertRow(i);
        QTableWidgetItem* pItem0 = new QTableWidgetItem;
        pItem0->setText(log.mUser);
        pItem0->setTextAlignment(Qt::AlignHCenter);
        ui->log_tableWidget->setItem(i, 0, pItem0);

		QTableWidgetItem* pItem1 = new QTableWidgetItem;
        pItem1->setText(log.mTime);//时间转换
		pItem1->setTextAlignment(Qt::AlignHCenter);
		ui->log_tableWidget->setItem(i, 1, pItem1);

		QTableWidgetItem* pItem2 = new QTableWidgetItem;
        pItem2->setText(log.mOperation);//操作
		pItem2->setTextAlignment(Qt::AlignHCenter);


		ui->log_tableWidget->setItem(i, 2, pItem2);

		QTableWidgetItem* pItem3 = new QTableWidgetItem;
        pItem3->setText(log.mDescribe);//操作描述
		pItem3->setTextAlignment(Qt::AlignHCenter);
		ui->log_tableWidget->setItem(i, 3, pItem3);
		//Sleep(10);
	}


	if (totalPage == 1)
	{
		ui->pastPage->setEnabled(false);
		ui->nextPage->setEnabled(false);
		return;
	}

	if (m_curpage == totalPage)
	{
		ui->pastPage->setEnabled(true);
		ui->nextPage->setEnabled(false);
		return;
	}

	if (m_curpage == 1)
	{
		ui->pastPage->setEnabled(false);
		ui->nextPage->setEnabled(true);
		return;
	}
	if (m_curpage > 1 && m_curpage<totalPage)
	{
		ui->pastPage->setEnabled(true);
		ui->nextPage->setEnabled(true);
		return;
	}
}

void logManagerDlg::onTaskLogClicked(){
    TaskLogDialog dlg(this);
    dlg.exec();
}