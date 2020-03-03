#pragma once


#include <QtCore>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "../../../Application/Interfaces/iapplication.h"
#include "../../Interfaces/Middleware/ipluginlinker.h"

#include "../../../Application/Interfaces/ipluginhandler.h"
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
	virtual void onReferencesSet() override;

	// IPluginLinker interface
public:
	virtual QWeakPointer<ILinkerItem> addPlugin(QString filename) override;
	virtual bool removePlugin(QWeakPointer<ILinkerItem> linkerItem) override;
	virtual bool loadPlugin(quint32 uid) override;
	virtual bool unloadPlugin(quint32 uid) override;
	virtual bool linkPlugins(quint32 referentUID, QString interface, quint32 referenceUID) override;
	virtual bool unlinkPlugins(quint32 referent, QString interface, quint32 referenceUID) override;
	virtual QWeakPointer<ILinkerItem> getItemByUID(quint32 uid) override;
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
	QMap<quint32, QSharedPointer<LinkerItemBase>> m_linkerItemsMap;

	QMap<Interface, QSharedPointer< QList<QWeakPointer<ILinkerItem>> > > m_rawInterfacesMap;
	QMap<quint32, QSharedPointer<ILinkerItem>> m_rawLinkerItemsMap;

private:
	ReferenceInstancePtr<IApplication> m_app;
	QSharedPointer<ReferenceInstancesList<IPlugin>> m_plugins;
};
//! @}

