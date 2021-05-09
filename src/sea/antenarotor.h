#ifndef ANTENAROTOR_H
#define ANTENAROTOR_H

#include <QObject>
#include <klibcore/src/kmacro.h>

class AntenaRotor : public QObject {
    Q_OBJECT
    K_QML_INTERFACE(AntenaRotor)
    K_READONLY_PROPERTY(double, resultAngle, resultAngle, setResultAngle, resultAngleChanged, 0)
    K_READONLY_PROPERTY(double, autoAngle, autoAngle, setAutoAngle, autoAngleChanged, 0)
    K_READONLY_PROPERTY(bool, stern, stern, setStern, sternChanged, false)
    K_AUTO_PROPERTY(double, inputAngle, inputAngle, setInputAngle, inputAngleChanged, 0)

    K_AUTO_PROPERTY(double, interval, interval, setInterval, intervalChanged, 0)
    K_AUTO_PROPERTY(bool, autoRotate, autoRotate, setAutoRotate, autoRotateChanged, 0)

private slots:
   void onAngleChanged();

public:
    explicit AntenaRotor(QObject *parent = nullptr);

signals:

};

#endif // ANTENAROTOR_H
