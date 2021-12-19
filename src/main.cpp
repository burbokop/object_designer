#include "client1.h"
#include "simplenegot.h"

#include <klibcore/src/memcontrol/kmodulehandler.h>

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

    return app.exec();
}
