#pragma once

#include <QtCore>

#include "i_user_task_data_ext.h"

#define IUserTaskDateDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QDateTime date READ date)

class IUserTaskDateDataExtention : public IUserTaskDataExtention
{
public:
	IUserTaskDateDataExtention_EXTENTION_PROPERTY
	virtual QDateTime date() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskDateDataExtention, "IUserTaskDateDataExtention/1.0")
