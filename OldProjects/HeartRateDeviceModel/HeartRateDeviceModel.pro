android { }
else {
TARGET = HeartRateDevice
TEMPLATE = lib
QT += widgets serialport serialbus charts



include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    heartratedevice.cpp

HEADERS += \
    heartratedevice.h

DISTFILES += \
    PluginMeta.json
}
