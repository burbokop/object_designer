#include "kobjectlifetracker.h"

#include <QQuickItem>

KObjectLifeTracker::KObjectLifeTracker(QObject *parent) : QObject(parent) {

}

void KObjectLifeTracker::sequentlyDestoy(QObject *trigger, QObject *target) {
    if(trigger && target) {
        if(auto item = qobject_cast<QQuickItem*>(target)) {
            (void)item;
            //QQmlEngine *e;
            //e->
        } else {
            connect(trigger, &QObject::destroyed, target, &QObject::deleteLater);
        }
    }
}

void KObjectLifeTracker::registerWatcher(QObject *trigger, QVariant arg) {
    connect(trigger, &QObject::destroyed, this, [this, arg](){
        emit watcherTriggered(arg);
    });
}
