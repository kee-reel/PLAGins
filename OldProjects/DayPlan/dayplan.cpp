#include "dayplan.h"

DayPlan::DayPlan() :
	QObject(),
	PluginBase(this, {INTERFACE(IDayPlan)})
{
	initPluginBase({
		{INTERFACE(IUserTaskManager), taskTreeModel},
		{INTERFACE(IExtendableDataManager), dataManager}
	});
	taskDataModel = nullptr;
	dateDataModel = nullptr;
	tableName = "IUserTaskManager";
	relationName = "IDayPlan";
}

DayPlan::~DayPlan()
{
}

void DayPlan::onReady()
{
	QMap<QString, QVariant::Type> newRelationStruct = {
		{"Date", QVariant::String},
	};
	QVector<QVariant> defaultData;
	defaultData << QDateTime::currentDateTime().toString(Qt::ISODate);
	dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);
	dataManager->AddExtention(relationName, relationName, newRelationStruct, defaultData);
	
	taskDataModel = dataManager->GetDataModel(tableName);
	dateDataModel = dataManager->GetDataModel(relationName);
}

QAbstractItemModel *DayPlan::GetTaskModel()
{
	return taskDataModel;
}

QAbstractItemModel *DayPlan::GetDateModel()
{
	return dateDataModel;
}

void DayPlan::SetDataTypeEditor(QWidget *widget)
{
	dataManager->RegisterExtentionFieldEditor(relationName, "datetime", widget);
}
