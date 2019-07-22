
TARGET = Core
TEMPLATE = lib
QT += widgets

SOURCES += \
    core.cpp \
    servicesmanager.cpp

HEADERS += \
    core.h \
    coreservicesmanager.h \
    icoreservice.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(CoreServiceBase/CoreServiceBase.pri)
