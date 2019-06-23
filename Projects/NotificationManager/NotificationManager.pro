
TARGET = NotificationManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

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
