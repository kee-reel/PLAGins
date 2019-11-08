#ifndef TaskSketchManager_H
#define TaskSketchManager_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "../../Interfaces/Utility/itasksketchmanager.h"
#include "../../Interfaces/Middleware/iextendabledatamanager.h"
#include "../../Interfaces/Utility/iusertaskmanager.h"

//! \addtogroup TaskSketchManager_imp
//! \{
class TaskSketchManager : public QObject, public PluginBase, public ITaskSketchManager
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin ITaskSketchManager)

public:
	TaskSketchManager();
	virtual ~TaskSketchManager() override;

public:
	// PluginBase interface
	virtual void onReferencesSet() override;
	virtual void onReady() override;

	// ITaskSketchManager interface
public:
	QAbstractItemModel *GetModel() override;
	QAbstractItemModel *GetInternalModel() override;
	void ConvertSketchToTask(int sketchId) override;
	void LinkEditorWidget(QWidget *widget) override;

private:
	ReferenceInstancePtr<IExtendableDataManager> m_dataManager;
	ReferenceInstancePtr<IUserTaskManager> m_myModel;
	QAbstractItemModel *taskModel;
	QAbstractItemModel *sketchItemModel;

	QString tableName;
	QString coreRelationName;
};
//! \}
#endif // TASKLISTMODEL_H
