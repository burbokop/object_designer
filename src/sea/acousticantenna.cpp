#include "acousticantenna.h"

#include <QTimer>
#include <QtDebug>

#include <src/math/processors/kintegratorprocessor.h>

AcousticAntenna::AcousticAntenna(QObject *parent) : QObject(parent) {
    //QTimer *timer = new QTimer();
    //connect(timer, &QTimer::timeout, this, [this]() {
    ////    qDebug() << "timeout" << bearing();
    //});
    //timer->start(1000);
    //
    //connect(this, &AcousticAntenna::bearingChanged, this, [](auto value) {
    ////    qDebug() << "bearingChanged" << value;
    //});


    setXnCount(12);
    setChannelCount(3);
    processor.setMaxVelocity(1);
    processor.setMinVelocity(-1);
    processor.setXnShiftAngle(12);

    //test()->addProperty("aaa", "int", 2);
    //test()->addProperty("bbb", "int", 3);
    //test()->ready();



    connect(this, &AcousticAntenna::distanceChanged, this, [](auto v){
        (void)v;
//        qDebug() << "1" << v;
    });



    processor << &amplifier << &noise << &noise;





    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        processor.setXnCount(xnCount());
        processor.setChannalCount(channelCount());
        processor.proceed();
        setSweep(processor.sweep());
        if(state()) {
            addPressure(angle());
        }
    });
    timer->start(40);

    connect(this, &AcousticAntenna::coefChanged, this, [this](auto v){ amplifier.setCoeficient(v); });

}

void AcousticAntenna::addPressure(double value) {
    processor.addPressure(value, afcoef(), 0, 1000);
}
