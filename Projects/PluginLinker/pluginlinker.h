#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include <QtCore>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "../../../Application/iapplication.h"
#include "../../Interfaces/ipluginlinker.h"

#include "../../../Application/ipluginhandler.h"
#include "../Core/CoreServiceBase/coreservicebase.h"

#include "pluginlinkeritem.h"
#include "servicelinkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker : public QObject, public Service::CoreServiceBase, public IPluginLinker
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        Service::ICoreService
        IPluginLinker
    )

public:
    PluginLinker();
    virtual ~PluginLinker() override;

    // ICoreService interface
public:
    virtual bool setReferences(Interface interface, QList<IReferenceDescriptorPtr> references) override;

    // IPluginLinker interface
public:
    virtual QWeakPointer<ILinkerItem> loadNewPlugin(QString filename) override;
    virtual bool loadPlugin(uid_t uid) override;
    virtual bool unloadPlugin(uid_t uid) override;
    virtual bool linkPlugins(uid_t referentUID, QString interface, uid_t referenceUID) override;
    virtual bool unlinkPlugins(uid_t referent, QString interface, uid_t referenceUID) override;
    virtual QWeakPointer<ILinkerItem> getItemByUID(uid_t uid) override;
    virtual QWeakPointer<QList<QWeakPointer<ILinkerItem> > > getItemsWithInterface(Interface interface) override;

signals:
    void onLinkageFinished();

public slots:
    void onServiceManagerInitialized();

private:
    bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool addPlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool setupLinks();

    template<class Type>
    Type *castToInterface(QObject *possiblePlugin) const;
    QSharedPointer<LinkerItemBase> createLinkerItem(QWeakPointer<IPluginHandler>);

private:
    QMap<Interface, QSharedPointer< QList<QWeakPointer<LinkerItemBase>> > > m_interfacesMap;
    QMap<uid_t, QSharedPointer<LinkerItemBase>> m_linkerItemsMap;

    QMap<Interface, QSharedPointer< QList<QWeakPointer<ILinkerItem>> > > m_rawInterfacesMap;
    QMap<uid_t, QSharedPointer<ILinkerItem>> m_rawLinkerItemsMap;

private:
    ReferenceInstance<IApplication> m_app;
};
//! @}
#endif // PLUGINLINKER_H
