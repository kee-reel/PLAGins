#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PomodoroManagerView
TEMPLATE = lib
QT += widgets multimedia

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

include(../../Interfaces/Architecture/UIElementBase/UIElementBase.pri)

SOURCES += \
    pomodorobutton.cpp \
    mytreeview.cpp \
    designproxymodel.cpp \
    pomodoromanagerview.cpp

HEADERS += \
    pomodorobutton.h \
    mytreeview.h \
    designproxymodel.h \
    pomodoromanagerview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui

RESOURCES += \
    res.qrc
