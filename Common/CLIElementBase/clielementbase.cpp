#include "clielementbase.h"

CLIElement::CLIElement(QObject* parent, QString commandName, QString help) :
	QObject(parent),
	m_commandName(commandName),
	m_help(help)
{

}

void CLIElement::handle(const QStringList& args)
{
	emit onHandle(args);
}

QString CLIElement::help()
{
	return m_help;
}

QString CLIElement::getComandName()
{
	return m_commandName;
}
