#include "plugin_base.h"

#include <QWidget>

PluginBase::PluginBase(QObject *object, QVector<Interface> interfaces,
                       QMap<Interface, QList<QSharedPointer<IReferenceInstance> > > instances,
                       QMap<Interface, QSharedPointer<IReferenceInstancesVariableList> > instancesList) :
    m_object(object),
    m_interfaces(interfaces),
    m_instances(instances),
    m_instancesList(instancesList)
{
    for(auto &interface : m_instances.keys())
        m_instancesInterfaces.append(interface);
    for(auto &interface : m_instancesList.keys())
        m_instancesInterfaces.append(interface);
}

bool PluginBase::pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta)
{
    m_descr = PluginDescriptor::make(uid, m_object, meta, m_interfaces, m_instancesInterfaces);
    if(m_descr.isNull())
    {
        return false;
    }

    m_isInited = true;
    return true;
}

QWeakPointer<IReferenceDescriptor> PluginBase::getDescriptor()
{
    return m_descr;
}

QWeakPointer<IReferenceInstancesHandler> PluginBase::getInstancesHandler()
{

}

bool PluginBase::pluginFini()
{
    m_descr.reset();
    m_instances.clear();
    m_instancesList.clear();

    m_isInited = false;
    m_isAllReferencesSet = false;
    m_isAllReferencesReady = false;

    return true;
}

//bool PluginBase::setReferences(Interface interface, QList<QWeakPointer<IReferenceDescriptor> > references)
//{
//    auto referenceIter = m_references.find(interface);
//    assert(referenceIter != m_references.end() && m_references.count() == references.count());

//    auto referencesByInterface = m_referencesMapByInterfaces.find(interface);
//    for(auto& reference : references)
//    {
//        auto referenceUID = reference.data()->uid();
//        referencesByInterface.value().append(reference);
//        m_referencesMap[referenceUID] = reference;
//    }

//    checkAllReferencesSet();
//    return true;
//}

//bool PluginBase::removeReferences(Interface interface)
//{
//    auto referenceIter = m_references.find(interface);
//    assert(referenceIter != m_references.end());

//    auto referencesByInterface = m_referencesMapByInterfaces.find(interface);
//    for(auto& descr : referencesByInterface.value())
//    {
//        auto uid = descr.data()->uid();
//        m_referencesMap.remove(uid);
//    }
//    m_referencesMapByInterfaces.remove(interface);

//    m_isAllReferencesSet = false;
//    m_isAllReferencesReady = false;
//    return true;
//}

QString PluginBase::getLastError() const
{
    return m_lastErrorString;
}

//void PluginBase::onReferenceReadyStateChanged(uid_t referenceUID, bool readyState)
//{
//    Q_UNUSED(readyState)
//    auto referenceIter = m_referencesMap.find(referenceUID);
//    if(referenceIter == m_referencesMap.end())
//    {
//        raiseError(QString("PluginBase::onReferenceReady: reference %1 not found in needed references")
//                   .arg(referenceUID));
//        return;
//    }
//    else
//    {
//        checkAllReferencesReady();
//    }
//}

//void PluginBase::log(SeverityType severityType, QString msg) const
//{
//    if(severityType < m_logSeverityType)
//    {
//        return;
//    }
//    auto&& descr = m_selfDescriptor->name();
//    auto&& msgTemplate = QString("[%1] (%2): %3");
//    switch (severityType)
//    {
//    case SeverityType::INFO:
//        qInfo() << msgTemplate.arg("INFO").arg(descr).arg(msg);
//        return;
//    case SeverityType::DEBUG:
//        qDebug() << msgTemplate.arg("DEBUG").arg(descr).arg(msg);
//        return;
//    case SeverityType::WARNING:
//        qWarning() << msgTemplate.arg("WARNING").arg(descr).arg(msg);
//        return;
//    case SeverityType::CRITICAL:
//        qCritical() << msgTemplate.arg("CRITICAL").arg(descr).arg(msg);
//        return;
//    case SeverityType::FATAL:
//        qCritical() << msgTemplate.arg("FATAL").arg(descr).arg(msg);
//        return;
//    }
//}

void PluginBase::raiseError(QString errorMessage)
{
    m_lastErrorString = errorMessage;
//    qCritical() << QString("[interface: %1, plugin: %2] Error raised: %3\n")
//                .arg(m_metaInfo.data()->Name).arg(m_metaInfo.data()->InterfaceName).arg(m_lastErrorString);
}

//void PluginBase::checkAllReferencesSet()
//{
//    bool isAllReferencesSet = true;
//    for (auto iter = m_references.begin(); iter != m_references.end(); ++iter)
//    {
//        auto count = m_references[iter.key()];
//        if(count != 0 && m_referencesMapByInterfaces[iter.key()].count() != count)
//        {
//            isAllReferencesSet = false;
//            break;
//        }
//    }

//    onAllReferencesSet(isAllReferencesSet);
//}

//void PluginBase::checkAllReferencesReady()
//{
//    bool isAllReferencesReady = true;
//    for (const auto &reference : m_referencesMap)
//    {
//        if(true/*!reference.data()->instance()->isReady()*/)
//        {
//            isAllReferencesReady = false;
//            break;
//        }
//    }

//    onAllReferencesReady(isAllReferencesReady);
//}

//void PluginBase::onAllReferencesSet(bool state)
//{
//    if(m_isAllReferencesSet == state)
//    {
//        return;
//    }

//    qDebug() << "onAllReferencesSet" << m_selfDescriptor->name();
//    m_isAllReferencesSet = state;
//    checkAllReferencesReady();
//    emit onReadyStateChanged(m_selfDescriptor->uid(), state);
//}

//void PluginBase::onAllReferencesReady(bool state)
//{
//    if(!m_isAllReferencesSet || m_isAllReferencesReady == state)
//    {
//        return;
//    }

//    qDebug() << "onAllReferencesReady" << m_selfDescriptor->name();
//    m_isAllReferencesReady = state;

//    for(auto iter = m_referenceInstances.begin(); iter != m_referenceInstances.end(); ++iter)
//    {
//        auto instances = iter.value();
//        auto descriptors = m_referencesMapByInterfaces[iter.key()];
//        assert(instances.size() != 0 and instances.size() == descriptors.size());
//        for(int i = 0; i < instances.size(); ++i)
//        {
//            instances[i]->reset(descriptors[i]);
//        }
//    }
//}
