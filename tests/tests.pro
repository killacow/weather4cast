#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T13:20:59
#
#-------------------------------------------------

QT       += widgets qml quick webengine xml xmlpatterns testlib qml quick webengine positioning network charts

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ../src/location/positioning.cpp \
    tests.cpp \
    ../src/location/fileparser.cpp \
    ../src/location/place.cpp \
    ../src/weather/weathermanager.cpp \
    ../src/weather/currentweather.cpp \
    ../src/weather/forecast.cpp \
    ../src/weather/weather.cpp \
    ../src/location/locationmanager.cpp \
    ../src/location/places.cpp \
    ../src/location/placesmodel.cpp \
    ../src/weather/forecastmodel.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../src/location/positioning.h \
    ../src/location/fileparser.h \
    ../src/location/place.h \
    ../src/weather/weathermanager.h \
    ../src/weather/currentweather.h \
    ../src/weather/forecast.h \
    ../src/weather/weather.h \
    ../src/utils.h \
    ../src/location/locationmanager.h \
    ../src/location/places.h \
    ../src/location/placesmodel.h \
    ../src/weather/forecastmodel.h

