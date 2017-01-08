#include "places.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

#include "place.h"
#include "fileparser.h"
#include "../settings.h"
#include <QUrl>
#include <QGuiApplication>


/**
 * @brief Менеджер списка мест.
 *
 * TODO: Менеджер работает с локальным файлом, однако, это неправильно.
 * Поскольку всю остальную информацию приложение вытягивает с внешних ресурсов,
 * нужно и его тоже каждый раз обновлять отсюда: http://bulk.openweathermap.org/sample/city.list.json.gz
 *
 * @param parent Предок согласно объектной иерархии Qt.
 */
Places::Places(QObject *parent) : QObject(parent) {
    fileParser = new FileParser(this);
    connect(fileParser, SIGNAL(done(bool,QHash<int,Place*>*)), this, SLOT(done(bool,QHash<int,Place*>*)));
}

Places::~Places() {
    clear();
}

void Places::readLocalFile() {
    fileParser->parseFile(Settings::makeAbsolutePath(Settings::getInstance()->value("placesLocalFile").toUrl()));
}

void Places::clear() {
    qDeleteAll(places);
    places.clear();
}

QHash<int, Place *> Places::getPlaces() const {
    return places;
}

void Places::done(bool error, QHash<int, Place *> *places) {
    if (!error) {
        clear();
        this->places = *places;
        emit updated();
    }
}
