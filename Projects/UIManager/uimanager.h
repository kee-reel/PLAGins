#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QtCore>
#include <QWidget>


#include "../../../Application/iapplication.h"
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
	virtual void onPluginReferencesListUpdated(Interface interface) override;

signals:
	void onPop();

private slots:
	void onOpenLink(uid_t selfUID, uid_t referenceUID);
	void onCloseLink(uid_t selfUID, uid_t referenceUID);
	void onCloseSelf(uid_t selfUID);

private:
	bool registerUIElement(ReferenceInstancePtr<IUIElement>& uiElement);
	bool unregisterUIElement(uid_t uid);
	inline uid_t getActiveElementUID()
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
	uid_t m_rootElementUID;

	QList<uid_t> m_elementsStack;
	QMap<uid_t, ReferenceInstancePtr<IUIElement> > m_elementsMap;
	QMap<QString, QList<uid_t> > m_elementLinksByNameMap;
};
//!  \}
#endif // UIMANAGER_H
