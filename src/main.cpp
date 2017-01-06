#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/qtwebengineglobal.h>

//#include <QtGui>

#include "testclass.h"
#include "location/positioning.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TestClass t;
    Positioning p;

    QObject::connect(&p, SIGNAL(responseRefreshLocation(bool,QGeoCoordinate)), &t, SLOT(responseRefreshLocation(bool,QGeoCoordinate)));

    QtWebEngine::initialize();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("locationManager", &t);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
