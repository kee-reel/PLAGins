#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QScroller>
#include <QQuickWidget>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"

#include "uniquepushbutton.h"
#include "aspectawaregridlayout.h"

#include "backend.h"


namespace Ui
{
class Form;
}

class QQuickWidget;

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
	
	// UIElementBase interface
public:
	void onUIElementReferencesListUpdated(QString link) override;

	// QWidget interface
	void closeEvent(QCloseEvent *event) override;
protected:
	void resizeEvent(QResizeEvent *event) override;
	
protected:
	QSharedPointer<Ui::Form> ui;

private slots:
	void UniqueButtonPressed(UniquePushButton *button);
	QString FormatMenuItemName(QString name);

private:
	void installMenuElements();

private:
	QLayout *layout;
	ReferenceInstancesListPtr<IUIElement> m_elements;
	QMap<uid_t, UniquePushButton *> m_uniqueButtons;
	QSharedPointer<UniquePushButton> m_exitItem;
	QSharedPointer<UniquePushButton> m_addItem;
	QSharedPointer<QObject> m_backEnd;
};
//!  \}
#endif // GRIDMAINMENUVIEW_H
