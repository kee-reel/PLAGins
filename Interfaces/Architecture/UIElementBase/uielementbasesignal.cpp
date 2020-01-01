#include "uielementbasesignal.h"

#include "../../Interfaces/Architecture/referenceshandler.h"
#include "uielementbase.h"
#include "uielementlinkshandler.h"

UIElementBaseSignal::UIElementBaseSignal(UIElementBase *instance, QWeakPointer<UIElementLinksHandler> handler) :
	QObject(), m_instance(instance), m_handler(handler)
{
	connect(m_handler.data(), &UIElementLinksHandler::onStateChanged, this, &UIElementBaseSignal::onStateChanged);
	connect(m_handler.data(), &UIElementLinksHandler::onReferencesListUpdated, this, &UIElementBaseSignal::onReferencesListUpdated);
}

void UIElementBaseSignal::onStateChanged(ReferencesHandlerState state)
{
	m_instance->onStateChanged(state);
}

void UIElementBaseSignal::onReferencesListUpdated(QString link)
{
	m_instance->onReferencesListUpdated(link);
}
