#pragma once

#include <QtCore>

class IPomodoroSettingsData
{
public:
	Q_PROPERTY(quint16 workSessionDuration READ workSessionDuration WRITE setWorkSessionDuration)
	Q_PROPERTY(quint16 easyRestDuration READ easyRestDuration WRITE setEasyRestDuration)
	Q_PROPERTY(quint16 longRestDuration READ longRestDuration WRITE setLongRestDuration)
	Q_PROPERTY(quint16 longRestPeriod READ longRestPeriod WRITE setLongRestPeriod)

	virtual quint16 workSessionDuration() = 0;
	virtual void setWorkSessionDuration(quint16 value) = 0;
	
	virtual quint16 easyRestDuration() = 0;
	virtual void setEasyRestDuration(quint16 value) = 0;
	
	virtual quint16 longRestDuration() = 0;
	virtual void setLongRestDuration(quint16 value) = 0;
	
	virtual quint16 longRestPeriod() = 0;
	virtual void setLongRestPeriod(quint16 value) = 0;
};
Q_DECLARE_INTERFACE(IPomodoroSettingsData, "IPomodoroSettingsData/1.0")
