#pragma once

#include <QtCore>

class IUserTasksCalendar
{
public slots:
	virtual QObject* getTasksForDay(QDate day) = 0;
};
Q_DECLARE_INTERFACE(IUserTasksCalendar, "IUserTasksCalendar/1.0")
