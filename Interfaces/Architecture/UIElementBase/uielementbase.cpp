#include "uielementbase.h"

UIElementBase::UIElementBase(QObject *parentObject, QWidget *parentWidget, QStringList linkNames) :
	m_parentObject(parentObject),
	m_parentWidget(parentWidget),
	m_linkNames(linkNames)
{
}

void UIElementBase::initUIElement(QMap<QString, IReferenceInstancePtr > instances,
                                  QMap<QString, IReferenceInstancesListPtr > instancesLists)
{
	m_methodsHandler.reset(new MethodsHandler(m_parentObject));
	m_linksHandler.reset(new UIElementLinksHandler(instances, instancesLists));
}

UIElementBase::~UIElementBase()
{
}

QWeakPointer<IUIElementLinksHandler> UIElementBase::getLinksHandler()
{
	return m_linksHandler;
}

QWeakPointer<IMethodsHandler> UIElementBase::getMethodsHandler()
{
	return m_methodsHandler;
}

uid_t UIElementBase::getUID()
{
	return m_descriptor.data()->uid();
}

QStringList UIElementBase::linkNames()
{
	return m_linkNames;
}

QObject *UIElementBase::getObject()
{
	return m_parentObject;
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

void UIElementBase::resetDescriptor(IReferenceDescriptorPtr descriptor)
{
	m_descriptor = descriptor;
}
