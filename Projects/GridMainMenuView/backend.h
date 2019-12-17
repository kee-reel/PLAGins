#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

class IBackEnd
{
public:
	virtual QString someText() = 0;
};
Q_DECLARE_INTERFACE(IBackEnd, "IBackEnd")

class BackEnd : public QObject, public IBackEnd
{
	Q_OBJECT
	Q_PROPERTY(QString someText READ someText NOTIFY someTextChanged)
	Q_INTERFACES(IBackEnd)
public:
	BackEnd(QObject* parent=nullptr) :
		QObject(parent),
		m_someText("Some text")
	{
		qDebug() << "X";
		connect(&m_timer, &QTimer::timeout, this, &BackEnd::onTimer);
		m_timer.start(10000);
	}
	
	Q_INVOKABLE QString someText() override
	{
		return m_someText;
	}

private Q_SLOTS:
	void onTimer()
	{
		m_someText = QString::number(QRandomGenerator::global()->generate());
		Q_EMIT someTextChanged();
	}

Q_SIGNALS:
	void someTextChanged();
	
private:
	QString m_someText;
	QTimer m_timer;
};

#endif // BACKEND_H
