#include "pluginlinkerview.h"

#include "ui_form.h"
#include <QFileDialog>

PluginLinkerView::PluginLinkerView() :
	QWidget(),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenuItem"}),
	ui(new Ui::Form)
{
	ui->setupUi(this);
	connect(ui->btnAdd, &QPushButton::clicked, this, &PluginLinkerView::addPlugin);
	connect(ui->btnRemove, &QPushButton::clicked, this, &PluginLinkerView::removePlugin);
	connect(ui->listPlugins, &QListView::clicked, this, &PluginLinkerView::onClicked);
	connect(ui->btnExit, &QPushButton::clicked, [this](){
		m_opener->closeSelf();
	});
	ui->listPlugins->setModel(&m_pluginsListModel);
	initPluginBase({
		{INTERFACE(IPluginLinker), m_pluginLinker}
	});
	initUIElementBase();
}

PluginLinkerView::~PluginLinkerView()
{
}

void PluginLinkerView::onPluginInited()
{
	resetDescriptor(descr());
}

void PluginLinkerView::onPluginReady()
{
	auto items = m_pluginLinker->instance()->getItemsWithInterface(INTERFACE(IPlugin));
	m_linkerItems.clear();
	
	for(auto& item : *items.data())
	{
		auto descr = item.data()->descr().data();
		auto id = QString("%1:%2").arg(descr->name()).arg(descr->uid());
		m_linkerItems.insert(id, item);
	}
	m_pluginsListModel.setStringList(m_linkerItems.keys());
}

void PluginLinkerView::addPlugin()
{
	auto filename = QFileDialog::getOpenFileName(this, "Load plugin");
	if(filename.isNull())
	{
		return;
	}
	
	if(m_pluginLinker->instance()->addPlugin(filename))
	{
		auto items = m_pluginLinker->instance()->getItemsWithInterface(INTERFACE(IPlugin));
		m_linkerItems.clear();
		
		if(items != nullptr)
		{		
			for(auto& item : *items.data())
			{
				auto itemPtr = item.data();
				auto descr = itemPtr->descr().data();
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
	m_pluginLinker->instance()->removePlugin(item);
	
	auto items = m_pluginLinker->instance()->getItemsWithInterface(INTERFACE(IPlugin));
	m_linkerItems.clear();
	
	for(auto& item : *items.data())
	{
		auto descr = item.data()->descr().data();
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
	//    auto meta = item.data()->getMeta();
	//    ui->textAbout->setText(meta.About);
}
