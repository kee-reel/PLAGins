#include "tasksketchmanager.h"

TaskSketchManager::TaskSketchManager() :
	QObject(nullptr),
	PluginBase(this),
	taskModel(nullptr),
	sketchItemModel(nullptr)
{
	initPluginBase({
		{INTERFACE(IPlugin), this},
		{INTERFACE(ITaskSketchManager), this}
	},
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
	m_dataManager->RegisterExtentionFieldEditor(tableName, "sketch", widget);
}

void TaskSketchManager::onReferencesSet()
{
	QMap<QString, QVariant::Type> newRelationStruct =
	{
		{"sketch",  QVariant::ByteArray}
	};
	QVector<QVariant> defaultData;
	defaultData << QByteArray();
	m_dataManager->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);
	m_dataManager->AddExtention("IUserTaskManager", coreRelationName, newRelationStruct, defaultData);
	sketchItemModel = m_dataManager->GetDataModel(tableName);
}

void TaskSketchManager::onReady()
{
	taskModel = m_dataManager->GetDataModel("IUserTaskManager");
}
