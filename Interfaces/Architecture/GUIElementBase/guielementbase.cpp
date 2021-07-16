#include "guielementbase.h"

#ifdef QML_UIElement
GUIElementBase::GUIElementBase(QObject *parentObject, QStringList linkNames, QString mainFileName) :
#else
GUIElementBase::GUIElementBase(QObject *parentObject, QStringList linkNames) :
#endif
	GUIElementBaseParent(nullptr),
#ifdef QML_UIElement
	m_mainFileName(mainFileName),
#endif
	m_parentObject(parentObject),
	m_pluginBase(qobject_cast<IPlugin*>(parentObject)),
	m_linkNames(linkNames),
	m_isOpened(false)
{
	GUIElementBaseParent::close();
}

void GUIElementBase::initGUIElementBase(
#ifdef QML_UIElement
        QMap<QString, QObject*> references,
#endif
        QMap<QString, IReferenceInstancePtr > instances,
        QMap<QString, IReferenceInstancesListPtr > instancesLists)
{
	m_linksHandler.reset(new UIElementLinksHandler(instances, instancesLists));
	connect(m_linksHandler.data(), &UIElementLinksHandler::onStateChanged, this, &GUIElementBase::onStateChanged);
	connect(m_linksHandler.data(), &UIElementLinksHandler::onReferencesListUpdated, this, &GUIElementBase::onReferencesListUpdated);

#ifdef QML_UIElement
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	rootContext()->setContextProperty("uiElement", this);
	for(auto iter = references.begin(); iter != references.end(); ++iter)
	{
		rootContext()->setContextProperty(iter.key(), iter.value());
	}
	if(!m_mainFileName.isEmpty())
	{
		setSource(m_mainFileName);
	}
#endif
}

void GUIElementBase::openLink(quint32 referenceUID)
{
	emit linkOpened(m_pluginBase->getDescriptor().toStrongRef()->uid(), referenceUID);
}

void GUIElementBase::closeLink(quint32 referenceUID)
{
	emit linkClosed(m_pluginBase->getDescriptor().toStrongRef()->uid(), referenceUID);
}

void GUIElementBase::closeSelf()
{
	emit selfClosed(m_pluginBase->getDescriptor().toStrongRef()->uid());
}

QWeakPointer<IReferencesHandler<QString> > GUIElementBase::getLinksHandler()
{
	return m_linksHandler;
}

quint32 GUIElementBase::getUID()
{
	return m_pluginBase->getDescriptor().toStrongRef()->uid();
}

QStringList GUIElementBase::linkNames()
{
	return m_linkNames;
}

QWidget *GUIElementBase::getWidget()
{
	return this;
}

bool GUIElementBase::open(QWidget* parent)
{
	if(!m_isOpened)
	{
		this->setParent(parent);
		this->show();
		m_isOpened = true;
		emit onOpened();
	}
	return true;
}

bool GUIElementBase::close()
{
	if(m_isOpened)
	{
		this->hide();
		m_isOpened = false;
	}
	return true;
}

bool GUIElementBase::isOpened() const
{
	return m_isOpened;
}

void GUIElementBase::onStateChanged(ReferencesHandlerState state)
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
		auto links = m_linksHandler->references();
		for(auto iter = links.begin(); iter != links.end(); ++iter)
		{
			onReferencesListUpdated(iter.key());
		}
		break;
	}
}

void GUIElementBase::onReferencesListUpdated(QString link)
{
	onUIElementReferencesListUpdated(link);
}

#ifdef QML_UIElement

#include <QScreen>
#include <QQmlEngine>
#include <QQuickItem>
#include <QGuiApplication>

void GUIElementBase::resizeEvent(QResizeEvent *event)
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
	return GUIElementBaseParent::resizeEvent(event);
}
#endif
