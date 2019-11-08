
TARGET = HeartRateDeviceView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    heartratedeviceview.cpp

HEADERS += \
    heartratedeviceview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
