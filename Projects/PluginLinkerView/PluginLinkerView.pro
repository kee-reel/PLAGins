
TARGET = PluginLinkerView
TEMPLATE = lib
QT += core widgets

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

include(../../Interfaces/Architecture/UIElementBase/UIElementBase.pri)

DEFINES += QWidget_UIElement

SOURCES += \
    pluginlinkerview.cpp

HEADERS += \
    pluginlinkerview.h
    
DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
