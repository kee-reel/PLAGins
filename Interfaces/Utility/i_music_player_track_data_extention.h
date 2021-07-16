#pragma once

#include <QtCore>

#include "../Middleware/idataextention.h"

#define IMusicPlayerTrackDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString name READ name) \
	Q_PROPERTY(QString path READ path)

class IMusicPlayerTrackDataExtention : public IDataExtention
{
public:
	IMusicPlayerTrackDataExtention_EXTENTION_PROPERTY
	virtual QString name() = 0;
	virtual QString path() = 0;
};
Q_DECLARE_INTERFACE(IMusicPlayerTrackDataExtention, "IMusicPlayerTrackDataExtention/1.0")
