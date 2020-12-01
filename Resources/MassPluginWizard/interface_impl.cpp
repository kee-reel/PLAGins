#include "%{HdrFileName}"

%{CN}::%{CN}(QObject* parent) :
	QObject(parent)
{
}

%{CN}::~%{CN}()
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
	emit testStringChanged(m_testString);
}
