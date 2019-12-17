#include "pluginlinker.h"

PluginLinker::PluginLinker() :
	QObject(nullptr),
	PluginBase(this,
{
			   INTERFACE(IPluginLinker)
			   })
{
	initPluginBase({ {INTERFACE(IApplication), m_app} });
}

PluginLinker::~PluginLinker()
{
	for(auto& iter : m_linkerItemsMap)
	{
		iter.data()->unload();
	}
}

void PluginLinker::onPluginReferencesSet()
{
	const auto &plugins = m_app->instance()->getPlugins();
	for(auto plugin : plugins)
	{
		addPluginHandler(plugin);
	}
}

QWeakPointer<IPluginLinker::ILinkerItem> PluginLinker::addPlugin(QString filename)
{
	auto handler = m_app->instance()->makePluginHandler(filename);
	auto item = createLinkerItem(handler);
	setupItemLinks(item);
	return item;
}

bool PluginLinker::removePlugin(QWeakPointer<IPluginLinker::ILinkerItem> linkerItem)
{
	auto uid = linkerItem.data()->descr().data()->uid();
	m_linkerItemsMap.remove(uid);
	m_rawLinkerItemsMap.remove(uid);
	return false;
}

bool PluginLinker::addPluginHandler(IPluginHandlerPtr pluginHandler)
{
	auto linkerItem = createLinkerItem(pluginHandler);
	if(linkerItem.isNull())
	{
		qCritical() << "PluginLinker::addNewPlugin: plugin adding failed";
		return false;
	}
	return true;
}

QSharedPointer<LinkerItemBase> PluginLinker::createLinkerItem(IPluginHandlerPtr pluginHandler)
{
	if(pluginHandler.isNull())
	{
		qDebug() << "PluginLinker::createLinkerItem: given hander is empty";
		//        log(SeverityType::WARNING, "PluginLinker::createLinkerItem: given hander is empty");
		return nullptr;
	}
	
	//	qDebug() << "Load:" << pluginHandler.data()->getUID();
	
	QSharedPointer<LinkerItemBase> linkerItemPtr;
	if(PluginLinkerItem::isPlugin(pluginHandler))
	{
		//		qDebug() << QString("PluginLinker::createLinkerItem: load plugin") << pluginHandler.data()->getMeta();
		//        log(SeverityType::WARNING, QString("PluginLinker::createLinkerItem: can't load plugin '%1'").arg(m_metaInfo.Name));
		linkerItemPtr.reset(new PluginLinkerItem(pluginHandler));
	}
	else
	{
		qDebug() << QString("PluginLinker::createLinkerItem: unkown plugin type");
		return nullptr;
	}
	
	if(!linkerItemPtr->load())
	{
		qDebug() << "Failed to load plugin";
		return nullptr;
	}
	
	auto&& uid = linkerItemPtr->descr().data()->uid();
	m_linkerItemsMap.insert(uid, linkerItemPtr);
	m_rawLinkerItemsMap.insert(uid, linkerItemPtr);
	
	auto&& references = linkerItemPtr->references();
	for(auto iter = references.begin(); iter != references.end(); ++iter)
	{
		auto& list = m_referencedInterfaces[iter.key()];
		if(list.isNull())
		{
			list.reset(new QList<QWeakPointer<LinkerItemBase>>);
		}
		list->append(linkerItemPtr);
	}
	
	auto&& interfaces = linkerItemPtr->descr().data()->interfaces();
	for(auto& interface : interfaces)
	{
		auto& list = m_interfacesMap[interface];
		auto& rawList = m_rawInterfacesMap[interface];
		
		if(list.isNull())
		{
			list.reset(new QList<QWeakPointer<LinkerItemBase>>);
			rawList.reset(new QList<QWeakPointer<ILinkerItem>>);
		}
		
		list->append(linkerItemPtr);
		rawList->append(linkerItemPtr);
		
	}
	
	setupItemLinks(linkerItemPtr);
	
	//qDebug() << "Add" << linkerItemPtr->descr().data()->name();
	//    log(SeverityType::INFO, QString("Plugin '%1' loaded").arg(metaInfo.data()->Name));
	return linkerItemPtr;
}

template<class Type>
Type *PluginLinker::castToInterface(QObject *possiblePlugin) const
{
	Type *plugin = qobject_cast<Type *>(possiblePlugin);
	
	if(!plugin)
	{
		//        log(SeverityType::WARNING, QString("Can't load the plugin '%1': not QObject.").arg(possiblePlugin->objectName()));
	}
	
	return plugin;
}

bool PluginLinker::setupItemLinks(QSharedPointer<LinkerItemBase> &item)
{
	QMap<Interface, QList<uid_t>> troubledPlugins;
	bool isLinkageSucceded = true;
	auto references = item->references();
	for(auto referencesIter = references.begin(); referencesIter != references.end(); ++referencesIter)
	{
		auto&& interface = referencesIter.key();
		auto&& requiredReferencesCount = referencesIter.value();
		auto referencesList = m_interfacesMap.find(interface);
		if(referencesList != m_interfacesMap.end())
		{
			for(auto& reference : *referencesList.value().data())
			{
				item->addReference(interface, reference);
				reference.data()->addReferent(interface, item);
			}
		}
		else if(requiredReferencesCount != 0)
		{
			auto& list = troubledPlugins[interface];
			list.append(item->descr().data()->uid());
			isLinkageSucceded = false;
		}
	}
	
	for(auto& interface : item->descr().data()->interfaces())
	{
		auto referencesList = m_referencedInterfaces.find(interface);
		if(referencesList != m_referencedInterfaces.end())
		{
			for(auto& reference : *referencesList.value().data())
			{
				reference.data()->addReference(interface, item);
				item->addReferent(interface, reference);
			}
		}
	}
	
	if(!isLinkageSucceded)
	{
		//log(SeverityType::CRITICAL) << "Linkage failed, next referenced plugins not found:" << troubledPlugins;
		qDebug() << "Linkage failed, next referenced plugins not found (Interface, list of referent plugins UID):" << troubledPlugins;
	}
	
	return isLinkageSucceded;
}

bool PluginLinker::loadPlugin(uid_t uid)
{
	m_linkerItemsMap.find(uid).value()->load();
	return true;
}

bool PluginLinker::unloadPlugin(uid_t uid)
{
	m_linkerItemsMap.find(uid).value()->unload();
	return true;
}

bool PluginLinker::linkPlugins(uid_t referentUID, QString interface, uid_t referenceUID)
{
	Q_UNUSED(referentUID)
	Q_UNUSED(interface)
	Q_UNUSED(referenceUID)
	return true;
}

bool PluginLinker::unlinkPlugins(uid_t referentUID, QString interface, uid_t referenceUID)
{
	Q_UNUSED(referentUID)
	Q_UNUSED(interface)
	Q_UNUSED(referenceUID)
	return true;
}

QWeakPointer<IPluginLinker::ILinkerItem> PluginLinker::getItemByUID(uid_t uid)
{
	return m_rawLinkerItemsMap.find(uid).value();
}

QWeakPointer<QList<QWeakPointer<IPluginLinker::ILinkerItem> > > PluginLinker::getItemsWithInterface(Interface interface)
{
	auto iter = m_rawInterfacesMap.find(interface);
	return iter != m_rawInterfacesMap.end() ? iter.value() : nullptr;
}
