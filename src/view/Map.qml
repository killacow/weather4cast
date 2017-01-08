import QtQuick 2.0
import QtWebEngine 1.0
import QtPositioning 5.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

/**
 * Объект - карта.
 * Фактически объект представляет собой браузер.
 * Содержимое карты определяет файл map.html, данный объект только отображает эту html страницу
 * и позволяет перемещать область видимости карты при помощи выполнения метода setView в коде страницы.
 */
WebEngineView {
    id: webEngineView
    url: "file:///" + mapFileName // Открываем в браузере страницу с картой.
    Connections {
        // Подписываемся на сигнал locationUpdated, посылаемый объектом-locationManager.
        target: locationManager
        onLocationUpdated: {
            // При поступлении сигнала получаем из его параметров широту и долготу и перемещаем область видимости карты методом setView в map.html.
            webEngineView.runJavaScript("setView(%1, %2, %3);".arg(location.latitude).arg(location.longitude).arg(mapDefaultScale))
        }
    }
}

