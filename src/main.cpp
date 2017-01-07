#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/qtwebengineglobal.h>

//#include <QtGui>

#include "testclass.h"
//#include "location/positioning.h"
#include "location/placesmodel.h"
#include "location/locationmanager.h"
#include "location/place.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
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
    locationManager.setCurrentPlace(LocationManager::autoLocation);
    PlacesModel *placesModel = locationManager.getPlacesModel();


    QtWebEngine::initialize();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("locationManager", &locationManager);
    engine.rootContext()->setContextProperty("placesModel", placesModel);
    engine.load(QUrl(QStringLiteral("qrc:/view/main.qml")));

    return app.exec();
}
