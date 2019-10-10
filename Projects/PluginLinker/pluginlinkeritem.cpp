#include "pluginlinkeritem.h"

const QMap<QString, QStringList> META_INFO_STRUCTURE = {
    {"interface", {}},
    {"references", {}},
    {"info", {"name", "about"}},
};

PluginLinkerItem::PluginLinkerItem(QWeakPointer<IPluginHandler> pluginHandler) :
    LinkerItemBase (pluginHandler)
{
    if(pluginHandler.data()->getInstance() == nullptr)
    {
        load();
    }
}

PluginLinkerItem::~PluginLinkerItem()
{

}

const references_map_t& PluginLinkerItem::references()
{
    return m_pluginInstance->getRefereneces();
}

bool PluginLinkerItem::isPlugin(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto metaInfoObject = pluginHandler.data()->getMeta();
    QJsonObject metaInfo = metaInfoObject.data()->value("MetaData").toObject();
    metaInfo = metaInfo.value("iplugin").toObject();
    for(auto iter = META_INFO_STRUCTURE.begin(); iter != META_INFO_STRUCTURE.end(); ++iter)
    {
        if(!metaInfo.contains(iter.key()))
        {
//            log(SeverityType::WARNING, QString("PluginBase::parseMetaInfo: meta has no field '%1' but has fields:").arg(metaFieldName));
            for(auto iter = metaInfo.begin(); iter != metaInfo.end(); ++iter)
            {
//                log(SeverityType::WARNING, QString("%1: %2").arg(iter.key()).arg(iter.value().toString()));
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

    m_descriptor = instance->pluginInit(m_uid, m_pluginHandler.data()->getMeta());

    if(m_descriptor.isNull())
    {
        return QString("internal plugin error: %1").arg(instance->getLastError());
    }
    else
    {
        m_pluginInstance.reset(m_descriptor);
        for(auto iter = m_references->begin(); iter != m_references->end(); ++iter)
        {
            QList<IReferenceDescriptorPtr> refs;
            for (auto refIter = iter.value().begin(); refIter != iter.value().end(); ++refIter)
            {
                refs.append(refIter->data()->descr());
            }
            m_pluginInstance->setReferences(iter.key(), refs);
        }
        return QString();
    }
}

QString PluginLinkerItem::finiItem()
{
    for(auto iter = m_references->begin(); iter != m_references->end(); ++iter)
    {
        m_pluginInstance->removeReferences(iter.key());
    }

    m_pluginInstance.reset();
    return QString();
}
