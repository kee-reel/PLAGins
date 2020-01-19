#include "gridmainmenuview.h"

GridMainMenuView::GridMainMenuView() :
	PluginBase(this),
	m_uiElementBase(new UIElementBase(this, {"MainMenu"}))
{
	initPluginBase(
	{
		{INTERFACE(IPlugin), this},
		{INTERFACE(IUIElement), m_uiElementBase}
	});
	m_elements.reset(new ReferenceInstancesList<IUIElement>());
	m_uiElementBase->initUIElementBase({}, { 
						  {"MainMenuItem", m_elements}
					  });
	m_uiElementBase->rootContext()->setContextProperty("elements", m_elements.data());
	m_uiElementBase->rootContext()->setContextProperty("uiElement", m_uiElementBase);
	
	connect(m_elements.data(), &ReferenceInstancesList<IUIElement>::instancesChanged, [=](){
		QMetaObject::invokeMethod(m_uiElementBase->rootObject(), "recreateMenuItems");
	});
	m_uiElementBase->setResizeMode(QQuickWidget::SizeRootObjectToView);
	m_uiElementBase->setSource(QUrl("qrc:/Menu.qml"));
}
