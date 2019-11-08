#include "plugin_base.h"

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

void PluginBase::referencesInit(QMap<Interface, IReferenceInstancePtr> instances, QMap<Interface, IReferenceInstancesListPtr> instancesList)
{
	m_instancesHandler.reset(new ReferencesHandler(instances, instancesList));
	m_pluginBaseSignal.reset(new PluginBaseSignal(this, m_instancesHandler));
}

bool PluginBase::pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta)
{
	assert(m_descr.isNull());
	m_descr.reset(PluginDescriptor::make(uid, m_object, meta, m_interfaces, m_instancesHandler));
	if(m_descr.isNull())
	{
		qDebug() << "PluginBase::pluginInit: can't initialize plugin" << m_object->objectName();
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

QWeakPointer<IPluginReferencesHandler> PluginBase::getInstancesHandler()
{
	return m_instancesHandler;
}

bool PluginBase::pluginFini()
{
	m_descr.reset();
	return true;
}

void PluginBase::onStateChanged(IPluginReferencesHandler::State state)
{
	switch (state)
	{
	case IPluginReferencesHandler::State::SETTING_REFS:
		break;
	case IPluginReferencesHandler::State::WAITING:
		onReferencesSet();
		break;
	case IPluginReferencesHandler::State::READY:
		onReady();
		break;
	}
}

PluginBaseSignal::PluginBaseSignal(PluginBase *instance, QWeakPointer<ReferencesHandler> handler) :
	QObject(), m_instance(instance), m_handler(handler)
{
	connect(m_handler.data(), &ReferencesHandler::onStateChanged, this, &PluginBaseSignal::onStateChanged);
}

void PluginBaseSignal::onStateChanged(IPluginReferencesHandler::State state)
{
	m_instance->onStateChanged(state);
}
