#ifndef LINKERITEMBASE_H
#define LINKERITEMBASE_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QMap>
#include <QHash>

#include "../../Interfaces/Middleware/ipluginlinker.h"
#include "../../../Application/ipluginhandler.h"


class LinkerItemBase : public QObject, public IPluginLinker::ILinkerItem
{
    Q_OBJECT
public:
    LinkerItemBase(IPluginHandlerPtr pluginHandler);
    virtual ~LinkerItemBase() override;

    // ILinkerItem interface
public:
    virtual IReferenceDescriptorPtr descr() override;

    virtual QWeakPointer<QMap<Interface, QList<QWeakPointer<IPluginLinker::ILinkerItem> > > > referenceItems() override;
    virtual QWeakPointer<QMap<Interface, QList<QWeakPointer<ILinkerItem> > > > referentItems() override;

    virtual bool isLoaded() override;

public:
    virtual const QMap<Interface, int>& references() = 0;

    virtual bool load();
    virtual bool unload();

    virtual void addReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem);
    virtual void removeReference(Interface interface, QWeakPointer<LinkerItemBase> linkItem);
    virtual void addReferent(Interface interface, QWeakPointer<LinkerItemBase> linkItem);
    virtual void removeReferent(Interface interface, QWeakPointer<LinkerItemBase> linkItem);
    virtual bool loadAllConnected();

signals:
    void onLoadedStateChanged(uid_t selfUID, bool isLoaded);
    void onReferencesChanged(uid_t selfUID, uid_t itemUID, bool isAdded);
    void onReferentsChanged(uid_t selfUID, uid_t itemUID, bool isAdded);

private slots:
    void onReferenceLoadedStateChanged(uid_t uid, bool isLoaded);

protected:
    virtual QString initItem(QObject* object) = 0;
    virtual QString finiItem() = 0;
    virtual bool isInited();

protected:
    uid_t m_uid;
    IReferenceDescriptorPtr m_descriptor;
    IPluginHandlerPtr m_pluginHandler;
    QSharedPointer<QMap< Interface, QList<QWeakPointer<IPluginLinker::ILinkerItem>> >> m_references;
    QSharedPointer<QMap< Interface, QList<QWeakPointer<IPluginLinker::ILinkerItem>> >> m_referents;
};

#endif // LINKERITEMBASE_H
