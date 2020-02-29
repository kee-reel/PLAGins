#include "taskcalendar.h"

TaskCalendar::TaskCalendar() :
	PluginBase(this)
{
	initPluginBase({
		{INTERFACE(IPlugin), this},
		{INTERFACE(ITaskCalendar), this}
	},
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
	m_dataManager->AddExtention("IUserTaskManager", "ITaskCalendar", newRelationStruct, defaultData);
}

void TaskCalendar::LinkEditorWidget(QWidget *widget)
{
	Q_UNUSED(widget)
}
