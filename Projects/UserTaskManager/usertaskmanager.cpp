#include "usertaskmanager.h"

UserTaskManager::UserTaskManager() :
	PluginBase(this,
{
	INTERFACE(IUserTaskManager)
})
{
	referencesInit({{INTERFACE(IExtendableDataManager), m_dataManager}}, {});
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
	m_dataManager->instance()->AddExtention(tableName, relationName, newRelationStruct, defaultData);
}

void UserTaskManager::onReady()
{
	treeModel = m_dataManager->instance()->GetDataModel(tableName);
}

QAbstractItemModel* UserTaskManager::GetTreeModel()
{
	return treeModel;
}
