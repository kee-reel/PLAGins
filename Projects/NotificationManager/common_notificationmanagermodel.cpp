#include "notificationmanager.h"

#include <QDebug>

NotificationManager::NotificationManager() :
	PluginBase(this,
{
	INTERFACE(INotificationManager)
})
{
	initPluginBase();
}

NotificationManager::~NotificationManager()
{
}
