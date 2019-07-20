#ifndef SERVICEBASE_H
#define SERVICEBASE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../iservice.h"


//! addtogroup CorePlugin_imp
//! {
namespace Service
{

class ServiceBase : public IService
{
public:
    ServiceBase(QObject *object);
    virtual ~ServiceBase();

    // IService interface
public:
    virtual void serviceInit(IApplication *app, IServicesManager *manager) override;
    virtual void serviceFini() override;
    virtual QObject *getObject() override;

private:
    QObject* m_object;
    IApplication* m_app;
    IServicesManager* m_serviceManager;
};

}
//! }
#endif // SERVICEBASE_H
