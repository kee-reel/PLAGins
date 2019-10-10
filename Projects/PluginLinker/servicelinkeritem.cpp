#include "servicelinkeritem.h"

ServiceLinkerItem::ServiceLinkerItem(QWeakPointer<IPluginHandler> pluginHandler) :
    LinkerItemBase (pluginHandler),
    m_linkKeys(new QStringList)
{
    auto metaInfoObject = pluginHandler.data()->getMeta();
    auto metaInfo = metaInfoObject.data()->value("MetaData").toObject();
    metaInfo = metaInfo.value("service").toObject();
    for(auto item : metaInfo.value("interfaces").toArray())
    {
        m_linkKeys->append(item.toString());
    }
    m_descriptionName = "Service";
    load();
}

ServiceLinkerItem::~ServiceLinkerItem()
{

}

const references_map_t& ServiceLinkerItem::references()
{
    return m_serviceInstance->getRefereneces();
}

bool ServiceLinkerItem::isService(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto metaInfoObject = pluginHandler.data()->getMeta();
    QJsonObject metaInfo = metaInfoObject.data()->value("MetaData").toObject();
    metaInfo = metaInfo.value("service").toObject();
    return !metaInfo.isEmpty() && metaInfo.contains("interfaces");
}

QString ServiceLinkerItem::initItem(QObject *object)
{
    auto instance = qobject_cast<Service::ICoreService *>(object);

    if(!instance)
    {
        return QString("can't cast plugin to IPlugin interface.");
    }
    m_descriptor = instance->serviceInit(m_uid, m_pluginHandler.data()->getMeta());
    m_serviceInstance.reset(m_descriptor);
    if(m_descriptor.isNull())
    {
        return QString("internal plugin error");
    }
    else
    {
        return QString();
    }
}

QString ServiceLinkerItem::finiItem()
{
    m_serviceInstance.reset();
    return QString();
}
