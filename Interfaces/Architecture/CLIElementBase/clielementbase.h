#pragma once

#include <QtCore>

#include "../../Interfaces/Architecture/iclielement.h"


class CLIElement : public QObject, public ICLIElement
{
	Q_OBJECT
	Q_INTERFACES(ICLIElement)
public:
	CLIElement(QObject* parent, QString commandName, QString help);

	// ICLIElement interface
public:
	void handle(const QStringList& args) override;
	QString help() override;
	QString getComandName() override;

signals:
	void onHandle(const QStringList& args);

private:
	QString m_commandName;
	QString m_help;
};
