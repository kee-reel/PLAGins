#ifndef POMODOROVIEW_H
#define POMODOROVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QWidget>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"

#include "../../Interfaces/Utility/ipomodoromanager.h"
#include "pomodorobutton.h"
#include "mytreeview.h"
#include "designproxymodel.h"

namespace Ui
{
class Form;
}

//! \addtogroup PomodoroManager_dep
//!  \{
class PomodoroManagerView : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin)
	
public:
	explicit PomodoroManagerView();
	virtual ~PomodoroManagerView() override;
	
	// PluginBase interface
private:
	virtual void onPluginReady() override;
	
public slots:
	QString linkName();

private slots:
	void UpdateSelectedTask();
	void PomodoroFinished();
	void buttonProjects_clicked();
	void buttonEdit_clicked();
	
	// QWidget interface
	void buttonDelete_clicked();
	
	void buttonAdd_clicked();
	void buttonExit_clicked();
	void treeView_pressed(const QModelIndex &index);
	
private:
	QSharedPointer<Ui::Form> ui;
	QPointer<UIElementBase> m_uiElementBase;
	ReferenceInstancePtr<IPomodoroManager> myModel;
	QAbstractItemModel *proxyModel;
	
	QModelIndex currentTask;
	IPomodoroManager::WorkSetup workSetup;
};
//!  \}
#endif // TASKLISTVIEW_H
