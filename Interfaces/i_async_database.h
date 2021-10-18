#pragma once

#include <QtCore>

class QSqlQuery;

class IQuery
{
public:
	virtual ~IQuery() {}
	virtual QUuid uuid() = 0;
	virtual QObject *object() = 0;
	virtual int lastInsertId() = 0;
	virtual QList<QVector<QVariant>> values() = 0;
public slots:
	virtual void exec() = 0;
signals:
	virtual void completed(QUuid uuid) = 0;
};

class IAsyncDataBase
{
public:
	virtual QSharedPointer<IQuery> executeQueryAsync(const QString &queryStr) = 0;
	virtual QSharedPointer<IQuery> executeQueryAsync(const QString &queryStr,
	        const QList<QString>& valuePlaceholders, const QList<QVariant>& values) = 0;

protected:
	virtual ~IAsyncDataBase() {}
};
Q_DECLARE_INTERFACE(IAsyncDataBase, "IAsyncDataBase/1.0")
//! @}
