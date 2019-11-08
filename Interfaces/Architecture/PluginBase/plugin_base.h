#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtCore>
#include <QJsonObject>

#include "../iplugin.h"
#include "plugindescriptor.h"
#include "referenceshandler.h"

enum SeverityType
{
	INFO,
	DEBUG,
	WARNING,
	CRITICAL,
	FATAL
};

class PluginBaseSignal;

//! \brief This interface provides basic methods for all plugins.
class PluginBase : public IPlugin
{
	friend class PluginBaseSignal;
public:
	explicit PluginBase(QObject *object, QVector<Interface> interfaces);

	virtual ~PluginBase()
	{
		if(!m_descr.isNull())
		{
			qDebug() << "Plugin" << m_descr->name() << "unloaded";
		}
	}

protected:
	void referencesInit(QMap<Interface, IReferenceInstancePtr> instances = {}, QMap<Interface, IReferenceInstancesListPtr> instancesList = {});

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

	// IPlugin interface
public:
	virtual bool pluginInit(uid_t uid, QWeakPointer<QJsonObject> meta) override;
	virtual bool isInited() override;
	virtual IReferenceDescriptorPtr getDescriptor() override;
	virtual QWeakPointer<IPluginReferencesHandler> getInstancesHandler() override;
	virtual bool pluginFini() override;

public:
	virtual void onReferencesSet() {}
	virtual void onReady() {}

private:
	void onStateChanged(IPluginReferencesHandler::State state);

private:
	QObject* m_object;
	QVector<Interface> m_interfaces;
	QSharedPointer<PluginDescriptor> m_descr;
	QSharedPointer<ReferencesHandler> m_instancesHandler;
	QSharedPointer<PluginBaseSignal> m_pluginBaseSignal;
	bool m_isReady;
};


class PluginBaseSignal : public QObject
{
	Q_OBJECT
public:
	PluginBaseSignal(PluginBase* instance, QWeakPointer<ReferencesHandler> handler);

public slots:
	void onStateChanged(IPluginReferencesHandler::State state);

public:
	PluginBase* m_instance;
	QWeakPointer<ReferencesHandler> m_handler;
};
#endif // PLUGINBASE_H


