#pragma once

#include <QObject>

#include "../ireferenceinstance.h"
#include "../../Interfaces/Architecture/iuielement.h"


class MethodsHandler : public IMethodsHandler
{
public:
	MethodsHandler(QObject* object)
	{
		Q_UNUSED(object)
//		auto metaObject = object->metaObject();
//		auto methodOffset = metaObject->methodOffset();
//		auto methodCount = metaObject->methodCount();
//		for(int i = methodOffset; i < methodCount; ++i)
//		{
//			qDebug() << metaObject->method(i).name();
//		}
	}
	virtual ~MethodsHandler()
	{

	}

public:
	virtual QList<QMetaMethod> getSignals() override
	{
		return QList<QMetaMethod>();
	}
	virtual QList<QMetaMethod> getSlots() override
	{
		return QList<QMetaMethod>();
	}
private:
//	QList<QMetaMethod>
};

#pragma once
