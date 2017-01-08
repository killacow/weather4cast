#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/qtwebengineglobal.h>

#include "settings.h"

#include "location/placesmodel.h"
#include "location/locationmanager.h"
#include "location/place.h"

#include "weather/weathermanager.h"
#include "weather/currentweather.h"
#include "weather/forecast.h"
#include "weather/forecastmodel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    //    QApplication app(argc, argv); // for qml charts

    Settings settings;
    Q_UNUSED(settings); // supress warnings

    LocationManager locationManager;
    PlacesModel *placesModel = locationManager.getPlacesModel();

    WeatherManager weatherManager;
    CurrentWeather *currentWeather = weatherManager.getCurrentWeather();
    Forecast *forecast = weatherManager.getForecast();
    ForecastModel *forecastModel = weatherManager.forecastModel;

    QObject::connect(&locationManager, SIGNAL(currentPlaceUpdated(Place)), &weatherManager, SLOT(currentPlaceUpdated(Place)));

    QtWebEngine::initialize();
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("mapFileName", Settings::makeAbsolutePath(Settings::getInstance()->value("mapFileName").toUrl()));
    context->setContextProperty("mapDefaultScale", Settings::getInstance()->value("mapDefaultScale"));
    context->setContextProperty("locationManager", &locationManager);
    context->setContextProperty("placesModel", placesModel);
    context->setContextProperty("currentWeather", currentWeather);
    context->setContextProperty("forecast", forecast);
    context->setContextProperty("forecastModel", forecastModel);
    engine.load(QUrl(QStringLiteral("qrc:/view/main.qml")));

    return app.exec();
}
