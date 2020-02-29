#pragma once


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
class PluginLinkerView : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.PluginLinkerView" FILE "PluginMeta.json")
	Q_INTERFACES(
		IPlugin
	)
	
public:
	PluginLinkerView();
	~PluginLinkerView() override = default;
	
	// PluginBase interface
public:
	virtual void onReady() override;
	
private slots:
	void addPlugin();
	void removePlugin();
	void onClicked(const QModelIndex &index);
	
private:
	QSharedPointer<Ui::Form> ui;
	QPointer<UIElementBase> m_uiElementBase;
	ReferenceInstancePtr<IPluginLinker> m_pluginLinker;
	QStringListModel m_pluginsListModel;
	QMap<QString, QWeakPointer<IPluginLinker::ILinkerItem>> m_linkerItems;
};
//! }

