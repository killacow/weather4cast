#ifndef FORECASTMODEL_H
#define FORECASTMODEL_H

#include <QAbstractListModel>
#include <QtGui>

class ForecastModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ForecastModel(QObject *parent = 0);

signals:

public slots:
};

#endif // FORECASTMODEL_H
