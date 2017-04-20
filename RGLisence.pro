#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T09:45:03
#
#-------------------------------------------------

QT       += core gui

TARGET = RGLisence
TEMPLATE = lib

DEFINES += RGLISENCE_LIBRARY

SOURCES += rglisence.cpp \
    lisencemanage.cpp

HEADERS += rglisence.h\
        rglisence_global.h \
    lisencemanage.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
