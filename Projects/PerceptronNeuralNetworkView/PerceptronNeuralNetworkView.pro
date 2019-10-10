#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PerceptronLearningAlgorithmView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/common.pri)

include(../../../Application/PluginBuildInfo.pri)

include(../PluginLinker/PluginBase/PluginBase.pri)

SOURCES += \
    qcustomplot.cpp \
    perceptronlearningalgorithmview.cpp

HEADERS += \
    qcustomplot.h \
    perceptronlearningalgorithmview.h


DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui

RESOURCES += \
    res.qrc
