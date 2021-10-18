cmake_minimum_required(VERSION 3.16)

set( REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/GUIElement" )

set( SOURCES ${SOURCES}
    ${REL_PATH}/iguielement.h
    ${REL_PATH}/guielementbase.cpp
    ${REL_PATH}/guielementbase.h
    ${REL_PATH}/guielementlinkshandler.cpp
    ${REL_PATH}/guielementlinkshandler.h
    ${REL_PATH}/../Plugin/referenceinstance.h
    ${REL_PATH}/../Plugin/referenceinstanceslist.h
    ${REL_PATH}/../Plugin/referenceshandler.h
)

if( IS_QWIDGET_UI )
    target_compile_definitions( ${PROJECT_NAME} PUBLIC
        QWidget_UIElement
    )
else()
    find_package(Qt6 COMPONENTS Qml)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        QML_UIElement
    )
    qt6_add_qml_module( "${PROJECT_NAME}_QML_StaticLib"
        VERSION 1.0
        URI "Plugins"
    )
endif()
