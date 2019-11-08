#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = ExtendableDataManagerPlugin
TEMPLATE = lib
QT += core sql widgets



include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

SOURCES += \
    tablehandler.cpp \
    extendableitemmodel.cpp \
    item.cpp \
    extendabledatamanager.cpp

HEADERS += \
    ../../Interfaces/Middleware/idatabase.h \
    ../../Interfaces/Middleware/iextendabledatamanager.h \
    tablehandler.h \
    extendableitemmodel.h \
    item.h \
    extendabledamanager.h

DISTFILES += \
    PluginMeta.json
