#ifndef PLUGINLINKERVIEW_H
#define PLUGINLINKERVIEW_H

#include <QtCore>
#include <QWidget>
#include <QStringListModel>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../UIManager/UIElementBase/uielementbase.h"
#include "../../Interfaces/ipluginlinker.h"


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
    PluginLinkerView(QWidget* parent=nullptr);
    virtual ~PluginLinkerView();

// PluginBase interface
signals:
    void onReady(IPlugin*);

signals:
    virtual void openLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link) override;
    virtual void closeLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link) override;
    virtual void closeSelf(IUIElement* self) override;

protected:
    void onAllReferencesSet(bool state) override;
    virtual void onAllReferencesReady(bool state) override;

private slots:
    void addPlugin();
    void removePlugin();
    void onClicked(const QModelIndex &index);

private:
    IPluginLinker* m_pluginLinker;
    QStringListModel m_pluginsListModel;
    QMap<QString, QWeakPointer<IPluginLinker::ILinkerItem>> m_linkerItems;
protected:
    QSharedPointer<Ui::Form> ui;
};
//! }
#endif // PLUGINLINKERVIEW_H
