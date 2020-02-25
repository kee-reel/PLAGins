#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QtCore>

#include "../../../Application/icore.h"
#include "../../Interfaces/Architecture/iplugin.h"
#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"

#include "simplelinker.h"

//! addtogroup CorePlugin_imp
//! {
class Core : public QObject, public PluginBase, public ICore, public IApplication
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.CorePlugin" FILE "PluginMeta.json")
	Q_INTERFACES(
		IPlugin
		ICore
		IApplication)

public:
	Core();
	virtual ~Core() override;

	// ICore interface
public:
	virtual void coreInit(QWeakPointer<IApplication> app) override;
	virtual bool coreFini() override;

	// PluginBase interface
public:
	virtual void onPluginReady() override;

	// IApplication interface
public:
	virtual QWidget *getParentWidget() override;
	virtual const QVector<IPluginHandlerPtr> &getPlugins() override;
	virtual IPluginHandlerPtr makePluginHandler(const QString &path) override;

private:
	QWeakPointer<IApplication> m_app;
	QSharedPointer<SimpleLinker> m_linker;
};
//! }
#endif // COREPLUGIN_H
