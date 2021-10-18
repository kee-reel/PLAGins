#pragma once

#include <QtCore>

#include "../Middleware/idataextention.h"

#define IHabitsTrackerDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString name READ name) \
	Q_PROPERTY(int streak READ streak) \
	Q_PROPERTY(int containerTaskId READ containerTaskId) \
	Q_PROPERTY(int lastTaskId READ lastTaskId) \
	Q_PROPERTY(QDate lastCompletedDate READ lastCompletedDate)

class IHabitsTrackerDataExtention : public IDataExtention
{
public:
	IHabitsTrackerDataExtention_EXTENTION_PROPERTY
	virtual QString name() = 0;
	virtual int streak() = 0;
	virtual int lastTaskId() = 0;
	virtual int containerTaskId() = 0;
	virtual QDate lastCompletedDate() = 0;
};
Q_DECLARE_INTERFACE(IHabitsTrackerDataExtention, "IHabitsTrackerDataExtention/1.0")
