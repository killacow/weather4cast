#include "places.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

#include "place.h"
#include "fileparser.h"

// FIXME: Написать пространный комментарий о том что лучше каждый раз вытягивать список городов заново, а не работать с локальным.

Places::Places(QObject *parent) : QObject(parent) {
    fileParser = new FileParser(this);
    connect(fileParser, SIGNAL(done(bool,QHash<int,Place*>*)), this, SLOT(done(bool,QHash<int,Place*>*)));
}

Places::~Places() {
    clear();
}

void Places::readLocalFile() {
    fileParser->parseFile("D:/Downloads/city.list.json/city.list.json"); // FIXME: Положить файл рядом с приложением, имя файла и путь - в ini.
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
