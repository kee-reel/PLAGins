#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QtCore>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"


//! \addtogroup UIManager_dep
//!  \{
class GridMainMenuView : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(
		IPlugin
	)

public:
	explicit GridMainMenuView();
	~GridMainMenuView() override = default;
	
private:
	UIElementBase* m_uiElementBase;
	ReferenceInstancesListPtr<IUIElement> m_elements;
};
//!  \}
#endif // GRIDMAINMENUVIEW_H
