#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../../Application/icoreplugin.h"

#include "iservice.h"
#include "servicesmanager.h"


//! addtogroup CorePlugin_imp
//! {
class CorePlugin : public QObject, ICorePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MASS.Module.CorePlugin" FILE "PluginMeta.json")
    Q_INTERFACES(ICorePlugin)

public:
    CorePlugin();
    virtual ~CorePlugin() override;

    // ICorePlugin interface
public:
    virtual void coreInit(IApplication *app) override;
    virtual bool coreFini() override;

 private:
    IApplication* m_app;
    Service::ServicesManager* m_servicesManager;
};
//! }
#endif // COREPLUGIN_H
