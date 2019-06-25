#ifndef PLUGINLINKERVIEW_H
#define PLUGINLINKERVIEW_H

#include <QObject>
#include <QDebug>
#include <QString>

#include <QStringListModel>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/ipluginlinker.h"

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
    virtual ~PluginLinkerView();

// PluginBase interface
protected slots:
    void onAllReferencesSet() override;
public:
    virtual void onAllReferencesReady() override;

private slots:
    void addPlugin();
    void removePlugin();

private:
    IPluginLinker* m_pluginLinker;
    QStringListModel m_pluginsListModel;
    QMap<QString, QWeakPointer<IPluginLinker::ILinkerItem>> m_linkerItems;
};
//! }
#endif // PLUGINLINKERVIEW_H
