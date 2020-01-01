#include "uielementlinkshandler.h"

UIElementLinksHandler::UIElementLinksHandler(QMap<QString, IReferenceInstancePtr> instances, QMap<QString, IReferenceInstancesListPtr> instancesLists) :
	QObject(nullptr),
	ReferencesHandler<QString>(instances, instancesLists)
{
	checkReferencesUpdate();
}

void UIElementLinksHandler::setState(ReferencesHandlerState state)
{
	if(m_state != state)
	{
		m_state = state;
		emit onStateChanged(state);
	}	
}

void UIElementLinksHandler::referencesListUpdated(QString link)
{
	emit onReferencesListUpdated(link);
}
