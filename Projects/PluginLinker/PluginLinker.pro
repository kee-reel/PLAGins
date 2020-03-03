#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PluginLinker
TEMPLATE = lib
QT += core widgets

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

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

DISTFILES += \
    PluginMeta.json
