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
    explicit PluginBase(QObject *object, QVector<Interface> interfaces, QMap<Interface, QList<QSharedPointer<IReferenceInstance> > > instances, QMap<Interface, QSharedPointer<IReferenceInstancesVariableList> > instancesList);

    virtual ~PluginBase()
    {
        qDebug() << "Plugin" << m_descr->name() << "unloaded";
    }

    // IPlugin interface
public:
    virtual bool pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta) override;
    virtual QWeakPointer<IReferenceDescriptor> getDescriptor() override;
    virtual QWeakPointer<IReferenceInstancesHandler> getInstancesHandler() override;
    virtual bool pluginFini() override;

    virtual QString getLastError() const override;

protected:
    void log(SeverityType severityType, QString msg) const;
    void raiseError(QString errorMessage);

    void checkAllReferencesSet();
    void checkAllReferencesReady();

    virtual void onAllReferencesSet(bool state);
    virtual void onAllReferencesReady(bool state);

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
    QMap<Interface, QList<QSharedPointer<IReferenceInstance> > > m_instances;
    QMap<Interface, QSharedPointer<IReferenceInstancesVariableList> > m_instancesList;
    QVector<Interface> m_instancesInterfaces;

    QString m_lastErrorString;
    SeverityType m_logSeverityType;

    bool m_isInited;
    bool m_isAllReferencesSet;
    bool m_isAllReferencesReady;
};
#endif // PLUGINBASE_H


