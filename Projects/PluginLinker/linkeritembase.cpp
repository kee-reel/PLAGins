#include "linkeritembase.h"

LinkerItemBase::LinkerItemBase(IPluginHandlerPtr pluginHandler):
	QObject (nullptr),
	m_uid(pluginHandler.toStrongRef()->getUID()),
	m_pluginHandler(pluginHandler),
	m_references(new QMap< Interface, QList<QWeakPointer<LinkerItemBase>> >),
	m_referents(new QMap< Interface, QList<QWeakPointer<LinkerItemBase>> >)
{
}

LinkerItemBase::~LinkerItemBase()
{

}

IReferenceDescriptorPtr LinkerItemBase::descr()
{
	return m_descriptor;
}

bool LinkerItemBase::load()
{
	if(!m_pluginHandler.toStrongRef()->load())
	{
		auto pluginName = descr().isNull() ? "Unknown" : descr().toStrongRef()->name();
		qCritical() << QString("Can't load plugin [%1]: error: %2.")
		            .arg(pluginName)
		            .arg(m_pluginHandler.toStrongRef()->getLastError());
		return false;
	}

	auto object = m_pluginHandler.toStrongRef()->getInstance();
	auto errMsg = initItem(object);
	if(errMsg.isEmpty())
	{
		emit onLoadedStateChanged(m_uid, true);
//		qDebug() << "Plugin" << descr().toStrongRef()->name() << "loaded";
		return true;
	}
	else
	{
		qWarning() << QString("Caught error on initialization of plugin [%1]: %2").arg(descr().toStrongRef()->name()).arg(errMsg);
		unload();
		return false;
	}
}

bool LinkerItemBase::unload()
{
	if(!isLoaded())
	{
		return true;
	}

	if(isInited())
	{
		auto errMsg = finiItem();
		if(!errMsg.isEmpty())
		{
			qWarning() << QString("Caught error on finalization of plugin [%1]: %2").arg(descr().toStrongRef()->name()).arg(errMsg);
		}
	}

	m_descriptor.clear();

	if(m_pluginHandler.isNull())
	{
		// Plugin was already unloaded.
		return true;
	}

	bool unloadResult = m_pluginHandler.toStrongRef()->unload();
	if(unloadResult)
	{
		// qDebug() << "Plugin" << descr().toStrongRef()->name() << "unloaded";
		emit onLoadedStateChanged(m_uid, false);
	}
	else
	{
		qCritical() << QString("Error raised during unloading of plugin [%1]: error: %2.")
		            .arg(descr().toStrongRef()->name())
		            .arg(m_pluginHandler.toStrongRef()->getLastError());
	}

	return unloadResult;
}

void LinkerItemBase::addReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem)
{
	auto & refs = (*m_references)[interface];
	refs.append(linkItem);
	connect(linkItem.toStrongRef().data(), SIGNAL(onLoadedStateChanged(uid_t, bool)), this, SLOT(onReferenceLoadedStateChanged(uid_t, bool)));
	emit onReferencesChanged(m_uid, linkItem.toStrongRef()->descr().toStrongRef()->uid(), true);
}

void LinkerItemBase::removeReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem)
{
	m_references->find(interface).value().removeOne(linkItem);
	disconnect(linkItem.toStrongRef().data(), SIGNAL(onLoadedStateChanged(uid_t, bool)), this, SLOT(onReferenceLoadedStateChanged(uid_t, bool)));
	emit onReferencesChanged(m_uid, linkItem.toStrongRef()->descr().toStrongRef()->uid(), false);
}

void LinkerItemBase::addReferent(Interface interface, QWeakPointer<LinkerItemBase> linkItem)
{
	auto & refs = (*m_referents)[interface];
	refs.append(linkItem);
	emit onReferentsChanged(m_uid, linkItem.toStrongRef()->descr().toStrongRef()->uid(), true);
}

void LinkerItemBase::removeReferent(Interface interface, QWeakPointer<LinkerItemBase> linkItem)
{
	m_referents->find(interface).value().removeOne(linkItem);
	emit onReferentsChanged(m_uid, linkItem.toStrongRef()->descr().toStrongRef()->uid(), false);
}

bool LinkerItemBase::loadAllConnected()
{
//    for(auto list : *m_references)
//    {
//        for(auto& item : list)
//        {
//            item.toStrongRef()->load();
//        }
//    }
//    for(auto list : *m_referents)
//    {
//        for(auto& item : list)
//        {
//            item.toStrongRef()->load();
//        }
//    }
	return true;
}

void LinkerItemBase::onReferenceLoadedStateChanged(uid_t uid, bool isLoaded)
{

}

bool LinkerItemBase::isInited()
{
	return !m_descriptor.isNull();
}

bool LinkerItemBase::isLoaded()
{
	return m_pluginHandler.isNull() || m_pluginHandler.toStrongRef()->getInstance() != nullptr;
}

QWeakPointer<QMap<Interface, QList<QWeakPointer<LinkerItemBase> > > > LinkerItemBase::referenceItems()
{
	return m_references;
}

QWeakPointer<QMap<Interface, QList<QWeakPointer<LinkerItemBase> > > > LinkerItemBase::referentItems()
{
	return m_referents;
}
