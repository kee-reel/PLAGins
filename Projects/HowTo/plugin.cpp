#include "plugin.h"

Plugin::Plugin() :
	QObject(nullptr),
	PluginBase(this)
  , m_impl(new HowTo(this))
{
	initPluginBase(
		{
			{INTERFACE(IPlugin), this}
			, {INTERFACE(IHowTo), m_impl}
		},
		{
			{INTERFACE(IPluginLinker), m_linker}
		},
		{}
	);
}

Plugin::~Plugin()
{
}

void Plugin::onReady()
{
	qDebug() << m_linker->getItemsWithInterface(INTERFACE(IPlugin)).toStrongRef()->length();
}
