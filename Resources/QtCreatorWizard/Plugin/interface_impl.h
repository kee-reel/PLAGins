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

private:
};
