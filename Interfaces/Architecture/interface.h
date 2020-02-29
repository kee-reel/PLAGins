#pragma once

#include <QtCore>

struct Interface
{
private:
	Interface(QString iid) : m_iid(iid)
	{
		Q_ASSERT(!iid.isEmpty());
	}
	
public:
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
		return key1.m_iid < key2.m_iid;
	}
	
	friend bool operator==(const Interface& key1, const Interface& key2)
	{
		return key1.m_iid == key2.m_iid;
	}
	
	friend QDebug operator<<(QDebug &debug, const Interface &instance)
	{
		debug << instance.m_iid;
		return debug;
	}
	
	const QString &iid() const
	{
		return m_iid;
	}
	
private:
	QString m_iid;
};

#define INTERFACE(Type) Interface::make<Type>()
