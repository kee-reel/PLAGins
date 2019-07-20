#ifndef ISERVICE_H
#define ISERVICE_H

#include <QtCore>

#include "../../../Application/icoreplugin.h"

namespace Service
{

class IServicesManager
{
public:
    virtual QList<QString> getServicesInterfaces() = 0;

    virtual QWeakPointer<QList<QObject*>> getServicesWithInterface(QString serviceInterface) = 0;

    virtual void addService(QString serviceInterface, QObject* service) = 0;

    virtual void removeService(QString serviceInterface, QObject* service) = 0;

    virtual QObject* getObject() = 0;

signals:
    void onServicesUpdated(QString serviceInterface);
};

class IService
{
public:
    virtual void serviceInit(IApplication* app, IServicesManager* manager) = 0;

    virtual void serviceFini() = 0;

    virtual QObject* getObject() = 0;
};

}
Q_DECLARE_INTERFACE(Service::IService, "IService")
#endif // ISERVICE_H
