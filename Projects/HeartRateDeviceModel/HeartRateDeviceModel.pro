android { }
else {
TARGET = HeartRateDevice
TEMPLATE = lib
QT += widgets serialport serialbus charts

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    heartratedevice.cpp

HEADERS += \
    heartratedevice.h

DISTFILES += \
    PluginMeta.json
}
