#include "uimanager.h"

#include <QApplication>
#include <QKeyEvent>
#include <QLayout>

UIManager::UIManager() :
	QObject(nullptr),
	PluginBase(this, {}),
           m_parentWidget(nullptr),
           m_rootElementUID(0)
{
	m_uiElementsList.reset(new ReferenceInstancesList<IUIElement>());
	referencesInit(
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
	if (event->type() == QEvent::KeyRelease)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

		if (keyEvent->key() == Qt::Key_Back)
		{
			onCloseSelf(getActive().data()->instance());
			return true;
		}
	}

	return QObject::eventFilter(watched, event);
}

void UIManager::onReady()
{
	m_parentWidget = m_app->instance()->getParentWidget();

	for(auto item : *m_uiElementsList.data())
	{
		registerUIElement(item);
	}

	for(auto element : m_elementsMap)
	{
		auto&& linksHandler = element.data()->instance()->getLinksHandler();
		auto references = linksHandler.data()->requiredReferences();
		for(auto referenceIter = references.begin(); referenceIter != references.end(); ++referenceIter)
		{
			auto elementsIter = m_elementLinksByNameMap.find(referenceIter.key());
			QList<IReferenceDescriptorPtr> list;
			if(elementsIter != m_elementLinksByNameMap.end())
			{
				auto&& elementsList = elementsIter.value();
				auto referencesCount = referenceIter.value();
				auto elementsCount = elementsList.count();
				if(referencesCount == 0 || referencesCount == elementsCount)
				{
					for(auto& element : elementsList)
					{
						list.append(element.data()->descr());
					}
				}
				else if(referencesCount < elementsCount)
				{
					// TODO: Add picking of references.
					for(int i = 0; i < referencesCount; ++i)
					{
						list.append(elementsList[i].data()->descr());
					}
				}
				else
				{
					qWarning() << "Not enough UI elements: need" << referencesCount << "has:" << elementsCount;
				}
				linksHandler.data()->setReferences(elementsIter.key(), list);
			}
		}
	}

	if(!m_elementsMap.isEmpty())
	{
		auto element = m_elementsMap[m_rootElementUID];
		auto instance = element.data()->instance();
		onOpenLink(instance, instance->linkNames()[0], instance->getUID());
	}
}

void UIManager::onOpenLink(IUIElement* self, QString linkName, uid_t referenceUID)
{
	if(!m_elementsStack.isEmpty() && self != getActive().data()->instance())
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
		getActive().data()->instance()->close();
	}

	m_elementsStack.append(descr);
	m_parentWidget->layout()->addWidget(element.data()->instance()->getWidget());
	element.data()->instance()->open(m_parentWidget);
}

void UIManager::onCloseLink(IUIElement* self, QString linkName, uid_t referenceUID)
{
	if(self != getActive().data()->instance())
	{
		return;
	}

	auto iter = m_elementsMap.find(referenceUID);
	if(iter == m_elementsMap.end())
	{
		return;
	}
//    log(SeverityType::INFO, QString("Pop window: %1").arg(uiElement->getNodeName()));
	onCloseSelf(iter.value().data()->instance());
}

void UIManager::onCloseSelf(IUIElement* self)
{
	if (m_elementsStack.count() > 1)
	{
		getActive().data()->instance()->close();
		m_elementsStack.removeLast();
		getActive().data()->instance()->open(m_parentWidget);
	}
	else
	{
		QApplication::exit();
	}
}

bool UIManager::registerUIElement(ReferenceInstancePtr<IUIElement> &uiElement)
{
	const auto &object = uiElement->instance()->getObject();
	if(!object)
	{
		qCritical() << "UIManager::addChildItem: skip element adding: no QObject available";
		return false;
	}

	auto uid = uiElement->descr().data()->uid();
	m_elementsMap[uid] = uiElement;
	m_rootElementUID = uid;

	auto linkNames = uiElement->instance()->linkNames();
	for(auto& linkName : linkNames)
	{
		auto elements = m_elementLinksByNameMap[linkName];
		elements.append(uiElement);
	}

	connect(object, SIGNAL(openLink(IUIElement*, QString, uid_t)), this, SLOT(onOpenLink(IUIElement*, QString, uid_t)));
	connect(object, SIGNAL(closeLink(IUIElement*, QString, uid_t)), this, SLOT(onCloseLink(IUIElement*, QString, uid_t)));
	connect(object, SIGNAL(closeSelf(IUIElement*)), this, SLOT(onCloseSelf(IUIElement*)));
	return true;
}
