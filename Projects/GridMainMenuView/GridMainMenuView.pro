
TARGET = GridMainMenuView
TEMPLATE = lib
QT += core widgets

HEADERS += \
    ../../Interfaces/iuimanager.h \
    ../UIManager/UIElementBase/uielementbase.h \
    ../UIManager/UIElementBase/uielementdescriptor.h \
    gridmainmenuview.h \
    aspectawaregridlayout.h \
    uniquepushbutton.h

SOURCES += \
    ../UIManager/UIElementBase/uielementbase.cpp \
    ../UIManager/UIElementBase/uielementdescriptor.cpp \
    gridmainmenuview.cpp \
    aspectawaregridlayout.cpp \
    uniquepushbutton.cpp

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

DISTFILES += \
    PluginMeta.json \
    MenuGrid.qml

FORMS += \
    form.ui

RESOURCES += \
    res.qrc
