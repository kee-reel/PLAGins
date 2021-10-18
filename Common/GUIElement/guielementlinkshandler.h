#pragma once

#include <QtCore>

#include "../Plugin/referenceshandler.h"

class UIElementLinksHandler : public QObject, public ReferencesHandler<QString>
{
	Q_OBJECT
	Q_PROPERTY(ReferencesHandlerState state READ state WRITE setState NOTIFY onStateChanged)
public:
	UIElementLinksHandler(QMap<QString, IReferenceInstancePtr > instances, QMap<QString, IReferenceInstancesListPtr > instancesLists);
	
signals:
	void onStateChanged(ReferencesHandlerState state);
	void onReferencesListUpdated(QString interface);
	
public:
	virtual void setState(ReferencesHandlerState state) override;
	virtual void referencesListUpdated(QString link) override;
};

//! \}
