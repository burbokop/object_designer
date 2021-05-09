#ifndef MOUSESPY_H
#define MOUSESPY_H

#include <QObject>

#include <klibcore/src/kmacro.h>

class MouseSpy : public QObject {
    Q_OBJECT
    K_QML_TYPE(MouseSpy)
    K_AUTO_PROPERTY(QObject*, target, target, setTarget, targetChanged, nullptr)
    K_READONLY_PROPERTY(int, mouseX, mouseX, setMouseX, mouseXChanged, 0)
    K_READONLY_PROPERTY(int, mouseY, mouseY, setMouseY, mouseYChanged, 0)
    QObject *last = nullptr;
public:
    explicit MouseSpy(QObject *parent = nullptr);

signals:
    void mouseEventDetected(int x, int y);

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // MOUSESPY_H
