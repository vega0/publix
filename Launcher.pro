#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T18:44:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Launcher
TEMPLATE = app


SOURCES += main.cpp\
        launcher.cpp \
    config.cpp \
    assist.cpp \
    webdispatch.cpp \
    versioncontrol.cpp \
    jsonversion.cpp \
    jsonlibrary.cpp \
    jsonrules.cpp \
    dirdispatch.cpp \
    qmapvalidator.cpp

HEADERS  += launcher.h \
    config.h \
    defines/entry.h \
    defines/HASH.h \
    defines/setups.h \
    assist.h \
    webdispatch.h \
    versioncontrol.h \
    jsonversion.h \
    jsonlibrary.h \
    jsonrules.h \
    dirdispatch.h \
    qmapvalidator.h

FORMS    += launcher.ui

CONFIG += static

CONFIG( debug, debug | release )
{
    #debug config / конфигурация при включенном режиме - дебаг
}

CONFIG( release, debug | release )
{
    #release config / Конфигурация при включенном режиме - релиз
}

RESOURCES += \
    pack.qrc
