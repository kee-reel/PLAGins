#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QScroller>

#include "../../Interfaces/iuielement.h"
#include "../PluginLinker/PluginBase/plugin_base.h"
#include "../UIManager/UIElementBase/uielementbase.h"

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

    // QWidget interface
    void closeEvent(QCloseEvent *event);
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
    int getUniqueId();
    void installMenuElements();

signals:
    virtual void openLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link) override;
    virtual void closeLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link) override;
    virtual void closeSelf(IUIElement* self) override;

signals:
    virtual void onReadyStateChanged(uid_t selfUID, bool readyState) override;

protected:
    QSharedPointer<Ui::Form> ui;

private:
    QLayout *layout;
    QMap<int, QWeakPointer<IUIElementDescriptor>> m_uiElements;
    int m_uniqueIdCounter;
    QVector<UniquePushButton *> m_uniqueButtons;
    UniquePushButton *m_exitItem;
};
//!  \}
#endif // GRIDMAINMENUVIEW_H
