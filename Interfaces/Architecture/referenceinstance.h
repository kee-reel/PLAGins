#pragma once

#include "iplugin.h"
#include "ireferenceinstance.h"

class ReferenceInstanceObject : public QObject, public IReferenceInstance
{
	Q_OBJECT
	Q_PROPERTY(quint32 uid READ uid NOTIFY descriptorChanged)
	Q_PROPERTY(QString name READ name NOTIFY descriptorChanged)
	Q_PROPERTY(QString about READ about NOTIFY descriptorChanged)
	Q_PROPERTY(QObject* object READ object NOTIFY descriptorChanged)
public:
	ReferenceInstanceObject(QObject* parent=nullptr) :
		QObject(parent),
		m_object(nullptr)
	{
        qRegisterMetaType<quint32>("quint32");
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
	
	quint32 uid()
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
		return m_object;
	}

Q_SIGNALS:
	void descriptorChanged();
	
protected:
	QObject* m_object;
	IReferenceDescriptorPtr m_descr;
};
Q_DECLARE_METATYPE(quint32)

template <class T>
class ReferenceInstance : public ReferenceInstanceObject
{
public:	
	ReferenceInstance(QObject* parent=nullptr) :
		ReferenceInstanceObject(parent),
		m_instance(nullptr),
		m_interface(Interface::make<T>())
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
			auto&& pluginObject = descr.toStrongRef()->object();
			IPlugin* pluginInstance = qobject_cast<IPlugin*>(pluginObject);
			QObject* instanceObject = pluginInstance->getInstance(m_interface);
			T* instancePtr = qobject_cast<T*>(instanceObject);
			if(instancePtr)
			{
				m_descr = descr;
				m_instance = instancePtr;
				m_object = instanceObject;
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
	Interface m_interface;
};

template<class T>
class ReferenceInstancePtr : public QSharedPointer<ReferenceInstance<T>>
{
public:
	ReferenceInstancePtr() : QSharedPointer<ReferenceInstance<T>>(new ReferenceInstance<T>()) 
	{}
	
	ReferenceInstance<T>* reference() const
	{
		return this->data();
	}
	
	T* operator->() const
	{
		return this->data()->instance();
	}
};
