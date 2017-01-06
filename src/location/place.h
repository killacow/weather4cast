#ifndef PLACE_H
#define PLACE_H

#include <QObject>

class Place : public QObject
{
    Q_OBJECT
public:
    explicit Place(QObject *parent = 0);

    int id;
    QString name;
    QString country;
    QGeoCoordinate coordinate;

signals:

public slots:
};

#endif // PLACE_H
