
TARGET = GridMainMenuView
TEMPLATE = lib
QT += core widgets quickwidgets qml quick

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

include(../../Interfaces/Architecture/UIElementBase/UIElementBase.pri)

HEADERS += \
    gridmainmenuview.h

SOURCES += \
    gridmainmenuview.cpp

DISTFILES += \
    PluginMeta.json

FORMS +=

RESOURCES += \
    res.qrc
