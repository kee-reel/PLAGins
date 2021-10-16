#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

@UI@#include "../../Interfaces/Architecture/GUIElementBase/guielementbase.h"
@UI@
@WID@namespace Ui
@WID@{
@WID@	class Form;
@WID@}
@WID@
@INT@#include "%{HdrFileName}"
@INT@
@QML@#include "%{REF_FILENAME}"
@QML@
class Plugin : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.%{CN}" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin)

public:
	Plugin();
	~Plugin() override;

private:
@WID@	QSharedPointer<Ui::Form> ui;
@UI@	GUIElementBase* m_guiElementBase;
@INT@	%{CN}* m_impl;
@QML@	ReferenceInstancePtr<%{REF}> m_reference;
};
