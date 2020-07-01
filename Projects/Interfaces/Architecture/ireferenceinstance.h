#pragma once

#include "ireferencedescriptor.h"


class IReferenceInstance
{
public:
	virtual const IReferenceDescriptorPtr& descr() = 0;
	virtual bool setInstance(IReferenceDescriptorPtr descr) = 0;
	virtual void clearInstance() = 0;
	virtual bool isSet() = 0;
protected:
	virtual ~IReferenceInstance() = default;
};
typedef QWeakPointer<IReferenceInstance> IReferenceInstancePtr;

class IReferenceInstancesList
{
public:
	virtual bool append(IReferenceDescriptorPtr descriptor) = 0;
	virtual void clearInstances() = 0;
	virtual int limit() = 0;
protected:
	virtual ~IReferenceInstancesList() = default;
};
typedef QWeakPointer<IReferenceInstancesList> IReferenceInstancesListPtr;
