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
#include "../../Interfaces/Middleware/ipluginlinker.h"

#include "../../../Application/ipluginhandler.h"
#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "pluginlinkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker : public QObject, public PluginBase, public IPluginLinker
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

	// PluginBase interface
public:
	virtual void onPluginReferencesSet() override;

	// IPluginLinker interface
public:
	virtual QWeakPointer<ILinkerItem> addPlugin(QString filename) override;
	virtual bool removePlugin(QWeakPointer<ILinkerItem> linkerItem) override;
	virtual bool loadPlugin(uid_t uid) override;
	virtual bool unloadPlugin(uid_t uid) override;
	virtual bool linkPlugins(uid_t referentUID, QString interface, uid_t referenceUID) override;
	virtual bool unlinkPlugins(uid_t referent, QString interface, uid_t referenceUID) override;
	virtual QWeakPointer<ILinkerItem> getItemByUID(uid_t uid) override;
	virtual QWeakPointer<QList<QWeakPointer<ILinkerItem> > > getItemsWithInterface(Interface interface) override;

signals:
	void onLinkageFinished();

private:
	bool addPluginHandler(IPluginHandlerPtr pluginHandler);

	template<class Type>
	Type *castToInterface(QObject *possiblePlugin) const;
	QSharedPointer<LinkerItemBase> createLinkerItem(IPluginHandlerPtr);
	bool setupItemLinks(QSharedPointer<LinkerItemBase> &item);

private:
	QMap<Interface, QSharedPointer< QList<QWeakPointer<LinkerItemBase>> > > m_referencedInterfaces;

	QMap<Interface, QSharedPointer< QList<QWeakPointer<LinkerItemBase>> > > m_interfacesMap;
	QMap<uid_t, QSharedPointer<LinkerItemBase>> m_linkerItemsMap;

	QMap<Interface, QSharedPointer< QList<QWeakPointer<ILinkerItem>> > > m_rawInterfacesMap;
	QMap<uid_t, QSharedPointer<ILinkerItem>> m_rawLinkerItemsMap;

private:
	ReferenceInstancePtr<IApplication> m_app;
	QSharedPointer<ReferenceInstancesList<IPlugin>> m_plugins;
};
//! @}
#endif // PLUGINLINKER_H
