#include "simplelinker.h"

SimpleLinker::SimpleLinker(QObject *parent, QWeakPointer<IApplication> app) :
	QObject(parent), m_app(app)
{
}

SimpleLinker::~SimpleLinker()
{
}

void SimpleLinker::addPlugin(IPluginHandlerPtr pluginHandler)
{
	if(pluginHandler.data()->load())
	{
		auto&& obj = pluginHandler.data()->getInstance();
		auto plugin = qobject_cast<IPlugin*>(obj );
		if(!plugin)
		{
			pluginHandler.data()->unload();
			return;
		}

		if(!plugin->pluginInit(pluginHandler.data()->getUID(), pluginHandler.data()->getMeta()))
		{
			return;
		}

		auto descr = plugin->getDescriptor();
		ReferenceInstance<IPlugin> instance;
		if(!instance.reset(descr))
		{
			return;
		}

		QSharedPointer<LoadedPluginPair> handler(new LoadedPluginPair(pluginHandler, instance));
		m_plugins.append(handler);
		for(auto& interface : descr.data()->interfaces())
		{
			auto& list = m_pluginsInterfaces[interface];
			list.append(handler);
		}
	}
}

void SimpleLinker::removePlugin(IReferenceDescriptorPtr descr)
{
//    QWeakPointer<QList<ICoreService*>> servicesList;
//    auto iter = m_services.find(serviceInterface);
//    if(iter != m_services.end())
//    {
//        auto&& list = iter.value().data();
//        list->removeOne(service);
//        if(list->empty())
//        {
//            m_services.remove(serviceInterface);
//        }
//    }
}

void SimpleLinker::init()
{
	auto&& plugins = m_app.data()->getPlugins();
	for (auto& plugin : plugins)
	{
		addPlugin(plugin);
	}

	for(auto& pluginPair : m_plugins)
	{
		qDebug() << "Plugin" << pluginPair->second.descr().data()->name();
		auto instancesHandler = pluginPair->second->getInstancesHandler();
		auto &&requiredReferences = instancesHandler.data()->requiredReferences();
		for (auto referenceIter = requiredReferences.begin(); referenceIter != requiredReferences.end(); ++referenceIter)
		{
			auto pluginsIter = m_pluginsInterfaces.find(referenceIter.key());
			if(pluginsIter != m_pluginsInterfaces.end())
			{
				qDebug() << "Reference" << pluginsIter.key().name();
				QList<IReferenceDescriptorPtr> list;
				auto referencesCount = referenceIter.value();
				auto &&pluginsList = pluginsIter.value();
				if(referencesCount == 0)
				{
					for(auto& plugin : pluginsList)
					{
						list.append(plugin.data()->second.descr());
					}
				}
				else
				{
					for(auto i = 0; i < referencesCount; ++i)
					{
						list.append(pluginsList[i].data()->second.descr());
					}
				}
				if(!instancesHandler.data()->setReferences(referenceIter.key(), list))
				{
					qDebug() << "Can't set references for plugin";
				}
			}
		}
	}

	for(auto& pluginPair : m_plugins)
	{
		qDebug() << "Plugin" << pluginPair->second.descr().data()->name();
		auto instancesHandler = pluginPair->second->getInstancesHandler();
		instancesHandler.data()->transitToReadyState();
	}
}
