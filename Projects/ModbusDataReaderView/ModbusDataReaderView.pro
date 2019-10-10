android {}
else {
TARGET = ModbusDataReaderView
TEMPLATE = lib
QT += widgets charts serialport serialbus

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    experimentcontrolview.cpp

HEADERS +=\
    experimentcontrolview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
}
