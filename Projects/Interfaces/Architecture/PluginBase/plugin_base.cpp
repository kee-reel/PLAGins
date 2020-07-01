#include "plugin_base.h"

PluginBase::PluginBase(QObject *object) :
	m_object(object)
{
}

void PluginBase::initPluginBase(QMap<Interface, QObject *> interfaces,
        const QMap<Interface, IReferenceInstancePtr> &instances,
        const QMap<Interface, IReferenceInstancesListPtr> &instancesList)
{
	auto pluginInterface = INTERFACE(IPlugin);
	if(!interfaces.contains(pluginInterface))
	{
		interfaces.insert(pluginInterface, m_object);
	}
	m_interfaces = interfaces;
	m_instancesHandler.reset(new PluginReferencesHandler(instances, instancesList));
	m_pluginBaseSignal.reset(new PluginBaseSignal(this, m_instancesHandler));
}

bool PluginBase::pluginInit(quint32 uid, const QWeakPointer<QJsonObject> &meta)
{
	assert(m_descr.isNull());
	m_descr.reset(PluginDescriptor::make(uid, m_object, meta, m_interfaces, m_instancesHandler));
	if(m_descr.isNull())
	{
		qDebug() << "PluginBase::pluginInit: can't initialize plugin" << m_object->objectName();
	}
	else
	{
		onInited();
	}
	return !m_descr.isNull();
}

bool PluginBase::isInited()
{
	return !m_descr.isNull();
}

QObject *PluginBase::getInstance(Interface interface)
{
	return m_interfaces[interface];
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
		onReferencesSet();
		break;
	case ReferencesHandlerState::READY:
		onReady();
		break;
	}
}

PluginBaseSignal::PluginBaseSignal(PluginBase* instance, QWeakPointer<PluginReferencesHandler> handler) :
	m_instance(instance),
	m_handler(std::move(handler))
{
	connect(m_handler.toStrongRef().data(), &PluginReferencesHandler::onStateChanged, this, &PluginBaseSignal::onStateChanged);
	connect(m_handler.toStrongRef().data(), &PluginReferencesHandler::onReferencesListUpdated, this, &PluginBaseSignal::onReferencesListUpdated);
}

void PluginBaseSignal::onStateChanged(ReferencesHandlerState state)
{
	m_instance->onStateChanged(state);
}

void PluginBaseSignal::onReferencesListUpdated(const Interface &interface)
{
	m_instance->onReferencesListUpdated(interface);
}
