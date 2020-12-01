#pragma once

#include <QtCore>

class %{InterfaceName}
{
	Q_PROPERTY(QString testString READ testString WRITE setTestString NOTIFY testStringChanged)
public slots:
	virtual QString testString() = 0;
	virtual void setTestString(QString testString) = 0;
signals:
	virtual void testStringChanged(QString testString);	
};
Q_DECLARE_INTERFACE(%{InterfaceName}, "%{InterfaceName}/1.0")
