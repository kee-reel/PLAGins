#ifndef SERVICESMANAGER_H
#define SERVICESMANAGER_H

#include "icoreservice.h"
#include "../../../Application/iapplication.h"

namespace Service
{

class CoreServicesManager : public QObject, public ICoreServicesManager
{
    Q_OBJECT
public:
    CoreServicesManager(QObject* parent, IApplication* app);
    virtual ~CoreServicesManager() override;

    // IServicesManager interface
public:
    virtual QList<QString> getServicesInterfaces() override;
    virtual QWeakPointer<QList<ICoreService*>> getServicesWithInterface(QString serviceInterface) override;
    virtual void addService(QString serviceInterface, ICoreService *service) override;
    virtual void removeService(QString serviceInterface, ICoreService *service) override;
    virtual QObject *getObject() override;

signals:
    void onInitialized();

private:
    IApplication* m_app;
    QMap<ICoreService*, QWeakPointer<IPluginHandler>> m_servicePlugins;
    QMap<QString, QSharedPointer<QList<ICoreService*>>> m_services;
};

}
#endif // SERVICESMANAGER_H
