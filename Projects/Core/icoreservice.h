#ifndef ISERVICE_H
#define ISERVICE_H

#include <QtCore>

namespace Service
{
class ICoreService;

class ICoreServicesManager
{
public:
    virtual QList<QString> getServicesInterfaces() = 0;

    virtual QWeakPointer<QList<ICoreService*>> getServicesWithInterface(QString serviceInterface) = 0;

    virtual void addService(QString serviceInterface, ICoreService* service) = 0;

    virtual void removeService(QString serviceInterface, ICoreService* service) = 0;

    virtual QObject* getObject() = 0;

signals:
    void onInitialized();
    void onServicesUpdated(QString serviceInterface);
};

class ICoreService
{
public:
    virtual void serviceInit(const QJsonObject& serviceMeta, ICoreServicesManager* manager) = 0;

    virtual void serviceFini() = 0;

    virtual QObject* getObject() = 0;
};

}
Q_DECLARE_INTERFACE(Service::ICoreService, "ICoreService")
#endif // ISERVICE_H
