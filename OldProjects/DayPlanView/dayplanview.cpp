#include "dayplanview.h"
#include "ui_form.h"

DayPlanView::DayPlanView() :
	QWidget(),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenuItem"}),
	ui(new Ui::Form)
{
	ui->setupUi(this);
	initPluginBase({
		{INTERFACE(IDayPlan), DayPlan}
	});
	initUIElementBase();
	itemModel = nullptr;
	connect(ui->buttonExit, &QPushButton::clicked, [this](){
		closeSelf();
	});
}

DayPlanView::~DayPlanView()
{
}

void DayPlanView::onInited()
{
	resetDescriptor(descr());	
}

void DayPlanView::onReady()
{
	DayPlan->SetDataTypeEditor(new DateTimeTypeEditor());
	
	auto model = DayPlan->GetTaskModel();
	itemModel = new DesignProxyModel(model);
	ui->treeView->setModel(itemModel);
	model = DayPlan->GetDateModel();
	itemModel = new DesignProxyModel(model);
	ui->treeView_2->setModel(itemModel);
}
