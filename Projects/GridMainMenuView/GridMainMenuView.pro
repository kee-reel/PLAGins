
TARGET = GridMainMenuView
TEMPLATE = lib
QT += core widgets quickwidgets qml quick

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

include(../../Interfaces/Architecture/UIElementBase/UIElementBase.pri)

DEFINES += QML_UIElement

HEADERS += \
    gridmainmenuview.h

SOURCES += \
    gridmainmenuview.cpp

DISTFILES += \
    PluginMeta.json

FORMS +=

RESOURCES += \
    res.qrc
