#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>
#include <QTimer>
#include <QVariant>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "../../Interfaces/Utility/ipomodoromanager.h"
#include "../../Interfaces/Middleware/iextendabledatamanager.h"
#include "../../Interfaces/Utility/iusertaskmanager.h"
#include "../../Interfaces/Middleware/inotificationmanager.h"

//! \addtogroup PomodoroManager_int
//! \{
class PomodoroManager : public QObject, public PluginBase, public IPomodoroManager
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin IPomodoroManager)

public:
	PomodoroManager();
	virtual ~PomodoroManager() override;

	// PluginBase interface
public:
	virtual void onPluginReferencesSet() override;
	virtual void onPluginReady() override;

private slots:
	void OnTimerEnded(int timerId);

	// IPomodoroManager interface
public:
	QAbstractItemModel *GetTaskModel() override;
	void SetActiveProject(QModelIndex index) override;
	QModelIndex* GetActiveProject() override;
	WorkSetup GetWorkSetup() override;

public slots:
	void StartPomodoro() override;

signals:
	void OnPomodoroFinished();
	void RestFinished();

private:
	ReferenceInstancePtr<IExtendableDataManager> m_dataManager;
	ReferenceInstancePtr<IUserTaskManager> m_myModel;
	ReferenceInstancePtr<INotificationManager> m_notificationManager;
	QAbstractItemModel *taskModel;

	QString tableName;
	QString coreRelationName;

	WorkSetup workSetup;
	QModelIndex currentTask;
	QModelIndex finishedPomodoros;
	QTimer periodsTimer;
	int notificationTimerId;
};
//! \}
#endif // TASKLISTMODEL_H
