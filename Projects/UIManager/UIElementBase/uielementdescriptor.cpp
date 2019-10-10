#include "uielementdescriptor.h"

QSharedPointer<UIElementDescriptor> UIElementDescriptor::make(uid_t uid, QWeakPointer<QJsonObject> meta)
{
    auto metaData = meta.data()->value("MetaData").toObject();
    auto section = metaData.value("iuielement").toObject();

    auto linkName = section.value("linkName").toString();
    auto displayName = section.value("displayName").toString();
    if(linkName.isEmpty() || linkName.isEmpty())
    {
        return nullptr;
    }

    auto referencesJSONMap = section.value("references").toObject();
    auto&& referencesPtr = QSharedPointer<QMap<QString, count_t>>(new QMap<QString, count_t>());
    for(auto iter = referencesJSONMap.begin(); iter != referencesJSONMap.end(); ++iter)
    {
        auto&& linkName = iter.key();
        auto referencesCount = iter.value().toInt(-1);
        if(linkName.isEmpty() || referencesCount == -1)
        {
            return nullptr;
        }
        else
        {
            referencesPtr->insert(linkName, static_cast<count_t>(referencesCount));
        }
    }

    auto&& ptr = new UIElementDescriptor();
    ptr->m_uid = uid;
    ptr->m_linkName = linkName;
    ptr->m_displayName = displayName;
    ptr->m_references = referencesPtr;
    return QSharedPointer<UIElementDescriptor>(ptr);
}
