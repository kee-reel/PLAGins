#ifndef PLUGINLINKERVIEW_H
#define PLUGINLINKERVIEW_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Common/plugin_base.h"

//! addtogroup PluginLinkerView_imp
//! {
class PluginLinkerView :
        public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MASS.Module.PluginLinkerView" FILE "PluginMeta.json")
    Q_INTERFACES(
            IPlugin
            )

public:
    PluginLinkerView();
    virtual ~PluginLinkerView() override;
};
//! }
#endif // PLUGINLINKERVIEW_H
