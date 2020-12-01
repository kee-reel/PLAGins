#pragma once

#include <QtCore>

#include "../../Interfaces/Middleware/iextendabledatamodel.h"

class IPomodoroManager
{
public:
	enum class TimerStatus : quint8
	{
		PAUSE,
		WORK,
		REST
	};

	virtual QPointer<IExtendableDataModel> GetTaskModel() = 0;
	virtual QPointer<IExtendableDataModelFilter> GetTaskModelFilter() = 0;
	virtual void SetActiveProject(QModelIndex) = 0;
	virtual QModelIndex GetActiveProject() = 0;
	virtual QPair<QString, quint16> getActiveProjectPomodoros() = 0;

	virtual QVariantMap getSettings() = 0;
	virtual void setSetting(QString setting, QVariant value) = 0;
	
	virtual TimerStatus getStatus() = 0;
public slots:
	virtual void changeStatus(TimerStatus status) = 0;
signals:
	void onStatusChanged(TimerStatus newStatus, QTime newTime);
	void onTimerTick(QTime timeLeft);
};
Q_DECLARE_INTERFACE(IPomodoroManager, "IPomodoroManager/1.0")

