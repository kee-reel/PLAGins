#pragma once

#include "ireferenceinstance.h"

class ReferenceInstanceObject : public QObject, public IReferenceInstance
{
	Q_OBJECT
	Q_PROPERTY(uid_t uid READ uid NOTIFY descriptorChanged)
	Q_PROPERTY(QString name READ name NOTIFY descriptorChanged)
	Q_PROPERTY(QString about READ about NOTIFY descriptorChanged)
	Q_PROPERTY(QObject* object READ object NOTIFY descriptorChanged)
public:
	ReferenceInstanceObject(QObject* parent=nullptr) :
		QObject(parent)
	{
        qRegisterMetaType<uid_t>("uid_t");
	}
	
	// IReferenceInstance interface
public:
	virtual bool isSet() override
	{
		return !m_descr.isNull();
	}
	
	const IReferenceDescriptorPtr& descr() override
	{
		return m_descr;
	}
	
	uid_t uid()
	{
		return isSet() ? m_descr.toStrongRef()->uid() : 0;
	}
	
	QString name()
	{
		return isSet() ? m_descr.toStrongRef()->name() : "Not set";
	}
	
	QString about()
	{
		return isSet() ? m_descr.toStrongRef()->about() : "Not set";
	}
	
	QObject* object()
	{
		return isSet() ? m_descr.toStrongRef()->object() : nullptr;
	}

Q_SIGNALS:
	void descriptorChanged();
	
protected:
	IReferenceDescriptorPtr m_descr;
};
Q_DECLARE_METATYPE(uid_t)

template <class T>
class ReferenceInstance : public ReferenceInstanceObject
{
public:	
	ReferenceInstance(QObject* parent=nullptr) :
		ReferenceInstanceObject(parent),
		m_instance(nullptr)
	{
	}
	
	virtual bool setInstance(IReferenceDescriptorPtr descr) override
	{
		bool isValid = true;
		if(descr.isNull() || isSet())
		{
			isValid = false;
			qDebug() << "Can't set instance: descriptor is empty";
		}
		else
		{
			auto&& object = descr.toStrongRef()->object();
			T* instancePtr = qobject_cast<T*>(object);
			if(instancePtr)
			{
				m_descr = descr;
				m_instance = instancePtr;
				emit descriptorChanged();
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
		emit descriptorChanged();
	}
	
	T* instance()
	{
		if(isSet())
			return m_instance;
		else
			assert(false);
	}
	
private:
	T* m_instance;
};

template<class T>
class ReferenceInstancePtr : public QSharedPointer<ReferenceInstance<T>>
{
public:
	ReferenceInstancePtr() : QSharedPointer<ReferenceInstance<T>>(new ReferenceInstance<T>()) 
	{}
};
