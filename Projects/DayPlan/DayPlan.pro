
TARGET = DayPlan
TEMPLATE = lib
QT += widgets



include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    dayplan.cpp

HEADERS += \
    dayplan.h

DISTFILES += \
    PluginMeta.json
