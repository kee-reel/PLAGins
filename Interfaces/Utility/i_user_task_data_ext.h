#pragma once

#include <QtCore>

#include "../Middleware/idataextention.h"

#define IUserTaskDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString name READ name) \
	Q_PROPERTY(bool isDone READ isDone)

class IUserTaskDataExtention : public IDataExtention
{
public:
	IUserTaskDataExtention_EXTENTION_PROPERTY
	virtual QString name() = 0;
	virtual bool isDone() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskDataExtention, "IUserTaskDataExtention/1.0")
