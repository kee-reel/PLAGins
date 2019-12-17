#ifndef DayPlan_H
#define DayPlan_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "../../Interfaces/Utility/idayplan.h"
#include "../../Interfaces/Utility/iusertaskmanager.h"
#include "../../Interfaces/Middleware/iextendabledatamanager.h"

//! \addtogroup DayPlan_imp
//! \{
class DayPlan : public QObject, public PluginBase, public IDayPlan
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IDayPlan
    )

public:
    DayPlan();
    virtual ~DayPlan() override;

    // PluginBase interface
public:
	virtual void onPluginReady() override;

    // IDayPlan interface
public:
    QAbstractItemModel *GetTaskModel() override;
    QAbstractItemModel *GetDateModel() override;
    void SetDataTypeEditor(QWidget *widget) override;

private:
    ReferenceInstancePtr<IUserTaskManager> taskTreeModel;
    ReferenceInstancePtr<IExtendableDataManager> dataManager;
    QString tableName, relationName;
    QAbstractItemModel *taskDataModel;
    QAbstractItemModel *dateDataModel;
};
//! \}
#endif // DayPlan_H
