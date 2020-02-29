#pragma once


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
class UserTaskManagerView : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin)
	
public:
	UserTaskManagerView();
	virtual ~UserTaskManagerView() override;
	
	// PluginBase interface
private:
	virtual void onReady() override;
	
public slots:
	void OpenTaskEditor(int id);
	
private slots:
	void OnAddFormClosed();
	void buttonAdd_clicked();
	void buttonDelete_clicked();
	void onTreeViewPressed(const QModelIndex &index);
	void buttonEdit_clicked();
	void onTreeViewClicked(const QModelIndex &index);
	void buttonExit_clicked();
	void onTreeViewDoubleClicked(const QModelIndex &index);
	
private:
	QSharedPointer<Ui::Form> ui;
	QPointer<UIElementBase> m_uiElementBase;
	
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

