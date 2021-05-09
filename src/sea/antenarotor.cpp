#include "antenarotor.h"

#include <src/math/kmath.h>

#include <QTimer>

void AntenaRotor::onAngleChanged() {
    setResultAngle(KMath::instance()->constrainDegrees(inputAngle() + autoAngle()));
    setStern(resultAngle() > 90 && resultAngle() < 270);
}

AntenaRotor::AntenaRotor(QObject *parent) : QObject(parent) {
    connect(this, &AntenaRotor::autoAngleChanged, this, &AntenaRotor::onAngleChanged);
    connect(this, &AntenaRotor::inputAngleChanged, this, &AntenaRotor::onAngleChanged);

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, [this]() {
        const auto speed = 0.75;
        setAutoAngle(KMath::instance()->constrainDegrees(autoAngle() + speed));
    });

    connect(this, &AntenaRotor::autoRotateChanged, this, [updateTimer](auto s){
        if(s) {
            updateTimer->start(50);
        } else {
            updateTimer->stop();
        }
    });
}
