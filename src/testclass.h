#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include <QtGui>
#include <QGeoCoordinate>

// FIXME: REMOVE ME!

class TestClass : public QObject
{
    Q_OBJECT
public:
    explicit TestClass(QObject *parent = 0);

signals:
    void sig(QString str);
    void locationUpdated(const QGeoCoordinate &location);

public slots:
    void responseRefreshLocation(bool errorFlag, const QGeoCoordinate &location);

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // TESTCLASS_H
