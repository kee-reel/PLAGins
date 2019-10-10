#ifndef IPLUGINLINKER_H
#define IPLUGINLINKER_H

#include <QtCore>

#include "../../Interfaces/ireferencedescriptor.h"

//!  \defgroup PluginLinker PluginLinker
//!      \ingroup Plugins
//!  \defgroup PluginLinker_int Interface
//!      \ingroup PluginLinker
//!  \defgroup PluginLinker_imp Implementation
//!      \ingroup PluginLinker
//!  \defgroup PluginLinker_dep Dependent plugins
//!      \ingroup PluginLinker

//!  \addtogroup PluginLinker_int
//!  \{

class IPluginLinker
{
public:
    class ILinkerItem
    {
    public:
        virtual IReferenceDescriptorPtr descr() = 0;

        virtual QWeakPointer<QMap< Interface, QList<QWeakPointer<ILinkerItem>> >> referenceItems() = 0;
        virtual QWeakPointer<QMap< Interface, QList<QWeakPointer<ILinkerItem>> >> referentItems() = 0;

        virtual bool isLoaded() = 0;

    signals:
        virtual void onLoadedStateChanged(uid_t selfUID, bool isLoaded) = 0;
        virtual void onReferencesChanged(uid_t selfUID, uid_t itemUID, bool isAdded) = 0;
        virtual void onReferentsChanged(uid_t selfUID, uid_t itemUID, bool isAdded) = 0;
    };

    virtual QWeakPointer<ILinkerItem> loadNewPlugin(QString filename) = 0;
    virtual bool loadPlugin(uid_t linkerItem) = 0;
    virtual bool unloadPlugin(uid_t linkerItem) = 0;
    virtual bool linkPlugins(uid_t referent, QString interface, uid_t reference) = 0;
    virtual bool unlinkPlugins(uid_t referent, QString interface, uid_t reference) = 0;

    virtual QWeakPointer<ILinkerItem> getItemByUID(uid_t uid) = 0;
    virtual QWeakPointer< QList<QWeakPointer<ILinkerItem>> > getItemsWithInterface(Interface interface) = 0;

signals:
    void onLinkageFinished();
};
//!  \}
Q_DECLARE_INTERFACE(IPluginLinker, "IPluginLinker")
#endif // IPLUGINLINKER_H