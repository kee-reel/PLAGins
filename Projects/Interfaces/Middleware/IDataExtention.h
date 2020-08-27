#pragma once

#include <QtGlobal>
#include <QVariant>

#include "../../Interfaces/Architecture/interface.h"
#include "iextendabledatamodel.h"

class IDataExtention
{
	Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
public:
	virtual QObject* model() = 0;
signals:
	virtual void modelChanged() = 0;

public:
	virtual QPointer<IExtendableDataModel> getModel() = 0;
	virtual void setModel(QPointer<IExtendableDataModel> model) = 0;
	virtual QVector<QString> getDataFields() = 0;
	virtual Interface getExtentionInterface() = 0;
	virtual Interface getExtendableInterface() = 0;
};
Q_DECLARE_INTERFACE(IDataExtention, "IDataExtention/1.0")
