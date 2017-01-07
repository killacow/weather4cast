#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/qtwebengineglobal.h>

//#include <QtGui>

#include "testclass.h"
//#include "location/positioning.h"
#include "location/placesmodel.h"
#include "location/locationmanager.h"
#include "location/place.h"

#include "weather/weathermanager.h"
#include "weather/currentweather.h"
#include "weather/forecast.h"
#include "weather/forecastmodel.h"

int main(int argc, char *argv[])
{
//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
//    qmlRegisterType<Place>("com.mycompany.messaging", 1, 0, "Place");

//    TestClass t;
//    Positioning p;



//    PlacesModel pm;

//    QStringListModel stringListModel;
//    QStringList list;
//    for (int i = 0; i < 1000; ++i) {
//        list.append(QString::number(i));
//    }
//    stringListModel.setStringList(list);

    //QObject::connect(&p, SIGNAL(responseRefreshLocation(bool,QGeoCoordinate)), &t, SLOT(responseRefreshLocation(bool,QGeoCoordinate)));

    LocationManager locationManager;
    PlacesModel *placesModel = locationManager.getPlacesModel();

    WeatherManager weatherManager;
    CurrentWeather *currentWeather = weatherManager.getCurrentWeather();
    Forecast *forecast = weatherManager.getForecast();
    ForecastModel *forecastModel = weatherManager.forecastModel;


    QtWebEngine::initialize();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("locationManager", &locationManager);
    engine.rootContext()->setContextProperty("placesModel", placesModel);
    engine.rootContext()->setContextProperty("currentWeather", currentWeather);
    engine.rootContext()->setContextProperty("forecast", forecast);
    engine.rootContext()->setContextProperty("forecastModel", forecastModel);
    engine.load(QUrl(QStringLiteral("qrc:/view/main.qml")));

//    locationManager.setCurrentPlace(LocationManager::autoLocation);
    weatherManager.requestCurrenWeather(QGeoCoordinate(58, 56));
    weatherManager.requestForecast(QGeoCoordinate(58, 56));

    return app.exec();
}
