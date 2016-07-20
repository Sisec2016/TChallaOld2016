#include "Verify.h"
#include <QSqlDatabase>
#include "safedisk.h"
#include "VerifyDialog.h"
#include "windowutils.h"
#include "settings.h"
//#define  VERIFY_VERSION



const char* Verify::version()
{
#ifdef VERIFY_VERSION
    return "2.0.3";
#else
    return "1.3.6.0.2";

#endif
}

QString Verify::downloadDir(){
    if (Settings::getItem(KEY_DOWNLOAD_DIR).isEmpty())
    {
#ifdef VERIFY_VERSION
        return QStringLiteral("M:/DownLoadVideo");
#else
        return QStringLiteral("D:/DownLoadVideo");
#endif
    }

    return Settings::getItem(KEY_DOWNLOAD_DIR);
}

QString Verify::downloadDirPath(){
    return downloadDir() + "/";
}

QString Verify::startExe(){
#ifdef VERIFY_VERSION
    return "StartSsd.exe";
#else
    return "Start.exe";

#endif
    }

bool Verify::init(){
#ifdef VERIFY_VERSION
    if (!SafeDisk::instance().init())
    {
        return false;
    }
    VerifyDialog dlg;
    return QDialog::Accepted == dlg.exec();
#endif
    return true;
}

void Verify::uninit(){

    WindowUtils::terminateProcess("VideoService");
    WindowUtils::terminateProcess("VideoService");
#ifdef VERIFY_VERSION
    SafeDisk::instance().unMountAll();
#endif

}
