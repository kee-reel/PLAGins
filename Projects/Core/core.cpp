#include "core.h"

#include <QWidget>

Core::Core() :
	QObject(nullptr),
	PluginBase(this,
{
	INTERFACE(IApplication)
})
{
	referencesInit();
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
}

void Core::onReady()
{
}

QWidget *Core::getParentWidget()
{
	return m_app.data()->getParentWidget();
}

const QVector<IPluginHandlerPtr> &Core::getPlugins()
{
	return m_app.data()->getPlugins();
}

IPluginHandlerPtr Core::makePluginHandler(QString path)
{
	return m_app.data()->makePluginHandler(path);
}
