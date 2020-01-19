#pragma once

#include <QtCore>
#include <QIcon>

#include "../../Interfaces/Architecture/iuielement.h"
#include "../../Interfaces/Architecture/iplugin.h"
#include "../../Interfaces/Architecture/referenceshandler.h"
#include "methodshandler.h"
#include "uielementbasesignal.h"
#include "uielementlinkshandler.h"


#ifdef QML_UIElement
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWidget>
#define UIElementBaseParent QQuickWidget
#endif

#ifdef QWidget_UIElement
#include <QWidget>
#define UIElementBaseParent QWidget
#endif


class UIElementBase : public UIElementBaseParent, public IUIElement
{
	friend class UIElementBaseSignal;
	Q_OBJECT
	Q_INTERFACES(
		IUIElement
	)
public:
	UIElementBase(QObject* parentObject, QStringList linkNames, QIcon icon=QIcon());
	~UIElementBase() override = default;
	
	// IUIElement interface
public slots:
	QWeakPointer<IMethodsHandler> getMethodsHandler() override;
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
	void initUIElementBase(QMap<QString, IReferenceInstancePtr> instances = {}, QMap<QString, IReferenceInstancesListPtr> instancesLists = {});
	
public slots:
	void openLink(uid_t referenceUID);
	void closeLink(uid_t referenceUID);
	void closeSelf();
	
signals:
	void linkOpened(uid_t selfUID, uid_t referenceUID);
	void linkClosed(uid_t selfUID, uid_t referenceUID);
	void selfClosed(uid_t selfUID);
	
private:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(QString link);


#ifdef QML_UIElement
	// QWidget interface
protected:
	void resizeEvent(QResizeEvent *event) override;
#endif
	
protected:
	QPointer<QObject> m_parentObject;
	IPlugin* m_pluginBase;
	QStringList m_linkNames;
	QIcon m_icon;
	QSharedPointer<UIElementLinksHandler> m_linksHandler;
	QSharedPointer<MethodsHandler> m_methodsHandler;
	QSharedPointer<UIElementBaseSignal> m_uiElementBaseSignal;
	bool m_isOpened;
};

//! \}
