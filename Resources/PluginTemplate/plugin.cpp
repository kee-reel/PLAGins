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
@QML@			// Set reference pointer object to internal plugin map, so it could be accessed by plugin linker
@QML@			{INTERFACE(%{REF}), m_reference}
		}
	);

@WID@	ui->setupUi(m_guiElementBase);
@WID@	m_guiElementBase->initGUIElementBase();
@WID@	connect(ui->exitButton, &QPushButton::clicked, m_guiElementBase, &GUIElementBase::closeSelf);
@QML@	m_guiElementBase->initGUIElementBase(
@QML@		{
@QML@			// Pass reference pointer object into QML
@QML@			{"reference", m_reference.data()}
@QML@		}
@QML@	);
}

Plugin::~Plugin()
{
}
