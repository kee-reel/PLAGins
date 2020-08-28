#pragma once

#include <QtGlobal>

#include "../../Interfaces/Architecture/interface.h"


class IExtendableDataModel : public QAbstractItemModel
{
public:
	Q_PROPERTY(QVariantMap header READ getVariantHeader NOTIFY headerChanged)

	virtual const QMap<Interface, QMap<QString, QVariant>>& getHeader() = 0;
	virtual QPointer<QSortFilterProxyModel> getFilter(QMap<Interface, QStringList> filteredColumns) = 0;
	Q_INVOKABLE virtual QVariantMap getVariantHeader() = 0;

	virtual const QMap<Interface, QMap<QString, QVariant>>& getItem(const QModelIndex &itemIndex) = 0;
	virtual const QMap<Interface, QMap<QString, QVariant>>& getItem(int itemId) = 0;

	virtual int addItem(QMap<Interface, QVariantMap> itemValues, int row, QModelIndex parentIndex=QModelIndex()) = 0;
	Q_INVOKABLE virtual int addVariantItem(QVariantMap itemValues) = 0;
	
	virtual bool updateItem(const QModelIndex &itemIndex, QMap<Interface, QMap<QString, QVariant>> itemValues) = 0;

	Q_INVOKABLE virtual bool removeItem(int itemId) = 0;
	Q_INVOKABLE virtual bool removeItem(const QModelIndex &itemIndex) = 0;
	
	virtual QList<int> getItemIds() = 0;

signals:
	virtual void headerChanged() = 0;
	virtual void itemAdded(int itemId) = 0;
	virtual void itemRemoved() = 0;
	virtual void modelChanged() = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataModel, "IExtendableDataModel/1.0")
