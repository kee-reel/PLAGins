#ifndef REFERENCEINSTANCESHANDLER_H
#define REFERENCEINSTANCESHANDLER_H

#include "../ireferenceinstance.h"
#include "../ireferenceinstanceshandler.h"


class ReferenceInstancesHandler : public QObject, public IReferenceInstancesHandler
{
    Q_OBJECT

public:
    ReferenceInstancesHandler(QMap<Interface, QList<IReferenceInstancePtr > > instances,
                              QMap<Interface, IReferenceInstancesListPtr > instancesLists) :
        QObject(),
        m_instances(instances),
        m_instancesList(instancesLists),
        m_state(State::SETTING_REFS)
    {
        for(auto iter = m_instances.begin(); iter != m_instances.end(); ++iter)
        {
            m_interfaces[iter.key()] = iter.value().size();
        }
        for(auto iter = m_instancesList.begin(); iter != m_instancesList.end(); ++iter)
        {
            Q_ASSERT(!m_interfaces.contains(iter.key()));
            m_interfaces[iter.key()] = 0;
        }
        checkReferencesSet();
    }

    // IReferenceInstancesHandler interface
public:
    virtual const QMap<Interface, int> &requiredReferences() override
    {
        return m_interfaces;
    }

    virtual const QMap<Interface, QList<IReferenceDescriptorPtr> > &references() override
    {
        return m_references;
    }

    virtual bool setReferences(Interface interface, QList<IReferenceDescriptorPtr> references) override
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
            auto instances = m_instances[interface];
            for(int i = 0; i < referencesCount; ++i)
            {
                if(!instances[i].data()->reset(references[i]))
                {
                    for(auto &instance : instances)
                    {
                        instance.data()->reset();
                    }
                    return false;
                }
                m_references[interface].append(references[i]);
            }
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
    virtual void onStateChanged(State stage) override;

private:
    void checkReferencesSet()
    {
        bool isSet = true;
        for(auto iter = m_interfaces.begin(); iter != m_interfaces.end(); ++iter)
        {
            if(m_references[iter.key()].size() != iter.value())
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
    QMap<Interface, int> m_interfaces;
    QMap<Interface, QList<IReferenceDescriptorPtr>> m_references;
    QMap<Interface, QList<IReferenceInstancePtr>> m_instances;
    QMap<Interface, IReferenceInstancesListPtr> m_instancesList;
    bool m_isAllSet;
    State m_state;
};

#endif // REFERENCEINSTANCESHANDLER_H
