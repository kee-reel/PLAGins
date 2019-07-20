#include "servicebase.h"

namespace Service
{

ServiceBase::ServiceBase(QObject* object) :
    m_object(object),
    m_app(nullptr),
    m_serviceManager(nullptr)
{
}

ServiceBase::~ServiceBase()
{
}

void ServiceBase::serviceInit(IApplication *app, IServicesManager *manager)
{
    qDebug() << "serviceInit" << app << manager;
    m_app = app;
    m_serviceManager = manager;

    m_serviceManager->addService("IDataBase", m_object);
}

void ServiceBase::serviceFini()
{
}

QObject *ServiceBase::getObject()
{
    return m_object;
}

}
