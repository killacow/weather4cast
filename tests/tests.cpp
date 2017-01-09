#include <QString>
#include <QtTest>
#include <QGeoCoordinate>
#include <QByteArray>
#include <QDateTime>
#include "../src/location/positioning.h"
#include "../src/location/fileparser.h"
#include "../src/location/place.h"
#include "../src/weather/weathermanager.h"
#include "../src/weather/currentweather.h"
#include "../src/weather/weather.h"
#include "../src/weather/forecast.h"
#include "../src/settings.h"

class Tests : public QObject
{
    Q_OBJECT

public:
    Tests();

private Q_SLOTS:
    void testPositioning();
    void testPlace();
    void testCurrentWeather();
    void testForecast();
};

Tests::Tests() {

}

void Tests::testPositioning() {
    QByteArray a("<query><status><![CDATA[ success ]]></status><country><![CDATA[ Russia ]]></country><countryCode><![CDATA[ RU ]]></countryCode><region><![CDATA[ PER ]]></region><regionName><![CDATA[ Perm Krai ]]></regionName><city><![CDATA[ Perm ]]></city><zip><![CDATA[ 614000 ]]></zip><lat><![CDATA[ 58 ]]></lat><lon><![CDATA[ 56.25 ]]></lon><timezone><![CDATA[ Asia/Yekaterinburg ]]></timezone><isp><![CDATA[ JSC ER-Telecom Holding ]]></isp><org><![CDATA[ JSC ER-Telecom Holding ]]></org><as><![CDATA[ AS12768 ER-TELECOM-AS ]]></as><query><![CDATA[ 37.112.7.205 ]]></query></query>");
    QGeoCoordinate c;
    QVERIFY(Positioning::parseLocationXML(a, &c));

    QCOMPARE(c, QGeoCoordinate(58, 56.25));
}

void Tests::testPlace() {
    QByteArray a("{\"_id\":8011163,\"name\":\"Arões (São Romão)\",\"country\":\"PT\",\"coord\":{\"lon\":-8.22069,\"lat\":41.45821}}");
    Place p;
    QVERIFY(FileParser::parseJson(a, &p));

    QCOMPARE(p.id, 8011163);
    QCOMPARE(p.name, QString("Arões (São Romão)"));
    QCOMPARE(p.country, QString("PT"));
    QCOMPARE(p.coordinate, QGeoCoordinate(41.45821, -8.22069));
}

void Tests::testCurrentWeather() {
    QByteArray a("<current><city id=\"3632308\" name=\"Merida\"><coord lon=\"-71.14\" lat=\"8.6\"/><country>VE</country><sun rise=\"2017-01-08T11:01:59\" set=\"2017-01-08T22:41:20\"/></city><temperature value=\"13.56\" min=\"13.56\" max=\"13.56\" unit=\"metric\"/><humidity value=\"99\" unit=\"%\"/><pressure value=\"817.9\" unit=\"hPa\"/><wind><speed value=\"0.87\" name=\"Calm\"/><gusts/><direction value=\"142.002\" code=\"SE\" name=\"SouthEast\"/></wind><clouds value=\"48\" name=\"scattered clouds\"/><visibility/><precipitation mode=\"no\"/><weather number=\"802\" value=\"scattered clouds\" icon=\"03d\"/><lastupdate value=\"2017-01-08T11:41:24\"/></current>");
    CurrentWeather w;
    QVERIFY(WeatherManager::parseCurrentWeatherXml(a, &w));

    QCOMPARE(w.cityId, 3632308);
    QCOMPARE(w.cityName, QString("Merida"));
    QCOMPARE(w.cityCoord, QGeoCoordinate(8.6, -71.14));
    QCOMPARE(w.cityCountry, QString("VE"));
    QCOMPARE(w.citySunRise, QDateTime(QDate(2017, 1, 8), QTime(11, 1, 59), Qt::UTC));
    QCOMPARE(w.citySunSet, QDateTime(QDate(2017, 1, 8), QTime(22, 41, 20), Qt::UTC));
    QCOMPARE(w.visibilityValue, 0.0);
    QCOMPARE(w.lastupdateValue, QDateTime(QDate(2017, 1, 8), QTime(11, 41, 24), Qt::UTC));

    QCOMPARE(w.weatherNumber, 802);
    QCOMPARE(w.weatherValue, QString("scattered clouds"));
    QCOMPARE(w.weatherIcon, QString("03d"));
    QCOMPARE(w.precipitationMode, QString("no"));
    QCOMPARE(w.precipitationValue, 0.0);
    QCOMPARE(w.windDirectionValue, 142.002);
    QCOMPARE(w.windDirectionCode, QString("SE"));
    QCOMPARE(w.windDirectionName, QString("SouthEast"));
    QCOMPARE(w.windSpeedValue, 0.87);
    QCOMPARE(w.windSpeedName, QString("Calm"));
    QCOMPARE(w.temperatureValue, 13.56);
    QCOMPARE(w.temperatureMin, 13.56);
    QCOMPARE(w.temperatureMax, 13.56);
    QCOMPARE(w.temperatureUnit, QString("metric"));
    QCOMPARE(w.pressureValue, 817.9);
    QCOMPARE(w.pressureUnit, QString("hPa"));
    QCOMPARE(w.humidityValue, 99.0);
    QCOMPARE(w.humidityUnit, QString("%"));
    QCOMPARE(w.cloudsValue, 48.0);
    QCOMPARE(w.cloudsName, QString("scattered clouds"));
}

void Tests::testForecast() {
    QByteArray a("<weatherdata><location><name>Mao</name><type/><country>DO</country><timezone/><location altitude=\"0\" latitude=\"19.551861\" longitude=\"-71.078133\" geobase=\"geonames\" geobaseid=\"0\"/></location><credit/><meta><lastupdate/><calctime>0.1983</calctime><nextupdate/></meta><sun rise=\"2017-01-08T11:20:37\" set=\"2017-01-08T22:22:17\"/><forecast><time from=\"2017-01-08T12:00:00\" to=\"2017-01-08T15:00:00\"><symbol number=\"800\" name=\"clear sky\" var=\"02d\"/><precipitation/><windDirection deg=\"170.003\" code=\"S\" name=\"South\"/><windSpeed mps=\"1.16\" name=\"Calm\"/><temperature unit=\"celsius\" value=\"26.17\" min=\"26.17\" max=\"27.07\"/><pressure unit=\"hPa\" value=\"1016.8\"/><humidity value=\"76\" unit=\"%\"/><clouds value=\"clear sky\" all=\"8\" unit=\"%\"/></time><time from=\"2017-01-08T15:00:00\" to=\"2017-01-08T18:00:00\"><symbol number=\"800\" name=\"clear sky\" var=\"01d\"/><precipitation/><windDirection deg=\"340.001\" code=\"NNW\" name=\"North-northwest\"/><windSpeed mps=\"1.78\" name=\"Light breeze\"/><temperature unit=\"celsius\" value=\"27.83\" min=\"27.83\" max=\"28.42\"/><pressure unit=\"hPa\" value=\"1014.78\"/><humidity value=\"69\" unit=\"%\"/><clouds value=\"clear sky\" all=\"0\" unit=\"%\"/></time></forecast></weatherdata>");
    Forecast f;
    QVERIFY(WeatherManager::parseForecastXml(a, &f));

    QCOMPARE(f.locationName, QString("Mao"));
    QCOMPARE(f.locationCountry, QString("DO"));
    QCOMPARE(f.location, QGeoCoordinate(19.551861, -71.078133, 0));
    QCOMPARE(f.metaCalctime, 0.1983);
    QCOMPARE(f.sunRise, QDateTime(QDate(2017, 1, 8), QTime(11, 20, 37), Qt::UTC));
    QCOMPARE(f.sunSet, QDateTime(QDate(2017, 1, 8), QTime(22, 22, 17), Qt::UTC));

    QCOMPARE(f.forecastTimeFrom.size(), 2);
    QCOMPARE(f.forecastTimeTo.size(), 2);
    QCOMPARE(f.forecastWeather.size(), 2);

    int i = 0;
    Weather *w;

    QCOMPARE(f.forecastTimeFrom.at(i), QDateTime(QDate(2017, 1, 8), QTime(12, 0, 0), Qt::UTC));
    QCOMPARE(f.forecastTimeTo.at(i), QDateTime(QDate(2017, 1, 8), QTime(15, 0, 0), Qt::UTC));

    w = f.forecastWeather.at(i);
    QCOMPARE(w->weatherNumber, 800);
    QCOMPARE(w->weatherValue, QString("clear sky"));
    QCOMPARE(w->weatherIcon, QString("02d"));
    QCOMPARE(w->precipitationMode, QString("no"));
    QCOMPARE(w->precipitationValue, 0.0);
    QCOMPARE(w->windDirectionValue, 170.003);
    QCOMPARE(w->windDirectionCode, QString("S"));
    QCOMPARE(w->windDirectionName, QString("South"));
    QCOMPARE(w->windSpeedValue, 1.16);
    QCOMPARE(w->windSpeedName, QString("Calm"));
    QCOMPARE(w->temperatureValue, 26.17);
    QCOMPARE(w->temperatureMin, 26.17);
    QCOMPARE(w->temperatureMax, 27.07);
    QCOMPARE(w->temperatureUnit, QString("celsius"));
    QCOMPARE(w->pressureValue, 1016.8);
    QCOMPARE(w->pressureUnit, QString("hPa"));
    QCOMPARE(w->humidityValue, 76.0);
    QCOMPARE(w->humidityUnit, QString("%"));
    QCOMPARE(w->cloudsValue, 8.0);
    QCOMPARE(w->cloudsName, QString("clear sky"));

    ++i;

    QCOMPARE(f.forecastTimeFrom.at(i), QDateTime(QDate(2017, 1, 8), QTime(15, 0, 0), Qt::UTC));
    QCOMPARE(f.forecastTimeTo.at(i), QDateTime(QDate(2017, 1, 8), QTime(18, 0, 0), Qt::UTC));

    w = f.forecastWeather.at(i);
    QCOMPARE(w->weatherNumber, 800);
    QCOMPARE(w->weatherValue, QString("clear sky"));
    QCOMPARE(w->weatherIcon, QString("01d"));
    QCOMPARE(w->precipitationMode, QString("no"));
    QCOMPARE(w->precipitationValue, 0.0);
    QCOMPARE(w->windDirectionValue, 340.001);
    QCOMPARE(w->windDirectionCode, QString("NNW"));
    QCOMPARE(w->windDirectionName, QString("North-northwest"));
    QCOMPARE(w->windSpeedValue, 1.78);
    QCOMPARE(w->windSpeedName, QString("Light breeze"));
    QCOMPARE(w->temperatureValue, 27.83);
    QCOMPARE(w->temperatureMin, 27.83);
    QCOMPARE(w->temperatureMax, 28.42);
    QCOMPARE(w->temperatureUnit, QString("celsius"));
    QCOMPARE(w->pressureValue, 1014.78);
    QCOMPARE(w->pressureUnit, QString("hPa"));
    QCOMPARE(w->humidityValue, 69.0);
    QCOMPARE(w->humidityUnit, QString("%"));
    QCOMPARE(w->cloudsValue, 0.0);
    QCOMPARE(w->cloudsName, QString("clear sky"));
}

QTEST_APPLESS_MAIN(Tests)

#include "tests.moc"
