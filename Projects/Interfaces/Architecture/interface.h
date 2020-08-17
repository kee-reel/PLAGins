#pragma once

#include <QtCore>

struct Interface
{
	Interface() = default;
	
	Interface(QString iid) : m_iid(iid)
	{
		Q_ASSERT(!iid.isEmpty());
	}
	
	Interface(const Interface &other) : m_iid(other.iid())
	{
	}
	
	template<class I>
	static Interface make()
	{
		return Interface(qobject_interface_iid<I*>());
	}
	
	Interface &operator=(const Interface& other)
	{
		m_iid = other.iid();
		return *this;
	}
	
	friend bool operator<(const Interface& key1, const Interface& key2)
	{
		return key1.iid() < key2.iid();
	}
	
	friend bool operator==(const Interface& key1, const Interface& key2)
	{
		return key1.iid() == key2.iid();
	}

	friend bool operator!=(const Interface& key1, const Interface& key2)
	{
		return key1.iid() != key2.iid();
	}
	
	friend QDebug operator<<(QDebug &debug, const Interface &instance)
	{
		debug << instance.iid();
		return debug;
	}
	
	inline const QString &iid() const
	{
		Q_ASSERT(!m_iid.isEmpty());
		return m_iid;
	}
	
private:
	QString m_iid;
};

#define INTERFACE(Type) Interface::make<Type>()
