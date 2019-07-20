#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include <QtCore>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "PluginBase/plugin_base.h"

#include "../CorePlugin/ServiceBase/servicebase.h"
#include "../../Interfaces/ipluginlinker.h"

#include "linkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker : public Service::ServiceBase, public IPluginLinker
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IPluginLinker
    )

public:
    PluginLinker();
    virtual ~PluginLinker() override;

    // IPluginLinker interface
public:
    virtual bool unloadPlugin(QWeakPointer<ILinkerItem> linkerItem) override;
    virtual bool loadPlugin(QString filename) override;

    virtual int getCorePluginUID() override;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() override;

signals:
    void onLinkageFinished();

private:
    bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool addPlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool setupLinks();

    template<class Type>
    Type *castToPlugin(QObject *possiblePlugin) const;
    QSharedPointer<MetaInfo> parseMetaInfo(const QJsonObject &metaInfoObject) const;
    QSharedPointer<LinkerItem> createLinkerItem(QWeakPointer<IPluginHandler>);

private:
    const QString META_FIELD_INTERFACE                  = "Interface";
    const QString META_FIELD_NAME                       = "Name";
    const QString META_FIELD_RELATED_PLUGIN_INTERFACES  = "RelatedPluginInterfaces";
    const QString META_FIELD_ABOUT                      = "About";

private:
    QSharedPointer<LinkerItem> m_corePlugin;
    QMap<QString, QSharedPointer<LinkerItem>> m_interfacesMap;
    QMap<int, QSharedPointer<LinkerItem>> m_linkerItemsMap;
    int m_pluginUidCounter;
};
//! @}
#endif // PLUGINLINKER_H
