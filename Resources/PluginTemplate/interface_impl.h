#pragma once

#include <QtCore>

#include "%{IPath}"

class %{CN} : public QObject, public %{InterfaceName}
{
	Q_OBJECT
	Q_INTERFACES(%{InterfaceName})

public:
	%{CN}(QObject* parent);
	virtual ~%{CN}() override;
	
	// %{InterfaceName} interface
public slots:
	QString testString() override;
	void setTestString(QString testString) override;
	
signals:
	void testStringChanged(QString testString) override;
	
private:
	QString m_testString;
};
