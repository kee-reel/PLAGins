#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H

#include <QtCore>

class Task : public QObject
{
	Q_OBJECT
	
	int INVALID_ID = -1;
public:
	Task() : QObject(nullptr), m_id(INVALID_ID) {}
	
	void setId(int id)
	{
		assert(m_id == INVALID_ID);
		m_id = id;
	}
	
	void ready()
	{
		assert(m_id != INVALID_ID);
		emit onReady(m_id);
	}
	
	bool isReady()
	{
		return m_isReady;
	}
	
	int id()
	{
		return m_id;
	}
	
signals:
	void onReady(int id);
	
private:
	int m_id;
	bool m_isReady;
};


class TasksManager : public QObject
{
	Q_OBJECT
public:
	TasksManager(QVector<QWeakPointer<Task>> tasks) :
		QObject(nullptr)
	{
		int id = 0;
		for(auto& task : tasks)
		{
			task.data()->setId(++id);
			m_tasksStatus[id] = task.data()->isReady();
			connect(task.data(), &Task::onReady, this, &TasksManager::onTaskCompleted);
		}
	}
	
private:
	void checkTasksReady()
	{
		if(m_isEmitted)
		{
			return;
		}
		for(auto& status : m_tasksStatus)
		{
			if(!status)
			{
				return;
			}
		}
		m_isEmitted = true;
		emit onTasksReady();
	}
	
private slots:
	void onTaskCompleted(int id)
	{
		m_tasksStatus[id] = true;
		checkTasksReady();
	}
	
signals:
	void onTasksReady();
	
private:
	QMap<int, bool> m_tasksStatus;
	bool m_isEmitted;
};

//! \}
#endif // TASKSMANAGER_H
