#include "core.h"

#include <QWidget>

Core::Core() : QObject(nullptr)
{
}

Core::~Core()
{
}

void Core::coreInit(IApplication* app)
{
    m_app = app;
    auto widget = m_app->getParentWidget();
    setParent(qobject_cast<QObject*>(widget));
    m_servicesManager = new Service::CoreServicesManager(this, app);

    auto p = app->getPlugins();
}

bool Core::coreFini()
{
}
