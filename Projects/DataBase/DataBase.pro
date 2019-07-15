#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DataBase
TEMPLATE = lib
QT += core sql

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../RootPluginLinker/PluginBase/PluginBase.pri)

include(../CorePlugin/ServiceBase/ServiceBase.pri)

SOURCES += \
    database.cpp

HEADERS += \
    database.h

DISTFILES += \
    PluginMeta.json
