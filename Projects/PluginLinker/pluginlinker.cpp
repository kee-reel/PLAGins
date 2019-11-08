#include "pluginlinker.h"

PluginLinker::PluginLinker() :
	QObject(nullptr),
	PluginBase(this,
{
	INTERFACE(IPluginLinker)
})
{
	referencesInit({ {INTERFACE(IApplication), m_app} });
}

PluginLinker::~PluginLinker()
{
	for(auto& iter : m_linkerItemsMap)
	{
		iter.data()->unload();
	}
}

void PluginLinker::onReferencesSet()
{
	const auto &plugins = m_app->instance()->getPlugins();
	for(auto plugin : plugins)
	{
		addPlugin(plugin);
	}
	setupLinks();
}

bool PluginLinker::addCorePlugin(IPluginHandlerPtr pluginHandler)
{
	auto linkerItem = createLinkerItem(pluginHandler);
	if(linkerItem.isNull())
	{
		qCritical() << "PluginLinker::addNewPlugin: core plugin adding failed";
		return false;
	}
	return true;
}

bool PluginLinker::addPlugin(IPluginHandlerPtr pluginHandler)
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
//	qDebug() << "Load:" << pluginHandler.data()->getUID();

	if(pluginHandler.isNull())
	{
		qDebug() << "PluginLinker::createLinkerItem: given hander is empty" << pluginHandler.data()->getMeta();
//        log(SeverityType::WARNING, "PluginLinker::createLinkerItem: given hander is empty");
		return nullptr;
	}

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

bool PluginLinker::setupLinks()
{
	bool isLinkageSucceded = true;
	QMap<Interface, QList<uid_t>> troubledPlugins;

	for(auto& itemsIter : m_linkerItemsMap)
	{
		auto references = itemsIter.data()->references();
		auto name = itemsIter->descr().data()->name();
		for(auto linksIter = references.begin(); linksIter != references.end(); ++linksIter)
		{
			auto&& interface = linksIter.key();
			auto interfacesIter = m_interfacesMap.find(interface);
			if(interfacesIter != m_interfacesMap.end())
			{
				//qDebug() << "link:" << name << "to:" << interface;
				for(auto& item : *interfacesIter.value().data())
				{
					itemsIter.data()->addReference(interface, item);
				}
			}
			else if(linksIter.value() != 0)
			{
				auto& list = troubledPlugins[interface];
				list.append(itemsIter->descr().data()->uid());
				isLinkageSucceded = false;
			}
		}
	}

	if(isLinkageSucceded)
	{
//		log(SeverityType::INFO, "Linkage suceeded");
		qDebug() << "Linkage suceeded, loaded plugins:" << m_interfacesMap.keys();
	}
	else
	{
		//log(SeverityType::CRITICAL) << "Linkage failed, next referenced plugins not found:" << troubledPlugins;
		qDebug() << "Linkage failed, next referenced plugins not found (Interface, list of referent plugins UID):" << troubledPlugins;
	}

	onLinkageFinished();
	return isLinkageSucceded;
}

QWeakPointer<IPluginLinker::ILinkerItem> PluginLinker::loadNewPlugin(QString filename)
{
	auto handler = m_app->instance()->makePluginHandler(filename);
	return createLinkerItem(handler);
}

bool PluginLinker::loadPlugin(uid_t uid)
{
	m_linkerItemsMap.find(uid).value()->load();
	return true;
}

bool PluginLinker::unloadPlugin(uid_t uid)
{
	auto pluginHandler = m_linkerItemsMap[uid];
	pluginHandler.data()->unload();
	m_linkerItemsMap.remove(uid);
}

bool PluginLinker::linkPlugins(uid_t referentUID, QString interface, uid_t referenceUID)
{
	return true;
}

bool PluginLinker::unlinkPlugins(uid_t referentUID, QString interface, uid_t referenceUID)
{
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
