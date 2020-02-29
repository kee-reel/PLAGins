#include "pluginlinkerview.h"

#include "ui_form.h"
#include <QFileDialog>

PluginLinkerView::PluginLinkerView() :
	QObject(),
	PluginBase(this),
	ui(new Ui::Form),
	m_uiElementBase(new UIElementBase(this, {"MainMenuItem"}))
{
	ui->setupUi(m_uiElementBase);
	connect(ui->btnAdd, &QPushButton::clicked, this, &PluginLinkerView::addPlugin);
	connect(ui->btnRemove, &QPushButton::clicked, this, &PluginLinkerView::removePlugin);
	connect(ui->listPlugins, &QListView::clicked, this, &PluginLinkerView::onClicked);
	connect(ui->btnExit, &QPushButton::clicked, [this](){
		m_uiElementBase->closeSelf();
	});
	ui->listPlugins->setModel(&m_pluginsListModel);
	initPluginBase({
		{INTERFACE(IPlugin), this},
		{INTERFACE(IUIElement), m_uiElementBase}
	},
	{
		{INTERFACE(IPluginLinker), m_pluginLinker}
	});
	m_uiElementBase->initUIElementBase();
}

void PluginLinkerView::onReady()
{
	auto items = m_pluginLinker->getItemsWithInterface(INTERFACE(IPlugin));
	m_linkerItems.clear();
	
	for(auto& item : *items.toStrongRef())
	{
		auto descr = item.toStrongRef()->descr().toStrongRef();
		auto id = QString("%1:%2").arg(descr->name()).arg(descr->uid());
		m_linkerItems.insert(id, item);
	}
	m_pluginsListModel.setStringList(m_linkerItems.keys());
}

void PluginLinkerView::addPlugin()
{
	auto filename = QFileDialog::getOpenFileName(m_uiElementBase, "Load plugin");
	if(filename.isNull())
	{
		return;
	}
	
	if(m_pluginLinker->addPlugin(filename))
	{
		auto items = m_pluginLinker->getItemsWithInterface(INTERFACE(IPlugin));
		m_linkerItems.clear();
		
		if(items != nullptr)
		{		
			for(auto& item : *items.toStrongRef())
			{
				auto itemPtr = item.toStrongRef();
				auto descr = itemPtr->descr().toStrongRef();
				auto id = QString("%1:%2").arg(descr->name()).arg(descr->uid());
				m_linkerItems.insert(id, item);
			}
		}
		m_pluginsListModel.setStringList(m_linkerItems.keys());
	}
}

void PluginLinkerView::removePlugin()
{
	auto index = ui->listPlugins->selectionModel()->currentIndex();
	auto pluginName = m_pluginsListModel.data(index).toString();
	auto item = m_linkerItems[pluginName];
	m_pluginLinker->removePlugin(item);
	
	auto items = m_pluginLinker->getItemsWithInterface(INTERFACE(IPlugin));
	m_linkerItems.clear();
	
	for(auto& item : *items.toStrongRef())
	{
		auto descr = item.toStrongRef()->descr().toStrongRef();
		if(descr)
		{
			auto id = QString("%1:%2").arg(descr->name()).arg(descr->uid());
			m_linkerItems.insert(id, item);
		}
	}
	m_pluginsListModel.setStringList(m_linkerItems.keys());
}

void PluginLinkerView::onClicked(const QModelIndex &index)
{
	auto pluginName = index.data().toString();
	auto item = m_linkerItems[pluginName];
	//    auto meta = item.toStrongRef()->getMeta();
	//    ui->textAbout->setText(meta.About);
}
