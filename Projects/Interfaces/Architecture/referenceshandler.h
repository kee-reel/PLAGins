#pragma once

#include "ireferenceshandler.h"
#include "referenceinstanceslist.h"

template <class IdentifierT>
class ReferencesHandler : public IReferencesHandler<IdentifierT>
{
public:
	ReferencesHandler(const QMap<IdentifierT, IReferenceInstancePtr > &instances, const QMap<IdentifierT, IReferenceInstancesListPtr > &instancesLists) :
		m_state(ReferencesHandlerState::SETTING_REFS),
		m_instances(instances),
		m_instancesList(instancesLists)
	{
		for(auto iter = m_instances.begin(); iter != m_instances.end(); ++iter)
		{
			m_identifiers[iter.key()] = 1;
		}
		for(auto iter = m_instancesList.begin(); iter != m_instancesList.end(); ++iter)
		{
			Q_ASSERT(!m_identifiers.contains(iter.key()));
			m_identifiers[iter.key()] = iter.value().toStrongRef()->limit();
		}
	}

	// IReferencesHandler interface
public:
	virtual const QMap<IdentifierT, int> &requiredReferences() override
	{
		return m_identifiers;
	}

	virtual const QMap<IdentifierT, QList<IReferenceDescriptorPtr> > &references() override
	{
		return m_references;
	}

	virtual bool setReferences(IdentifierT identifier, QList<IReferenceDescriptorPtr> references) override
	{
		auto iter = m_identifiers.find(identifier);
		if(iter == m_identifiers.end())
		{
			return false;
		}

		auto &&referencesCount = iter.value();
		if(referencesCount != 0 && referencesCount != references.size())
		{
			return false;
		}

		if(referencesCount == 1)
		{
			auto instance = m_instances[identifier];
			instance.toStrongRef()->clearInstance();
			if(!instance.toStrongRef()->setInstance(references[0]))
			{
				instance.toStrongRef()->clearInstance();
				return false;
			}
			m_references[identifier].append(references[0]);
		}
		else
		{
			auto instancesList = m_instancesList[identifier];
			instancesList.toStrongRef()->clearInstances();
			for(auto &ref : references)
			{
				if(!instancesList.toStrongRef()->append(ref))
				{
					return false;
				}
				m_references[identifier].append(ref);
			}
			if(m_state == ReferencesHandlerState::WAITING || m_state == ReferencesHandlerState::READY)
			{
				referencesListUpdated(identifier);
			}
		}

		checkReferencesUpdate();
		return true;
	}

	virtual bool transitToReadyState() override
	{
		if(m_state == ReferencesHandlerState::SETTING_REFS)
		{
			return false;
		}
		setState(ReferencesHandlerState::READY);
		return true;
	}

	virtual ReferencesHandlerState state() override
	{
		return m_state;
	}

protected:
	void checkReferencesUpdate()
	{
		bool isSet = true;
		for(auto iter = m_instances.begin(); iter != m_instances.end(); ++iter)
		{
			if(!iter.value().toStrongRef()->isSet())
			{
				isSet = false;
				break;
			}
		}

		ReferencesHandlerState newState = m_state;
		switch(m_state)
		{
		case ReferencesHandlerState::SETTING_REFS:
			if(isSet)
			{
				newState = ReferencesHandlerState::WAITING;
			}
			break;
		case ReferencesHandlerState::WAITING:
		case ReferencesHandlerState::READY:
			if(!isSet)
			{
				newState = ReferencesHandlerState::SETTING_REFS;
			}
			break;
		}

		setState(newState);
	}

protected:
	virtual void setState(ReferencesHandlerState state) = 0;
	virtual void referencesListUpdated(IdentifierT identifier) = 0;

protected:
	ReferencesHandlerState m_state;

private:
	QMap<IdentifierT, int> m_identifiers;
	QMap<IdentifierT, QList<IReferenceDescriptorPtr>> m_references;
	QMap<IdentifierT, IReferenceInstancePtr> m_instances;
	QMap<IdentifierT, IReferenceInstancesListPtr> m_instancesList;
};
