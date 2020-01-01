	#pragma once

#include <QtCore>
#include <typeindex>

struct Interface
{
private:
	Interface(QString name, QString versionId, size_t typeHash) :
		m_name(name), m_versionId(versionId), m_typeHash(typeHash), m_isValid(true)
	{};
	
public:
	Interface(const Interface &other) :
		m_name(other.name()), m_versionId(other.versionId()), m_typeHash(other.typeHash()), m_isValid(other.isValid())
	{
	}
	
	template<class I>
	static Interface make(QString name)
	{
		auto&& x = Interface(name, qobject_interface_iid<I*>(), typeid(I).hash_code());
		//	qDebug() << x.m_name << x.m_versionId;
		return x;
	}
	
	template<class I>
	static bool isType(Interface interface)
	{
		return interface.m_typeHash == typeid(I).hash_code();
	}
	
	Interface &operator=(const Interface& other)
	{
		m_name = other.name();
		m_versionId = other.versionId();
		m_typeHash = other.typeHash();
		m_isValid= other.isValid();
		return *this;
	}
	
	friend bool operator<(const Interface& key1, const Interface& key2)
	{
		return key1.m_name < key2.m_name;
	}
	
	friend bool operator==(const Interface& key1, const Interface& key2)
	{
		return key1.m_name == key2.m_name;
	}
	
	friend QDebug operator<<(QDebug &debug, const Interface &instance)
	{
		debug << QString("%1 (%2)\n").arg(instance.m_name).arg(instance.m_versionId);
		return debug;
	}
	
	const QString &name() const
	{
		return m_name;
	}
	
	const QString &versionId() const
	{
		return m_versionId;
	}
	
	size_t typeHash() const
	{
		return m_typeHash;
	}
	
	bool isValid() const
	{
		return m_isValid;
	}
	
private:
	QString m_name;
	QString m_versionId;
	size_t m_typeHash;
	bool m_isValid;
};

#define INTERFACE(Type) Interface::make<Type>(#Type)
