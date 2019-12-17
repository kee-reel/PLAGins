#include "uielementbase.h"

UIElementBase::UIElementBase(QObject *parentObject, QWidget *parentWidget, QStringList linkNames) :
	m_parentObject(parentObject),
	m_parentWidget(parentWidget),
	m_linkNames(linkNames)
{
	m_opener.reset(new UIElementLinksOpener(this));
}

void UIElementBase::initUIElementBase(QMap<QString, IReferenceInstancePtr > instances,
									  QMap<QString, IReferenceInstancesListPtr > instancesLists)
{
	m_methodsHandler.reset(new MethodsHandler(m_parentObject));
	m_linksHandler.reset(new UIElementLinksHandler(instances, instancesLists));
	m_uiElementBaseSignal.reset(new UIElementBaseSignal(this, m_linksHandler));
}

UIElementBase::~UIElementBase()
{
}

QWeakPointer<IReferencesHandler<QString> > UIElementBase::getLinksHandler()
{
	return m_linksHandler;
}

QWeakPointer<IMethodsHandler> UIElementBase::getMethodsHandler()
{
	return m_methodsHandler;
}

QWeakPointer<IUIElementLinksOpener> UIElementBase::getLinksOpener()
{
	return m_opener;
}

uid_t UIElementBase::getUID()
{
	return m_descriptor.data()->uid();
}

QStringList UIElementBase::linkNames()
{
	return m_linkNames;
}

QWidget *UIElementBase::getWidget()
{
	return m_parentWidget;
}

bool UIElementBase::open(QWidget* parent)
{
	if(!m_isOpened)
	{
		m_parentWidget->setParent(parent);
		m_parentWidget->show();
		m_isOpened = true;
	}
	return true;
}

bool UIElementBase::close()
{
	if(m_isOpened)
	{
		m_parentWidget->hide();
		m_isOpened = false;
	}
	return true;
}

bool UIElementBase::isOpened() const
{
	return m_isOpened;
}

void UIElementBase::onStateChanged(ReferencesHandlerState state)
{
	switch (state)
	{
		case ReferencesHandlerState::SETTING_REFS:
			break;
		case ReferencesHandlerState::WAITING:
			onUIElementReferencesSet();
			break;
		case ReferencesHandlerState::READY:
			onUIElementReady();
			break;
	}
}

void UIElementBase::onReferencesListUpdated(QString link)
{
	onUIElementReferencesListUpdated(link);
}

void UIElementBase::resetDescriptor(IReferenceDescriptorPtr descriptor)
{
	m_descriptor = descriptor;
}

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
