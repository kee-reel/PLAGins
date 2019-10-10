android {}
else {
TARGET = ModbusDeviceDataManager
TEMPLATE = lib
QT += widgets serialbus serialport gui

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    modbusdevicedatamanager.cpp \
    modbusdevicehandler.cpp

HEADERS +=\
    modbusdevicedatamanager.h \
    modbusdevicehandler.h

DISTFILES += \
    PluginMeta.json
}
