#pragma once

#include "ireferencedescriptor.h"

template <class IdentifierT>
class IReferencesHandler
{
public:
    enum State
    {
	SETTING_REFS,
	WAITING,
	READY
    };

public:
    virtual const QMap<IdentifierT, int> &requiredReferences() = 0;
    virtual const QMap<IdentifierT, QList<IReferenceDescriptorPtr>> &references() = 0;
    virtual bool setReferences(IdentifierT identifier, QList<IReferenceDescriptorPtr> references) = 0;
    virtual bool transitToReadyState() = 0;

    virtual State state() = 0;
    virtual QObject* object() = 0;

signals:
    void onStateChanged(State stage);
};
