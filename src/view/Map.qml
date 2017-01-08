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




//    RowLayout {

//        anchors.fill: parent
        WebEngineView {

            // FIXME: to ini
            property string fileName: applicationDirPath +"/map.html"
            property int defaultScale: 6

//            Layout.fillHeight: true
//            Layout.fillWidth: true

            id: webEngineView

            url: fileName // Открываем в браузере страницу с картой.

            Connections {
                // Подписываемся на сигнал locationUpdated, посылаемый объектом-locationManager.
                target: locationManager
                //            onCurrentPlaceUpdated:
                onLocationUpdated:
                {
                    //if (webEngineView.loading == false)
                    {
                        // При поступлении сигнала получаем из его параметров широту и долготу и перемещаем область видимости карты методом setView в map.html.
                        //                webEngineView.runJavaScript("setView(%1, %2, %3);".arg(currentPlace.coord.latitude).arg(currentPlace.coord.longitude).arg(defaultScale))
                        webEngineView.runJavaScript("setView(%1, %2, %3);".arg(location.latitude).arg(location.longitude).arg(defaultScale))
                        //placesModel.selectPlace(list.currentIndex);//
                    }
                }
            }

            //        onLoadingChanged: {
            //            console.log("loadRequest" + loadRequest.status)
            //            if (loadRequest.status == WebEngineView.LoadSucceededStatus) {
            //                placesModel.selectPlace(list.currentIndex);
            //            }
            //        }



            //        Component.onCompleted: {
            //            webEngineView.url = fileName;
            //            console.log("Nested Completed Running!")
            //        }
        }
//    }
//}
