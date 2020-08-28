#pragma once

#include <QtCore>
#include <QIcon>

#include "../../Interfaces/Architecture/iuielement.h"
#include "../../Interfaces/Architecture/iplugin.h"
#include "../../Interfaces/Architecture/referenceshandler.h"
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
	Q_INTERFACES(IUIElement)
public:
	UIElementBase(QObject* parentObject, QStringList linkNames, QIcon icon=QIcon());
	~UIElementBase() override = default;

	// IUIElement interface
public slots:
	QWeakPointer<IReferencesHandler<QString>> getLinksHandler() override;

	quint32 getUID() override;
	QStringList linkNames() override;
	QWidget *getWidget() override;
	QIcon getIcon() override;

	bool open(QWidget *parent) override;
	bool close() override;
	bool isOpened() const override;

signals:
	void onOpened();

public:
	virtual void onUIElementReferencesSet() {}
	virtual void onUIElementReady() {}
	virtual void onUIElementReferencesListUpdated(QString link) {Q_UNUSED(link)}
	void initUIElementBase(QMap<QString, IReferenceInstancePtr> instances = {}, QMap<QString, IReferenceInstancesListPtr> instancesLists = {});

public slots:
	void openLink(quint32 referenceUID);
	void closeLink(quint32 referenceUID);
	void closeSelf();

signals:
	void linkOpened(quint32 selfUID, quint32 referenceUID);
	void linkClosed(quint32 selfUID, quint32 referenceUID);
	void selfClosed(quint32 selfUID);

private:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(QString link);

private:
	UIElementBase* m_instance;
	QWeakPointer<UIElementLinksHandler> m_handler;


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
	bool m_isOpened;
};

//! \}
