#ifndef UIELEMENTLINKSHANDLER_H
#define UIELEMENTLINKSHANDLER_H

#include <QObject>

#include "../ireferenceinstance.h"
#include "../../Interfaces/Architecture/iuielement.h"


class UIElementLinksHandler : public QObject, public IUIElementLinksHandler
{
	Q_OBJECT

public:
	UIElementLinksHandler(QMap<QString, IReferenceInstancePtr > instances,
	                      QMap<QString, IReferenceInstancesListPtr > instancesLists) :
		QObject(nullptr),
		m_instances(instances),
		m_instancesList(instancesLists),
		m_isAllSet(false),
		m_state(IUIElementLinksHandler::State::SETTING_REFS)
	{
		for(auto iter = m_instances.begin(); iter != m_instances.end(); ++iter)
		{
			m_interfaces[iter.key()] = 1;
		}
		for(auto iter = m_instancesList.begin(); iter != m_instancesList.end(); ++iter)
		{
			Q_ASSERT(!m_interfaces.contains(iter.key()));
			m_interfaces[iter.key()] = iter.value().data()->limit();
		}
		checkReferencesSet();
	}

	// IReferencesHandler interface
public:
	virtual const QMap<QString, int> &requiredReferences() override
	{
		return m_interfaces;
	}

	virtual const QMap<QString, QList<IReferenceDescriptorPtr> > &references() override
	{
		return m_references;
	}

	virtual bool setReferences(QString interface, QList<IReferenceDescriptorPtr> references) override
	{
		auto iter = m_interfaces.find(interface);
		if(iter == m_interfaces.end())
		{
			return false;
		}

		auto &&referencesCount = iter.value();
		if(referencesCount != 0 && referencesCount != references.size())
		{
			return false;
		}

		if(referencesCount)
		{
			auto instance = m_instances[interface];
			if(!instance.data()->setInstance(references[0]))
			{
				instance.data()->clearInstance();
				return false;
			}
			m_references[interface].append(references[0]);
		}
		else
		{
			auto instancesList = m_instancesList[interface];
			instancesList.clear();
			for(auto &ref : references)
			{
				if(!instancesList.data()->append(std::move(ref)))
				{
					instancesList.clear();
					return false;
				}
				m_references[interface].append(ref);
			}
		}

		checkReferencesSet();
		return true;
	}

	virtual bool transitToReadyState() override
	{
		if(m_state != State::WAITING)
		{
			return false;
		}
		m_state = State::READY;
		emit onStateChanged(m_state);
		return true;
	}

	virtual State state() override
	{
		return m_state;
	}

	virtual QObject *object() override
	{
		return this;
	}

signals:
	void onStateChanged(State stage);

private:
	void checkReferencesSet()
	{
		bool isSet = true;
		for(auto iter = m_instances.begin(); iter != m_instances.end(); ++iter)
		{
			if(!iter.value().data()->isSet())
			{
				isSet = false;
				break;
			}
		}
		if(isSet && m_state == State::SETTING_REFS)
		{
			m_state = State::WAITING;
			emit onStateChanged(m_state);
		}
	}

private:
	QMap<QString, int> m_interfaces;
	QMap<QString, QList<IReferenceDescriptorPtr>> m_references;
	QMap<QString, IReferenceInstancePtr> m_instances;
	QMap<QString, IReferenceInstancesListPtr> m_instancesList;
	bool m_isAllSet;
	State m_state;
};

#endif // UIELEMENTLINKSHANDLER_H
