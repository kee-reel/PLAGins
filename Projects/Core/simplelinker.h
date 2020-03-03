#pragma once


#include "../../../Application/Interfaces/iapplication.h"
#include "../../Interfaces/Architecture/iplugin.h"
#include "../../Interfaces/Architecture/referenceinstance.h"

class SimpleLinker : public QObject
{
	Q_OBJECT
public:
	SimpleLinker(QObject* parent, QWeakPointer<IApplication> app);
	virtual ~SimpleLinker() override;

public:
	void init();

	void addPlugin(IPluginHandlerPtr plugin);
	void removePlugin(IReferenceDescriptorPtr descr);

private:
	typedef QPair<IPluginHandlerPtr, ReferenceInstancePtr<IPlugin>> LoadedPluginPair;

private:
	QWeakPointer<IApplication> m_app;
	QMap<Interface, QList<QWeakPointer<LoadedPluginPair>>> m_pluginsInterfaces;
	QList<QSharedPointer<LoadedPluginPair>> m_plugins;
};

