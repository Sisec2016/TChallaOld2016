#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>

#include <Windows.h>
#include <Tlhelp32.h>
#include <qdebug.h>

#include "singleapllication.h"
#include "cwaitdlg.h"
#include "settings.h"
#include "protobufclient.h"

#include "VerifyDialog.h"
#include <QFile>
#include <QString>
#define AuthorFile "AuthorFile"

QString getMd5(){
    QFile file(AuthorFile);
    QString md5;
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> md5;
    }

    return md5;
}

void terminate(const char* sProssExe)
{
    HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    PROCESSENTRY32* processInfo=new PROCESSENTRY32;
    processInfo->dwSize = sizeof(PROCESSENTRY32);
    int index=0;
       //这里我们将快照句柄和PROCESSENTRY32结构传给Process32Next()。
       //执行之后，PROCESSENTRY32 结构将获得进程的信息。我们循环遍历，直到函数返回FALSE。
       //printf("****************开始列举进程****************/n");
    int ID = 0;
    while (Process32Next(hSnapShot, processInfo) != FALSE)
    {
       index++;
       //printf("****************** %d ******************/n",index);
       //printf("PID       Name      Current Threads/n");
       //printf("%-15d%-25s%-4d/n",processInfo->th32ProcessID,processInfo->szExeFile,processInfo->cntThreads);
       int size= WideCharToMultiByte(CP_ACP, 0, processInfo->szExeFile, -1, NULL, 0, NULL, NULL);
       char *ch = new char[size + 1];
       if (WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile, -1, ch, size, NULL, NULL))
       {
         if (strstr(ch, sProssExe))//使用这段代码的时候只需要改变"cmd.exe".将其改成你要结束的进程名就可以了。
         {
                ID = processInfo->th32ProcessID;
                HANDLE hProcess;
                // 现在我们用函数 TerminateProcess()终止进程：
                // 这里我们用PROCESS_ALL_ACCESS
                hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ID);
                TerminateProcess(hProcess,0);
                CloseHandle(hProcess);
           }
       }
    }

    CloseHandle(hSnapShot);
    delete processInfo;
}

void initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fast_video.db");
    db.setUserName("fast_video");
    db.setPassword("fast_video!@#");
    if (!db.open())
    {
        qDebug()<<"connet db failed!"<<db.lastError();
        return ;
    }

    Settings::createTable();

    return ;
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file(QApplication::applicationDirPath() + "/log/start.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


#define UPGRADE_FILE  "upgrade.exe"

int main(int argc, char *argv[])
{


//    VerifyDialog dlg;
//    dlg.exec();
    SingleApplication a(argc, argv);
    qInstallMessageHandler(outputMessage);
    initDb();
    MainWindow w;
    a.setMainWidget(&w);
    QString appDir = QApplication::applicationDirPath() + "/";
    QString upgradeFile = appDir + UPGRADE_FILE;
    QString upState = Settings::getItem(KEY_UPGRADE_STATE);
    if (upState == KEY_UPGRADE_STATE_DOWNLOADED || upState == KEY_UPGRADE_STATE_INSTALLING){
        QFile f(upgradeFile);
        if (f.exists()){
            Settings::setItem(KEY_UPGRADE_STATE, KEY_UPGRADE_STATE_INSTALLING);
            std::shared_ptr<bool> bCanGoOn = std::make_shared<bool>(false);
            CWaitDlg::waitForDoing(nullptr, QString::fromLocal8Bit("正在升级中..."), [=]()
            {
                QStringList arguments;
                arguments.append("/VERYSILENT");
                QProcess::execute(upgradeFile, arguments);
                *bCanGoOn = true;
            }, [](bool){});

            while (!(*bCanGoOn)){
                ::Sleep(500);
            }

            Settings::setItem(KEY_CURVERSION, Settings::getItem(KEY_DOWNLOAD_VERSION));
            Settings::setItem(KEY_UPGRADE_STATE, KEY_UPGRADE_STATE_INSTALLED);
            Settings::setItem(KEY_MD5, Settings::getItem(KEY_DOWNLOAD_MD5));
            Settings::setItem(KEY_FILE_URL, Settings::getItem(KEY_DOWNLOAD_FILE_URL));

        }
        else{
            Settings::setItem(KEY_UPGRADE_STATE, KEY_UPGRADE_STATE_INSTALLED);
        }
    }

    ::Sleep(1);
    QStringList arguments;
    arguments.append("-s");
    qDebug()<<appDir;
    QProcess::startDetached(appDir + "FastVideo.exe", arguments);

    if (a.isRunning()) {
       qDebug()<<"isrunning";
       return 0;
    }
    qDebug()<<"loadSetting";
    ProtobufClient::instance().loadSetting(getMd5());

    /*if (Settings::getItem(KEY_SERVER_VERSION) != Settings::getItem(KEY_CURVERSION)){
        QFile f(upgradeFile);
        if (f.exists()){
            f.remove();
        }

        Settings::setItem(KEY_UPGRADE_STATE, KEY_UPGRADE_STATE_DOWNLOADING);
        Settings::setItem(KEY_DOWNLOAD_VERSION, Settings::getItem(KEY_SERVER_VERSION));
        Settings::setItem(KEY_DOWNLOAD_MD5, Settings::getItem(KEY_SERVER_MD5));
        Settings::setItem(KEY_DOWNLOAD_FILE_URL, Settings::getItem(KEY_SERVER_FILE_URL));
        QString downloadCmd = QString(appDir + "download.exe \"%1\" \"%2\" \"%3\"")
                .arg(Settings::getItem(KEY_SERVER_FILE_URL)).arg(upgradeFile).arg(Settings::getItem(KEY_SERVER_MD5));
        qDebug()<< downloadCmd;
        QProcess::execute(downloadCmd);
        qDebug()<< "downloadCmd finish";
        Settings::setItem(KEY_UPGRADE_STATE, KEY_UPGRADE_STATE_DOWNLOADED);
    }*/

    return 0;
}
