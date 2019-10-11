#include "core.h"

#include <QWidget>

Core::Core() :
    QObject(nullptr),
    PluginBase(this, {INTERFACE(IApplication)})
{
    referencesInit({}, {});
}

Core::~Core()
{
}

void Core::coreInit(IApplication* app)
{
    m_app = app;
    m_linker = new Service::SimpleLinker(this, app);
    m_linker->init();
}

bool Core::coreFini()
{
}

QWidget *Core::getParentWidget()
{
    return m_app->getParentWidget();
}

QVector<IPluginHandlerPtr > Core::getPlugins()
{
    return m_app->getPlugins();
}

IPluginHandlerPtr Core::makePluginHandler(QString path)
{
    return m_app->makePluginHandler(path);
}
