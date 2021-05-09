#ifndef XNPAINTER_H
#define XNPAINTER_H
#include <QQuickPaintedItem>
#include <klibcore/src/kmacro.h>

class RpItem : public QQuickPaintedItem {
    Q_OBJECT
    K_QML_TYPE(RpItem)
    K_AUTO_PROPERTY(int, count, count, setCount, countChanged, 0)
    K_AUTO_PROPERTY(double, shiftAngle, shiftAngle, setShiftAngle, shiftAngleChanged, 0)
    K_AUTO_PROPERTY(double, widthAngle, widthAngle, setWidthAngle, widthAngleChanged, 0)
    K_AUTO_PROPERTY(QColor, color, color, setColor, colorChanged, QColor(255,  0, 0, 15))
public:
    RpItem(QQuickItem *parent = nullptr);

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter) override;
};

#endif // XNPAINTER_H
