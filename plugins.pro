TEMPLATE = subdirs

# SUBDIRS += $$files(Projects/*.pro, true)

SUBDIRS += \
    Projects/Core/Core.pro \
    Projects/UIManager/UIManager.pro \
    Projects/DataBase/DataBase.pro \
    Projects/NotificationManager/NotificationManager.pro \
    Projects/ExtendableDataManager/ExtendableDataManager.pro \
    Projects/PluginLinker/PluginLinker.pro \
    Projects/PluginLinkerView/PluginLinkerView.pro \
    Projects/GridMainMenuView/GridMainMenuView.pro \
    Projects/UserTaskManager/UserTaskManager.pro \
    Projects/UserTaskManagerView/UserTaskManagerView.pro \
    Projects/PomodoroManager/PomodoroManager.pro \
    Projects/PomodoroManagerView/PomodoroManagerView.pro \
    Projects/TaskCalendar/TaskCalendar.pro \
#    Projects/DayPlan/DayPlan.pro \
#    Projects/DayPlanView/DayPlanView.pro \
    Projects/TaskSketchManager/TaskSketchManager.pro
#    Projects/TaskSketchManagerView/TaskSketchManagerView.pro
