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
    pluginlinkercore.cpp

HEADERS += \
    ../../Interfaces/ipluginlinker.h \
    ../../../Application/icoreplugin.h \
    linkeritem.h \
    metadataparser.h \
    pluginlinkercore.h

DEFINES += PLUGIN_BASE_QOBJECT

include(PluginBase/PluginBase.pri)

DISTFILES += \
    PluginMeta.json
