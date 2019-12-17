#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "../../Interfaces/Utility/iusertaskmanager.h"
#include "../../Interfaces/Middleware/iextendabledatamanager.h"

//! \addtogroup UserTaskManager_imp
//! \{
class UserTaskManager : public QObject, public PluginBase, public IUserTaskManager
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(
	    IPlugin
	    IUserTaskManager
	)

public:
	UserTaskManager();
	virtual ~UserTaskManager() override;

	// PluginBase interface
protected:
	virtual void onPluginReferencesSet() override;
	virtual void onPluginReady() override;

	// IUserTaskManager interface
public:
	virtual QAbstractItemModel *GetTreeModel() override;

signals:
	void OpenTaskEdit(int id);

private:
	void SetupModel();

	QString tableName;
	QString relationName;
	ReferenceInstancePtr<IExtendableDataManager> m_dataManager;
	QAbstractItemModel *treeModel;
};
//! \}
#endif // TASKLISTMODEL_H
