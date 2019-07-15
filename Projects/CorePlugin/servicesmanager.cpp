#include "servicesmanager.h"

namespace Service
{

ServicesManager::ServicesManager(IApplication *app) :
    m_app(app)
{
    auto&& plugins = m_app->getPlugins();
    for (auto& plugin : plugins)
    {
        auto&& metaData = plugin.data()->getMeta().value("MetaData").toObject();
        if(!metaData.contains("service"))
            continue;

        auto&& serviceMetaData = metaData.value("service").toObject();
        if(!serviceMetaData.contains("interfaces"))
            continue;

        auto&& interfaces = serviceMetaData.value("interfaces").toArray();
        if(interfaces.isEmpty())
            continue;

        if(plugin.data()->load())
        {
            auto&& obj = plugin.data()->getInstance();
            auto service = qobject_cast<IService*>(obj);
            if(service)
            {
                m_servicePlugins[service] = plugin;
                for(auto interface : interfaces)
                {
                    auto&& interfaceStr = interface.toString();
                    if(m_services.contains(interfaceStr))
                    {
                        auto& servicesList = m_services[interfaceStr];
                        servicesList->append(service);
                    }
                    else
                    {
                        auto&& servicesList = QSharedPointer<QList<IService*>>(new QList<IService*>());
                        servicesList->append(service);
                        m_services[interfaceStr] = servicesList;
                    }
                }
            }
            else
            {
                plugin.data()->unload();
            }
        }
    }

    for(auto& servicesList : m_services)
    {
        for(auto& service : *servicesList.data())
        {
            service->serviceInit(m_app, this);
        }
    }
}

ServicesManager::~ServicesManager()
{

}

QList<QString> ServicesManager::getServicesInterfaces()
{
}

QWeakPointer<QList<QObject *> > ServicesManager::getServicesWithInterface(QString serviceInterface)
{
}

void ServicesManager::addService(QString serviceInterface, QObject *service)
{

}

void ServicesManager::removeService(QString serviceInterface, QObject *service)
{
}

QObject *ServicesManager::getObject()
{
}

}
