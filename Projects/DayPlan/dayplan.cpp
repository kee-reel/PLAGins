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

void DayPlan::onPluginReady()
{
	QMap<QString, QVariant::Type> newRelationStruct = {
		{"Date", QVariant::String},
	};
	QVector<QVariant> defaultData;
	defaultData << QDateTime::currentDateTime().toString(Qt::ISODate);
	dataManager->instance()->AddExtention(tableName, relationName, newRelationStruct, defaultData);
	dataManager->instance()->AddExtention(relationName, relationName, newRelationStruct, defaultData);
	
	taskDataModel = dataManager->instance()->GetDataModel(tableName);
	dateDataModel = dataManager->instance()->GetDataModel(relationName);
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
	dataManager->instance()->RegisterExtentionFieldEditor(relationName, "datetime", widget);
}
