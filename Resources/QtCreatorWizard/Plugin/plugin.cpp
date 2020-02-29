#include "plugin.h"
@if '%{PluginType}' === 'QWidget'
#include "ui_form.h"
@endif

Plugin::Plugin() :
	QObject(nullptr),
	PluginBase(this)
@if '%{PluginType}' === 'QWidget'
	, ui(new Ui::Form)
@endif
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
	, m_uiElementBase(new UIElementBase(this, {""}))
@endif
@if %{CreateNewInterface}
	, m_impl(new %{CN}(this))
@endif
{
@if '%{PluginType}' === 'QWidget'
	ui->setupUi(m_uiElementBase);
@endif
	initPluginBase(
		{
			{INTERFACE(IPlugin), this}
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
			, {INTERFACE(IUIElement), m_uiElementBase}
@endif
@if %{CreateNewInterface}
			, {INTERFACE(%{InterfaceName}), m_impl}
@endif
		},
		{},
		{}
	);
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
	m_uiElementBase->initUIElementBase(
		{}, 
		{}
	);
@endif
@if '%{PluginType}' === 'QWidget with QML'
	m_uiElementBase->setSource(QUrl("qrc:/form.qml"));
@endif
}

Plugin::~Plugin()
{
}
