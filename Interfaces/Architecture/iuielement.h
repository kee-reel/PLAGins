#ifndef IUIELEMENT_H
#define IUIELEMENT_H

#include <QtCore>

#include "../../Interfaces/Architecture/ireferenceshandler.h"

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


class IMethodsHandler
{
public:
	virtual QList<QMetaMethod> getSignals() = 0;
	virtual QList<QMetaMethod> getSlots() = 0;
};

class IUIElementLinksOpener
{
public:
	virtual QObject* getObject() = 0;
signals:
	void linkOpened(uid_t selfUID, uid_t referenceUID);
	void linkClosed(uid_t selfUID, uid_t referenceUID);
	void selfClosed(uid_t selfUID);
};

class IUIElement
{
public:
	virtual QWeakPointer<IMethodsHandler> getMethodsHandler() = 0;
	virtual QWeakPointer<IUIElementLinksOpener> getLinksOpener() = 0;
	virtual QWeakPointer<IReferencesHandler<QString>> getLinksHandler() = 0;
	
	virtual uid_t getUID() = 0;
	virtual QStringList linkNames() = 0;
	virtual QWidget *getWidget() = 0;
	
	virtual bool open(QWidget *parent) = 0;
	virtual bool isOpened() const = 0;
	virtual bool close() = 0;
};
//!  \}
Q_DECLARE_INTERFACE(IUIElement, "IUIElement")
#endif // IUIELEMENT_H
