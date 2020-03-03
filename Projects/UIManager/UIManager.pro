
TARGET = UIManager
TEMPLATE = lib
QT += core widgets

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    uimanager.cpp

HEADERS += \
    uimanager.h \
    ../../Interfaces/Architecture/iuielement.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json
