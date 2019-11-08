#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QScroller>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"

#include "uniquepushbutton.h"
#include "aspectawaregridlayout.h"


namespace Ui
{
class Form;
}

//! \addtogroup UIManager_dep
//!  \{
class GridMainMenuView : public QWidget, public PluginBase, public UIElementBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(
	    IPlugin
	    IUIElement
	)

public:
	explicit GridMainMenuView();
	virtual ~GridMainMenuView() override;

signals:
	void lolKek();

	// PluginBase interface
public:
	virtual void onReady() override;

	// QWidget interface
	void closeEvent(QCloseEvent *event) override;
protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	enum PredefinedIndices
	{
		EXIT = -1,
		ADD_ITEM = -2
	};

private slots:
	void UniqueButtonPressed(UniquePushButton *button);
	QString FormatMenuItemName(QString name);

private:
	void installMenuElements();

signals:
	void openLink(IUIElement *self, QString linkName, uid_t referenceUID);
	void closeLink(IUIElement *self, QString linkName, uid_t referenceUID);
	void closeSelf(IUIElement *self);

protected:
	QSharedPointer<Ui::Form> ui;

private:
	QLayout *layout;
	ReferenceInstancesListPtr<IUIElement> m_elements;
	int m_uniqueIdCounter;
	QVector<UniquePushButton *> m_uniqueButtons;
	UniquePushButton *m_exitItem;
};
//!  \}
#endif // GRIDMAINMENUVIEW_H
