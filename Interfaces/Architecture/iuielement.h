#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/ireferenceshandler.h"

class IUIElement
{
public:
	virtual QWeakPointer<IReferencesHandler<QString>> getLinksHandler() = 0;
	
	virtual quint32 getUID() = 0;
	virtual QStringList linkNames() = 0;
	virtual QWidget *getWidget() = 0;
	virtual QIcon getIcon() = 0;
	
	virtual bool open(QWidget *parent) = 0;
	virtual bool isOpened() const = 0;
	virtual bool close() = 0;

	void linkOpened(quint32 selfUID, quint32 referenceUID);
	void linkClosed(quint32 selfUID, quint32 referenceUID);
	void selfClosed(quint32 selfUID);
protected:
	virtual ~IUIElement() = default;
};
Q_DECLARE_INTERFACE(IUIElement, "IUIElement/1.0")
