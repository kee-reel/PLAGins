#pragma once

#include <QtCore>

#include "i_user_task_data_ext.h"

#define IUserTaskProjectDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(bool isProject READ isProject)

class IUserTaskProjectDataExtention : public IUserTaskDataExtention
{
public:
	IUserTaskProjectDataExtention_EXTENTION_PROPERTY
	virtual bool isProject() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskProjectDataExtention, "IUserTaskProjectDataExtention/1.0")
