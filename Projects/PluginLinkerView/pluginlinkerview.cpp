#include "pluginlinkerview.h"

#include "ui_form.h"
#include <QFileDialog>

PluginLinkerView::PluginLinkerView() :
    PluginBase()
{
    connect(ui->btnAdd, &QPushButton::clicked, this, &PluginLinkerView::addPlugin);
    connect(ui->btnRemove, &QPushButton::clicked, this, &PluginLinkerView::removePlugin);
    connect(ui->btnExit, &QPushButton::clicked, this, &PluginLinkerView::close);
    ui->listPlugins->setModel(&m_pluginsListModel);
}

PluginLinkerView::~PluginLinkerView()
{
}

void PluginLinkerView::onAllReferencesSet()
{
    if(m_isAllReferencesSet)
    {
        for(const auto &reference : m_referencesMap)
        {
            if(!reference->getPluginMetaInfo().InterfaceName.compare("IPluginLinker", Qt::CaseInsensitive))
            {
                m_pluginLinker = castPluginToInterface<IPluginLinker>(reference);
                Q_ASSERT(m_pluginLinker);
            }
        }
    }
    PluginBase::onAllReferencesSet();
}


void PluginLinkerView::onAllReferencesReady()
{
    auto plugins = m_pluginLinker->getPluginsMap();
    m_linkerItems.clear();

    for(auto iter = plugins.begin(); iter != plugins.end(); ++iter)
    {
        auto meta = iter.value().data()->getMeta();
        m_linkerItems.insert(meta.Name, iter.value());
    }
    m_pluginsListModel.setStringList(m_linkerItems.keys());
    PluginBase::onAllReferencesReady();
}

void PluginLinkerView::addPlugin()
{
    auto filename = QFileDialog::getOpenFileName(this, "Load plugin");
    if(m_pluginLinker->loadPlugin(filename))
    {
        auto plugins = m_pluginLinker->getPluginsMap();
        m_linkerItems.clear();

        for(auto iter = plugins.begin(); iter != plugins.end(); ++iter)
        {
            auto meta = iter.value().data()->getMeta();
            m_linkerItems.insert(meta.Name, iter.value());
        }
        m_pluginsListModel.setStringList(m_linkerItems.keys());
    }
}

void PluginLinkerView::removePlugin()
{
    auto index = ui->listPlugins->selectionModel()->currentIndex();
    auto pluginName = m_pluginsListModel.data(index).toString();
    auto item = m_linkerItems[pluginName];
    m_pluginLinker->unloadPlugin(item);

    auto plugins = m_pluginLinker->getPluginsMap();
    m_linkerItems.clear();

    for(auto iter = plugins.begin(); iter != plugins.end(); ++iter)
    {
        auto meta = iter.value().data()->getMeta();
        m_linkerItems.insert(meta.Name, iter.value());
    }
    m_pluginsListModel.setStringList(m_linkerItems.keys());
}
