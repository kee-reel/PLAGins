
TARGET = HowTo
TEMPLATE = lib
QT += core

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../../Interfaces/Architecture/PluginBase/PluginBase.pri)


HEADERS += \
	plugin.h \
	howto.h

SOURCES += \
	plugin.cpp \
	howto.cpp

DISTFILES += PluginMeta.json

