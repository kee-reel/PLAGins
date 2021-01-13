
TARGET = %{CN}
TEMPLATE = lib
QT += core
@if '%{PluginType}' === 'QWidget'
QT += widgets

DEFINES += QWidget_UIElement
@elsif '%{PluginType}' === 'QML'
QT += quickwidgets qml quick

DEFINES += QML_UIElement
@endif

include(../../plugin.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)

@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QML'
include(../../Interfaces/Architecture/UIElementBase/UIElementBase.pri)
@endif

@if %{CreateNewInterface}
HEADERS += \\
	plugin.h \\
	%{HdrFileName}
@else
HEADERS += \\
	plugin.h
@endif

@if %{CreateNewInterface}
SOURCES += \\
	plugin.cpp \\
	%{SrcFileName}
@else
SOURCES += \\
	plugin.cpp
@endif

DISTFILES += PluginMeta.json

@if '%{PluginType}' === 'QWidget'
FORMS += form.ui
@elsif '%{PluginType}' === 'QML'
RESOURCES += res.qrc
@endif
