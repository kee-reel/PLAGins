#include "pomodoromanagerview.h"
#include "ui_form.h"

PomodoroManagerView::PomodoroManagerView() :
	QWidget(),
	PluginBase(this, {INTERFACE(IUIElement)}),
	UIElementBase(this, this, {"MainMenuItem"}),
	ui(new Ui::Form)
{
	ui->setupUi(this);

    ui->treeView->setVisible(false);
    ui->buttonEdit->setVisible(false);
    ui->buttonDelete->setVisible(false);
    ui->buttonAdd->setVisible(false);

    connect(ui->buttonAdd, SIGNAL(clicked(bool)), this, SLOT(buttonAdd_clicked()));
    connect(ui->buttonEdit, SIGNAL(clicked(bool)), this, SLOT(buttonEdit_clicked()));
    connect(ui->buttonDelete, SIGNAL(clicked(bool)), this, SLOT(buttonDelete_clicked()));
    connect(ui->buttonProjects, SIGNAL(clicked(bool)), this, SLOT(buttonProjects_clicked()));
    connect(ui->treeView, SIGNAL(pressed(const QModelIndex &)), this, SLOT(treeView_pressed(const QModelIndex &)));
    connect(ui->buttonExit, SIGNAL(clicked(bool)), SLOT(buttonExit_clicked()));
    
    initPluginBase({
		{INTERFACE(IPomodoroManager), myModel}
    });
    initUIElementBase();

#ifdef Q_OS_ANDROID
    ui->buttonAdd->setFocusPolicy(Qt::NoFocus);
    ui->buttonAdd->setToolTip("");
    ui->buttonDelete->setFocusPolicy(Qt::NoFocus);
    ui->buttonDelete->setToolTip("");
    ui->buttonEdit->setFocusPolicy(Qt::NoFocus);
    ui->buttonEdit->setToolTip("");
    ui->buttonProjects->setFocusPolicy(Qt::NoFocus);
    ui->buttonProjects->setToolTip("");
    ui->buttonExit->setVisible(false);
#endif
}

PomodoroManagerView::~PomodoroManagerView()
{
}

void PomodoroManagerView::onPluginInited()
{
	resetDescriptor(descr());	
}

QString PomodoroManagerView::linkName()
{
	return UIElementBase::linkNames().first();
}

void PomodoroManagerView::onPluginReady()
{
	connect(ui->pomodoroButton, SIGNAL(OnStartPomodoro()), myModel->descr().data()->object(), SLOT(StartPomodoro()));
	connect(myModel->descr().data()->object(), SIGNAL(OnPomodoroFinished()), SLOT(PomodoroFinished()));

    proxyModel = myModel->instance()->GetTaskModel();
    ui->treeView->setModel(proxyModel);
    workSetup = myModel->instance()->GetWorkSetup();
    ui->pomodoroButton->secsTarget = workSetup.workSessionDuration;
    UpdateSelectedTask();
}

void PomodoroManagerView::PomodoroFinished()
{
    UpdateSelectedTask();
//    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros->data().toString()));
}

void PomodoroManagerView::buttonProjects_clicked()
{
    bool isTimerButtonVisible = !ui->pomodoroButton->isVisible();
    ui->buttonProjects->setIcon(QIcon(
        isTimerButtonVisible ?
        ":/Res/ic_assignment_black_36dp.png" :
        ":/Res/ic_timelapse_black_24dp.png"));
    ui->treeView->      setVisible(!isTimerButtonVisible);
    ui->pomodoroButton->setVisible(isTimerButtonVisible);
    ui->buttonEdit->    setVisible(!isTimerButtonVisible);
    ui->buttonDelete->  setVisible(!isTimerButtonVisible);
    ui->buttonAdd->     setVisible(!isTimerButtonVisible);
}

void PomodoroManagerView::buttonEdit_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedRows();
    if(list.length() == 0) return;
}

void PomodoroManagerView::buttonDelete_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    for(int i = list.count()-1; i >= 0; --i)
        proxyModel->removeRows(list[i].row(), 1, list[i].parent());
}

void PomodoroManagerView::buttonAdd_clicked()
{
    proxyModel->insertRow(0);
}

void PomodoroManagerView::buttonExit_clicked()
{
    m_opener->closeSelf();
}

void PomodoroManagerView::UpdateSelectedTask()
{
    bool isTaskValid = currentTask.isValid();
    auto taskName = isTaskValid ? currentTask.data().toString() : "Task not selected";
    ui->labelProject->setText(taskName);
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(taskName));
    ui->pomodoroButton->isEnabled = isTaskValid;
}

void PomodoroManagerView::treeView_pressed(const QModelIndex &index)
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    if(list.length() == 0) return;
    auto selected = list.first();

    currentTask = selected;
    myModel->instance()->SetActiveProject(currentTask);

    UpdateSelectedTask();
}

bool PomodoroManagerView::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->pomodoroButton && event->type() == QEvent::MouseButtonRelease)
    {
        return currentTask.isValid();
    }
    return QWidget::eventFilter(watched, event);
}
