#pragma once

#include <QtCore>
#include <QIcon>

#include "iguielement.h"
#include "../Plugin/iplugin.h"
#include "../Plugin/referenceshandler.h"
#include "guielementlinkshandler.h"


#ifdef QML_UIElement
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWidget>
#define GUIElementBaseParent QQuickWidget
#endif

#ifdef QWidget_UIElement
#include <QWidget>
#define GUIElementBaseParent QWidget
#endif

class GUIElementBase : public GUIElementBaseParent, public IGUIElement
{
	friend class GUIElementBaseSignal;
	Q_OBJECT
	Q_INTERFACES(IGUIElement)
public:
#ifdef QML_UIElement
	GUIElementBase(QObject* parentObject, QStringList linkNames, QString mainFileName=QString());
#else
	GUIElementBase(QObject* parentObject, QStringList linkNames);
#endif
	~GUIElementBase() override = default;

	// IGUIElement interface
public slots:
	QWeakPointer<IReferencesHandler<QString>> getLinksHandler() override;

	quint32 getUID() override;
	QStringList linkNames() override;
	QWidget *getWidget() override;

	bool open(QWidget *parent) override;
	bool close() override;
	bool isOpened() const override;

signals:
	void onOpened();

public:
	virtual void onUIElementReferencesSet() {}
	virtual void onUIElementReady() {}
	virtual void onUIElementReferencesListUpdated(QString link) {Q_UNUSED(link)}
	void initGUIElementBase(
#ifdef QML_UIElement
		QMap<QString, QObject*> references = {},
#endif		
		QMap<QString, IReferenceInstancePtr> instances = {},
		QMap<QString, IReferenceInstancesListPtr> instancesLists = {}
	);

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
	GUIElementBase* m_instance;
	QWeakPointer<UIElementLinksHandler> m_handler;


#ifdef QML_UIElement
	// QWidget interface
protected:
	void resizeEvent(QResizeEvent *event) override;
protected:
	QString m_mainFileName;
#endif

protected:
	QPointer<QObject> m_parentObject;
	IPlugin* m_pluginBase;
	QStringList m_linkNames;
	QSharedPointer<UIElementLinksHandler> m_linksHandler;
	bool m_isOpened;
};

//! \}
