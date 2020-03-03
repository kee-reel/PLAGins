#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchManager
TEMPLATE = lib
QT += widgets

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    rawimagedelegate.cpp \
    tasksketchmanager.cpp

HEADERS +=\
    rawimagedelegate.h \
    tasksketchmanager.h

DISTFILES += \
    PluginMeta.json
