#pragma once

#include <QtCore>

class IContactList
{
public:
	virtual QWeakPointer<QAbstractTableModel> getModel() = 0;
};
Q_DECLARE_INTERFACE(IContactList, "IContactList/1.0")
