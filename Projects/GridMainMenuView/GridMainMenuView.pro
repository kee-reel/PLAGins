
TARGET = GridMainMenuView
TEMPLATE = lib
QT += core widgets

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

include(../../Interfaces/Architecture/UIElementBase/UIElementBase.pri)

HEADERS += \
    gridmainmenuview.h \
    aspectawaregridlayout.h \
    uniquepushbutton.h

SOURCES += \
    gridmainmenuview.cpp \
    aspectawaregridlayout.cpp \
    uniquepushbutton.cpp

DISTFILES += \
    PluginMeta.json \
    MenuGrid.qml

FORMS += \
    form.ui

RESOURCES += \
    res.qrc
