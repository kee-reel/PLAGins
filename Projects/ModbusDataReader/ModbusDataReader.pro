android {}
else {
TARGET = ModbusDataReader
TEMPLATE = lib
QT += widgets serialport serialbus charts

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    registerspacktablemodel.cpp \
    registerspackhandler.cpp \
    modbusdevicesmodel.cpp \
    modbusdatareader.cpp

HEADERS +=\
    registerspacktablemodel.h \
    modbusdevicesmodel.h \
    registerspackhandler.h \
    modbusdatareader.h

DISTFILES += \
    PluginMeta.json
}
