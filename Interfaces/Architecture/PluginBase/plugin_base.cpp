#include "plugin_base.h"

#include <QWidget>

PluginBase::PluginBase(QObject *object, QVector<Interface> interfaces) :
    m_object(object),
    m_interfaces(interfaces)
{
}

bool PluginBase::pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta)
{
    m_descr = PluginDescriptor::make(uid, m_object, meta, m_interfaces, m_instancesHandler);
    if(m_descr.isNull())
    {
        return false;
    }

    return true;
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

void PluginBase::referencesInit(QMap<Interface, QList<IReferenceInstancePtr> > instances, QMap<Interface, IReferenceInstancesListPtr> instancesList)
{
    m_instancesHandler.reset(new ReferenceInstancesHandler(instances, instancesList));
}
