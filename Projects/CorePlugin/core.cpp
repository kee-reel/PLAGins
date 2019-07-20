#include "coreplugin.h"

CorePlugin::CorePlugin() : QObject(nullptr)
{
}

CorePlugin::~CorePlugin()
{
}

void CorePlugin::coreInit(IApplication* app)
{
//    setParent(app.data()->getParentWidget());
    m_app = app;
    m_servicesManager = new Service::ServicesManager(app);

    auto p = app->getPlugins();
}

bool CorePlugin::coreFini()
{
}
