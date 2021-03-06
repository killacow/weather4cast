# TODO: Разобраться, почему при деплое при помощи windeployqt не копируется папка QtWebEngine. Если то же делать с примером minimal - папка копируется.

TEMPLATE = app

QT += qml quick webengine positioning network
CONFIG += c++11
CONFIG   -= app_bundle

RC_FILE = app.rc

SOURCES += main.cpp \
    location/places.cpp \
    location/positioning.cpp \
    weather/currentweather.cpp \
    weather/forecast.cpp \
    weather/weather.cpp \
    weather/weathermanager.cpp \
    location/locationmanager.cpp \
    weather/forecastmodel.cpp \
    location/place.cpp \
    location/placesmodel.cpp \
    location/fileparser.cpp \
    settings.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    location/places.h \
    location/positioning.h \
    weather/currentweather.h \
    weather/forecast.h \
    weather/weather.h \
    weather/weathermanager.h \
    utils.h \
    location/locationmanager.h \
    weather/forecastmodel.h \
    location/place.h \
    location/placesmodel.h \
    location/fileparser.h \
    settings.h
