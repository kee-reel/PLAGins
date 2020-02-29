#pragma once


#include <QtCore>

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
class TaskSketchManagerView : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
	Q_INTERFACES(IPlugin)
	
public:
	TaskSketchManagerView();
	virtual ~TaskSketchManagerView() override;
	
	// PluginBase interface
private:
	virtual void onReferencesSet() override;
	
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
	QPointer<UIElementBase> m_elementBase;
	ReferenceInstancePtr<ITaskSketchManager> myModel;
	PaintWidget *paintWidgetTypeEditor;
	
	QAbstractItemModel *sketchModel;
	QAbstractItemModel *taskModel;
	GalleryForm *galleryForm;
	
	QString imageFormat;
};
//!  \}

