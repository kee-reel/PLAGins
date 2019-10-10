#ifndef SERVICESMANAGER_H
#define SERVICESMANAGER_H

#include "../../../Application/iapplication.h"
#include "../../Interfaces/Architecture/iplugin.h"
#include "../../Interfaces/Architecture/ireferenceinstance.h"
#include "../../Interfaces/Architecture/ireferenceinstanceshandler.h"

namespace Service
{

class SimpleLinker : public QObject
{
    Q_OBJECT
public:
    SimpleLinker(QObject* parent, IApplication* app);
    virtual ~SimpleLinker() override;

public:
    void init();

    void addPlugin(QWeakPointer<IPluginHandler> plugin);
    void removePlugin(IReferenceDescriptorPtr descr);

private:
    typedef QPair<QWeakPointer<IPluginHandler>, ReferenceInstance<IPlugin>> LoadedPluginPair;


private:
    IApplication* m_app;
    QMap<Interface, QList<QWeakPointer<LoadedPluginPair>>> m_pluginsInterfaces;
    QList<QSharedPointer<LoadedPluginPair>> m_plugins;
};

}
#endif // SERVICESMANAGER_H
