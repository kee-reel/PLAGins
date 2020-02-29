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

void UserTaskManager::onReferencesSet()
{
	QMap<QString, QVariant::Type> newRelationStruct =
	{
		{"name", QVariant::String}
	};
	QVector<QVariant> defaultData;
	defaultData << "New task";
	m_dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);
	m_dataManager->SetActiveExtention(tableName, relationName);
}

void UserTaskManager::onReady()
{
	treeModel = m_dataManager->GetDataModel(tableName);
}

QAbstractItemModel* UserTaskManager::GetTreeModel()
{
	return treeModel;
}
