#pragma once

#include <QtCore>

class ITestLogic
{
	Q_PROPERTY(QString testString READ testString WRITE setTestString NOTIFY testStringChanged)
public slots:
	virtual QString testString() = 0;
	virtual void setTestString(QString testString) = 0;
signals:
	virtual void testStringChanged(QString testString) = 0;
};
Q_DECLARE_INTERFACE(ITestLogic, "ITestLogic/1.0")
