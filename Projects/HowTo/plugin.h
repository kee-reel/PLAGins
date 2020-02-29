#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "../../Interfaces/Utility/ihowto.h"
#include "howto.h"

#include "../../Interfaces/Middleware/ipluginlinker.h"

class Plugin : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.HowTo" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin)
	
public:
	Plugin();
	~Plugin() override;
	
private:
	HowTo* m_impl;
	ReferenceInstancePtr<IPluginLinker> m_linker;
	
	// PluginBase interface
protected:
	void onReady() override;
};
