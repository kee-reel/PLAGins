#pragma once

#include <QtGlobal>
#include <QObject>

#include "../../Interfaces/Architecture/interface.h"

typedef QMap<Interface, QMap<QString, QVariant>> ExtendableItemDataMap;

class IExtendableDataModelBase
{
public:
	Q_PROPERTY(QVariantMap header READ getVariantHeader NOTIFY headerChanged)

	virtual ExtendableItemDataMap getHeader() = 0;
	virtual const ExtendableItemDataMap& getDefaultItem() = 0;
	virtual int getItemId(const QModelIndex &index) = 0;
	virtual const ExtendableItemDataMap& getItem(const QModelIndex &itemIndex) = 0;
	virtual const ExtendableItemDataMap& getItem(int itemId) = 0;
	virtual QList<int> getItemIds() = 0;

public slots:
	virtual QVariantMap getVariantDefaultItem() = 0;
	virtual QVariantMap getVariantItem(int itemId) = 0;
	virtual QModelIndex getItemIndex(int itemId) = 0;
	virtual int appendItem(const QMap<Interface, QVariantMap>& itemValues) = 0;
	virtual int addItem(const QMap<Interface, QVariantMap>& itemValues, int row, QModelIndex parentIndex) = 0;
	virtual int addVariantItem(const QVariantMap& itemValues, int row, int parentId) = 0;
	virtual bool updateItem(int itemId, const ExtendableItemDataMap& itemValues) = 0;
	virtual bool updateVariantItem(int itemId, const QVariantMap& itemValues) = 0;
	virtual bool updateItem(const QModelIndex &itemIndex, const ExtendableItemDataMap& itemValues) = 0;
	virtual bool removeItem(int itemId) = 0;
	virtual bool removeItem(const QModelIndex &itemIndex) = 0;

signals:
	virtual void headerChanged() = 0;
	virtual void itemAdded(int itemId) = 0;
	virtual void itemUpdated(int itemId, const ExtendableItemDataMap& before, const ExtendableItemDataMap& after) = 0;
	virtual void itemRemoved() = 0;
	virtual void modelChanged() = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataModelBase, "IExtendableDataModelBase/1.0")


class IExtendableDataModelFilter : public QSortFilterProxyModel, public IExtendableDataModelBase
{
	Q_PROPERTY(int parentId READ parentId NOTIFY parentIdChanged)
public:
	virtual void setColumns(QMap<Interface, QStringList> filteredColumns) = 0;
	virtual void setTreeParent(QModelIndex parentIndex) = 0;
	virtual void setTreeParent(int parentRow) = 0;
	virtual int parentId() const = 0;
signals:
	virtual void parentIdChanged(int parentId) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataModelFilter, "IExtendableDataModelFilter/1.0")


class IExtendableDataModel : public QAbstractItemModel, public IExtendableDataModelBase
{
public:
	virtual QPointer<IExtendableDataModelFilter> getFilter() = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataModel, "IExtendableDataModel/1.0")
