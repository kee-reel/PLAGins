#include "tasksketchmanager.h"

TaskSketchManager::TaskSketchManager() :
	QObject(nullptr),
	PluginBase(this,
{
	INTERFACE(ITaskSketchManager)
})
{
	referencesInit(
	{
		{INTERFACE(IExtendableDataManager), m_dataManager},
		{INTERFACE(IUserTaskManager), m_myModel}
	});

	tableName = "iTaskSketchManager";
	coreRelationName = "iTaskSketchManager";
}

TaskSketchManager::~TaskSketchManager()
{
}

QAbstractItemModel *TaskSketchManager::GetModel()
{
	return taskModel;
}

QAbstractItemModel *TaskSketchManager::GetInternalModel()
{
	return sketchItemModel;
}

void TaskSketchManager::ConvertSketchToTask(int sketchId)
{
	QModelIndex modelIndex = sketchItemModel->index(sketchId, 0);
	QMap<int, QVariant> map = sketchItemModel->itemData(modelIndex);

	if(!map.contains(Qt::UserRole))
	{
		qCritical() << "Can't resolve data model!";
		return;
	}

	//    QMap<QString, QVariant> dataMap = map[Qt::UserRole].toMap();
	//    QList<QVariant> data = dataMap[coreRelationName].toList();
	taskModel->insertRows(taskModel->rowCount(), 1);
	modelIndex = taskModel->index(taskModel->rowCount()-1, 0);
	//    dataManager->SetActiveRelation(tableName, coreRelationName);
	taskModel->setItemData(modelIndex, map);
	//emit ConvertTaskToSketch(map[0].toInt());
}

void TaskSketchManager::LinkEditorWidget(QWidget *widget)
{
	m_dataManager->instance()->RegisterExtentionFieldEditor(tableName, "sketch", widget);
}

void TaskSketchManager::onReferencesSet()
{
	QMap<QString, QVariant::Type> newRelationStruct =
	{
		{"sketch",  QVariant::ByteArray}
	};
	QVector<QVariant> defaultData;
	defaultData << QByteArray();
	m_dataManager->instance()->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);
	m_dataManager->instance()->AddExtention("IUserTaskManager", coreRelationName, newRelationStruct, defaultData);
}

void TaskSketchManager::onReady()
{
	sketchItemModel = m_dataManager->instance()->GetDataModel(tableName);
	taskModel = m_dataManager->instance()->GetDataModel("IUserTaskManager");
}
