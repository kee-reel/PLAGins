#include "uimanager.h"

UIManager::UIManager() :
    QObject(nullptr),
    Service::CoreServiceBase(this, {INTERFACE(Service::ICoreService)}, {}),
    m_pluginLinker(nullptr),
    m_parentWidget(nullptr),
    m_lastGeneratedUID(1),
    m_rootElementUID(0)
{
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
            onCloseSelf(getActive()->m_element);
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

void UIManager::onServiceManagerInitialized()
{
    auto appServices = getServices("IApplication");
    if(appServices.isNull())
    {
        qCritical() << "No IApplication service found";
        return;
    }

    for(auto& service : *appServices.data())
    {
        IApplication* app = castToInterface<IApplication>(service->getObject());
        m_parentWidget = app->getParentWidget();
    }

    auto linkerServices = getServices("IPluginLinker");
    if(linkerServices.isNull())
    {
        qCritical() << "No IPluginLinker service found";
        return;
    }

    auto pluginLinker = castToInterface<IPluginLinker>(linkerServices.data()->last()->getObject());
    auto items = pluginLinker->getItemsWithInterface("IUIElement");
    for(auto item : *items.data())
    {
        pluginLinker->loadPlugin(item.data()->uid());
        auto element = castToInterface<IUIElement>(item.data()->object());
        registerUIElement(element, item.data()->meta());
    }

    for(auto element : m_elementsMap)
    {
        auto&& references = element.data()->m_element->getLinks().data();
        for(auto referenceIter = references->begin(); referenceIter != references->end(); ++referenceIter)
        {
            auto elementsIter = m_elementLinksByNameMap.find(referenceIter.key());
            if(elementsIter != m_elementLinksByNameMap.end())
            {
                auto&& elementsList = elementsIter.value();
                auto referencesCount = referenceIter.value();
                auto elementsCount = static_cast<uid_t>(elementsList->count());
                if(referencesCount == 0 || referencesCount == elementsCount)
                {
                    element->m_element->setLinks(elementsIter.key(), *elementsList.data());
                }
                else if(referencesCount < elementsCount)
                {
                    QList<QWeakPointer<IUIElementDescriptor>> list;
                    // TODO: Add picking of references.
                    for(uid_t i = 0; i < referencesCount; ++i)
                    {
                        list.append(elementsList->at(static_cast<int>(i)));
                    }
                }
                else
                {
                    qWarning() << "Not enough UI elements: need" << referencesCount << "has:" << elementsCount;
                }
            }
        }
    }

    auto element = m_elementsMap[m_rootElementUID];
    onOpenLink(element->m_element, element->m_elementDescr);
}

void UIManager::onOpenLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link)
{
    if(!m_elementsStack.isEmpty() && self != getActive()->m_element)
    {
        return;
    }

    auto iter = m_elementsMap.find(link.data()->uid());
    if(iter == m_elementsMap.end())
    {
        return;
    }

    auto descr = iter.key();
    auto element = iter.value();
//    log(SeverityType::INFO, QString("Push window: %1").arg(uiElement->getNodeName()));

    if (!m_elementsStack.isEmpty())
    {
        getActive()->m_element->close();
    }

    m_elementsStack.append(descr);
    m_parentWidget->layout()->addWidget(element->m_element->getWidget());
    element->m_element->open(m_parentWidget);
}

void UIManager::onCloseLink(IUIElement* self, QWeakPointer<IUIElementDescriptor> link)
{
    if(self != getActive()->m_element)
    {
        return;
    }

    auto iter = m_elementsMap.find(link.data()->uid());
    if(iter == m_elementsMap.end())
    {
        return;
    }
//    log(SeverityType::INFO, QString("Pop window: %1").arg(uiElement->getNodeName()));
    onCloseSelf(iter.value()->m_element);
}

void UIManager::onCloseSelf(IUIElement* self)
{
    if (m_elementsStack.count() > 1)
    {
        getActive()->m_element->close();
        m_elementsStack.removeLast();
        getActive()->m_element->open(m_parentWidget);
    }
    else
    {
        QApplication::exit();
    }
}

bool UIManager::registerUIElement(IUIElement* uiElement, QWeakPointer<QJsonObject> meta)
{
    const auto &object = uiElement->getObject();
    if(!object)
    {
        qCritical() << "UIManager::addChildItem: skip element adding: no QObject available";
        return false;
    }


    auto elementDescr = uiElement->initUIElement(m_lastGeneratedUID, meta);
    auto&& elementHandler = QSharedPointer<UIElementHandler>(
                new UIElementHandler({uiElement, elementDescr}));
    m_elementsMap[m_lastGeneratedUID] = elementHandler;

    if(m_rootElementUID == 0)
        m_rootElementUID = m_lastGeneratedUID;
    ++m_lastGeneratedUID;

    auto key = elementHandler->m_elementDescr.data()->linkKey();
    auto iter = m_elementLinksByNameMap.find(key);
    if(iter != m_elementLinksByNameMap.end())
    {
        iter.value()->append(elementDescr);
    }
    else
    {
        auto list = new QList<QWeakPointer<IUIElementDescriptor>>();
        list->append(elementDescr);
        m_elementLinksByNameMap[key].reset(list);
    }

    connect(object, SIGNAL(openLink(IUIElement*, QWeakPointer<IUIElementDescriptor>)),
            this, SLOT(onOpenLink(IUIElement*, QWeakPointer<IUIElementDescriptor>)));

    connect(object, SIGNAL(closeLink(IUIElement*, QWeakPointer<IUIElementDescriptor>)),
            this, SLOT(onCloseLink(IUIElement*, QWeakPointer<IUIElementDescriptor>)));

    connect(object, SIGNAL(closeSelf(IUIElement*)), this, SLOT(onCloseSelf(IUIElement*)));

    return true;
}
