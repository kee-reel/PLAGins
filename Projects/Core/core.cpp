#include "core.h"

#include <QWidget>

Core::Core() :
	QObject(nullptr),
	PluginBase(this,
{
	INTERFACE(IApplication)
})
{
	initPluginBase();
}

Core::~Core()
{
}

void Core::coreInit(QWeakPointer<IApplication> app)
{
	m_app = app;
	m_linker.reset(new SimpleLinker(this, app));
	m_linker->init();
}

bool Core::coreFini()
{
	return true;
}

void Core::onPluginReady()
{
}

QWidget *Core::getParentWidget()
{
	return m_app.toStrongRef()->getParentWidget();
}

const QVector<IPluginHandlerPtr> &Core::getPlugins()
{
	return m_app.toStrongRef()->getPlugins();
}

IPluginHandlerPtr Core::makePluginHandler(const QString &path)
{
	return m_app.toStrongRef()->makePluginHandler(path);
}
