#include "coreservicesmanager.h"

namespace Service
{

CoreServicesManager::CoreServicesManager(QObject *parent, IApplication *app) :
    QObject(parent),
    m_app(app)
{
    auto&& plugins = m_app->getPlugins();
    for (auto& plugin : plugins)
    {
        auto&& metaData = plugin.data()->getMeta().value("MetaData").toObject();
        if(!metaData.contains("service"))
            continue;

        if(plugin.data()->load())
        {
            auto&& obj = plugin.data()->getInstance();
            auto service = qobject_cast<ICoreService*>(obj);
            if(service)
            {
                m_servicePlugins[service] = plugin;
                service->serviceInit(metaData, this);
            }
            else
            {
                plugin.data()->unload();
            }
        }
    }
    emit onInitialized();
}

CoreServicesManager::~CoreServicesManager()
{

}

QList<QString> CoreServicesManager::getServicesInterfaces()
{
    return m_services.keys();
}

QWeakPointer<QList<ICoreService *> > CoreServicesManager::getServicesWithInterface(QString serviceInterface)
{
    QWeakPointer<QList<ICoreService*>> servicesList;
    auto iter = m_services.find(serviceInterface);
    if(iter != m_services.end())
    {
        servicesList = iter.value();
    }
    return servicesList;
}

void CoreServicesManager::addService(QString serviceInterface, ICoreService *service)
{
    QWeakPointer<QList<ICoreService*>> servicesList;
    auto iter = m_services.find(serviceInterface);
    if(iter != m_services.end())
    {
        servicesList = iter.value();
    }
    else
    {
        QSharedPointer<QList<ICoreService*>> newList(new QList<ICoreService*>());
        m_services[serviceInterface] = newList;
        servicesList = newList;
    }
    servicesList.data()->append(service);
}

void CoreServicesManager::removeService(QString serviceInterface, ICoreService *service)
{
    QWeakPointer<QList<ICoreService*>> servicesList;
    auto iter = m_services.find(serviceInterface);
    if(iter != m_services.end())
    {
        auto&& list = iter.value().data();
        list->removeOne(service);
        if(list->empty())
        {
            m_services.remove(serviceInterface);
        }
    }
}

QObject *CoreServicesManager::getObject()
{
    return this;
}

}
