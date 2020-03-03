#pragma once

#include "referenceinstance.h"
#include <QObject>

class ReferenceInstancesListObject : public QObject, public IReferenceInstancesList
{
	Q_OBJECT
	Q_PROPERTY(QList<QObject*> instances READ instances NOTIFY instancesChanged)
	Q_PROPERTY(int count READ count NOTIFY instancesChanged)
public:
	ReferenceInstancesListObject(QObject* parent=nullptr, int limit=0) :
		QObject(parent), 
		m_limit(limit)
	{
	}

public:
	virtual QList<QObject*> instances() = 0;
	virtual int count() = 0;

Q_SIGNALS:
	void instancesChanged();
	
	// IReferenceInstancesVariableList interface
public:	
	virtual int limit() override
	{
		return m_limit;
	}
	
private:
	int m_limit;
};

template <class T>
class ReferenceInstancesList : public ReferenceInstancesListObject, public QList<ReferenceInstancePtr<T>>
{
public:
	ReferenceInstancesList(QObject* parent=nullptr, int limit=0) :
		ReferenceInstancesListObject(parent, limit), 
		QList<ReferenceInstancePtr<T>>()
	{
	}

	// IReferenceInstancesVariableList interface
public:
	virtual bool append(IReferenceDescriptorPtr &&descriptor) override
	{
		assert(limit() == 0 || this->size() != limit());
		ReferenceInstancePtr<T> instance;
		if(instance.reference()->setInstance(descriptor))
		{
			QList<ReferenceInstancePtr<T>>::append(instance);
			emit instancesChanged();
			return true;
		}
		return false;
	}
	
	void clearInstances() override
	{
		QList<ReferenceInstancePtr<T>>::clear();
		emit instancesChanged();
	}
	
	QList<QObject*> instances() override
	{
		QList<QObject*> instances;
		for(int i = 0; i < this->length(); ++i)
		{
			QObject* object = this->at(i).data();
			instances.append(object);
		}
		return instances;
	}
	
	int count() override
	{
		return this->length(); 
	} 
};

template<class T>
class ReferenceInstancesListPtr : public QSharedPointer<ReferenceInstancesList<T>>
{
};
