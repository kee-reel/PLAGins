!android {

TARGET = COMPortDataManager
TEMPLATE = lib
QT += widgets serialport



include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    serialporthandler.cpp \
    comportdatamanager.cpp

HEADERS +=\
    serialporthandler.h \
    comportdatamanager.h

DISTFILES += \
    PluginMeta.json
}
