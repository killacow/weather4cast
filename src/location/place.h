#ifndef PLACE_H
#define PLACE_H

#include <QObject>
#include <QGeoCoordinate>

class Place : public QObject
{
    Q_OBJECT
public:
    explicit Place(QObject *parent = 0);
    Place &operator=(const Place &other);

    int id;
    QString name;
    QString country;
    QGeoCoordinate coordinate;
};

#endif // PLACE_H
