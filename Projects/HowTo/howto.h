#pragma once

#include <QtCore>

#include "/home/curunir/Projects/MASS/MASS-Plugins/Interfaces/Utility/ihowto.h"

class HowTo : public QObject, public IHowTo
{
	Q_OBJECT
	Q_INTERFACES(IHowTo)
	
public:
	HowTo(QObject* parent);
	virtual ~HowTo() override;
	
private:
};
