#-------------------------------------------------
#
# Project created by QtCreator 2014-03-06T15:51:38
#
#-------------------------------------------------

QT       += core gui network xml
CONFIG += c++11
QMAKE_COMPILER_DEFINES = _WIN32
BOOST_PATH = D:/work/common/boost/boost_1_57_0
DESTDIR += ../bin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = VideoDownloader
TEMPLATE = app
DEFINES += WIN32
DEFINES += _X86_
DEFINES += WIN32_LEAN_AND_MEAN

SOURCES += main.cpp\
        videoserver.cpp \
    uiutils.cpp \
    windowutils.cpp \
    channelwidget.cpp \
    listview.cpp \
    downloadwidget.cpp \
    globalvariables.cpp \
    playrecordfilewidget.cpp \
    log.cpp \
    taskwidget.cpp \
    maindialog.cpp \
    devicewidget.cpp \
    downloadtasktreewidget.cpp \
    downloadtask.cpp \
    timedialog.cpp \
    timeedit.cpp \
    qgiflabel.cpp \
    singleapllication.cpp \
    cwaitdlg.cpp \
    messageboxdlg.cpp \
    screenadaption.cpp \
    xmlsettings.cpp \
    utils.cpp \
    devicelistwidget.cpp \
    channellistwidget.cpp \
    loginddevicedialog.cpp \
    loginsuccessdialog.cpp \
    formlogineddevices.cpp \
    formdeviceinfo.cpp \
    dialoglogineddevices.cpp \
    noflamedlg.cpp \
    formfactoryitem.cpp \
    dialogdownloadfiles.cpp \
    formdownloadfile.cpp \
    loginedserverprotect.cpp \
    screenadaption.cpp


HEADERS  += \
    videoserver.h \
    uiutils.h \
    windowutils.h \
    channelwidget.h \
    listview.h \
    downloadwidget.h \
    playrecordfilewidget.h \
    log.h \
    IVideoServer.h \
    taskwidget.h \
    maindialog.h \
    devicewidget.h \
    downloadtasktreewidget.h \
    downloadtask.h \
    timedialog.h \
    timeedit.h \
    qgiflabel.h \
    singleapllication.h \
    cwaitdlg.h \
    needtaptip.h \
    messageboxdlg.h \
    screenadaption.h \
    xmlsettings.h \
    utils.h \
    devicelistwidget.h \
    channellistwidget.h \
    loginddevicedialog.h \
    loginsuccessdialog.h \
    formlogineddevices.h \
    formdeviceinfo.h \
    dialoglogineddevices.h \
    noflamedlg.h \
    formfactoryitem.h \
    dialogdownloadfiles.h \
    formdownloadfile.h \
    loginedserverprotect.h \
    screenadaption.h



FORMS    += \
    channelwidget.ui \
    downloadwidget.ui \
    playrecordfilewidget.ui \
    maindialog.ui \
    devicewidget.ui \
    timedialog.ui \
    taskwidget.ui \
    cwaitdlg.ui \
    messageboxdlg.ui \
    loginddevicedialog.ui \
    loginsuccessdialog.ui \
    formlogineddevices.ui \
    formdeviceinfo.ui \
    dialoglogineddevices.ui \
    formfactoryitem.ui \
    dialogdownloadfiles.ui \
    formdownloadfile.ui



RESOURCES += \
    res.qrc


INCLUDEPATH += $$BOOST_PATH

LIBS += $$BOOST_PATH/bin/vc12/libboost_log_setup-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_log-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_thread-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_system-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_date_time-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_chrono-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_regex-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_filesystem-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_locale-vc120-mt-1_57.lib

LIBS += -lws2_32 \
    -liphlpapi \
    -lUser32


