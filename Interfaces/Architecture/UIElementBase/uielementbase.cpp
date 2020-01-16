#include "uielementbase.h"

UIElementBase::UIElementBase(QObject *parentObject, QWidget *parentWidget, QStringList linkNames, QIcon icon) :
	m_parentObject(parentObject),
	m_parentWidget(parentWidget),
	m_linkNames(linkNames),
	m_icon(icon),
	m_isOpened(false)
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
	return m_descriptor.toStrongRef()->uid();
}

QStringList UIElementBase::linkNames()
{
	return m_linkNames;
}

QWidget *UIElementBase::getWidget()
{
	return m_parentWidget;
}

QIcon UIElementBase::getIcon()
{
	return m_icon;
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
