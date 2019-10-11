#ifndef PLUGINLINKERITEM_H
#define PLUGINLINKERITEM_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QMap>
#include <QHash>

#include "linkeritembase.h"

#include "../../Interfaces/Architecture/iplugin.h"
#include "../../Interfaces/Architecture/ireferenceinstance.h"
#include "../../Interfaces/Architecture/ireferenceinstanceshandler.h"


class PluginLinkerItem : public LinkerItemBase
{
    Q_OBJECT
public:
    PluginLinkerItem(IPluginHandlerPtr pluginHandler);
    virtual ~PluginLinkerItem() override;

    // ILinkerItem interface
public:
    virtual const QMap<Interface, int>& references() override;

protected:
    virtual QString initItem(QObject *object) override;
    virtual QString finiItem() override;

public:
    static bool isPlugin(IPluginHandlerPtr pluginHandler);

private:
    ReferenceInstance<IPlugin> m_pluginInstance;
};

#endif // PLUGINLINKERITEM_H
