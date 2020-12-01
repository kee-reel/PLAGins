#pragma once

#include <QtCore>

class IHabitsTracker
{
	Q_PROPERTY(QDate currentDate READ currentDate NOTIFY currentDateChanged)
	Q_PROPERTY(QList<QObject*> habits READ habits NOTIFY habitsChanged)
	Q_PROPERTY(int totalStreak READ totalStreak NOTIFY totalStreakChanged)

public slots:
	virtual QDate currentDate() = 0;
	virtual int totalStreak() = 0;
	virtual QList<QObject*> habits() = 0;
	virtual void addHabit(QString name) = 0;

signals:
	virtual void currentDateChanged() = 0;
	virtual void habitsChanged() = 0;
};
Q_DECLARE_INTERFACE(IHabitsTracker, "IHabitsTracker/1.0")
