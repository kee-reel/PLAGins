#ifndef METADATAPARSER_H
#define METADATAPARSER_H

#include <QObject>

class MetaDataParser : public QObject
{
    Q_OBJECT
public:
    explicit MetaDataParser(QObject *parent = nullptr);

signals:

public slots:
};

#endif // METADATAPARSER_H
