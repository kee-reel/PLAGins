#include "coreservicebase.h"

namespace Service
{

CoreServiceBase::CoreServiceBase(QObject* object) :
    m_object(object),
    m_serviceManager(nullptr)
{
}

CoreServiceBase::~CoreServiceBase()
{
}

void CoreServiceBase::serviceInit(const QJsonObject &serviceMeta, ICoreServicesManager *manager)
{
    qDebug() << "serviceInit" << serviceMeta << manager;
    m_serviceManager = manager;
    QObject::connect(m_serviceManager->getObject(), SIGNAL(onInitialized()), m_object, SLOT(onServiceManagerInitialized()));

    m_interfaces = getServiceInterfaces(serviceMeta);    
    for(const auto& interfaceName : m_interfaces)
    {
        m_serviceManager->addService(interfaceName, this);
    }
}

QStringList CoreServiceBase::getServiceInterfaces(const QJsonObject& servicexMeta)
{
    if(!servicexMeta.contains("service"))
        return QStringList();

    auto&& serviceMetaData = servicexMeta.value("service").toObject();
    if(!serviceMetaData.contains("interfaces"))
        return QStringList();

    auto&& interfaces = serviceMetaData.value("interfaces").toArray();
    if(interfaces.isEmpty())
        return QStringList();

    QStringList list;
    for (const auto& item : interfaces.toVariantList())
    {
        list.append(item.toString());
    }
    return list;
}

void CoreServiceBase::serviceFini()
{
    for(const auto& interfaceName : m_interfaces)
    {
        m_serviceManager->removeService(interfaceName, this);
    }
}

QObject *CoreServiceBase::getObject()
{
    return m_object;
}

void CoreServiceBase::onServiceManagerInitialized()
{
    qDebug() << "init" << m_serviceManager->getServicesInterfaces();
}

}
