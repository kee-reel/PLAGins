#ifndef IUIELEMENT_H
#define IUIELEMENT_H

#include <QtCore>

#include "../../Interfaces/ireferencedescriptor.h"

//!  \defgroup UIManager UIManager
//!      \ingroup Plugins
//!  \defgroup UIManager_int Interface
//!      \ingroup UIManager
//!  \defgroup UIManager_imp Implementation
//!      \ingroup UIManager
//!  \defgroup UIManager_dep Dependent plugins
//!      \ingroup UIManager

//!  \addtogroup UIManager_int
//!  \{

typedef uint16_t count_t;

//! \brief Holds basic information about plugin.
class IUIElementDescriptor
{
public:
    //! \brief Plugin unique id. Every plugin in system guaranteed to have unique id.
    virtual uid_t uid() = 0;
    //! \brief Plugin name.
    virtual const QString& displayName() = 0;
    //! \brief Plugin name.
    virtual const QString& linkKey() = 0;
    //! \brief Description of features and purpose of this plugin.
    virtual const QString& about() = 0;
};


class IUIElement
{
public:
    virtual QWeakPointer<IUIElementDescriptor> initUIElement(uid_t uid, QWeakPointer<QJsonObject> meta) = 0;
    virtual QWeakPointer<IUIElementDescriptor> getDescriptor() = 0;
    virtual bool finiUIElement() = 0;

    virtual QWeakPointer<QMap<QString, count_t>> getLinks() = 0;
    virtual void setLinks(QString linkName, QList<QWeakPointer<IUIElementDescriptor>> elements) = 0;
    virtual void removeLinks(QString linkName) = 0;

    virtual QObject *getObject() = 0;
    virtual QWidget *getWidget() = 0;

    virtual bool open(QWidget* parent) = 0;
    virtual bool close() = 0;
    virtual bool isOpened() const = 0;

signals:
    void openLink(QWeakPointer<IUIElement> self, QWeakPointer<IUIElementDescriptor> link);
    void closeLink(QWeakPointer<IUIElement> self, QWeakPointer<IUIElementDescriptor> link);
    void closeSelf(QWeakPointer<IUIElement> self);

protected:
    virtual ~IUIElement() {}
};
//!  \}
Q_DECLARE_INTERFACE(IUIElement, "IUIElement")
Q_DECLARE_INTERFACE(IUIElementDescriptor, "IUIElementDescriptor")
#endif // IUIELEMENT_H
