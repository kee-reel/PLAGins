#pragma once


#include <QObject>
#include <QDebug>
#include <QString>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "../../Interfaces/Utility/itaskcalendar.h"
#include "../../Interfaces/Middleware/iextendabledatamanager.h"
#include "../../Interfaces/Utility/iusertaskmanager.h"

//! \addtogroup TaskCalendar_imp
//!  \{
class TaskCalendar : public QObject, public PluginBase, public ITaskCalendar
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(
	    IPlugin
	    ITaskCalendar
	)

public:
	TaskCalendar();
	virtual ~TaskCalendar() override;

	// PluginBase interface
public:
	virtual void onReferencesSet() override;

	// ITaskCalendar interface
public:
	virtual void LinkEditorWidget(QWidget *) override;

private:
	ReferenceInstancePtr<IExtendableDataManager> m_dataManager;
	ReferenceInstancePtr<IUserTaskManager> m_taskTree;
	QWidget* customDataWidget;
};
//!  \}

