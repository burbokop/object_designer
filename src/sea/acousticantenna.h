#ifndef ACOUSTICANTENNA_H
#define ACOUSTICANTENNA_H

#include <QObject>
#include <klibcore/src/kmacro.h>
#include "antenarotor.h"
#include "kcustomobject.h"
#include <src/lib/dynamicobject/jsonconfiguratedworker.h>
#include <klibcore/src/math/processors/krppressureprocessor.h>
#include <src/math/processors/kamplifier.h>
#include <src/math/processors/knoisegenerator.h>

class AcousticAntenna : public QObject {
    Q_OBJECT
    K_QML_INTERFACE(AcousticAntenna)

    K_READONLY_PROPERTY(AntenaRotor*, rotor, rotor, setRotor, rotorChanged, new AntenaRotor(this))
    K_READONLY_PROPERTY(QVector<double>, sweep, sweep, setSweep, sweepChanged, {})
    K_AUTO_PROPERTY(double, distance, distance, setDistance, distanceChanged, 0)
    K_AUTO_PROPERTY(double, angle, angle, setAngle, angleChanged, 0)
    K_AUTO_PROPERTY(int, xnCount, xnCount, setXnCount, xnCountChanged, 0)
    K_AUTO_PROPERTY(int, channelCount, channelCount, setChannelCount, channelCountChanged, 0)
    K_AUTO_PROPERTY(bool, state, state, setState, stateChanged, 0)
    K_AUTO_PROPERTY(double, coef, coef, setCoef, coefChanged, 1)
    K_AUTO_PROPERTY(double, afcoef, afcoef, setAfCoef, afcoefChanged, 1)

    K_AUTO_PROPERTY(double, sy, sy, setSy, syChanged, 0)
    K_AUTO_PROPERTY(double, sg, sg, setSg, sgChanged, 0)


    K_READONLY_PROPERTY(QObject*, sumator, sumator, setSumator, sumatorChanged, KDynamicObject::load<JsonConfiguratedWorker>(":/resources/prog.json", this))

    KRpPressureProcessor processor;
    KAmplifier amplifier;
    KNoiseGenerator noise;
    KNoiseGenerator noise2 = KNoiseGenerator(0.05, 12);
public:
    explicit AcousticAntenna(QObject *parent = nullptr);
public slots:
    void addPressure(double value);

signals:

};

#endif // ACOUSTICANTENNA_H
