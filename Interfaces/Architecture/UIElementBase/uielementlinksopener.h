#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/iuielement.h"

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

//! \}
