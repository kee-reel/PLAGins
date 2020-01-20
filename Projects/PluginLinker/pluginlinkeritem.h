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
#include "../../Interfaces/Architecture/referenceinstance.h"


class PluginLinkerItem : public LinkerItemBase
{
	Q_OBJECT
public:
	PluginLinkerItem(IPluginHandlerPtr pluginHandler);
	virtual ~PluginLinkerItem() override;

	// ILinkerItem interface
public:
	virtual const QMap<Interface, int>& references() override;
	
	// LinkerItemBase interface
public:
	void addReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem) override;
	void removeReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem) override;

protected:
	virtual QString initItem(QObject *object) override;
	virtual QString finiItem() override;

private slots:
	void connectionsChanged(quint32 selfUID, quint32 itemUID, bool isAdded);

public:
	static bool isPlugin(IPluginHandlerPtr pluginHandler);
	void setupReferences();

private:
	ReferenceInstancePtr<IPlugin> m_pluginInstance;
};

#endif // PLUGINLINKERITEM_H
