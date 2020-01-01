#pragma once

#include <QtCore>

#include "../ireferenceshandler.h"

class UIElementBase;
class UIElementLinksHandler;
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

//! \}
