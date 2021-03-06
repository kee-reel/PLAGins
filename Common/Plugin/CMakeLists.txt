cmake_minimum_required(VERSION 3.16)

target_compile_options( ${PROJECT_NAME} PRIVATE -Wall -Wno-undef )

set( REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Plugin" )
set( MOC_HEADERS ${MOC_HEADERS}
    ${REL_PATH}/referenceinstance.h
    ${REL_PATH}/referenceinstanceslist.h
    ${REL_PATH}/referenceshandler.h
    ${REL_PATH}/plugin_base.h
    ${REL_PATH}/plugindescriptor.h )
set( SOURCES ${SOURCES}
    ${REL_PATH}/interface.h
    ${REL_PATH}/iplugin.h
    ${REL_PATH}/plugin_base.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib")

set(SHARED_LIBRARY_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/${SHARED_LIBRARY_NAME}"
                "${CMAKE_CURRENT_BINARY_DIR}/../../../Application/Plugins/${SHARED_LIBRARY_NAME}")
