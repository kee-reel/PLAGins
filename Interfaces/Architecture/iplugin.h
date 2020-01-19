#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtCore>
#include <QObject>
#include <QJsonObject>

#include "ireferenceshandler.h"


//! \brief This interface provides basic methods for all plugins.
class IPlugin
{
public:
	virtual QObject* getInstance(Interface interface) = 0;
	virtual IReferenceDescriptorPtr getDescriptor() = 0;
	virtual QWeakPointer<IReferencesHandler<Interface>> getInstancesHandler() = 0;
	
	virtual bool pluginInit(uid_t uid, const QWeakPointer<QJsonObject> &metaInfoObject) = 0;
	virtual bool isInited() = 0;
	virtual bool pluginFini() = 0;
};
Q_DECLARE_INTERFACE(IPlugin, "IPlugin/1.0")
#endif // IPLUGIN_H
