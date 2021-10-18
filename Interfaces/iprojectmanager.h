#pragma once

#include <QtCore>

class IProjectManager
{
	Q_PROPERTY(QString projectFilePath READ testString WRITE setProjectFilePath NOTIFY projectFilePathChanged)
public slots:
	virtual QString projectFilePath() = 0;
public slots:
	virtual bool setProjectFilePath(QString path) = 0;
signals:
	virtual void projectFilePathChanged(QString path) = 0;
public slots:
	virtual void refreshExistingProjects() = 0;
	virtual void downloadPluginFromRepository(QUrl url) = 0;
	virtual void removePluginRepository(QString pluginPath) = 0;
};
Q_DECLARE_INTERFACE(IProjectManager, "IProjectManager/1.0")
