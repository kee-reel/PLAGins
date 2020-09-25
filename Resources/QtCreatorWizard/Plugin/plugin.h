#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"
@endif
@if '%{PluginType}' === 'QWidget'
namespace Ui
{
class Form;
}

@endif
@if %{CreateNewInterface}
#include "%{HdrFileName}"

@endif
class Plugin : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.%{CN}" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin)

public:
	Plugin();
	~Plugin() override;

private:
@if '%{PluginType}' === 'QWidget'
	QSharedPointer<Ui::Form> ui;
@endif
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
	UIElementBase* m_uiElementBase;
@endif
@if %{CreateNewInterface}
	%{CN}* m_impl;
@endif
};
