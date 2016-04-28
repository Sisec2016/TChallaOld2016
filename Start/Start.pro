#-------------------------------------------------
#
# Project created by QtCreator 2015-09-04T16:05:12
#
#-------------------------------------------------

QT       += core sql gui network
CONFIG += c++11
DESTDIR += D:/work/downloadVideo/bin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

##DEFINES += VERSION_SSD
##TARGET = StartSsd

TARGET = Start


TEMPLATE = app

BOOST_PATH = D:/work/common/boost/boost_1_57_0
PROTOBUF_PATH = D:/work/common/protobuf
SOURCES += main.cpp\
        mainwindow.cpp \
    cwaitdlg.cpp \
    qgiflabel.cpp \
    singleapllication.cpp \
    protobufclient.cpp \
    settings.cpp \
    ../common/protobuf/SettingInfo.pb.cc \
    ../common/protobuf/pos_request.pb.cc \
    ../common/protobuf/Device.pb.cc \
    ../common/protobuf/DeviceType.pb.cc \
    ../common/protobuf/VersionInfo.pb.cc \
    SAGESSDDll.cpp \
    safedisk.cpp \
    VerifyDialog.cpp \
    dialogmodifypassword.cpp

HEADERS  += mainwindow.h \
    cwaitdlg.h \
    qgiflabel.h \
    customEvent.h \
    singleapllication.h \
    protobufclient.h \
    settings.h \
    ../common/protobuf/SettingInfo.pb.h \
    ../common/protobuf/pos_request.pb.h \
    ../common/protobuf/Device.pb.h \
    ../common/protobuf/DeviceType.pb.h \
    ../common/protobuf/VersionInfo.pb.h \
    SAGESSDDll.h \
    VirDisk_SageAPI.h \
    safedisk.h \
    VerifyDialog.h \
    dialogmodifypassword.h

FORMS    += mainwindow.ui \
    cwaitdlg.ui \
    VerifyDialog.ui \
    dialogmodifypassword.ui

RESOURCES += \
    Start.qrc

INCLUDEPATH += $$BOOST_PATH
INCLUDEPATH += $$PROTOBUF_PATH/include

LIBS += $$BOOST_PATH/bin/vc12/libboost_log_setup-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_log-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_thread-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_system-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_date_time-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_chrono-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_regex-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_filesystem-vc120-mt-1_57.lib
LIBS += $$BOOST_PATH/bin/vc12/libboost_locale-vc120-mt-1_57.lib

LIBS += $$PROTOBUF_PATH/libprotobuf.lib
LIBS += -L$$PWD/ -lVirDisk_SageAPI
