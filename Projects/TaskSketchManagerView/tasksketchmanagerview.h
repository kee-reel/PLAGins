#ifndef TASKSKETCHVIEW_H
#define TASKSKETCHVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QAbstractProxyModel>
#include <QPainter>
#include <QAbstractItemModel>
#include <QResizeEvent>


#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"

#include "../../Interfaces/Utility/itasksketchmanager.h"
#include "paintwidget.h"
#include "galleryform.h"

namespace Ui
{
class Form;
}


//! \addtogroup TaskSketchManager_dep
//!  \{
class TaskSketchManagerView : public QWidget, public PluginBase, public UIElementBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin IUIElement)
	
public:
	TaskSketchManagerView();
	virtual ~TaskSketchManagerView() override;
	
	// PluginBase interface
private:
	virtual void onPluginInited() override;
	virtual void onPluginReferencesSet() override;

private:
	virtual void resizeEvent(QResizeEvent *event) override;
	
signals:
	void OnItemConvert(int index);
	
private slots:
	void OnItemDelete(int index);
	void OnItemConvertSlot(int index);
	void buttonClear_clicked();
	void buttonSave_clicked();
	void buttonOpenGallery_clicked();
	void buttonClose_clicked();
	
private:
	QSharedPointer<Ui::Form> ui;
	ReferenceInstancePtr<ITaskSketchManager> myModel;
	PaintWidget *paintWidgetTypeEditor;
	
	QAbstractItemModel *sketchModel;
	QAbstractItemModel *taskModel;
	GalleryForm *galleryForm;
	
	QString imageFormat;
};
//!  \}
#endif // TASKSKETCHVIEW_H
