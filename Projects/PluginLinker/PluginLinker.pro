#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PluginLinker
TEMPLATE = lib
QT += core widgets


SOURCES += \
    linkeritembase.cpp \
    pluginlinkeritem.cpp \
    pluginlinker.cpp

HEADERS += \
    ../../Interfaces/ipluginlinker.h \
    ../../../Application/ipluginhandler.h \
    ../../../Application/icoreplugin.h \
    linkeritembase.h \
    pluginlinkeritem.h \
    pluginlinker.h

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

DISTFILES += \
    PluginMeta.json
