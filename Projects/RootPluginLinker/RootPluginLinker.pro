#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = RootPluginLinker
TEMPLATE = lib
QT += core widgets


SOURCES += \
    Linker/linker.cpp \
    Linker/linkeritem.cpp \
    Linker/metadataparser.cpp \
    pluginlinkercore.cpp

HEADERS += \
    ../../Interfaces/ipluginlinker.h \
    ../../../Application/icoreplugin.h \
    Linker/linker.h \
    Linker/linkeritem.h \
    Linker/metadataparser.h \
    pluginlinkercore.h

DEFINES += PLUGIN_BASE_QOBJECT

include(Linker/PluginBase/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
