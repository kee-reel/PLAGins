
TARGET = Core
TEMPLATE = lib
QT += core widgets

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    core.cpp \
    simplelinker.cpp
    
HEADERS += \
    core.h \
    simplelinker.h
    
DISTFILES += \
    PluginMeta.json
