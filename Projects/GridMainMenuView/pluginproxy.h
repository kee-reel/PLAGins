#ifndef PLUGINPROXY_H
#define PLUGINPROXY_H

#include <QObject>
#include "backend.h"

class PluginProxy : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QObject* backEnd READ backEnd NOTIFY backEndChanged)
public:
	PluginProxy(QObject* parent=nullptr) :
		QObject(parent),
		m_backEnd(new BackEnd)
	{
	}
	
	QObject* backEnd()
	{
		return m_backEnd;
	}
Q_SIGNALS:
	void backEndChanged();
private:
	QObject* m_backEnd;
};

#endif // PLUGINPROXY_H
