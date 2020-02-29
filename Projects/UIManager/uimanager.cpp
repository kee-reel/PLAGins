#include "uimanager.h"

#include <QApplication>
#include <QKeyEvent>
#include <QLayout>

UIManager::UIManager() :
	QObject(nullptr),
	PluginBase(this),
	m_parentWidget(nullptr),
	m_rootElementUID(0)
{
	m_uiElementsList.reset(new ReferenceInstancesList<IUIElement>());
	initPluginBase(
	{
		{INTERFACE(IPlugin), this}
	},
	{
		{INTERFACE(IApplication), m_app},
		{INTERFACE(IPluginLinker), m_pluginLinker}
	},
	{
		{INTERFACE(IUIElement), m_uiElementsList}
	});
}

UIManager::~UIManager()
{
}

bool UIManager::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		
		if (keyEvent->key() == Qt::Key_Back)
		{
			onCloseSelf(getActiveElementUID());
			return true;
		}
	}
	
	return QObject::eventFilter(watched, event);
}

void UIManager::onReferencesListUpdated(Interface interface)
{
	Q_UNUSED(interface)
	m_parentWidget = m_app->getParentWidget();
	Q_ASSERT_X(m_parentWidget, "UIManager initialization", "parent widget is null");
	
	m_parentWidget->installEventFilter(this);
	m_parentWidget->layout()->setMargin(0);
	
	QList<quint32> removedElements = m_elementsMap.keys();
	for(auto uiElement : *m_uiElementsList)
	{
		auto uid = uiElement.reference()->descr().toStrongRef()->uid();
		if(!m_elementsMap.contains(uid))
		{
			registerUIElement(uiElement);
		}
		removedElements.removeOne(uid);
	}
	
	for(auto uid : removedElements)
	{
		unregisterUIElement(uid);
	}
	
	for(auto element : m_elementsMap)
	{
		auto&& linksHandler = element->getLinksHandler();
		auto references = linksHandler.toStrongRef()->requiredReferences();
		for(auto referenceIter = references.begin(); referenceIter != references.end(); ++referenceIter)
		{
			auto elementsIter = m_elementLinksByNameMap.find(referenceIter.key());
			QList<IReferenceDescriptorPtr> list;
			if(elementsIter != m_elementLinksByNameMap.end())
			{
				auto&& elementIdsList = elementsIter.value();
				auto referencesCount = referenceIter.value();
				auto elementsCount = elementIdsList.count();
				if(referencesCount == 0 || referencesCount == elementsCount)
				{
					for(auto& elementId : elementIdsList)
					{
						list.append(m_elementsMap[elementId].reference()->descr());
					}
				}
				else if(referencesCount < elementsCount)
				{
					// TODO: Add picking of references.
					for(int i = 0; i < referencesCount; ++i)
					{
						list.append(m_elementsMap[elementIdsList[i]].reference()->descr());
					}
				}
				else
				{
					qWarning() << "Not enough UI elements: need" << referencesCount << "has:" << elementsCount;
				}
				linksHandler.toStrongRef()->setReferences(elementsIter.key(), list);
			}
		}
	}
	
	while(m_elementsStack.count() > 1)
	{
		onCloseSelf(getActiveElementUID());
	}
	
	if(!m_elementsMap.isEmpty())
	{
		onOpenLink(m_rootElementUID, m_rootElementUID);
	}
}

void UIManager::onOpenLink(quint32 selfUID, quint32 referenceUID)
{
	if(!m_elementsStack.isEmpty() && referenceUID == getActiveElementUID())
	{
		return;
	}
	
	auto iter = m_elementsMap.find(referenceUID);
	if(iter == m_elementsMap.end())
	{
		return;
	}
	
	auto descr = iter.key();
	auto element = iter.value();
	//    log(SeverityType::INFO, QString("Push window: %1").arg(uiElement->getNodeName()));
	
	if (!m_elementsStack.isEmpty())
	{
		getActiveElement()->close();
	}
	
	m_elementsStack.append(descr);
	m_parentWidget->layout()->addWidget(element->getWidget());
	element->open(m_parentWidget);
}

void UIManager::onCloseLink(quint32 selfUID, quint32 referenceUID)
{
	if(selfUID != getActiveElementUID())
	{
		return;
	}
	
	auto iter = m_elementsMap.find(referenceUID);
	if(iter == m_elementsMap.end())
	{
		return;
	}
	//    log(SeverityType::INFO, QString("Pop window: %1").arg(uiElement->getNodeName()));
	onCloseSelf(iter.value()->getUID());
}

void UIManager::onCloseSelf(quint32 selfUID)
{
	Q_ASSERT(selfUID == getActiveElementUID());
	if (m_elementsStack.count() > 1)
	{
		auto element = getActiveElement();
		element->close();
		
		m_elementsStack.removeLast();
		getActiveElement()->open(m_parentWidget);
	}
	else
	{
		QApplication::exit();
	}
}

bool UIManager::registerUIElement(ReferenceInstancePtr<IUIElement> &uiElement)
{
	const auto &object = uiElement.data()->object();
	if(!object)
	{
		qCritical() << "UIManager::addChildItem: skip element adding: no QObject available";
		return false;
	}
	
	auto uid = uiElement.reference()->descr().toStrongRef()->uid();
	m_elementsMap[uid] = uiElement;
	auto linkNames = uiElement->linkNames();
	for(auto& linkName : linkNames)
	{
		auto& elements = m_elementLinksByNameMap[linkName];
		elements.append(uid);
	}
	
	if(linkNames.contains("MainMenu"))
	{
		m_rootElementUID = uid;	
	}
	
	connect(object, SIGNAL(linkOpened(quint32, quint32)), this, SLOT(onOpenLink(quint32, quint32)));
	connect(object, SIGNAL(linkClosed(quint32, quint32)), this, SLOT(onCloseLink(quint32, quint32)));
	connect(object, SIGNAL(selfClosed(quint32)), this, SLOT(onCloseSelf(quint32)));
	return true;
}

bool UIManager::unregisterUIElement(quint32 uid)
{
	auto uiElementIter = m_elementsMap.find(uid);
	if(uiElementIter == m_elementsMap.end())
	{
		return true;
	}
	
	m_elementsMap.remove(uid);
	m_elementsStack.removeOne(uid);
	auto uiElement = uiElementIter.value();
	for(auto& linksList : m_elementLinksByNameMap)
	{
		linksList.removeOne(uid);
	}
	return true;
}
