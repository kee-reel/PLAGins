#include "plugin.h"
@WID@#include "ui_form.h"

Plugin::Plugin() :
	QObject(nullptr),
	PluginBase(this)
@WID@	, ui(new Ui::Form)
@QML@	, m_guiElementBase(new GUIElementBase(this, {"MainMenuItem"}, "qrc:/form.qml"))
@WID@	, m_guiElementBase(new GUIElementBase(this, {"MainMenuItem"}))
@INT@	, m_impl(new %{CN}(this))
{
	initPluginBase(
		{
			{INTERFACE(IPlugin), this}
@UI@			, {INTERFACE(IGUIElement), m_guiElementBase}
@INT@			, {INTERFACE(%{InterfaceName}), m_impl}
		},
		{
		// Commented code shows how to add new references. Uncomment and modify according to type used in plugin.h
		//	{INTERFACE(IExample), m_exampleReference}
		}
	);

@WID@	ui->setupUi(m_guiElementBase);
@WID@	m_guiElementBase->initGUIElementBase();
@WID@	connect(ui->exitButton, &QPushButton::clicked, m_guiElementBase, &GUIElementBase::closeSelf);
@QML@	m_guiElementBase->initGUIElementBase(
@QML@		{
@QML@		// Commented code shows how to use reference to QML file. Uncomment, modify and go to form.qml for further instructions.
@QML@		//	{"exampleReference", m_exampleReference.data()}
@QML@		}
@QML@	);
}

Plugin::~Plugin()
{
}
