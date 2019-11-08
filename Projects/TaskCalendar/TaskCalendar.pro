
TARGET = TaskCalendar
TEMPLATE = lib
QT += widgets

SOURCES += \
    taskcalendar.cpp

HEADERS += \
    taskcalendar.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)
