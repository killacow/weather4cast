#include "testclass.h"



TestClass::TestClass(QObject *parent) : QObject(parent) {
    startTimer(5000);   // 1-second timer
    //    m_str = "qwerty";
}

void TestClass::responseRefreshLocation(bool errorFlag, const QGeoCoordinate &location) {
    Q_UNUSED(errorFlag)
}

void TestClass::timerEvent(QTimerEvent *event) {
    killTimer(event->timerId());
    qDebug() << "Timer ID:" << event->timerId();
    //m_str = "asdfg";
    emit sig("opa");
    emit locationUpdated(QGeoCoordinate(57,58));
    //emit strChanged();
}
