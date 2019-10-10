!android {

TARGET = COMPortDataManager
TEMPLATE = lib
QT += widgets serialport

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    serialporthandler.cpp \
    comportdatamanager.cpp

HEADERS +=\
    serialporthandler.h \
    comportdatamanager.h

DISTFILES += \
    PluginMeta.json
}
