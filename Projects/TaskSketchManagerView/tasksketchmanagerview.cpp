#include "tasksketchmanagerview.h"
#include "ui_form.h"

TaskSketchManagerView::TaskSketchManagerView() :
	QWidget(),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenuItem"}),
	ui(new Ui::Form)
{
	ui->setupUi(this);
	paintWidgetTypeEditor = nullptr;
	galleryForm = new GalleryForm(this);
	galleryForm->setVisible(false);
	imageFormat = "png";
	connect(ui->buttonSave, SIGNAL(clicked(bool)), SLOT(buttonSave_clicked()));
	connect(ui->buttonClear, SIGNAL(clicked(bool)), ui->widgetPaint, SLOT(Clean()));
	connect(ui->buttonOpenGallery, SIGNAL(clicked(bool)), SLOT(buttonOpenGallery_clicked()));
	connect(ui->buttonClose, SIGNAL(clicked(bool)), SLOT(buttonClose_clicked()));
	
	connect(galleryForm, SIGNAL(OnItemDelete(int)), SLOT(OnItemDelete(int)));
	connect(galleryForm, SIGNAL(OnItemConvert(int)), SLOT(OnItemConvertSlot(int)));
	
#ifdef Q_OS_ANDROID
	ui->buttonClear->setFocusPolicy(Qt::NoFocus);
	ui->buttonClear->setToolTip("");
	ui->buttonOpenGallery->setFocusPolicy(Qt::NoFocus);
	ui->buttonOpenGallery->setToolTip("");
	ui->buttonSave->setFocusPolicy(Qt::NoFocus);
	ui->buttonSave->setToolTip("");
	ui->buttonClose->setVisible(false);
#endif
	initPluginBase({
		{INTERFACE(ITaskSketchManager), myModel}
	});
	initUIElementBase();
}

TaskSketchManagerView::~TaskSketchManagerView()
{
	delete galleryForm;
	
//	if(paintWidgetTypeEditor && paintWidgetTypeEditor->parent())
//		delete paintWidgetTypeEditor;
}

void TaskSketchManagerView::onPluginInited()
{
	resetDescriptor(descr());
}

void TaskSketchManagerView::onPluginReferencesSet()
{
	paintWidgetTypeEditor = new PaintWidget();
	myModel->instance()->LinkEditorWidget(paintWidgetTypeEditor);
	
	taskModel = myModel->instance()->GetModel();
	sketchModel = myModel->instance()->GetInternalModel();
	galleryForm->SetModel(sketchModel);
	
	int n = sketchModel->rowCount();
	for(int i = 0; i < n; ++i)
	{
		QModelIndex index = sketchModel->index(i, 0);
		QByteArray ba = index.data().toByteArray();
		galleryForm->AddImage(i, ba);
	}
}

void TaskSketchManagerView::resizeEvent(QResizeEvent *event)
{
	galleryForm->setGeometry(rect());
}

void TaskSketchManagerView::OnItemDelete(int index)
{
	sketchModel->removeRows(index, 1);
}

void TaskSketchManagerView::OnItemConvertSlot(int index)
{
	myModel->instance()->ConvertSketchToTask(index);
}

void TaskSketchManagerView::buttonClear_clicked()
{
	ui->widgetPaint->Clean();
}

void TaskSketchManagerView::buttonSave_clicked()
{
	QByteArray array = ui->widgetPaint->value().toByteArray();
	
	sketchModel->insertRows(0, 1);
	QModelIndex root = sketchModel->index(0, 0);
	sketchModel->setData(root, QVariant(array));
	galleryForm->AddImage(0, array);
}

void TaskSketchManagerView::buttonOpenGallery_clicked()
{
	galleryForm->show();
}

void TaskSketchManagerView::buttonClose_clicked()
{
	closeSelf();
}
