#include "database.h"

DataBase::DataBase() :
	QObject(nullptr),
	PluginBase(this,
{
	INTERFACE(IDataBase)
})
{
	m_possibleDriverNames<< "SQLITECIPHER"<< "QSQLITE";
	referencesInit();
}

DataBase::~DataBase()
{
	m_dbconn.close();
}

void DataBase::onReady()
{
	Setup();
}

QSqlQuery DataBase::ExecuteQuery(QString &queryText)
{
	if(!Setup())
	{
		return QSqlQuery();
	}

	QSqlQuery query;
	if(!query.exec(queryText))
	{
		qDebug() << "Error in execution query" << queryText << "Error:" << query.lastError();
	}
	return query;
}

QSqlQuery DataBase::ExecuteQuery(QString &queryText, QList<QString> *valuePlaceholders, QList<QVariant> *values)
{
	QSqlQuery query;
	if(valuePlaceholders->count() != values->count())
	{
		qDebug() << "Values lists count not equal";
		return query;
	}
	query.prepare(queryText);
	for(int i = 0; i < valuePlaceholders->count(); ++i)
	{
		QFlags<QSql::ParamTypeFlag> flag = (values->at(i).type() == QVariant::ByteArray) ? QSql::In | QSql::Binary : QSql::In;
		query.bindValue(valuePlaceholders->at(i), values->at(i), flag);
	}

	if(!query.exec())
	{
		qDebug() << "Error in execution query" << queryText << "Error:" << query.lastError();
	}
	return query;
}

void DataBase::SetPassword(QString password)
{
	m_password = password;
}

bool DataBase::Setup()
{
	if(m_dbconn.isOpen())
	{
		return true;
	}

//	qDebug() << "Available drivers are" << QSqlDatabase::drivers();
	foreach (auto driverName, m_possibleDriverNames)
	{
		if(ConnectWithDriver(driverName))
		{
//			qDebug() << "Connected to database with driver:" << driverName;
			return true;
		}
	}
	return false;
}

bool DataBase::ConnectWithDriver(QString driverName)
{
	if(!QSqlDatabase::isDriverAvailable(driverName))
	{
//		qCritical() << "Driver not available";
		return false;
	}

	m_connectionName = QString("db_%1.db").arg(driverName);
	m_dbconn = QSqlDatabase::addDatabase(driverName);

	// Create database
	m_dbconn.setDatabaseName(m_connectionName);
	m_dbconn.setPassword(m_password);
	bool isConnected = m_dbconn.open();

	if(isConnected)
	{
		m_password = "";
	}
	else
	{
		qCritical() << "Database connection error:" << m_dbconn.lastError();
	}

	return isConnected;
}
