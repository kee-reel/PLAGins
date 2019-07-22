#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../../Application/icoreplugin.h"

#include "icoreservice.h"
#include "coreservicesmanager.h"


//! addtogroup CorePlugin_imp
//! {
class Core : public QObject, public ICore
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MASS.Module.CorePlugin" FILE "PluginMeta.json")
    Q_INTERFACES(ICore)

public:
    Core();
    virtual ~Core() override;

    // ICorePlugin interface
public:
    virtual void coreInit(IApplication *app) override;
    virtual bool coreFini() override;

 private:
    IApplication* m_app;
    Service::CoreServicesManager* m_servicesManager;
};
//! }
#endif // COREPLUGIN_H
