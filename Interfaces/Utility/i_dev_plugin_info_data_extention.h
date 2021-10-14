#pragma once

#include <QtCore>

#include "../Middleware/idataextention.h"

#define IDevPluginInfoDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString name READ name) \
	Q_PROPERTY(QString path READ path) \
	Q_PROPERTY(QString repository READ repository) \
	Q_PROPERTY(bool isEnabled READ isEnabled) \
	Q_PROPERTY(bool updateAvailable READ updateAvailable) \
	Q_PROPERTY(bool hasLocalChanges READ hasLocalChanges)

class IDevPluginInfoDataExtention : public IDataExtention
{
public:
	IDevPluginInfoDataExtention_EXTENTION_PROPERTY
	virtual QString name() = 0;
	virtual QString path() = 0;
	virtual QString repository() = 0;
	virtual bool isEnabled() = 0;
	virtual bool updateAvailable() = 0;
	virtual bool hasLocalChanges() = 0;
};
Q_DECLARE_INTERFACE(IDevPluginInfoDataExtention, "IDevPluginInfoDataExtention/1.0")
