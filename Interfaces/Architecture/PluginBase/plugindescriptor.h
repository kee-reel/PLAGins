#ifndef PLUGINDESCRIPTOR_H
#define PLUGINDESCRIPTOR_H

#include "referenceshandler.h"

class PluginDescriptor : public IReferenceDescriptor
{
public:
	static PluginDescriptor* make(uid_t uid, QObject* instance, QWeakPointer<QJsonObject> meta,
	                              QVector<Interface> interfaces, const QSharedPointer<ReferencesHandler> &instances)
	{
		auto metaData = meta.data()->value("MetaData").toObject();
		auto section = metaData.value("iplugin").toObject();


		auto&& infoSection = section.value("info").toObject();
		auto&& name = infoSection.value("name").toString();
		auto&& about = infoSection.value("about").toString();
		if(name.isEmpty() || about.isEmpty())
		{
			qDebug() << QString("PluginBase::parseMetaInfo: parse error: fields name or about is empty.");
			return nullptr;
		}

		QStringList interfacesNames;
		for(auto& interface : interfaces)
		{
			interfacesNames << interface.name();
		}

		auto iterfacesJSONArr = section.value("interfaces").toArray();
		for(auto iterfaceJSON : iterfacesJSONArr)
		{
			auto interface = iterfaceJSON.toString();
			if(interface.isEmpty())
			{
				qDebug() << QString("PluginBase::parseMetaInfo: interface entry is empty.");
				return nullptr;
			}
			else
			{
				assert(interfacesNames.contains(interface));
//				qDebug() << QString("PluginBase::parseMetaInfo: plugin and meta data interfaces description doesn't match.");
			}
		}

		QStringList referencesNames;
		auto &requiredReferences = instances->requiredReferences();
		for(auto iter = requiredReferences.keyBegin(); iter != requiredReferences.keyEnd(); ++iter)
		{
			referencesNames << iter->name();
		}

		auto referencesJSONMap = section.value("references").toObject();
		for(auto iter = referencesJSONMap.begin(); iter != referencesJSONMap.end(); ++iter)
		{
			auto&& referenceName = iter.key();
			auto referencesCount = iter.value().toInt(-1);
			if(referenceName.isEmpty() || referencesCount == -1)
			{
				qDebug() << QString("PluginBase::parseMetaInfo: reference entry is empty or reference count is invalid.");
				return nullptr;
			}
			else
			{
				assert(referencesNames.contains(referenceName));
			}
		}

		auto ptr = new PluginDescriptor();
		ptr->m_uid = uid;
		ptr->m_name = name;
		ptr->m_about = about;
		ptr->m_instance = instance;
		ptr->m_interfaces = interfaces;

//        qDebug() << "PluginDescriptor::make: created reference descriptor:" <<
//            "uid:" << uid << endl <<
//            "name:" << name << endl <<
//            "about:" << about << endl <<
//            "instance:" << instance << endl <<
//            "interfaces:" << interfaces << endl <<
//            "references:" << referencesNames << endl;

		return ptr;
	}
private:
	PluginDescriptor() = default;
public:
	virtual ~PluginDescriptor() = default;

	// IReferenceDescriptor interface
public:
	inline virtual uid_t uid() override
	{
		return m_uid;
	}
	inline virtual const QVector<Interface> &interfaces() override
	{
		return m_interfaces;
	}
	inline virtual const QString &name() override
	{
		return m_name;
	}
	inline virtual const QString &about() override
	{
		return m_about;
	}
	inline virtual QObject *object() override
	{
		return m_instance;
	}

private:
	uid_t m_uid;
	QString m_name;
	QString m_about;
	QObject* m_instance;
	QVector<Interface> m_interfaces;
};

#endif // PLUGINDESCRIPTOR_H
