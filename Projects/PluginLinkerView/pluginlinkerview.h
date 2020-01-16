#ifndef PLUGINLINKERVIEW_H
#define PLUGINLINKERVIEW_H

#include <QtCore>
#include <QWidget>
#include <QStringListModel>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"

#include "../../Interfaces/Middleware/ipluginlinker.h"


namespace Ui
{
class Form;
}

//! addtogroup PluginLinkerView_imp
//! {
class PluginLinkerView : public QWidget, public PluginBase, public UIElementBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.PluginLinkerView" FILE "PluginMeta.json")
	Q_INTERFACES(
			IPlugin
			IUIElement
			)
	
public:
	PluginLinkerView();
	~PluginLinkerView() override = default;
	
	// PluginBase interface
public:
	virtual void onPluginInited() override;
	virtual void onPluginReady() override;
	
private slots:
	void addPlugin();
	void removePlugin();
	void onClicked(const QModelIndex &index);
	
private:
	QSharedPointer<Ui::Form> ui;
	ReferenceInstancePtr<IPluginLinker> m_pluginLinker;
	QStringListModel m_pluginsListModel;
	QMap<QString, QWeakPointer<IPluginLinker::ILinkerItem>> m_linkerItems;
};
//! }
#endif // PLUGINLINKERVIEW_H
