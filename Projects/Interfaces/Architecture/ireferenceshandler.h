#pragma once

#include "ireferencedescriptor.h"

enum ReferencesHandlerState
{
	SETTING_REFS,
	WAITING,
	READY
};

template <class IdentifierT>
class IReferencesHandler
{
public:
	virtual const QMap<IdentifierT, int> &requiredReferences() = 0;
	virtual const QMap<IdentifierT, QList<IReferenceDescriptorPtr>> &references() = 0;
	virtual bool setReferences(IdentifierT identifier, QList<IReferenceDescriptorPtr> references) = 0;
	
	virtual bool transitToReadyState() = 0;
	virtual ReferencesHandlerState state() = 0;
};
