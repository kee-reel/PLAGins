#include "plugin_base.h"

#include <QWidget>

PluginBase::PluginBase(QObject *object, QVector<Interface> interfaces) :
	m_object(object),
	m_interfaces(interfaces)
{
}

void PluginBase::referencesInit(QMap<Interface, QList<IReferenceInstancePtr> > instances, QMap<Interface, IReferenceInstancesListPtr> instancesList)
{
	m_instancesHandler.reset(new ReferenceInstancesHandler(instances, instancesList));
	m_pluginBaseSignal.reset(new PluginBaseSignal(this, m_instancesHandler));
}

bool PluginBase::pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta)
{
	m_descr = PluginDescriptor::make(uid, m_object, meta, m_interfaces, m_instancesHandler);
	return !m_descr.isNull();
}

IReferenceDescriptorPtr PluginBase::getDescriptor()
{
	return m_descr;
}

QWeakPointer<IReferenceInstancesHandler> PluginBase::getInstancesHandler()
{
	return m_instancesHandler;
}

bool PluginBase::pluginFini()
{
	m_descr.reset();
	return true;
}

void PluginBase::onStateChanged(IReferenceInstancesHandler::State state)
{
	switch (state)
	{
	case IReferenceInstancesHandler::State::SETTING_REFS:
		onReadyStateChanged(false);
		break;
	case IReferenceInstancesHandler::State::READY:
		onReadyStateChanged(true);
		break;
	}
}

PluginBaseSignal::PluginBaseSignal(PluginBase *instance, QWeakPointer<ReferenceInstancesHandler> handler) :
	QObject(), m_instance(instance), m_handler(handler)
{
	connect(m_handler.data(), &ReferenceInstancesHandler::onStateChanged, this, &PluginBaseSignal::onStateChanged);
}

void PluginBaseSignal::onStateChanged(IReferenceInstancesHandler::State state)
{
	m_instance->onStateChanged(state);
}
