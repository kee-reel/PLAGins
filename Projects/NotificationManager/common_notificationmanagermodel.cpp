#include "notificationmanager.h"

#include <QDebug>

NotificationManager::NotificationManager() :
    PluginBase(this)
{
    //    NotificationManagerModel::SetInstance(this);
}

NotificationManager::~NotificationManager()
{
}

void NotificationManager::onAllReferencesSet()
{
    PluginBase::onAllReferencesSet();
}

void NotificationManager::onAllReferencesReady()
{
    PluginBase::onAllReferencesReady();
}
