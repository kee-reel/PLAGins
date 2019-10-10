
TARGET = DayPlan
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    dayplan.cpp

HEADERS += \
    dayplan.h

DISTFILES += \
    PluginMeta.json
