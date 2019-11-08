#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DataBase
TEMPLATE = lib
QT += core sql



include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    database.cpp

HEADERS += \
    database.h

DISTFILES += \
    PluginMeta.json
