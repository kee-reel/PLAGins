#pragma once

#include "ireferencedescriptor.h"


class IReferenceInstance
{
public:
	virtual const IReferenceDescriptorPtr& descr() = 0;
	virtual bool setInstance(IReferenceDescriptorPtr descr) = 0;
	virtual void clearInstance() = 0;
	virtual bool isSet() = 0;
};
typedef QWeakPointer<IReferenceInstance> IReferenceInstancePtr;

class IReferenceInstancesList
{
public:
	virtual bool append(IReferenceDescriptorPtr &&descriptor) = 0;
	virtual void clear() = 0;
	virtual int limit() = 0;
};
typedef QWeakPointer<IReferenceInstancesList> IReferenceInstancesListPtr;

template <class T>
class ReferenceInstance : public IReferenceInstance
{
public:	
	ReferenceInstance() :
		m_instance(nullptr)
	{
	}
	
	virtual bool setInstance(IReferenceDescriptorPtr descr) override
	{
		bool isValid = true;
		if(descr.isNull() || isSet())
		{
			isValid = false;
			qDebug() << "Can't set instance: description is empty";
		}
		else
		{
			T* instancePtr = qobject_cast<T*>(descr.data()->object());
			if(instancePtr)
			{
				m_descr = descr;
				m_instance = instancePtr;
				name = descr.data()->name();
			}
			else
			{
				isValid = false;
				qDebug() << "Can't set instance: can't cast to object";
			}
		}
		return isValid;
	}
	
	virtual void clearInstance() override
	{
		m_descr.clear();
		m_instance = nullptr;
		name = "";
	}
	
	virtual bool isSet() override
	{
		return !m_descr.isNull();
	}
	
	const IReferenceDescriptorPtr& descr() override
	{
		return m_descr;
	}
	
	T* instance()
	{
		if(isSet())
			return m_instance;
		else
			assert(false);
	}
	
private:
	IReferenceDescriptorPtr m_descr;
	T* m_instance;
	QString name;
};

template<class T>
class ReferenceInstancePtr : public QSharedPointer<ReferenceInstance<T>>
{
public:
	ReferenceInstancePtr() : QSharedPointer<ReferenceInstance<T>>(new ReferenceInstance<T>()) 
	{}
};


template <class T>
class ReferenceInstancesList : public IReferenceInstancesList, public QList<ReferenceInstancePtr<T>>
{
public:
	ReferenceInstancesList(int limit=0) : 
		QList<ReferenceInstancePtr<T>>(),
		m_limit(limit)
	{
		
	}

	// IReferenceInstancesVariableList interface
public:
	virtual bool append(IReferenceDescriptorPtr &&descriptor) override
	{
		assert(m_limit == 0 || this->size() != m_limit);
		ReferenceInstancePtr<T> instance;
		if(instance->setInstance(descriptor))
		{
			QList<ReferenceInstancePtr<T>>::append(instance);
			return true;
		}
		return false;
	}
	
	virtual void clear() override
	{
		QList<ReferenceInstancePtr<T>>::clear();
	}
	
	virtual int limit() override
	{
		return m_limit;
	}
private:
	int m_limit;
};

template<class T>
class ReferenceInstancesListPtr : public QSharedPointer<ReferenceInstancesList<T>>
{
};
