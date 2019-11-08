#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <QtCore>
#include <QWidget>

#include "../../Interfaces/Architecture/iuielement.h"
#include "../../Interfaces/Middleware/ipluginlinker.h"

#include "uielementlinkshandler.h"
#include "methodshandler.h"

//! \addtogroup UIManager_imp
//!  \{
class UIElementBase : public IUIElement
{
public:
	UIElementBase(QObject* object, QWidget *parent, QStringList linkNames);
	virtual ~UIElementBase();

	// IUIElement interface
public:
	virtual QWeakPointer<IUIElementLinksHandler> getLinksHandler() override;
	virtual QWeakPointer<IMethodsHandler> getMethodsHandler() override;

	virtual uid_t getUID() override;
	virtual QStringList linkNames() override;
	virtual QObject *getObject() override;
	virtual QWidget *getWidget() override;

	virtual bool open(QWidget *parent) override;
	virtual bool close() override;
	virtual bool isOpened() const override;

protected:
    void resetDescriptor(IReferenceDescriptorPtr descriptor);
	void initUIElement(QMap<QString, IReferenceInstancePtr> instances = {}, QMap<QString, IReferenceInstancesListPtr> instancesLists = {});

signals:
	void openLink(IUIElement *self, QString linkName, uid_t referenceUID);
	void closeLink(IUIElement *self, QString linkName, uid_t referenceUID);
	void closeSelf(IUIElement *self);

private:
	QObject* m_parentObject;
	QWidget* m_parentWidget;
	IReferenceDescriptorPtr m_descriptor;
	QStringList m_linkNames;
	QSharedPointer<UIElementLinksHandler> m_linksHandler;
	QSharedPointer<MethodsHandler> m_methodsHandler;
	bool m_isOpened;
};
//! \}
#endif // UIELEMENT_H
