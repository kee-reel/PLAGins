#pragma once

#include <QtCore>

class ICLIElement
{
public:
	virtual void handle(const QStringList& args) = 0;
	virtual QString help() = 0;
	virtual QString getComandName() = 0;
};
Q_DECLARE_INTERFACE(ICLIElement, "ICLIElement/1.0")
