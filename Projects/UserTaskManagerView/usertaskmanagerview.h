#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QAbstractProxyModel>
#include <QPainter>
#include <QAbstractItemModel>
#include <QResizeEvent>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"
#include "../../Interfaces/Utility/iusertaskmanager.h"

#include "designproxymodel.h"
#include "addform.h"
#include "mytreeview.h"
namespace Ui
{
class Form;
}

//! \addtogroup UserTaskManager_dep
//!  \{
class UserTaskManagerView : public QWidget, public PluginBase, public UIElementBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin IUIElement)
	
public:
	UserTaskManagerView();
	virtual ~UserTaskManagerView() override;
	
	// PluginBase interface
private:
	virtual void onPluginInited() override;
	virtual void onPluginReady() override;
	
public slots:
	void OpenTaskEditor(int id);
	
private:
	virtual void resizeEvent(QResizeEvent *event) override;
	
private slots:
	void OnAddFormClosed();
	void buttonAdd_clicked();
	void buttonDelete_clicked();
	void onTreeViewPressed(const QModelIndex &index);
	void buttonEdit_clicked();
	void onTreeViewClicked(const QModelIndex &index);
	void buttonExit_clicked();
	
private:
	QSharedPointer<Ui::Form> ui;
	
	ReferenceInstancePtr<IUserTaskManager> m_taskManager;
	QIdentityProxyModel *proxyModel;
	QAbstractItemModel *taskTree;
	
	AddForm *addForm;
	QAbstractItemModel *model;
	QTreeView *myTreeView;
	bool expandFlag;
	const QModelIndex *currentModelIndex;
};
//!  \}
#endif // TASKLISTVIEW_H
