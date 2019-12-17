#include "plugin_base.h"

#include <utility>

#include <utility>

PluginBase::PluginBase(QObject *object, QVector<Interface> interfaces) :
	m_object(object)
{
	auto interface = INTERFACE(IPlugin);
	if(!interfaces.contains(interface))
	{
		interfaces.append(interface);
	}
	m_interfaces = interfaces;
}

void PluginBase::initPluginBase(const QMap<Interface, IReferenceInstancePtr> &instances, const QMap<Interface, IReferenceInstancesListPtr> &instancesList)
{
	m_instancesHandler.reset(new PluginReferencesHandler(instances, instancesList));
	m_pluginBaseSignal.reset(new PluginBaseSignal(this, m_instancesHandler));
}

bool PluginBase::pluginInit(uid_t uid, const QWeakPointer<QJsonObject> &meta)
{
	assert(m_descr.isNull());
	m_descr.reset(PluginDescriptor::make(uid, m_object, meta, m_interfaces, m_instancesHandler));
	if(m_descr.isNull())
	{
		qDebug() << "PluginBase::pluginInit: can't initialize plugin" << m_object->objectName();
	}
	else
	{
		onPluginInited();
	}
	return !m_descr.isNull();
}

bool PluginBase::isInited()
{
	return !m_descr.isNull();
}

IReferenceDescriptorPtr PluginBase::getDescriptor()
{
	return m_descr;
}

QWeakPointer<IReferencesHandler<Interface> > PluginBase::getInstancesHandler()
{
	return m_instancesHandler;
}

bool PluginBase::pluginFini()
{
	m_descr.reset();
	return true;
}

IReferenceDescriptorPtr PluginBase::descr()
{
	return getDescriptor();
}

void PluginBase::onStateChanged(ReferencesHandlerState state)
{
	switch (state)
	{
	case ReferencesHandlerState::SETTING_REFS:
		break;
	case ReferencesHandlerState::WAITING:
		onPluginReferencesSet();
		break;
	case ReferencesHandlerState::READY:
		onPluginReady();
		break;
	}
}

void PluginBase::onReferencesListUpdated(const Interface &interface)
{
	onPluginReferencesListUpdated(interface);
}

PluginBaseSignal::PluginBaseSignal(PluginBase* instance, QWeakPointer<PluginReferencesHandler> handler) :
	m_instance(instance),
	m_handler(std::move(handler))
{
	connect(m_handler.data(), &PluginReferencesHandler::onStateChanged, this, &PluginBaseSignal::onStateChanged);
	connect(m_handler.data(), &PluginReferencesHandler::onReferencesListUpdated, this, &PluginBaseSignal::onReferencesListUpdated);
}

void PluginBaseSignal::onStateChanged(ReferencesHandlerState state)
{
	m_instance->onStateChanged(state);
}

void PluginBaseSignal::onReferencesListUpdated(const Interface &interface)
{
	m_instance->onReferencesListUpdated(interface);
}
