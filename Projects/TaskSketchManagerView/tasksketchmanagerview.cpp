#include "tasksketchmanagerview.h"
#include "ui_form.h"

TaskSketchManagerView::TaskSketchManagerView() :
	QObject(),
	PluginBase(this),
	ui(new Ui::Form),
	m_elementBase(new UIElementBase(this, {"MainMenuItem"}))
{
	ui->setupUi(m_elementBase);
	paintWidgetTypeEditor = nullptr;
	galleryForm = new GalleryForm(m_elementBase);
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
		{INTERFACE(IPlugin), this},
		{INTERFACE(IUIElement), m_elementBase}
	},
	{
		{INTERFACE(ITaskSketchManager), myModel}
	});
	m_elementBase->initUIElementBase();
}

TaskSketchManagerView::~TaskSketchManagerView()
{	
//	if(paintWidgetTypeEditor && paintWidgetTypeEditor->parent())
//		delete paintWidgetTypeEditor;
}

void TaskSketchManagerView::onReferencesSet()
{
	paintWidgetTypeEditor = new PaintWidget();
	myModel->LinkEditorWidget(paintWidgetTypeEditor);
	
	taskModel = myModel->GetModel();
	sketchModel = myModel->GetInternalModel();
	galleryForm->SetModel(sketchModel);
	
	if(!sketchModel)
	{
		return;
	}
	
	int n = sketchModel->rowCount();
	for(int i = 0; i < n; ++i)
	{
		QModelIndex index = sketchModel->index(i, 0);
		QByteArray ba = index.data().toByteArray();
		galleryForm->AddImage(i, ba);
	}
}

void TaskSketchManagerView::OnItemDelete(int index)
{
	sketchModel->removeRows(index, 1);
}

void TaskSketchManagerView::OnItemConvertSlot(int index)
{
	myModel->ConvertSketchToTask(index);
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
	m_elementBase->closeSelf();
}
