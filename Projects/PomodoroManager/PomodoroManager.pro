#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PomodoroManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    pomodoromanager.cpp

HEADERS += \
    pomodoromanager.h

DISTFILES += \
    PluginMeta.json
