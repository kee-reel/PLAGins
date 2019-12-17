#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtCore>
#include <QJsonObject>

#include "../iplugin.h"
#include "../referenceshandler.h"
#include "plugindescriptor.h"

class PluginReferencesHandler : public QObject, public ReferencesHandler<Interface>
{
	Q_OBJECT
public:
	PluginReferencesHandler(const QMap<Interface, IReferenceInstancePtr > &instances, const QMap<Interface, IReferenceInstancesListPtr > &instancesLists) :
		ReferencesHandler<Interface>(instances, instancesLists)
	{
		checkReferencesUpdate();
	}
	
Q_SIGNALS:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(Interface interface);
	
	// ReferencesHandler interface
protected:
	void setState(ReferencesHandlerState state) override
	{
		if(m_state != state)
		{
			m_state = state;
			Q_EMIT onStateChanged(state);
		}	
	}
	
	void referencesListUpdated(Interface identifier) override
	{
		emit onReferencesListUpdated(identifier);
	}
};

class PluginBase;
class PluginBaseSignal : public QObject
{
	Q_OBJECT
public:
	PluginBaseSignal(PluginBase* instance, QWeakPointer<PluginReferencesHandler> handler);
	
public slots:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(const Interface &interface);
	
public:
	PluginBase* m_instance;
	QWeakPointer<PluginReferencesHandler> m_handler;
};

//! \brief This interface provides basic methods for all plugins.
class PluginBase : public IPlugin
{
	friend class PluginBaseSignal;
public:
	explicit PluginBase(QObject *object, QVector<Interface> interfaces);
	
	virtual ~PluginBase()
	{
	}
	
protected:
	void initPluginBase(const QMap<Interface, IReferenceInstancePtr> &instances = {}, const QMap<Interface, IReferenceInstancesListPtr> &instancesList = {});
	
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
private:
	virtual bool pluginInit(uid_t uid, const QWeakPointer<QJsonObject> &meta) override;
	virtual bool isInited() override;
	virtual IReferenceDescriptorPtr getDescriptor() override;
	virtual QWeakPointer<IReferencesHandler<Interface>> getInstancesHandler() override;
	virtual bool pluginFini() override;
	
protected:
	virtual void onPluginInited() {}
	virtual void onPluginReferencesSet() {}
	virtual void onPluginReady() {}
	virtual void onPluginReferencesListUpdated(Interface interface) {Q_UNUSED(interface)}
	
	IReferenceDescriptorPtr descr();
	
private:
	void onStateChanged(ReferencesHandlerState state);
	void	onReferencesListUpdated(const Interface &interface);
	
private:
	QObject* m_object;
	QVector<Interface> m_interfaces;
	QSharedPointer<PluginDescriptor> m_descr;
	QSharedPointer<PluginReferencesHandler> m_instancesHandler;
	QSharedPointer<PluginBaseSignal> m_pluginBaseSignal;
};
#endif // PLUGINBASE_H


