#pragma once

#include <QtCore>
#include <QImage>

#include "../Utility/i_user_task_data_ext.h"

#define IUserTaskNotesDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString notes READ notes)

class IUserTaskNotesDataExtention : public IUserTaskDataExtention
{
public:
	IUserTaskNotesDataExtention_EXTENTION_PROPERTY
	virtual QString notes() = 0;
};
Q_DECLARE_INTERFACE(IUserTaskNotesDataExtention, "IUserTaskNotesDataExtention/1.0")
