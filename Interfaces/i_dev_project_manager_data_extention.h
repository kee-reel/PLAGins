#pragma once

#include <QtCore>

#include "../Middleware/idataextention.h"

#define IDevProjectManagerDataExtention_EXTENTION_PROPERTY \
	Q_PROPERTY(QString path READ path) \
	Q_PROPERTY(QString repository READ repository)

class IDevProjectManagerDataExtention : public IDataExtention
{
public:
	IDevProjectManagerDataExtention_EXTENTION_PROPERTY
	virtual QString path() = 0;
	virtual QString repository() = 0;

};
Q_DECLARE_INTERFACE(IDevProjectManagerDataExtention, "IDevProjectManagerDataExtention/1.0")
