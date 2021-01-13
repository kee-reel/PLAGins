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
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QML'
	, m_uiElementBase(new UIElementBase(this, {"MainMenuItem"}), "qrc:/form.qml")
@endif
@if %{CreateNewInterface}
	, m_impl(new %{CN}(this))
@endif
{
	initPluginBase(
		{
			{INTERFACE(IPlugin), this}
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QML'
			, {INTERFACE(IUIElement), m_uiElementBase}
@endif
@if %{CreateNewInterface}
			, {INTERFACE(%{InterfaceName}), m_impl}
@endif
		},
		{
		// Commented code shows how to add new references. Uncomment and modify according to type used in plugin.h
		//	{INTERFACE(IExample), m_exampleReference}
		}
	);

@if '%{PluginType}' === 'QWidget'
	ui->setupUi(m_uiElementBase);
	m_uiElementBase->initUIElementBase();
	connect(ui->exitButton, &QPushButton::clicked, m_uiElementBase, &UIElementBase::closeSelf);
@endif
@if '%{PluginType}' === 'QML'
	m_uiElementBase->initUIElementBase(,
		{
		// Commented code shows how to use reference to QML file. Uncomment, modify and go to form.qml for further instructions.
		//	{"exampleReference", m_exampleReference.data()}
		}
	);
@endif
}

Plugin::~Plugin()
{
}
