#include "notificationmanager.h"

#include <QDebug>

NotificationManager::NotificationManager() :
	PluginBase(this)
{
	initPluginBase({
		{INTERFACE(INotificationManager), this}
	});
}

NotificationManager::~NotificationManager()
{
}
