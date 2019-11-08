#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtCore>
#include <QObject>
#include <QJsonObject>

#include "ireferenceshandler.h"


class IPluginReferencesHandler : public IReferencesHandler<Interface>
{
};

//! \brief This interface provides basic methods for all plugins.
class IPlugin
{
public:
    virtual bool pluginInit(uid_t uid, QWeakPointer<QJsonObject> metaInfoObject) = 0;
    virtual bool isInited() = 0;
	virtual IReferenceDescriptorPtr getDescriptor() = 0;
    virtual QWeakPointer<IPluginReferencesHandler> getInstancesHandler() = 0;
    virtual bool pluginFini() = 0;
};
Q_DECLARE_INTERFACE(IPlugin, "IPlugin")
#endif // IPLUGIN_H
