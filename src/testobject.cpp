#include "testobject.h"

#include <QTimer>
#include <math.h>

TestObject::TestObject(QObject *parent) : QObject(parent) {
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        setSignal(std::sin(m_it += 0.1));
    });
    timer->start(100);
}
