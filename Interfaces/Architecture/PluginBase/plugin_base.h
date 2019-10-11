#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtCore>
#include <QObject>
#include <QJsonObject>
#include <QMap>

#include "../iplugin.h"
#include "plugindescriptor.h"
#include "referenceinstanceshandler.h"

enum SeverityType
{
    INFO,
    DEBUG,
    WARNING,
    CRITICAL,
    FATAL
};


//! \brief This interface provides basic methods for all plugins.
class PluginBase : public IPlugin
{
public:
    explicit PluginBase(QObject *object, QVector<Interface> interfaces);

    virtual ~PluginBase()
    {
        qDebug() << "Plugin" << m_descr->name() << "unloaded";
    }

    // IPlugin interface
public:
    virtual bool pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta) override;
    virtual IReferenceDescriptorPtr getDescriptor() override;
    virtual QWeakPointer<IReferenceInstancesHandler> getInstancesHandler() override;
    virtual bool pluginFini() override;

protected:
    void referencesInit(QMap<Interface, QList<IReferenceInstancePtr> > instances, QMap<Interface, IReferenceInstancesListPtr> instancesList);

    template<class T>
    T *castPluginToInterface(QObject *possiblePlugin)
    {
        if(!possiblePlugin)
        {
            qCritical() << "PluginBase::castPluginToInterface: possiblePlugin is nullptr.";
            return nullptr;
        }
        T *plugin = qobject_cast<T *>(possiblePlugin);
        if(!plugin)
        {
            qCritical() << QString("Can't cast plugin to interface.");
        }

        return plugin;
    }

private:
    QObject* m_object;
    QVector<Interface> m_interfaces;
    QSharedPointer<PluginDescriptor> m_descr;
    QSharedPointer<ReferenceInstancesHandler> m_instancesHandler;
};
#endif // PLUGINBASE_H


