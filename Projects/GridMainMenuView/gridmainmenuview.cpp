#include "gridmainmenuview.h"
#include "ui_form.h"

#include <QMessageBox>

GridMainMenuView::GridMainMenuView() :
    PluginBase(),
    m_uiManager(nullptr),
    m_uniqueIdCounter(0),
    m_exitItem(nullptr)
{
    layout = new AspectAwareGridLayout(this);
    ui->scrollAreaWidgetContents->setLayout(layout);
#ifdef Q_OS_ANDROID
    ui->scrollArea->grabGesture(Qt::TapAndHoldGesture);
    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
#endif
}

GridMainMenuView::~GridMainMenuView()
{

}

void GridMainMenuView::UniqueButtonPressed(UniquePushButton *button)
{
    if(button == m_exitItem)
    {
        close();
    }
    else
    {
        auto menuItem = m_uiElements[button->getId()];
        auto root = m_uiManager->getRootElement();
        menuItem.data()->open();
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

int GridMainMenuView::getUniqueId()
{
    return ++m_uniqueIdCounter;
}

void GridMainMenuView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    //    container->resize(size());
}

void GridMainMenuView::onAllReferencesSet()
{
    if(m_isAllReferencesSet)
    {
        for(const auto &reference : m_referencesMap)
        {
            if(!reference->getPluginMetaInfo().InterfaceName.compare("IUIMANAGER", Qt::CaseInsensitive))
            {
                m_uiManager = castPluginToInterface<IUIManager>(reference);
                Q_ASSERT(m_uiManager);
            }
        }
    }
    PluginBase::onAllReferencesSet();
}

bool GridMainMenuView::open()
{
    auto rootItem = m_uiManager->getRootElement();
    auto connectedElements = rootItem.data()->getConnectedElements();

    QVector<QWeakPointer<IUIManager::IUIElement>> menuItems;
    menuItems.reserve(connectedElements.size()+1);
    for(const auto &item : connectedElements)
    {
        qDebug() << item.data()->getMeta().Name;
        if(!item.data()->getElementWidget())
        {
            menuItems.append(item);
        }
    }
    menuItems.append(rootItem);

    if(menuItems.count() != 0)
    {
        int itemMinHeight = (height() / menuItems.count()) * 1.2;
        layout->setSpacing(itemMinHeight * 0.3);
        int rowCapacity = 1;
        QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        layout->addItem(topSpacer);

        for(const auto &menuItem : menuItems)
        {
            auto &&meta = menuItem.data()->getMeta();
            auto uniqueId = getUniqueId();
            m_uiElements.insert(uniqueId, menuItem);
            UniquePushButton *uniqueButton = new UniquePushButton(uniqueId, FormatMenuItemName(meta.Name), this);
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

    return PluginBase::open();
}

void GridMainMenuView::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Close",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
        }
}
