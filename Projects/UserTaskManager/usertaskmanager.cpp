#include "usertaskmanager.h"

UserTaskManager::UserTaskManager() :
	PluginBase(this)
{
	initPluginBase({
		{INTERFACE(IPlugin), this},
		{INTERFACE(IUserTaskManager), this},
	},
	{
		{INTERFACE(IExtendableDataManager), m_dataManager}
	}, {});
	tableName = "iUserTaskManager";
	relationName = "iUserTaskManager";
	treeModel = nullptr;
}

UserTaskManager::~UserTaskManager()
{
}

void UserTaskManager::onPluginReferencesSet()
{
	QMap<QString, QVariant::Type> newRelationStruct =
	{
		{"name", QVariant::String}
	};
	QVector<QVariant> defaultData;
	defaultData << "New task";
	m_dataManager->instance()->AddExtention(tableName, relationName, newRelationStruct, defaultData);
	m_dataManager->instance()->SetActiveExtention(tableName, relationName);
}

void UserTaskManager::onPluginReady()
{
	treeModel = m_dataManager->instance()->GetDataModel(tableName);
}

QAbstractItemModel* UserTaskManager::GetTreeModel()
{
	return treeModel;
}
