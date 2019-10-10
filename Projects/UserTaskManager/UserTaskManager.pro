TARGET = UserTaskManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

HEADERS += \
    usertaskmanager.h

SOURCES += \
    usertaskmanager.cpp

DISTFILES += \
    PluginMeta.json \
    RelationsInclude.pri
