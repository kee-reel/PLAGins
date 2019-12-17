
TARGET = NotificationManager
TEMPLATE = lib
QT += widgets

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

android{
QT += androidextras
}

SOURCES += \
    qextendedtimer.cpp \
    common_notificationmanagermodel.cpp

android {
SOURCES += android_notificationmanagermodel.cpp
} else {
SOURCES += win_motificationmanagermodel.cpp
}

HEADERS +=\
    qextendedtimer.h \
    notificationmanager.h

DISTFILES += \
    PluginMeta.json
