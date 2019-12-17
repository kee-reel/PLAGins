#include "notificationmanager.h"

#include <QDebug>

static bool isTriggered = false;

void NotificationManager::ShowNotification(QString title, QString message, int id)
{
	QAndroidJniObject javaTitle = QAndroidJniObject::fromString(title);
	QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
	//    public static void showNotification(String title, String message, int notifyId)
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "showNotification",
											  "(Ljava/lang/String;Ljava/lang/String;I)V",
											  javaTitle.object<jstring>(),
											  javaMessage.object<jstring>(),
											  jint(id));
}

void NotificationManager::CancelNotification(int id)
{
	//    public static void cancelNotification(int notifyId)
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "cancelNotification",
											  "(I)V",
											  jint(id));
}

void NotificationManager::ShowToast(const QString &message, Duration duration)
{
	//    public static void showToast(String msg, int delay)
	QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "showToast",
											  "(Ljava/lang/String;I)V",
											  javaMessage.object<jstring>(),
											  jint(duration));
}

void NotificationManager::PlanApplicationWakeup(TimeType type, QDateTime time)
{
	auto activity = QtAndroid::androidActivity();
	auto packageManager = activity.callObjectMethod("getPackageManager",
													"()Landroid/content/pm/PackageManager;");
	auto activityIntent = packageManager.callObjectMethod("getLaunchIntentForPackage",
														  "(Ljava/lang/String;)Landroid/content/Intent;",
														  activity.callObjectMethod("getPackageName",
																					"()Ljava/lang/String;").object());
	auto pendingIntent = QAndroidJniObject::callStaticObjectMethod("android/app/PendingIntent", "getActivity",
																   "(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
																   activity.object(), jint(0), activityIntent.object(),
																   QAndroidJniObject::getStaticField<jint>("android/content/Intent",
																										   "FLAG_ACTIVITY_CLEAR_TOP"));
	auto alarmManager = activity.callObjectMethod("getSystemService",
												  "(Ljava/lang/String;)Ljava/lang/Object;",
												  QAndroidJniObject::getStaticObjectField("android/content/Context",
																						  "ALARM_SERVICE",
																						  "Ljava/lang/String;").object());
	alarmManager.callMethod<void>("set", "(IJLandroid/app/PendingIntent;)V",
								  jint(type),
								  jlong(time.toMSecsSinceEpoch()),
								  pendingIntent.object());
}

int NotificationManager::SetAlarm(INotificationManager::TimeType type, QDateTime time)
{
	qDebug() << "SET ALARM" << time.toSecsSinceEpoch();
	//    public static void setAlarm(int type, int time)
	auto activity = QtAndroid::androidActivity();
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarm",
											  "(IJ)V",
											  jint(type),
											  jlong(time.toMSecsSinceEpoch()));
	delayedCallbackTimer.start();
	return 0;
}

int NotificationManager::SetRepeatingAlarm(INotificationManager::TimeType type, QDateTime triggerTime, QDateTime interval)
{
	qDebug() << "SET" << triggerTime.toSecsSinceEpoch() << interval.toSecsSinceEpoch();
	//    public static void setRepeatingAlarm(int type, int triggerTime, int interval)
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setRepeatingAlarm",
											  "(IJJ)V",
											  jint(type),
											  jlong(triggerTime.toMSecsSinceEpoch()),
											  jlong(interval.toMSecsSinceEpoch()));
	delayedCallbackTimer.start();
	return 0;
}

void NotificationManager::SetAlarmedNotification(INotificationManager::TimeType type, QDateTime time, QString title,
												 QString message, int id)
{
	QAndroidJniObject javaTitle = QAndroidJniObject::fromString(title);
	QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
	//    public static void setAlarmedNotification(int type, long time, String title, String message, int notifyId)
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarmedNotification",
											  "(IJLjava/lang/String;Ljava/lang/String;I)V",
											  jint(type),
											  jlong(time.toMSecsSinceEpoch()),
											  javaTitle.object<jstring>(),
											  javaMessage.object<jstring>(),
											  jint(id));
}

void NotificationManager::SetAlarmedToast(INotificationManager::TimeType type, QDateTime time, const QString &message,
										  INotificationManager::Duration duration)
{
	QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
	//    public static void setAlarmedToast(int type, long time, String message, int delay)
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarmedToast",
											  "(IJLjava/lang/String;I)V",
											  jint(type),
											  jlong(time.toMSecsSinceEpoch()),
											  javaMessage.object<jstring>(),
											  jint(duration));
}

void NotificationManager::CancelAlarm()
{
	//    public static void cancelAlarm()
	QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "cancelAlarm");
}

void NotificationManager::OnAndroidAlarmRecieved(JNIEnv *, jobject)
{
	qDebug() << "OnAndroidAlarmRecieved" << &isTriggered << isTriggered;
	isTriggered = true;
}

void NotificationManager::CheckTimerTimeout()
{
	qDebug() << "~TIMEOUT" << &isTriggered << isTriggered;
	
	if(isTriggered)
	{
		isTriggered = false;
		delayedCallbackTimer.stop();
		emit OnTimerTimeout(0);
	}
}
