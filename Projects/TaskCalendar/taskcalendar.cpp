#include "taskcalendar.h"

TaskCalendar::TaskCalendar() :
	PluginBase(this,
{
	INTERFACE(ITaskCalendar)
})
{
	referencesInit(
	{
		{INTERFACE(IExtendableDataManager), m_dataManager},
		{INTERFACE(IUserTaskManager), m_taskTree}
	});
}

TaskCalendar::~TaskCalendar()
{
}

void TaskCalendar::onReferencesSet()
{
	QMap<QString, QVariant::Type> newRelationStruct =
	{
		{"Date",   QVariant::DateTime}
	};
	QVector<QVariant> defaultData;
	defaultData << QDateTime::currentDateTime();
	m_dataManager->instance()->AddExtention("IUserTaskManager", "ITaskCalendar", newRelationStruct, defaultData);
}

void TaskCalendar::LinkEditorWidget(QWidget *widget)
{
}
