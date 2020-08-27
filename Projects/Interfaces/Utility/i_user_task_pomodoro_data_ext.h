#pragma once

#include <QtCore>

#include "i_user_task_data_ext.h"

#define IUserTaskPomodoroDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(int pomodorosFinished READ pomodorosFinished)

class IUserTaskPomodoroDataExtention : public IUserTaskDataExtention
{
	IUserTaskPomodoroDataExtention_EXTENTION_PROPERTY
	virtual int pomodorosFinished() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskPomodoroDataExtention, "IUserTaskPomodoroDataExtention/1.0")

