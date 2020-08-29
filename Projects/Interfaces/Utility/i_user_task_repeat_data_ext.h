#pragma once

#include <QtCore>

#include "i_user_task_data_ext.h"

#define IUserTaskRepeatDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(int repeatType READ repeatType) \
	Q_PROPERTY(bool isSpawnedNewTask READ isSpawnedNewTask)

enum RepeatType
{
	NONE,
	DAILY,
	WEEKLY,
	MONTHLY,
	YEARLY
};

class IUserTaskRepeatDataExtention : public IUserTaskDataExtention
{
public:
	IUserTaskRepeatDataExtention_EXTENTION_PROPERTY
	virtual int repeatType() = 0;
	virtual bool isSpawnedNewTask() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskRepeatDataExtention, "IUserTaskRepeatDataExtention/1.0")
