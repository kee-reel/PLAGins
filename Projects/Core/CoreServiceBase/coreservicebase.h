#ifndef SERVICEBASE_H
#define SERVICEBASE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../icoreservice.h"


//! addtogroup CorePlugin_imp
//! {
namespace Service
{

class CoreServiceBase : public ICoreService
{
    Q_GADGET
public:
    CoreServiceBase(QObject *object);
    virtual ~CoreServiceBase();

    // IService interface
public:
    virtual void serviceInit(const QJsonObject& serviceMeta, ICoreServicesManager *manager) override;
    virtual void serviceFini() override;
    virtual QObject *getObject() override;

public slots:
    virtual void onServiceManagerInitialized();

private:
    QObject* m_object;
    QStringList m_interfaces;
    ICoreServicesManager* m_serviceManager;

private:
    QStringList getServiceInterfaces(const QJsonObject &servicexMeta);
};

}
//! }
#endif // SERVICEBASE_H
