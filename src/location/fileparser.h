#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QThread>
#include <QHash>

class Place;

class FileParser : public QThread
{
    Q_OBJECT
public:
    explicit FileParser(QObject *parent = 0);
    void parseFile(const QString &fileName);
    static bool parseJson(const QByteArray &jsonData, Place *place);

signals:
    void done(bool error, QHash<int, Place *> *places);

protected:
    QString fileName;
    QHash<int, Place *> places;
    void run();
};

#endif // FILEPARSER_H
