#include "settings.h"
#include <QGuiApplication>
#include <QUrl>

Settings *Settings::self = 0;

Settings::Settings(QObject *parent) : QSettings(QGuiApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat, parent) {
    self = this;
    if (allKeys().isEmpty()) {
        setValue("placesLocalFile", "city.list.json");
        setValue("mapFileName", "map.html");
        setValue("mapDefaultScale", 6);
        setValue("refreshPeriodSec", 10 * 60);
        setValue("openweathermapAppid", "ccc14cee93ba94cebca502708f6fca03");
    }
}

Settings *Settings::getInstance() {
    return self;
}

QString Settings::makeAbsolutePath(const QString &path) {
    return makeAbsolutePath(QUrl(path));
}

QString Settings::makeAbsolutePath(const QUrl &url) {
    QString str = url.toString();
    if (url.isRelative()) {
        str.prepend(QGuiApplication::applicationDirPath() + "/");
    }
    return str;
}
