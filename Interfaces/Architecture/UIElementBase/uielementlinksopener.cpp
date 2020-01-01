#include "uielementlinksopener.h"

#include "uielementbase.h"
#include "methodshandler.h"

UIElementLinksOpener::UIElementLinksOpener(UIElementBase *instance) :
	m_instance(instance)
{
}

QObject *UIElementLinksOpener::getObject()
{
	return this;
}

void UIElementLinksOpener::openLink(uid_t referenceUID)
{
	emit linkOpened(m_instance->getUID(), referenceUID);
}

void UIElementLinksOpener::closeLink(uid_t referenceUID)
{
	emit linkClosed(m_instance->getUID(), referenceUID);
}

void UIElementLinksOpener::closeSelf()
{
	emit selfClosed(m_instance->getUID());
}
