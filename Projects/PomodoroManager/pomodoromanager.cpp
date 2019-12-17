#include "pomodoromanager.h"

PomodoroManager::PomodoroManager() :
	PluginBase(this,
{
	INTERFACE(IPomodoroManager)
})
{
	initPluginBase(
	{
		{INTERFACE(IExtendableDataManager), m_dataManager},
		{INTERFACE(IUserTaskManager), m_myModel},
		{INTERFACE(INotificationManager), m_notificationManager}
	});
	taskModel = nullptr;
	tableName = "IUserTaskManager";
	coreRelationName = "iPomodoroManager";
	workSetup.workSessionDuration = 5;//35 * 60;
	workSetup.easyRestDuration = 5 * 60;
	workSetup.longRestDuration = 15 * 60;
	workSetup.longRestPeriod = 3;
}

PomodoroManager::~PomodoroManager()
{
}

void PomodoroManager::onPluginReferencesSet()
{
	QMap<QString, QVariant::Type> newRelationStruct =
	{
		{"pomodoros",   QVariant::Int}
	};
	QVector<QVariant> defaultData;
	defaultData << 0;
	m_dataManager->instance()->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);
}

void PomodoroManager::onPluginReady()
{
	taskModel = m_dataManager->instance()->GetDataModel(tableName);
}

QAbstractItemModel *PomodoroManager::GetTaskModel()
{
	return taskModel;
}

void PomodoroManager::SetActiveProject(QModelIndex index)
{
	currentTask = index;
}

QModelIndex* PomodoroManager::GetActiveProject()
{
	return &currentTask;
}

IPomodoroManager::WorkSetup PomodoroManager::GetWorkSetup()
{
	return workSetup;
}

void PomodoroManager::StartPomodoro()
{
	notificationTimerId = m_notificationManager->instance()->SetAlarm(INotificationManager::RTC_TIME,
	                      QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration));

	m_notificationManager->instance()->SetAlarmedNotification(INotificationManager::RTC_TIME,
	        QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration),
	        "Message from Pomodoro:",
	        "You can take a rest now");
}

void PomodoroManager::OnTimerEnded(int timerId)
{
//    if(notificationTimerId != timerId) return;
	if(!currentTask.isValid()) return;
	auto branchIndex = currentTask;
	while(branchIndex.isValid())
	{
		auto pomodoros = branchIndex.data().toInt() + 1;
		taskModel->setData(branchIndex, QVariant(pomodoros));
		branchIndex = branchIndex.parent();
	}
	emit OnPomodoroFinished();
}
