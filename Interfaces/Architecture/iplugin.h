#pragma once

#include <QtCore>
#include <QObject>
#include <QJsonObject>

#include "ireferenceshandler.h"

class IPlugin
{
public:
	virtual QObject* getInstance(Interface interface) = 0;
	virtual IReferenceDescriptorPtr getDescriptor() = 0;
	virtual QWeakPointer<IReferencesHandler<Interface>> getInstancesHandler() = 0;

	virtual bool pluginInit(quint32 uid, const QWeakPointer<QJsonObject> &metaInfoObject) = 0;
	virtual bool isInited() = 0;
	virtual bool pluginFini() = 0;
protected:
	virtual ~IPlugin() = default;
};
Q_DECLARE_INTERFACE(IPlugin, "IPlugin/1.0")
