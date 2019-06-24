
TARGET = PluginLinkerView
TEMPLATE = lib
QT += widgets

SOURCES += \
    pluginlinkerview.cpp

HEADERS += \
    pluginlinkerview.h

DEFINES += \
    PLUGIN_BASE_QWIDGET
    
DISTFILES += \
    PluginMeta.json

include(../../Common/BuildInfo.pri)

FORMS += \
    form.ui
