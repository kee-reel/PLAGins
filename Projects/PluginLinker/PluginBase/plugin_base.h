#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtCore>
#include <QObject>
#include <QJsonObject>
#include <QMap>

#include "iplugin.h"

#if defined(PLUGIN_BASE_QOBJECT)
#define PLUGIN_BASE_PARENT QObject

#elif defined(PLUGIN_BASE_QWIDGET)
#define PLUGIN_BASE_PARENT QWidget
#include <QWidget>

namespace Ui
{
class Form;
}
#elif defined(PLUGIN_BASE_QWIDGET_QML)
#define PLUGIN_BASE_PARENT QObject

#endif

enum SeverityType
{
    INFO,
    DEBUG,
    WARNING,
    CRITICAL,
    FATAL
};

//! \brief This interface provides basic methods for all plugins.
class PluginBase : public IPlugin
{
public:
#if defined(PLUGIN_BASE_QOBJECT)
    explicit PluginBase(QObject *object = nullptr);

#elif defined(PLUGIN_BASE_QWIDGET)
    explicit PluginBase(QWidget *parent = nullptr);

#elif defined(PLUGIN_BASE_QWIDGET_QML)
    PluginBase(QWidget *parent = nullptr);

#endif

    virtual ~PluginBase()
    {
        qDebug() << "Plugin" << getPluginDescription(m_metaInfo) << "unloaded";
    }

public:
    virtual bool pluginInit(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject) override;
    virtual bool addReferencePlugin(IPlugin *referencePlugin) override;
    virtual bool removeReferencePlugin(IPlugin *referencePlugin) override;

    virtual QString getLastError() const override;
    virtual const MetaInfo &getPluginMetaInfo() const override;
    virtual QObject *getObject() override;
    virtual QWidget *getWidget() override;
    virtual bool isReady() override;
    virtual void onAllReferencesSet();
    virtual void onAllReferencesReady();

signals:
    void onReady(IPlugin*);
    void onOpen(IPlugin*);
    void onClose(IPlugin*);

protected slots:
    virtual void onReferenceReady(IPlugin* reference) override;
    virtual bool open() override;
    virtual bool close() override;

protected:
    void log(SeverityType severityType, QString msg) const;
    void constructorInit();
    void raiseError(QString errorMessage);
    inline QString getPluginDescription(const MetaInfo &meta) const
    {
        return QString("[%1 : %2]").arg(meta.InterfaceName).arg(meta.Name);
    }

    void checkAllReferencesSet();
    void checkAllReferencesReady();

    template<class T>
    T *castPluginToInterface(IPlugin *possiblePlugin)
    {
        if(!possiblePlugin)
        {
            qCritical() << "PluginBase::castPluginToInterface: possiblePlugin is nullptr.";
            return nullptr;
        }
        QObject *object = possiblePlugin->getObject();
        T *plugin = qobject_cast<T *>(object);

        if(!plugin)
        {
            auto &&meta = possiblePlugin->getPluginMetaInfo();
            qCritical() << QString("Can't cast plugin %1 to interface %2.").arg(meta.Name).arg(meta.InterfaceName);
        }

        return plugin;
    }

protected:
    QMap<QString, IPlugin *> m_referencesMap;
    QMap<QString, bool> m_referencesReadyMap;
    QString m_lastErrorString;
    MetaInfo m_metaInfo;
    SeverityType m_logSeverityType;

    bool m_isInited;
    bool m_isAllReferencesSet;
    bool m_isAllReferencesReady;

private:
    QObject* m_object;

#if defined(PLUGIN_BASE_QWIDGET)
protected:
    QSharedPointer<Ui::Form> ui;
#endif
};
#endif // PLUGINBASE_H

