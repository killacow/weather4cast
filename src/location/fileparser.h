#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QObject>

class FileParser : public QObject
{
    Q_OBJECT
public:
    explicit FileParser(QObject *parent = 0);

signals:

public slots:
};

#endif // FILEPARSER_H