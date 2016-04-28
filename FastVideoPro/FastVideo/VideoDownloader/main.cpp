#include <stdlib.h>
#include <QSharedMemory>
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QTextCodec>
#include "windowutils.h"
#include <QThread>
#include <QDir>
#include <QMessageBox>
#include "maindialog.h"
#include <QCryptographicHash>
#include <iostream>
#include <excpt.h>

#include "singleapllication.h"

#include "log.h"
#include <QCollator>
#include "utils.h"

#include <iostream>

void execDlg(MainDialog& dlg)
{
    __try{
        dlg.exec();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout<<"execDlg unkonw error!"<<std::endl;
        //Log::add("execDlg unkonw error!", fatal);
        exit(-1);
    }
}
void showMainDlg(SingleApplication& a)
{
    MainDialog logd;
    a.setMainWidget(&logd);
    execDlg(logd);
}


void showMainDlgNoExcept(SingleApplication& a)
{
    __try{
        showMainDlg(a);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout<<"showMainDlgNoExcept unkonw error!"<<std::endl;
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv);
    if (a.isRunning()) {
       return 0;
    }

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    showMainDlgNoExcept(a);

    return -1;
}


