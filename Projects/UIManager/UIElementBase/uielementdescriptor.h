#ifndef UIELEMENTLINK_H
#define UIELEMENTLINK_H

#include "../../Interfaces/iuielement.h"

class UIElementDescriptor : public IUIElementDescriptor
{
public:
    static QSharedPointer<UIElementDescriptor> make(uid_t uid, QWeakPointer<QJsonObject> meta);

private:
    UIElementDescriptor() = default;
public:
    virtual ~UIElementDescriptor() = default;

    // IReferenceDescriptor interface
public:

    inline virtual uid_t uid() override
    {
        return m_uid;
    }
    inline virtual const QString& displayName() override
    {
        return m_displayName;
    }
    inline virtual const QString& linkKey() override
    {
        return m_linkName;
    }
    virtual const QString &about() override
    {
        return m_about;
    }
    QWeakPointer<QMap<QString, count_t>> links()
    {
        return m_references;
    }

private:
    uid_t m_uid;
    QString m_displayName;
    QString m_linkName;
    QString m_about;
    QSharedPointer<QMap<QString, count_t>> m_references;
};

#endif // UIELEMENTLINK_H
