#ifndef LINKER_H
#define LINKER_H

#include <QtCore>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "../../Interfaces/ipluginlinker.h"
#include "linkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class Linker : public IPluginLinker
{
    Q_OBJECT

public:
    Linker();
    virtual ~Linker();

    // IPluginLinker interface
public:
    virtual bool unloadPlugin(QWeakPointer<ILinkerItem> linkerItem) override;
    virtual bool loadPlugin(QString filename) override;

    virtual int getCorePluginUID() override;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() override;

signals:
    void onLinkageFinished();

private:
    bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool addPlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool setupLinks();

    template<class Type>
    Type *castToPlugin(QObject *possiblePlugin) const;
    QSharedPointer<MetaInfo> parseMetaInfo(const QJsonObject &metaInfoObject) const;
    QSharedPointer<LinkerItem> createLinkerItem(QWeakPointer<IPluginHandler>);

private:
    const QString META_FIELD_INTERFACE                  = "interface";
    const QString META_FIELD_NAME                       = "name";
    const QString META_FIELD_RELATED_PLUGIN_INTERFACES  = "RelatedPluginInterfaces";
    const QString META_FIELD_ABOUT                      = "about";

private:
    QWidget *m_parentWidget;
    QSharedPointer<LinkerItem> m_corePlugin;
    QMap<QString, QSharedPointer<LinkerItem>> m_interfacesMap;
    QMap<int, QSharedPointer<LinkerItem>> m_linkerItemsMap;
    int m_pluginUidCounter;

    // IPluginLinker interface
public:
};
//! @}
#endif // LINKER_H
