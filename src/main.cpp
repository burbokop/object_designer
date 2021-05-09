#include "client1.h"
#include "simplenegot.h"

#include <src/utility/kmodulehandler.h>

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QElapsedTimer>

#include <src/network/klocalbeacon.h>
#include <src/network/klocalretranslator.h>



int main(int argc, char **argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    KLocalBeacon beacon;
    beacon.start(4444);

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/resources/main.qml"));
    //engine.load(QUrl("qrc:/resources/LocalBeaconTest.qml"));

    SimpleNegot negot1;
    SimpleNegot negot2;

    QElapsedTimer timer;
    std::vector<uint8_t> tmp;



    negot1.writePackage({ { 12, 23, }, { 1, 2 } });

    negot2.f = [](auto d){
        qDebug() << "fff" << d;
    };

    while (1) {
        tmp = negot1.proceed(tmp, timer.elapsed());
        tmp = negot2.proceed(tmp, timer.elapsed());
    }


    return app.exec();
}
