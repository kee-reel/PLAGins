#include "uielementbase.h"

UIElementBase::UIElementBase(QObject *parentObject, QWidget *parentWidget) :
    m_parentObject(parentObject),
    m_parentWidget(parentWidget)
{
}

UIElementBase::~UIElementBase()
{
}

QWeakPointer<IUIElementDescriptor> UIElementBase::initUIElement(uid_t uid, QWeakPointer<QJsonObject> meta)
{
    m_selfDescriptor = UIElementDescriptor::make(uid, meta);
    return m_selfDescriptor;
}

QWeakPointer<IUIElementDescriptor> UIElementBase::getDescriptor()
{
    return m_selfDescriptor;
}

bool UIElementBase::finiUIElement()
{
    m_selfDescriptor = nullptr;
    return true;
}

QWeakPointer<QMap<QString, count_t> > UIElementBase::getLinks()
{
    return m_selfDescriptor->links();
}

void UIElementBase::setLinks(QString linkName, QList<QWeakPointer<IUIElementDescriptor> > elements)
{
    m_links[linkName] = elements;
}

void UIElementBase::removeLinks(QString linkName)
{

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
