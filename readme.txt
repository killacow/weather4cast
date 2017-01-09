Программа weather4cast отображает прогноз погоды и карту скорости ветра.

Программа работает под: 
Windows (Windows Vista и новее; проверялась под 64-разрядными Windows 7 и Windows 10), 
Linux (проверялась на Debian 8.6), 
macOS (проверялась под OS X 10.11 El Capitan).

Известные проблемы
Сервис openweathermap работает весьма нестабильно, так что получение слоя ветров может занять длительное время.

Сборка 
Для сборки программы из исходников вам потребуется установленный фреймворк Qt версии не младше 5.7.1 (в случае Windows обязательно должна быть установлена VS-версия Qt). 
Проверена корректная работа приложения, собранного: 
Qt 5.7.1 for Windows 64-bit VS 2015 (http://download.qt.io/official_releases/qt/5.7/5.7.1/qt-opensource-windows-x86-msvc2015_64-5.7.1.exe.mirrorlist),
Qt 5.7.1 for Linux 64-bit (http://download.qt.io/official_releases/qt/5.7/5.7.1/qt-opensource-linux-x64-5.7.1.run.mirrorlist), 
Qt 5.7.1 for macOS (http://download.qt.io/official_releases/qt/5.7/5.7.1/qt-opensource-mac-x64-clang-5.7.1.dmg.mirrorlist).
На Windows дополнительно потребуется установка MS Visual Studio 2015, на Linux (возможно) - "sudo apt-get install libgl1-mesa-dev", на macOS - Xcode.
Для сборки необходимо открыть проект weather4cast в IDE Qt Creator (устанавливается вместе с фреймворками по ссылкам выше) и собрать его (Build).

Развертывание
После сборки нужно создать для исполняемого файла программы необходимое рабочее окружение: библиотеки, плагины, и т.п. Воспользуйтесь этими инструкциями: 
http://doc.qt.io/qt-5/windows-deployment.html,
http://doc.qt.io/qt-5/linux-deployment.html,
http://doc.qt.io/qt-5/osx-deployment.html.

Например, в случае Windows необходимо выполнить файл [QTDIR]\5.7\msvc2015_64\bin\windeployqt.exe c параметрами --qmldir [директория с qml-файлами src\view] [путь к полученному на этапе сборки исполняемому файлу weather4cast.exe]. 
Пример: 
windeployqt.exe --qmldir D:\Programming\w\repo\weather4cast\src\view D:\Programming\w\repo\weather4cast\src\build-weather4cast-Desktop_Qt_5_7_1_MSVC2015_64bit-Release\release\weather4cast.exe
После этого дополнительно нужно разместить в директории с исполняемым файлом программы weather4cast.exe папку [QTDIR]\5.7\msvc2015_64\qml\QtWebEngine (windeployqt почему-то не копирует ее туда).
Дополнительно в директорию с программой необходимо поместить файлы city.list.json и map.html, находящиеся в директории res.
После выполнения этих действий вы получите директорию, из которой можно запускать программу.
