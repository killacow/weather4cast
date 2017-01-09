#ifndef PLACESMODEL_H
#define PLACESMODEL_H

#include <QAbstractListModel>
#include <QtGui>

class LocationManager;
class Place;
class Places;

class PlacesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlacesModel(LocationManager *locationManager, Places *places, QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE void selectPlace(int index);
    Q_INVOKABLE int getIndexByText(QString text);

public slots:
    void updated();

protected:
    LocationManager *locationManager;
    Places *places;
    QList<Place *> placeList;
};
#endif // PLACESMODEL_H
