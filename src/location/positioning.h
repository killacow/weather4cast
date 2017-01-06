#ifndef POSITIONING_H
#define POSITIONING_H

#include <QObject>
#include <QGeoCoordinate>
#include <QtNetwork>

class Positioning : public QObject
{
    Q_OBJECT
public:
    explicit Positioning(QObject *parent = 0);
    const QGeoCoordinate &getLocation() const;
    bool requestRefreshLocation();

signals:
    void responseRefreshLocation(bool errorFlag, const QGeoCoordinate &location);

public slots:
    void clearLocation();

protected:
    QGeoCoordinate location;
    QNetworkAccessManager *networkAccessManager;

protected slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // POSITIONING_H
