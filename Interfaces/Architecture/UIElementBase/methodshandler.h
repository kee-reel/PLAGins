#ifndef METHODSHANDLER_H
#define METHODSHANDLER_H

#include <QObject>

#include "../ireferenceinstance.h"
#include "../../Interfaces/Architecture/iuielement.h"


class MethodsHandler : public IMethodsHandler
{
public:
	MethodsHandler(QObject* object)
	{
		auto metaObject = object->metaObject();
		auto methodOffset = metaObject->methodOffset();
		auto methodCount = metaObject->methodCount();
		for(int i = methodOffset; i < methodCount; ++i)
		{
			qDebug() << metaObject->method(i).name();
		}
	}
	virtual ~MethodsHandler()
	{

	}

public:
	virtual QList<QMetaMethod> getSignals() override
	{

	}
	virtual QList<QMetaMethod> getSlots() override
	{

	}
private:
//	QList<QMetaMethod>
};

#endif // METHODSHANDLER_H
