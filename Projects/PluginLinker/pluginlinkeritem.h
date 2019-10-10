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

#include "PluginBase/iplugin.h"


class PluginLinkerItem : public LinkerItemBase
{
    Q_OBJECT
public:
    PluginLinkerItem(QWeakPointer<IPluginHandler> pluginHandler);
    virtual ~PluginLinkerItem() override;

    // ILinkerItem interface
public:
    virtual const references_map_t& references() override;

protected:
    virtual QString initItem(QObject *object) override;
    virtual QString finiItem() override;

public:
    static bool isPlugin(QWeakPointer<IPluginHandler> pluginHandler);

private:
    ReferenceInstance<IPlugin> m_pluginInstance;
};

#endif // PLUGINLINKERITEM_H
