#ifndef IPLUGINLINKER_H
#define IPLUGINLINKER_H

#include <QtCore>

#include "../../Application/ipluginhandler.h"

//! \brief Holds basic information about plugin.
struct MetaInfo
{
    //! \brief Plugin interface name. By this field all plugins are linked.
    QString InterfaceName;
    //! \brief Plugin name.
    QString Name;
    //! \brief Names of references' interfaces that required by plugin. If no reference with such interface exists,
    //! plugin will use default instance with same interface that embedded in this plugin.
    QList<QString> EmbeddedInterfaces;
    //! \brief Names of references' interfaces that required by plugin. If no referece with such interface exists plugin won't work.
    QList<QString> RequiredInterfaces;
    //! \brief Names of references' interfaces. References' of this type not required for proper work of plugin,
    //! but could be loaded to extend some of its features.
    QList<QString> OptionalInterfaces;
    //! \brief Description of features and purpose of this plugin.
    QString About;
};


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
        virtual bool isLoaded() const = 0;
        virtual bool isOpened() const = 0;
        virtual MetaInfo getMeta() const = 0;
        virtual int getPluginUID() const = 0;

        virtual QWidget *getWidget() const = 0;
        virtual const QObject *getObject() const = 0;

        virtual QMap<int, QWeakPointer<ILinkerItem>> getReferences() = 0;
        virtual QMap<int, QWeakPointer<ILinkerItem>> getReferents() = 0;

        virtual bool open() = 0;
        virtual bool close() = 0;

    signals:
        void onLoaded(int itemId);
        void onOpened(int itemId);
        void onClosed(int itemId);
        void onConnectionsChanged(int itemId);
    };

    virtual bool unloadPlugin(QWeakPointer<ILinkerItem> linkerItem) = 0;
    virtual bool loadPlugin(QString filename) = 0;

    virtual int getCorePluginUID() = 0;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() = 0;

signals:
    void onLinkageFinished();
};
//!  \}
Q_DECLARE_INTERFACE(IPluginLinker, "IPluginLinker")
#endif // IPLUGINLINKER_H
