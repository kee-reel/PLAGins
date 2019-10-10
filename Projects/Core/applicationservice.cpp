#include "applicationservice.h"

ApplicationService::ApplicationService(IApplication *app, QObject* parent, QWidget* parentWidget) :
    QObject(parent),
    Service::CoreServiceBase(this,
        {INTERFACE(IApplication), INTERFACE(ICoreService)},
        {}),
    m_app(app),
    m_parentWidget(parentWidget)
{

}

QWidget *ApplicationService::getParentWidget()
{
    return m_parentWidget;
}

QVector<QWeakPointer<IPluginHandler> > ApplicationService::getPlugins()
{
    return m_app->getPlugins();
}

QWeakPointer<IPluginHandler> ApplicationService::makePluginHandler(QString path)
{
    return m_app->makePluginHandler(path);
}

bool ApplicationService::setReferences(Interface interface, QList<IReferenceDescriptorPtr> references)
{
    START_ASSIGNMENT(interface, references, getRefereneces())
    END_ASSIGNMENT()
}
