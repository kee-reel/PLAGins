#include "uielementbase.h"

UIElementBase::UIElementBase(QObject *parentObject, QStringList linkNames, QIcon icon) :
	UIElementBaseParent(nullptr),
	m_parentObject(parentObject),
	m_pluginBase(qobject_cast<IPlugin*>(parentObject)),
	m_linkNames(linkNames),
	m_icon(icon),
	m_isOpened(false)
{
	UIElementBaseParent::close();
}

void UIElementBase::initUIElementBase(QMap<QString, IReferenceInstancePtr > instances,
        QMap<QString, IReferenceInstancesListPtr > instancesLists)
{
	m_linksHandler.reset(new UIElementLinksHandler(instances, instancesLists));
	connect(m_linksHandler.data(), &UIElementLinksHandler::onStateChanged, this, &UIElementBase::onStateChanged);
	connect(m_linksHandler.data(), &UIElementLinksHandler::onReferencesListUpdated, this, &UIElementBase::onReferencesListUpdated);

#ifdef QML_UIElement
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	rootContext()->setContextProperty("uiElement", this);
#endif
}

void UIElementBase::openLink(quint32 referenceUID)
{
	emit linkOpened(m_pluginBase->getDescriptor().toStrongRef()->uid(), referenceUID);
}

void UIElementBase::closeLink(quint32 referenceUID)
{
	emit linkClosed(m_pluginBase->getDescriptor().toStrongRef()->uid(), referenceUID);
}

void UIElementBase::closeSelf()
{
	emit selfClosed(m_pluginBase->getDescriptor().toStrongRef()->uid());
}

QWeakPointer<IReferencesHandler<QString> > UIElementBase::getLinksHandler()
{
	return m_linksHandler;
}

quint32 UIElementBase::getUID()
{
	return m_pluginBase->getDescriptor().toStrongRef()->uid();
}

QStringList UIElementBase::linkNames()
{
	return m_linkNames;
}

QWidget *UIElementBase::getWidget()
{
	return this;
}

QIcon UIElementBase::getIcon()
{
	return m_icon;
}

bool UIElementBase::open(QWidget* parent)
{
	if(!m_isOpened)
	{
		this->setParent(parent);
		this->show();
		m_isOpened = true;
	}
	return true;
}

bool UIElementBase::close()
{
	if(m_isOpened)
	{
		this->hide();
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

#ifdef QML_UIElement

#include <QScreen>
#include <QQmlEngine>
#include <QQuickItem>
#include <QGuiApplication>

void UIElementBase::resizeEvent(QResizeEvent *event)
{
	qreal refDpi = 102.;
	qreal refWidth = 540.;
	qreal refHeight = 960.;
	QRect rect = this->rect();
	qreal height = qMax(rect.width(), rect.height());
	qreal width = qMin(rect.width(), rect.height());
	qreal dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
	qreal ratio = qMin(height/refHeight, width/refWidth);
	qreal ratioFont = qMin(height*dpi/(refDpi*refHeight), width*dpi/(refDpi*refWidth));
	this->rootContext()->setContextProperty("ratio", ratio);
	this->rootContext()->setContextProperty("ratioFont", ratioFont);
	return UIElementBaseParent::resizeEvent(event);
}
#endif
