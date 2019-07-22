#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PluginLinker
TEMPLATE = lib
QT += core widgets


SOURCES += \
    linkeritem.cpp \
    metadataparser.cpp \
    pluginlinker.cpp

HEADERS += \
    ../../Interfaces/ipluginlinker.h \
    ../../../Application/icoreplugin.h \
    linkeritem.h \
    metadataparser.h \
    pluginlinker.h

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../Core/CoreServiceBase/CoreServiceBase.pri)

DISTFILES += \
    PluginMeta.json
