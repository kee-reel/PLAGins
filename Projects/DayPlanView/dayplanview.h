#ifndef DAYPLANVIEW_H
#define DAYPLANVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"

#include "../../Interfaces/Utility/idayplan.h"
#include "datetimetypeeditor.h"
#include "designproxymodel.h"

namespace Ui
{
class Form;
}

//! \addtogroup DayPlan_dep
//!  \{
class DayPlanView : public QWidget, public PluginBase, public UIElementBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin IUIElement)
	
public:
	explicit DayPlanView();
	virtual ~DayPlanView() override;
	
	// PluginBase interface
private:
	virtual void onPluginReady() override;
	virtual void onPluginInited() override;
	
private:
	QWidget *referenceWidget;
	
private:
	ReferenceInstancePtr<IDayPlan> DayPlan;
	QAbstractItemModel * itemModel;
	
private:
	QSharedPointer<Ui::Form> ui;
};
//!  \}
#endif // DAYPLANVIEW_H
