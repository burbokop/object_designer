#include "mousespy.h"

#include <QEvent>
#include <QMouseEvent>

MouseSpy::MouseSpy(QObject *parent) : QObject(parent) {
    connect(this, &MouseSpy::targetChanged, this, [this](QObject *newObj){
        if(last)
            last->installEventFilter(nullptr);
        newObj->installEventFilter(this);
        last = newObj;
    });
}


bool MouseSpy::eventFilter(QObject *watched, QEvent *event) {
    QEvent::Type t = event->type();
    if (t == QEvent::MouseButtonDblClick
            || t == QEvent::MouseButtonPress
            || t == QEvent::MouseButtonRelease
            || t == QEvent::MouseMove) {
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        emit mouseEventDetected(e->x(), e->y());
        setMouseX(e->x());
        setMouseY(e->y());
    }

    if (t == QEvent::DragMove) {
        QDragMoveEvent* e = static_cast<QDragMoveEvent*>(event);
        emit mouseEventDetected(e->pos().x(), e->pos().y());
        setMouseX(e->pos().x());
        setMouseY(e->pos().y());
    }
    return QObject::eventFilter(watched, event);
}
