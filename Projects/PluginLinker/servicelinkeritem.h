#ifndef SERVICELINKERITEM_H
#define SERVICELINKERITEM_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QMap>
#include <QHash>

#include "linkeritembase.h"

#include "../../Interfaces//icoreservice.h"


class ServiceLinkerItem : public LinkerItemBase
{
    Q_OBJECT
public:
    ServiceLinkerItem(IPluginHandlerPtr pluginHandler);
    virtual ~ServiceLinkerItem() override;

    // ILinkerItem interface
public:
    virtual const references_map_t& references() override;

public:
    static bool isService(IPluginHandlerPtr pluginHandler);

protected:
    virtual QString initItem(QObject* object) override;
    virtual QString finiItem() override;

private:
    QString m_descriptionName;
    QSharedPointer<QStringList> m_linkKeys;
    ReferenceInstance<Service::ICoreService> m_serviceInstance;
public:
};

#endif // SERVICELINKERITEM_H
