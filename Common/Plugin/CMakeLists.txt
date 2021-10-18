cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_options( ${PROJECT_NAME} PRIVATE -Wall -Wno-undef )

set( REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Plugin" )

set( SOURCES ${SOURCES}
    ${REL_PATH}/interface.h
    ${REL_PATH}/iplugin.h
    ${REL_PATH}/referenceinstance.h
    ${REL_PATH}/referenceinstanceslist.h
    ${REL_PATH}/referenceshandler.h
    ${REL_PATH}/plugin_base.cpp
    ${REL_PATH}/plugin_base.h
    ${REL_PATH}/plugindescriptor.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib")

set(SHARED_LIBRARY_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/${SHARED_LIBRARY_NAME}"
                "${CMAKE_CURRENT_BINARY_DIR}/../../../Application/Plugins/${SHARED_LIBRARY_NAME}")
