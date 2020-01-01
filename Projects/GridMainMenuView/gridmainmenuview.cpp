#include "gridmainmenuview.h"

#include <QMessageBox>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QGuiApplication>
#include <QScreen>
#include <QDesktopWidget>

GridMainMenuView::GridMainMenuView() :
	QQuickWidget (nullptr),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenu"})
{
	initPluginBase();
	m_elements.reset(new ReferenceInstancesList<IUIElement>());
	initUIElementBase({}, { 
						  {"MainMenuItem", m_elements}
					  });
	this->rootContext()->setContextProperty("elements", m_elements.data());
	this->rootContext()->setContextProperty("links", m_opener.data());
	
	connect(m_elements.data(), &ReferenceInstancesList<IUIElement>::instancesChanged, [=](){
		QMetaObject::invokeMethod(this->rootObject(), "recreateMenuItems");
	});
	setRatio();
	this->setResizeMode(QQuickWidget::SizeRootObjectToView);
	this->setSource(QUrl("qrc:/Menu.qml"));
}

GridMainMenuView::~GridMainMenuView()
{
	
}

void GridMainMenuView::onPluginInited()
{
	resetDescriptor(descr());
}

void GridMainMenuView::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Close",
																tr("Are you sure?\n"),
																QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
																QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes)
	{
		event->ignore();
	}
	else
	{
		event->accept();
	}
}

void GridMainMenuView::setRatio()
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
	qDebug() << "setRatio" << rect << dpi << ratio << ratioFont;
}

void GridMainMenuView::resizeEvent(QResizeEvent *event)
{
	setRatio();
	return QQuickWidget::resizeEvent(event);
}
