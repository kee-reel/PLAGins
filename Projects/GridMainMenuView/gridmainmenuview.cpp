#include "gridmainmenuview.h"
#include "ui_form.h"

#include <QMessageBox>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlListProperty>

GridMainMenuView::GridMainMenuView() :
	QQuickWidget (nullptr),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenu"}),
	ui(new Ui::Form),
	m_exitItem(nullptr)
{
	//ui->setupUi(this);
	//layout = new AspectAwareGridLayout(this);
	//ui->scrollAreaWidgetContents->setLayout(layout);
#ifdef Q_OS_ANDROID
	ui->scrollArea->grabGesture(Qt::TapAndHoldGesture);
	QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
#endif
	initPluginBase();
	m_elements.reset(new ReferenceInstancesList<IUIElement>());
	initUIElementBase({}, { 
						  {"MainMenuItem", m_elements}
					  });
	//installMenuElements();
//	qmlRegisterInterface<IBackEnd>("IBackEnd");
	m_backEnd.reset(new BackEnd);
//	qmlRegisterUncreatableType<IBackEnd>("io.qt.examples.backEnd", 1, 0, "BackEnd", "You can't create it");
//	connect(&m_timer, &QTimer::timeout, this, &GridMainMenuView::onTimer);
//	m_timer.start(3000);
	this->rootContext()->setContextProperty("backEnd", m_elements.data());
	this->rootContext()->setContextProperty("links", m_opener.data());
	setSource(QUrl("qrc:/Menu.qml"));
	show();
}

GridMainMenuView::~GridMainMenuView()
{
	
}

void GridMainMenuView::onPluginInited()
{
	resetDescriptor(descr());
}

void GridMainMenuView::onUIElementReferencesListUpdated(QString link)
{
	return;
	for(const auto &menuItem : *m_elements)
	{
		auto descr = menuItem->descr().data();
		auto uid = descr->uid();
		if(!m_uniqueButtons.contains(uid))
		{
			UniquePushButton *uniqueButton = new UniquePushButton(uid, FormatMenuItemName(descr->name()), this);
			uniqueButton->setMinimumHeight(50);
			connect(uniqueButton, SIGNAL(OnMenuItemSelected(UniquePushButton *)), SLOT(UniqueButtonPressed(UniquePushButton *)));
			m_uniqueButtons[uid] = uniqueButton;
			layout->addWidget(uniqueButton);// j/rowCapacity, j%rowCapacity);
		}
	}
//	auto button = m_uniqueButtons.begin();
//	while(button != m_uniqueButtons.end())
//	{
//		if(!m_elements->contains(button.key()))
//		{
		
//		}
//	}
}

void GridMainMenuView::resizeEvent(QResizeEvent *event)
{
	//	installMenuElements();
	QWidget::resizeEvent(event);
//	container->resize(size());
}

void GridMainMenuView::UniqueButtonPressed(UniquePushButton *button)
{
	if(button == m_exitItem)
	{
		m_opener->closeSelf();
	}
	else
	{
		m_opener->openLink(button->getId());
	}
}

QString GridMainMenuView::FormatMenuItemName(QString name)
{
	QRegExp regExp = QRegExp("([A-Z]+[a-z]+)");
	regExp.setCaseSensitivity(Qt::CaseSensitive);
	QStringList list;
	QString itemMenuName;
	int pos = regExp.indexIn(name, itemMenuName.length());
	while(pos >= 0)
	{
		itemMenuName.append(regExp.cap(0));
		pos = itemMenuName.length();
		pos = regExp.indexIn(name, itemMenuName.length());
	}
	return itemMenuName;
}

void GridMainMenuView::installMenuElements()
{
	if(m_elements->count() != 0)
	{
		int itemMinHeight = (height() / m_elements->count()) * 1.2;
		layout->setSpacing(itemMinHeight * 0.3);
		int rowCapacity = 1;
		QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
		layout->addItem(topSpacer);
	}
#ifndef Q_OS_ANDROID
	QSpacerItem *bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	layout->addItem(bottomSpacer);
	
	m_exitItem.reset(new UniquePushButton(0, "Exit", this));
	connect(m_exitItem.data(), SIGNAL(OnMenuItemSelected(UniquePushButton *)), SLOT(UniqueButtonPressed(UniquePushButton *)));
	layout->addWidget(m_exitItem.data());
#endif
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
