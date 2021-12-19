#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#include <src/kmacro.h>

class TestObject : public QObject {
    Q_OBJECT
    K_QML_TYPE(TestObject)
    double m_it = 0;
public:
    Q_INVOKABLE explicit TestObject(QObject *parent = nullptr);
    K_READONLY_PROPERTY(double, signal, signal, setSignal, signalChanged, 0)

signals:

};

#endif // TESTOBJECT_H
