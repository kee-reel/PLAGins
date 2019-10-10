#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QMap>
#include <QLayout>
#include <QEnableSharedFromThis>

#include "../Core/CoreServiceBase/coreservicebase.h"

#include "../../Interfaces/iuielement.h"
#include "../../Interfaces/ipluginlinker.h"
#include "../../../Application/iapplication.h"

//! \addtogroup UIManager_imp
//!  \{
class UIManager : public QObject, public Service::CoreServiceBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        Service::ICoreService
    )

public:
    UIManager();
    virtual ~UIManager() override;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;

    // IUIManager interface
public:
    bool registerUIElement(IUIElement *uiElement, QWeakPointer<QJsonObject> meta);

signals:
    void onPop();

private slots:
    void onOpenLink(IUIElement *self, QWeakPointer<IUIElementDescriptor> link);
    void onCloseLink(IUIElement *self, QWeakPointer<IUIElementDescriptor> link);
    void onCloseSelf(IUIElement *self);

private:
    struct UIElementHandler
    {
        IUIElement* m_element;
        QWeakPointer<IUIElementDescriptor> m_elementDescr;
    };

private:
    inline QSharedPointer<UIElementHandler> getActive()
    {
        return m_elementsMap[m_elementsStack.last()];
    }

private:
    IPluginLinker* m_pluginLinker;
    QWidget *m_parentWidget;
    uid_t m_lastGeneratedUID;
    uid_t m_rootElementUID;

    QList<uid_t> m_elementsStack;
    QMap<uid_t, QSharedPointer<UIElementHandler>> m_elementsMap;
    QMap<QString, QSharedPointer<QList<QWeakPointer<IUIElementDescriptor>>> > m_elementLinksByNameMap;
};
//!  \}
#endif // UIMANAGER_H
