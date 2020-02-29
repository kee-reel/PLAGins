#include "usertaskmanagerview.h"
#include "ui_form.h"

UserTaskManagerView::UserTaskManagerView() :
	QObject(nullptr),
	PluginBase(this),
	ui(new Ui::Form),
	m_uiElementBase(new UIElementBase(this, {"MainMenuItem"}))
{
	ui->setupUi(m_uiElementBase);
	taskTree = nullptr;
	proxyModel = nullptr;
	
	myTreeView = new MyTreeView(m_uiElementBase);
	
	connect(ui->buttonAdd, &QPushButton::clicked, this, &UserTaskManagerView::buttonAdd_clicked);
	connect(ui->buttonEdit, &QPushButton::clicked, this, &UserTaskManagerView::buttonEdit_clicked);
	connect(ui->buttonDelete, &QPushButton::clicked, this, &UserTaskManagerView::buttonDelete_clicked);
	connect(ui->buttonExit, &QPushButton::clicked, this, &UserTaskManagerView::buttonExit_clicked);
	
	connect(myTreeView, &QTreeView::clicked, this, &UserTaskManagerView::onTreeViewClicked);
	connect(myTreeView, &QTreeView::doubleClicked, this, &UserTaskManagerView::onTreeViewDoubleClicked);
	connect(myTreeView, &QTreeView::pressed, this, &UserTaskManagerView::onTreeViewPressed);
	myTreeView->setExpandsOnDoubleClick(false);
	
#ifdef Q_OS_ANDROID
	ui->buttonAdd->setFocusPolicy(Qt::NoFocus);
	ui->buttonAdd->setToolTip("");
	ui->buttonDelete->setFocusPolicy(Qt::NoFocus);
	ui->buttonDelete->setToolTip("");
	ui->buttonEdit->setFocusPolicy(Qt::NoFocus);
	ui->buttonEdit->setToolTip("");
	ui->buttonExit->setVisible(false);
#endif
	
	addForm = new AddForm(m_uiElementBase);
	connect(addForm, SIGNAL(OnClose()), this, SLOT(OnAddFormClosed()));
	
	ui->verticalLayout->setDirection(QBoxLayout::BottomToTop);
	ui->verticalLayout->addWidget(addForm);
	ui->verticalLayout->addWidget(myTreeView);
	
	initPluginBase({
		{INTERFACE(IPlugin), this},
		{INTERFACE(IUIElement), m_uiElementBase}
	},
	{
		{INTERFACE(IUserTaskManager), m_taskManager}
	});
	m_uiElementBase->initUIElementBase();
}

UserTaskManagerView::~UserTaskManagerView()
{
	
}

void UserTaskManagerView::onReady()
{
	taskTree = m_taskManager->GetTreeModel();
	model = new DesignProxyModel(taskTree);
	currentModelIndex = nullptr;
	myTreeView->setModel(model);
	addForm->SetModel(model);
}

void UserTaskManagerView::OpenTaskEditor(int id)
{
}

void UserTaskManagerView::OnAddFormClosed()
{
	ui->buttonAdd->setFocusPolicy(Qt::StrongFocus);
	ui->buttonDelete->setFocusPolicy(Qt::StrongFocus);
	ui->buttonEdit->setFocusPolicy(Qt::StrongFocus);
	ui->buttonExit->setFocusPolicy(Qt::StrongFocus);
	myTreeView->setFocusPolicy(Qt::StrongFocus);
	myTreeView->setFocus();
}

void UserTaskManagerView::buttonExit_clicked()
{
	m_uiElementBase->closeSelf();
}

void UserTaskManagerView::buttonAdd_clicked()
{
	QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
	QModelIndex newIndex;
	if(list.count())
	{
		model->insertRows(model->rowCount(list.first()), 1, list.first());
		myTreeView->expand(list.first());
		newIndex = model->index(model->rowCount(list.first())-1, 0, list.first());
	}
	else
	{
		model->insertRows(-1, 1);
		newIndex = model->index(model->rowCount()-1, 0);
	}
	addForm->ShowModelData(newIndex, true);
}

void UserTaskManagerView::buttonDelete_clicked()
{
	QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
	for(int i = list.count()-1; i >= 0; --i) {
		model->removeRows(list[i].row(), 1, list[i].parent());
	}
}

void UserTaskManagerView::buttonEdit_clicked()
{
	QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
	if(list.count())
		addForm->ShowModelData(list.first());
}

void UserTaskManagerView::onTreeViewPressed(const QModelIndex &index)
{
	currentModelIndex = &index;
	if(index.isValid())
		addForm->ShowModelData(index);
}

void UserTaskManagerView::onTreeViewClicked(const QModelIndex &index)
{
	if(expandFlag)
		expandFlag = false;
	else
	{
		myTreeView->setExpanded(index, !myTreeView->isExpanded(index));
		expandFlag = true;
	}
	if(index.isValid())
		addForm->ShowModelData(index);
}

void UserTaskManagerView::onTreeViewDoubleClicked(const QModelIndex &index)
{
	if(index.isValid())
		addForm->ShowModelData(index);
}
