QT = core network gui
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
SOURCES += main.cpp \
    downloadmanager.cpp

DESTDIR += D:/work/downloadVideo/bin
TARGET = download
INSTALLS += target

OTHER_FILES +=

HEADERS += \
    downloadmanager.h \
    etimcrypt.h

