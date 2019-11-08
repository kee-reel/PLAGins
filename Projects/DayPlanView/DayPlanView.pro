
TARGET = DayPlanView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    dayplanview.cpp \
    datetimetypeeditor.cpp \
    mytreeview.cpp \
    designproxymodel.cpp

HEADERS +=\
    dayplanview.h \
    datetimetypeeditor.h \
    mytreeview.h \
    designproxymodel.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
