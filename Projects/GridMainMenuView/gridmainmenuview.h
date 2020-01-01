#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QQuickWidget>
#include <QtCore>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"


//! \addtogroup UIManager_dep
//!  \{
class GridMainMenuView : public QQuickWidget, public PluginBase, public UIElementBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(
	    IPlugin
	    IUIElement
	)

public:
	explicit GridMainMenuView();
	~GridMainMenuView() override;

	// PluginBase interface
public:
	virtual void onPluginInited() override;

	// QWidget interface
	void closeEvent(QCloseEvent *event) override;

private:
	void setRatio();

private:
	ReferenceInstancesListPtr<IUIElement> m_elements;
	
	// QWidget interface
protected:
	virtual void resizeEvent(QResizeEvent *event) override;
};
//!  \}
#endif // GRIDMAINMENUVIEW_H
