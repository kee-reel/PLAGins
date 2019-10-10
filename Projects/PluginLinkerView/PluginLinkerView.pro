
TARGET = PluginLinkerView
TEMPLATE = lib
QT += core widgets

SOURCES += \
    pluginlinkerview.cpp \
    ../UIManager/UIElementBase/uielementbase.cpp

HEADERS += \
    ..\..\Interfaces/ipluginlinker.h \
    pluginlinkerview.h \
    ../UIManager/UIElementBase/uielementbase.h

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

#include(../UIManager/UIElementBase/UIElementBase.pri)
    
DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
