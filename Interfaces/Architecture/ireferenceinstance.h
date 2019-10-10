#pragma once

#include "ireferencedescriptor.h"


class IReferenceInstance
{
public:
    virtual const IReferenceDescriptorPtr& descr() = 0;
    virtual bool reset(IReferenceDescriptorPtr descr = IReferenceDescriptorPtr()) = 0;
};


class IReferenceInstancesVariableList : QList<QSharedPointer<IReferenceInstance>>
{
public:
    virtual bool append(IReferenceDescriptorPtr &&descriptor) = 0;
};


template <class T>
class ReferenceInstance : public IReferenceInstance
{
public:
    ReferenceInstance() :
	m_instance(nullptr)
    {
    }

    ReferenceInstance(IReferenceDescriptorPtr& descr) :
	m_instance(nullptr)
    {
	reset(descr);
    }

    virtual bool reset(IReferenceDescriptorPtr descr = IReferenceDescriptorPtr()) override
    {
	if(descr.isNull())
	{
	    m_descr.clear();
	    m_instance = nullptr;
	    return true;
	}
	else
	{
	    T* instancePtr = qobject_cast<T*>(descr.data()->object());
	    if(instancePtr)
	    {
		m_descr = descr;
		m_instance = instancePtr;
		return true;
	    }
	    else
	    {
		qDebug() << "Can't cast object";
		reset();
		return false;
	    }
	}
    }

    T* operator->()
    {
	assert(!m_descr.isNull());
	return m_instance;
    }

    bool isNull()
    {
	return m_descr.isNull();
    }

    const IReferenceDescriptorPtr& descr() override
    {
	return m_descr;
    }

private:
    IReferenceDescriptorPtr m_descr;
    T* m_instance;
};


template <class T>
class ReferenceInstancesVariableList : public IReferenceInstancesVariableList
{
public:
    ReferenceInstancesVariableList()
    {
    }

    // IReferenceInstancesVariableList interface
public:
    virtual bool append(IReferenceDescriptorPtr &&descriptor) override
    {
	QSharedPointer<ReferenceInstance<T>> instance(new ReferenceInstance<T>());
	auto isValid = instance.data()->reset(descriptor);
	if(isValid)
	{
	    append(instance);
	}
	return isValid;
    }
};
