#pragma once

#include <QtCore>
#include <QWidget>
#include <QIcon>

#include "../../Interfaces/Architecture/iuielement.h"
#include "../../Interfaces/Architecture/referenceshandler.h"
#include "methodshandler.h"
#include "uielementbasesignal.h"
#include "uielementlinkshandler.h"
#include "uielementlinksopener.h"

//! \addtogroup UIManager_imp
//!  \{
class UIElementBase : public IUIElement
{
	friend class UIElementBaseSignal;
public:
	UIElementBase(QObject* object, QWidget *parent, QStringList linkNames, QIcon icon=QIcon());
	virtual ~UIElementBase();
	
	// IUIElement interface
public slots:
	QWeakPointer<IMethodsHandler> getMethodsHandler() override;
	QWeakPointer<IUIElementLinksOpener> getLinksOpener() override;
	QWeakPointer<IReferencesHandler<QString>> getLinksHandler() override;
	
	uid_t getUID() override;
	QStringList linkNames() override;
	QWidget *getWidget() override;
	QIcon getIcon() override;
	
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
	QIcon m_icon;
	QSharedPointer<UIElementLinksHandler> m_linksHandler;
	QSharedPointer<MethodsHandler> m_methodsHandler;
	QSharedPointer<UIElementBaseSignal> m_uiElementBaseSignal;
	QSharedPointer<UIElementLinksOpener> m_opener;
	bool m_isOpened;
};

//! \}
