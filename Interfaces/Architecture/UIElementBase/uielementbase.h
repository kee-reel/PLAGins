#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <QtCore>
#include <QWidget>

#include "../../Interfaces/Architecture/iuielement.h"
#include "../../Interfaces/Architecture/referenceshandler.h"
#include "methodshandler.h"

class UIElementLinksHandler : public QObject, public ReferencesHandler<QString>
{
	Q_OBJECT
	Q_PROPERTY(ReferencesHandlerState state READ state WRITE setState NOTIFY onStateChanged)
public:
	UIElementLinksHandler(QMap<QString, IReferenceInstancePtr > instances, QMap<QString, IReferenceInstancesListPtr > instancesLists);
	
signals:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(QString interface);

public:
	virtual void setState(ReferencesHandlerState state) override;
	virtual void referencesListUpdated(QString link) override;
};

class UIElementBase;
class UIElementLinksOpener : public QObject, public IUIElementLinksOpener
{
	Q_OBJECT
public:
	UIElementLinksOpener(UIElementBase* instance);
	
	// IUIElementLinksOpener interface
public:
	virtual QObject *getObject() override;

public slots:
	void openLink(uid_t referenceUID);
	void closeLink(uid_t referenceUID);
	void closeSelf();
	
signals:
	void linkOpened(uid_t selfUID, uid_t referenceUID);
	void linkClosed(uid_t selfUID, uid_t referenceUID);
	void selfClosed(uid_t selfUID);

private:
	UIElementBase* m_instance;
};

class UIElementBaseSignal : public QObject
{
	Q_OBJECT
public:
	UIElementBaseSignal(UIElementBase* instance, QWeakPointer<UIElementLinksHandler> handler);
	
public slots:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(QString link);
	
private:
	UIElementBase* m_instance;
	QWeakPointer<UIElementLinksHandler> m_handler;
};

//! \addtogroup UIManager_imp
//!  \{
class UIElementBase : public IUIElement
{
	friend class UIElementBaseSignal;
public:
	UIElementBase(QObject* object, QWidget *parent, QStringList linkNames);
	virtual ~UIElementBase();
	
	// IUIElement interface
public:
	QWeakPointer<IMethodsHandler> getMethodsHandler() override;
	QWeakPointer<IUIElementLinksOpener> getLinksOpener() override;
	QWeakPointer<IReferencesHandler<QString>> getLinksHandler() override;
	
	uid_t getUID() override;
	QStringList linkNames() override;
	QWidget *getWidget() override;
	
	bool open(QWidget *parent) override;
	bool close() override;
	bool isOpened() const override;
	
public:
	virtual void onUIElementReferencesSet() {}
	virtual void onUIElementReady() {}
	virtual void onUIElementReferencesListUpdated(QString link) {Q_UNUSED(link)}
	
private:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(QString link);
	
protected:
	void resetDescriptor(IReferenceDescriptorPtr descriptor);
	void initUIElementBase(QMap<QString, IReferenceInstancePtr> instances = {}, QMap<QString, IReferenceInstancesListPtr> instancesLists = {});
	
protected:
	QPointer<QObject> m_parentObject;
	QPointer<QWidget> m_parentWidget;
	IReferenceDescriptorPtr m_descriptor;
	QStringList m_linkNames;
	QSharedPointer<UIElementLinksHandler> m_linksHandler;
	QSharedPointer<MethodsHandler> m_methodsHandler;
	QSharedPointer<UIElementBaseSignal> m_uiElementBaseSignal;
	QSharedPointer<UIElementLinksOpener> m_opener;
	bool m_isOpened;
};

//! \}
#endif // UIELEMENT_H
