#include "gridmainmenuview.h"
#include "ui_form.h"

#include <QMessageBox>

GridMainMenuView::GridMainMenuView() :
	QWidget (nullptr),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenu"}),
	ui(new Ui::Form),
	m_uniqueIdCounter(0),
	m_exitItem(nullptr)
{
	ui->setupUi(this);
	layout = new AspectAwareGridLayout(this);
	ui->scrollAreaWidgetContents->setLayout(layout);
#ifdef Q_OS_ANDROID
	ui->scrollArea->grabGesture(Qt::TapAndHoldGesture);
	QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
#endif
	referencesInit();
	m_elements.reset(new ReferenceInstancesList<IUIElement>());
	initUIElement({}, { 
		{"MainMenuItems", m_elements}
	});
}

GridMainMenuView::~GridMainMenuView()
{
	
}

void GridMainMenuView::onReady()
{
	resetDescriptor(getDescriptor());
	installMenuElements();
}

void GridMainMenuView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	//    container->resize(size());
}

void GridMainMenuView::UniqueButtonPressed(UniquePushButton *button)
{
	if(button == m_exitItem)
	{
		emit closeSelf(this);
	}
	else
	{
		emit openLink(this, "MainMenuItem", button->getId());
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
		
		for(const auto &menuItem : *m_elements)
		{
			auto descr = menuItem->descr().data();
			UniquePushButton *uniqueButton = new UniquePushButton(descr->uid(), FormatMenuItemName(descr->name()), this);
			uniqueButton->setMinimumHeight(itemMinHeight);
			connect(uniqueButton, SIGNAL(OnMenuItemSelected(UniquePushButton *)), SLOT(UniqueButtonPressed(UniquePushButton *)));
			m_uniqueButtons.append(uniqueButton);
			layout->addWidget(uniqueButton);// j/rowCapacity, j%rowCapacity);
		}
	}
#ifndef Q_OS_ANDROID
	QSpacerItem *bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	layout->addItem(bottomSpacer);
	
	UniquePushButton *exitItem = new UniquePushButton(PredefinedIndices::EXIT, "Exit", this);
	m_exitItem = exitItem;
	connect(exitItem, SIGNAL(OnMenuItemSelected(UniquePushButton *)), SLOT(UniqueButtonPressed(UniquePushButton *)));
	m_uniqueButtons.append(exitItem);
	layout->addWidget(exitItem);
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
