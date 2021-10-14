# Generated from plugin.pro.

cmake_minimum_required(VERSION 3.16)
project(%{CN})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}")

find_package(Qt6 COMPONENTS Core)
@UI@find_package(Qt6 COMPONENTS Gui)
@QML@find_package(Qt6 COMPONENTS QuickWidgets)
@QML@find_package(Qt6 COMPONENTS Qml)
@QML@find_package(Qt6 COMPONENTS Quick)

add_library(%{CN} SHARED
@UI@    ../../Interfaces/Architecture/GUIElementBase/../iguielement.h
@UI@    ../../Interfaces/Architecture/GUIElementBase/../referenceinstance.h
@UI@    ../../Interfaces/Architecture/GUIElementBase/../referenceinstanceslist.h
@UI@    ../../Interfaces/Architecture/GUIElementBase/../referenceshandler.h
@UI@    ../../Interfaces/Architecture/GUIElementBase/guielementbase.cpp ../../Interfaces/Architecture/GUIElementBase/guielementbase.h
@UI@    ../../Interfaces/Architecture/GUIElementBase/guielementlinkshandler.cpp ../../Interfaces/Architecture/GUIElementBase/guielementlinkshandler.h
    ../../Interfaces/Architecture/PluginBase/../iplugin.h
    ../../Interfaces/Architecture/PluginBase/../referenceinstance.h
    ../../Interfaces/Architecture/PluginBase/../referenceinstanceslist.h
    ../../Interfaces/Architecture/PluginBase/../referenceshandler.h
    ../../Interfaces/Architecture/PluginBase/plugin_base.cpp ../../Interfaces/Architecture/PluginBase/plugin_base.h
    ../../Interfaces/Architecture/PluginBase/plugindescriptor.h
    plugin.cpp plugin.h
    PluginMeta.json
@INT@	%{IPath}
@INT@	%{SrcFileName} %{HdrFileName}
@WID@	form.ui
@QML@	form.qml res.qrc
)

@UI@target_compile_definitions(%{CN} PUBLIC
@QML@    QML_UIElement
@WID@    QWidget_UIElement
@UI@)
target_compile_options( %{CN} PRIVATE -Wall -Wno-undef )
target_link_libraries(%{CN} PUBLIC
    Qt::Core
@UI@    Qt::Gui
@QML@    Qt::Qml
@QML@    Qt::Quick
@QML@    Qt::QuickWidgets
)

@QML@qt6_add_qml_module(QML_StaticLib
@QML@    VERSION 1.0
@QML@    URI "Plugins"
@QML@)
@QML@
if(WIN32)
    target_compile_definitions(Supper PUBLIC
        WIN32_LEAN_AND_MEAN
    )
endif()

