#include "pluginlinkerview.h"

#include "ui_form.h"

PluginLinkerView::PluginLinkerView() :
    PluginBase()
{
    connect(ui->btnExit, &QPushButton::clicked, this, &PluginLinkerView::close);
}

PluginLinkerView::~PluginLinkerView()
{
}
