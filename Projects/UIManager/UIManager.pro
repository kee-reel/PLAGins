
TARGET = UIManager
TEMPLATE = lib
QT += core widgets

SOURCES += \
    uimanager.cpp

HEADERS += \
    ../../Interfaces/iuielement.h \
    ../../Interfaces/ipluginlinker.h \
    uimanager.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../Core/CoreServiceBase/CoreServiceBase.pri)
