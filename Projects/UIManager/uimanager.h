#pragma once


#include <QtCore>
#include <QWidget>


#include "../../../Application/Interfaces/iapplication.h"
#include "../../Interfaces/Architecture/iuielement.h"
#include "../../Interfaces/Middleware/ipluginlinker.h"
#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

//! \addtogroup UIManager_imp
//!  \{
class UIManager : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(
	    IPlugin
	)

public:
	UIManager();
	virtual ~UIManager() override;

	// QObject interface
public:
	bool eventFilter(QObject *watched, QEvent *event) override;

	// PluginBase interface
public:
	virtual void onReferencesListUpdated(Interface interface) override;

signals:
	void onPop();

private slots:
	void onOpenLink(quint32 selfUID, quint32 referenceUID);
	void onCloseLink(quint32 selfUID, quint32 referenceUID);
	void onCloseSelf(quint32 selfUID);

private:
	bool registerUIElement(ReferenceInstancePtr<IUIElement>& uiElement);
	bool unregisterUIElement(quint32 uid);
	inline quint32 getActiveElementUID()
	{
		return m_elementsStack.last();
	}
	inline ReferenceInstancePtr<IUIElement>& getActiveElement()
	{
		return m_elementsMap[getActiveElementUID()];
	}

private:
	ReferenceInstancePtr<IApplication> m_app;
	ReferenceInstancePtr<IPluginLinker> m_pluginLinker;
	ReferenceInstancesListPtr<IUIElement> m_uiElementsList;
	QWidget *m_parentWidget;
	quint32 m_rootElementUID;

	QList<quint32> m_elementsStack;
	QMap<quint32, ReferenceInstancePtr<IUIElement> > m_elementsMap;
	QMap<QString, QList<quint32> > m_elementLinksByNameMap;
};
//!  \}

