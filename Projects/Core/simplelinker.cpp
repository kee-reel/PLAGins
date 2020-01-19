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
	if(pluginHandler.toStrongRef()->load())
	{
		auto&& obj = pluginHandler.toStrongRef()->getInstance();
		auto plugin = qobject_cast<IPlugin*>(obj );
		if(!plugin)
		{
			pluginHandler.toStrongRef()->unload();
			return;
		}

		if(!plugin->pluginInit(pluginHandler.toStrongRef()->getUID(), pluginHandler.toStrongRef()->getMeta()))
		{
			return;
		}

		QSharedPointer<LoadedPluginPair> handler(new LoadedPluginPair(pluginHandler, ReferenceInstancePtr<IPlugin>()));
		auto descr = plugin->getDescriptor();
		if(!handler->second->setInstance(descr))
		{
			return;
		}

		m_plugins.append(handler);
		for(auto& interface : descr.toStrongRef()->interfaces())
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
//        auto&& list = iter.value().toStrongRef();
//        list->removeOne(service);
//        if(list->empty())
//        {
//            m_services.remove(serviceInterface);
//        }
//    }
}

void SimpleLinker::init()
{
	auto&& plugins = m_app.toStrongRef()->getPlugins();
	try 
	{
		qDebug() << "Load";
		for (auto& plugin : plugins)
		{
			addPlugin(plugin);
		}
	}
	catch(QException e)
	{
		qDebug() << "Can't load plugin:" << e.what();
	}
	for(auto& pluginPair : m_plugins)
	{
		auto instancesHandler = pluginPair->second->instance()->getInstancesHandler();
		auto &&requiredReferences = instancesHandler.toStrongRef()->requiredReferences();
//		qDebug() << "Referent" << pluginPair->second.toStrongRef()->descr().toStrongRef()->name() << "require" << requiredReferences;
		for (auto referenceIter = requiredReferences.begin(); referenceIter != requiredReferences.end(); ++referenceIter)
		{
			auto pluginsIter = m_pluginsInterfaces.find(referenceIter.key());
			if(pluginsIter != m_pluginsInterfaces.end())
			{
//				qDebug() << "Reference" << pluginsIter.key().name();
				QList<IReferenceDescriptorPtr> list;
				auto referencesCount = referenceIter.value();
				auto &&pluginsList = pluginsIter.value();
				if(referencesCount == 0)
				{
					for(auto& plugin : pluginsList)
					{
						list.append(plugin.toStrongRef()->second->descr());
					}
				}
				else
				{
					for(auto i = 0; i < referencesCount; ++i)
					{
						list.append(pluginsList[i].toStrongRef()->second->descr());
					}
				}
				if(!instancesHandler.toStrongRef()->setReferences(referenceIter.key(), list))
				{
					qDebug() << "Can't set references for plugin";
				}
			}
		}
	}

	for(auto& pluginPair : m_plugins)
	{
		auto instancesHandler = pluginPair->second->instance()->getInstancesHandler();
		instancesHandler.toStrongRef()->transitToReadyState();
	}
}
