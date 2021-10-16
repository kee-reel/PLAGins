#include "%{HdrFileName}"

%{CN}::%{CN}(QObject* parent) :
	QObject(parent)
{
}

%{CN}::~%{CN}()
{
}


QString %{CN}::testString()
{
	return m_testString;
}

void %{CN}::setTestString(QString testString)
{
	if (m_testString == testString)
		return;
	
	m_testString = testString;
	qDebug() << "New text:" << testString;
	emit testStringChanged(m_testString);
}
