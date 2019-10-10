#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <QtCore>
#include <QWidget>

#include "../../Interfaces/iuielement.h"
#include "../../Interfaces/ipluginlinker.h"

#include "uielementdescriptor.h"

//! \addtogroup UIManager_imp
//!  \{
class UIElementBase : public IUIElement
{
public:
    UIElementBase(QObject* object, QWidget *parent);
    virtual ~UIElementBase() override;

    // IUIElement interface
public:
    virtual QWeakPointer<IUIElementDescriptor> initUIElement(uid_t uid, QWeakPointer<QJsonObject> meta) override;
    virtual QWeakPointer<IUIElementDescriptor> getDescriptor() override;
    virtual bool finiUIElement() override;

    virtual QWeakPointer<QMap<QString, count_t>> getLinks() override;
    virtual void setLinks(QString linkName, QList<QWeakPointer<IUIElementDescriptor> > elements) override;
    virtual void removeLinks(QString linkName) override;

    virtual QObject *getObject() override;
    virtual QWidget *getWidget() override;

    virtual bool open(QWidget *parent) override;
    virtual bool close() override;
    virtual bool isOpened() const override;

signals:
    virtual void openLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link) = 0;
    virtual void closeLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link) = 0;
    virtual void closeSelf(IUIElement* self) = 0;

protected:
    QMap<QString, QList<QWeakPointer<IUIElementDescriptor>> > m_links;

private:
    QObject* m_parentObject;
    QWidget* m_parentWidget;
    QSharedPointer<UIElementDescriptor> m_selfDescriptor;
    bool m_isOpened;
};
//! \}
#endif // UIELEMENT_H
