#ifndef FTPDLG_H
#define FTPDLG_H

#include <QtGui>
#include <QDialog>
//#include <QtNetwork/QFtp>
#include <QProcess>
#include <QProgressDialog>
#include <QObject>
#include "MyBaseDialog.h"

#include"FTPPathadddlg.h"

#include "qftp.h"

#include "LogHeader.h"
#include "LogManager.h"

#pragma comment(lib, "QFtp.lib")

class QFile;
class QFtp;
class myQUrlInfo;
class QProgressDialog;
class QTableWidgetItem;
class QTreeWidgetItem;

namespace Ui {
    class FTPDlg;
	class Ftpclient;
}

class Ftpclient : public QObject
{
	Q_OBJECT
public:
	Ftpclient(QObject *parent);
	~Ftpclient();
	
	bool	isDir(QString fileName){return isDirectory.value(fileName);};
	QString GetOldName(QString name){ return DirectoryLatinName.value(name); };

	int		ftpConnect(T_FTPPath *pFTPPath);
	int     ftpDisConnect();

	void	cdParent();
	void	cdChild(QString dir);
	void    cdDir(QString dir);
	void	getFile(const QString&);
	void	putFile(QString&, QString& filePath);
	bool	getStart(){return this->start;};
	QString	getLocalPath(){return this->localPath;};
	QString	getPath(){return this->currentPath;};
	void	setLocalPath(QString s){ localPath = s;};

signals:
	void	cmdConnected(bool isConnect);
	void	cmdGot(bool error);
	void	cmdPut(bool error);
	void	cmdList(bool error);
	//void	cmdIsTopDir(bool isTop);
	void	cmdChangeList(const myQUrlInfo&);
	void	cmdDownloading();
	void	cmdUploading();

public slots:
	void	ftpCommandFinished(int commandId,bool error);
	//void	updateDataTransferProgress(qint64 readBytes,qint64 totalBytes);
	void	updateDataTransferProgress1(qint64 readBytes,qint64 totalBytes);
	void	addToList(const myQUrlInfo&);
	//void	cancelDownload();
	//void	cancelUpload();

private:
	QFtp* m_ftp;
	QFile*	m_file;

	QHash<QString,bool> isDirectory;
	QHash<QString, QString> DirectoryLatinName;
	
	bool	start;
	QString	localPath;
	QString	currentPath;
	QProgressDialog*	UpLoadprogressDialog;
};

class FTPDlg : public MyBaseDialog {
    Q_OBJECT
public:
    FTPDlg(QWidget *parent = 0);
    ~FTPDlg();
protected slots:
    void onAddFTPPathBtn();
    void onModifyFTPPathBtn();
    void onDelFTPPathBtn();
    void onOutputFTPBtn();
    void onItemDoubleClicked(QTableWidgetItem * item );
    void onItemClicked ( QTableWidgetItem * item );

	void	processItem(QTreeWidgetItem* item, int);
	void	cdParent();
	//void    switchDownloadButton();
	//void    switchUploadButton();
	//void	downloadFile();
	//void	uploadFile();
	//void	localFile();

	void	changeList(const myQUrlInfo &urlInfo);
	void	onConnect(bool);
	void	onGet(bool);
	void	onPut(bool);
	void	onList(bool);
	void	onTopDir(bool);

protected:
    void changeEvent(QEvent *e);
    void closeEvent (QCloseEvent * e );
private:
    void readFTPPathListFile();
    void writeFTPPathListFile();
    void addToTableWidget(T_FTPPath *pFTPPath);
private:
    Ui::FTPDlg *ui;
	Ftpclient *m_ftpClient;
    QList<T_FTPPath> m_listFTPPath;

	QString m_CurHost;
};


#endif