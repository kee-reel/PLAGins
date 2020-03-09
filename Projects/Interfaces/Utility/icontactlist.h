#pragma once

#include <QtCore>

class IContactList
{
public:
	Q_PROPERTY(QAbstractItemModel* model READ model NOTIFY modelChanged)

	Q_INVOKABLE virtual QAbstractItemModel* model() = 0;
	Q_INVOKABLE virtual QPointer<QAbstractItemModel> getModel() = 0;
signals:
	virtual void modelChanged() = 0;
};
Q_DECLARE_INTERFACE(IContactList, "IContactList/1.0")
