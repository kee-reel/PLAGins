#include "pluginlinkeritem.h"

const QMap<QString, QStringList> META_INFO_STRUCTURE =
{
	{"interfaces", {}},
	{"references", {}},
	{"info", {"name", "about"}},
};

PluginLinkerItem::PluginLinkerItem(IPluginHandlerPtr pluginHandler) :
	LinkerItemBase (pluginHandler)
{
	connect(this, &LinkerItemBase::onReferencesChanged, this, &PluginLinkerItem::connectionsChanged);
}

PluginLinkerItem::~PluginLinkerItem()
{

}

const QMap<Interface, int> &PluginLinkerItem::references()
{
	return m_pluginInstance->instance()->getInstancesHandler().toStrongRef()->requiredReferences();
}

void PluginLinkerItem::addReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem)
{
	LinkerItemBase::addReference(interface, linkItem);
	setupReferences();
}

void PluginLinkerItem::removeReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem)
{
	LinkerItemBase::removeReference(interface, linkItem);
	setupReferences();
}

bool PluginLinkerItem::isPlugin(IPluginHandlerPtr pluginHandler)
{
	auto metaInfoObject = pluginHandler.toStrongRef()->getMeta();
	QJsonObject metaInfo = metaInfoObject.toStrongRef()->value("MetaData").toObject();
	metaInfo = metaInfo.value("iplugin").toObject();
	for(auto iter = META_INFO_STRUCTURE.begin(); iter != META_INFO_STRUCTURE.end(); ++iter)
	{
		if(!metaInfo.contains(iter.key()))
		{
			qDebug() << QString("PluginBase::parseMetaInfo: meta has no field '%1' but has fields:").arg(iter.key());
			for(auto allFieldsIter = metaInfo.begin(); allFieldsIter != metaInfo.end(); ++allFieldsIter)
			{
				qDebug() << QString("%1: %2").arg(allFieldsIter.key()).arg(allFieldsIter.value().toString());
			}
			return false;
		}
	}
	return true;
}

QString PluginLinkerItem::initItem(QObject* object)
{
	auto instance = qobject_cast<IPlugin *>(object);

	if(!instance)
	{
		return QString("can't cast plugin to IPlugin interface.");
	}

	if(!instance->isInited() && !instance->pluginInit(m_uid, m_pluginHandler.toStrongRef()->getMeta()))
	{
		instance->pluginFini();
		return "Can't load";
	}

	m_descriptor = instance->getDescriptor();

	if(m_descriptor.isNull())
	{
//        return QString("internal plugin error: %1").arg(instance->getLastError());
		return QString("internal plugin error");
	}
	else
	{
		m_pluginInstance->setInstance(m_descriptor);
		setupReferences();
		return QString();
	}
}

void PluginLinkerItem::setupReferences()
{
	const auto &handler = m_pluginInstance->instance()->getInstancesHandler();
	for(auto iter = m_references->begin(); iter != m_references->end(); ++iter)
	{
		QList<IReferenceDescriptorPtr> refs;
		for (auto refIter = iter.value().begin(); refIter != iter.value().end(); ++refIter)
		{
			refs.append(refIter->data()->descr());
		}
		handler.toStrongRef()->setReferences(iter.key(), refs);
	}
}

QString PluginLinkerItem::finiItem()
{
	m_pluginInstance->instance()->pluginFini();
	m_pluginInstance.reset();
	return QString();
}

void PluginLinkerItem::connectionsChanged(quint32 selfUID, quint32 itemUID, bool isAdded)
{
	if(m_pluginInstance->isSet())
	{
		setupReferences();
	}
}
