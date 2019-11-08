#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = UserTaskManagerView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    addform.cpp \
    designproxymodel.cpp \
    mytreeview.cpp \
    usertaskmanagerview.cpp

HEADERS += \
    addform.h \
    designproxymodel.h \
    mytreeview.h \
    usertaskmanagerview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    addform.ui \
    form.ui

RESOURCES += \
    res.qrc
