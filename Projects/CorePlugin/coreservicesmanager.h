#ifndef SERVICESMANAGER_H
#define SERVICESMANAGER_H

#include "iservice.h"

namespace Service
{

class ServicesManager : public IServicesManager
{
public:
    ServicesManager(IApplication* app);
    virtual ~ServicesManager();

    // IServicesManager interface
public:
    virtual QList<QString> getServicesInterfaces() override;
    virtual QWeakPointer<QList<QObject*>> getServicesWithInterface(QString serviceInterface) override;
    virtual void addService(QString serviceInterface, QObject* service) override;
    virtual void removeService(QString serviceInterface, QObject* service) override;
    virtual QObject *getObject() override;

private:
    IApplication* m_app;
    QMap<IService*, QWeakPointer<IPluginHandler>> m_servicePlugins;
    QMap<QString, QSharedPointer<QList<IService*>>> m_services;
};

}
#endif // SERVICESMANAGER_H
