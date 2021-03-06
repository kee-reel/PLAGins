cmake_minimum_required(VERSION 3.16)

include(../../Common/CMakeLists.txt)

set( PROJECT_NAME %{CN} )

project( ${PROJECT_NAME} )

find_package(Qt6 COMPONENTS Core)
@UI@find_package(Qt6 COMPONENTS Gui)
@QML@find_package(Qt6 COMPONENTS QuickWidgets)
@QML@find_package(Qt6 COMPONENTS Qml)
@QML@find_package(Qt6 COMPONENTS Quick)

qt_add_plugin( ${PROJECT_NAME} SHARED )
set( SOURCES
	plugin.cpp plugin.h
@INT@	%{IPath}
@INT@	%{SrcFileName}
@WID@	form.ui
@QML@	form.qml res.qrc
)
set( MOC_HEADERS 
	plugin.h
@INT@	%{HdrFileName}
)
@WID@qt6_wrap_ui( SOURCES form.ui )

include(../../Common/Plugin/CMakeLists.txt)

@WID@set( IS_QWIDGET_UI ON )
@UI@include(../../Common/GUIElement/CMakeLists.txt)
@UI@
qt_wrap_cpp( SOURCES ${MOC_HEADERS} )
target_sources( ${PROJECT_NAME} PRIVATE ${SOURCES} )

target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt::Core
@UI@	Qt::Gui
@QML@	Qt::Qml
@QML@	Qt::Quick
@QML@	Qt::QuickWidgets
)

