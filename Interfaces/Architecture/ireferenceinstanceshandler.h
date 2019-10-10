#pragma once

#include "ireferencedescriptor.h"

class IReferenceInstancesHandler
{
public:
    enum State
    {
	SETTING_REFS,
	WAITING,
	READY
    };

public:
    virtual const QMap<Interface, int> &requiredReferences() = 0;
    virtual const QMap<Interface, QList<IReferenceDescriptorPtr>> &references() = 0;
    virtual bool setReferences(Interface interface, QList<IReferenceDescriptorPtr> references) = 0;
    virtual bool transitToReadyState() = 0;

    virtual State state() = 0;
    virtual QObject* object() = 0;

signals:
    virtual void onStateChanged(State stage) = 0;
};
