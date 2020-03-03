TARGET = UserTaskManager
TEMPLATE = lib
QT += widgets

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

HEADERS += \
    usertaskmanager.h \
    ../../Interfaces/Middleware/iextendabledatamanager.h \
    ../../Interfaces/Utility/iusertaskmanager.h 

SOURCES += \
    usertaskmanager.cpp

DISTFILES += \
    PluginMeta.json \
    RelationsInclude.pri
