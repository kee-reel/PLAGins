
TARGET = CorePlugin
TEMPLATE = lib
QT += widgets

SOURCES += \
    ServiceBase/servicebase.cpp \
    coreplugin.cpp \
    servicesmanager.cpp

HEADERS += \
    ServiceBase/servicebase.h \
    coreplugin.h \
    iservice.h \
    servicesmanager.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json

include(../../Common/common.pri)

include(../../../Application/pluginsBuildInfo.pri)
