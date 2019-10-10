#include "pluginlinkerview.h"

#include "ui_form.h"
#include <QFileDialog>

PluginLinkerView::PluginLinkerView(QWidget *parent) :
    QWidget(parent),
    PluginBase(this),
    UIElementBase(this, this),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &PluginLinkerView::addPlugin);
    connect(ui->btnRemove, &QPushButton::clicked, this, &PluginLinkerView::removePlugin);
    connect(ui->listPlugins, &QListView::clicked, this, &PluginLinkerView::onClicked);
    connect(ui->btnExit, &QPushButton::clicked, [this](){
        emit closeSelf(this);
    });
    ui->listPlugins->setModel(&m_pluginsListModel);
}

PluginLinkerView::~PluginLinkerView()
{
}

void PluginLinkerView::onAllReferencesSet(bool state)
{
    if(m_isAllReferencesSet)
    {
        for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
        {
            if(!iter.value().data()->interfaces().data()->contains("IPluginLinker"))
            {
                m_pluginLinker = castPluginToInterface<IPluginLinker>(iter.value().data()->object());
                Q_ASSERT(m_pluginLinker);
            }
        }
    }
    PluginBase::onAllReferencesSet(state);
}

void PluginLinkerView::onAllReferencesReady(bool state)
{
    auto plugins = m_pluginLinker->getItemsWithInterface("");
    m_linkerItems.clear();

    for(auto& plugin : *plugins.data())
    {
        m_linkerItems.insert(QString::number(plugin.data()->uid()), plugin);
    }
    m_pluginsListModel.setStringList(m_linkerItems.keys());
    PluginBase::onAllReferencesReady(state);
}

void PluginLinkerView::addPlugin()
{
    auto filename = QFileDialog::getOpenFileName(this, "Load plugin");
    if(m_pluginLinker->loadNewPlugin(filename))
    {
        auto plugins = m_pluginLinker->getItemsWithInterface("IUIElement");
        m_linkerItems.clear();

        for(auto& plugin : *plugins.data())
        {
            m_linkerItems.insert(QString::number(plugin.data()->uid()), plugin);
        }
        m_pluginsListModel.setStringList(m_linkerItems.keys());
    }
}

void PluginLinkerView::removePlugin()
{
    auto index = ui->listPlugins->selectionModel()->currentIndex();
    auto pluginName = m_pluginsListModel.data(index).toString();
    auto item = m_linkerItems[pluginName];
    m_pluginLinker->unloadPlugin(item.data()->uid());

    auto plugins = m_pluginLinker->getItemsWithInterface("IUIElement");
    m_linkerItems.clear();

    for(auto& plugin : *plugins.data())
    {
        m_linkerItems.remove(QString::number(plugin.data()->uid()));
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
