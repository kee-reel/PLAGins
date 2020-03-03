
TARGET = TaskCalendar
TEMPLATE = lib
QT += widgets

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    taskcalendar.cpp

HEADERS += \
    taskcalendar.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json
