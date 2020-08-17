#pragma once

#include <QtCore>

#include "../Middleware/IDataExtention.h"

#define IUserTaskDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString name READ name)

class IUserTaskDataExtention : public IDataExtention
{
public:
	IUserTaskDataExtention_EXTENTION_PROPERTY
	virtual QString name() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskDataExtention, "IUserTaskDataExtention/1.0")
