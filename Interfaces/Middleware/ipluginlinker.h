#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/ireferencedescriptor.h"

class IPluginLinker
{
public:
    class ILinkerItem
    {
    public:
        virtual IReferenceDescriptorPtr descr() = 0;
        virtual bool isLoaded() = 0;

    signals:
        void onLoadedStateChanged(quint32 selfUID, bool isLoaded);
        void onReferencesChanged(quint32 selfUID, quint32 itemUID, bool isAdded);
        void onReferentsChanged(quint32 selfUID, quint32 itemUID, bool isAdded);
    };

    virtual QWeakPointer<ILinkerItem> addPlugin(QString filename) = 0;
	virtual bool removePlugin(QWeakPointer<ILinkerItem> linkerItem) = 0;
    virtual bool loadPlugin(quint32 linkerItem) = 0;
    virtual bool unloadPlugin(quint32 linkerItem) = 0;
    virtual bool linkPlugins(quint32 referent, QString interface, quint32 reference) = 0;
    virtual bool unlinkPlugins(quint32 referent, QString interface, quint32 reference) = 0;

    virtual QWeakPointer<ILinkerItem> getItemByUID(quint32 uid) = 0;
    virtual QWeakPointer< QList<QWeakPointer<ILinkerItem>> > getItemsWithInterface(Interface interface) = 0;

signals:
    void onLinkageFinished();
};
Q_DECLARE_INTERFACE(IPluginLinker, "IPluginLinker/1.0")
