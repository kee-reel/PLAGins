TEMPLATE = subdirs

# SUBDIRS += $$files(Projects/*.pro, true)

SUBDIRS += \
    Projects/Core/Core.pro \
    Projects/PluginLinker/PluginLinker.pro \
    Projects/UIManager/UIManager.pro \
    Projects/DataBase/DataBase.pro \
    Projects/ExtendableDataManager/ExtendableDataManager.pro \
    Projects/UserTaskManager/UserTaskManager.pro \
    Projects/PomodoroManager/PomodoroManager.pro \
    Projects/TaskSketchManager/TaskSketchManager.pro \
    Projects/NotificationManager/NotificationManager.pro \
    Projects/TaskCalendar/TaskCalendar.pro \
    Projects/GridMainMenuView/GridMainMenuView.pro
