#include <QPainterPath>
#include "math.h"
#include <QPainter>

#include "rppainter.h"

RpItem::RpItem(QQuickItem *parent) : QQuickPaintedItem(parent) {
    connect(this, &RpItem::countChanged, this, [this]() { update(); });
    connect(this, &RpItem::shiftAngleChanged, this, [this]() { update(); });
    connect(this, &RpItem::widthAngleChanged, this, [this]() { update(); });
}


void RpItem::paint(QPainter *painter) {
    auto wsize = painter->window().size() / 2;
    painter->translate(wsize.width(), wsize.height());
    auto minSize = std::min(wsize.width(), wsize.height());

    QPainterPath xnPath;

    //creating one XN

    const int n = 10;
    double massR[n + 1];
    /* W -> coefficient for cos(5 * w)=0.8 */
    //auto w = 7.37398;
    auto w = acos(0.8) / (m_widthAngle * M_PI / 180);
    double step = M_PI / (w * 2 * n);

    QVector<QPointF> points;
    for(int i = 0; i <= n; i++) {
        auto phi = i * step;
        //phi *= w;
        massR[i] = minSize * cos(w * phi);
        points.append({ massR[i] * sin(phi), -massR[i] * cos(phi) });
    }

    //painting first half
    bool frst = true;
    for(auto p: points) {
        if (frst) {
            xnPath.moveTo(p);
            frst = false;
        } else {
            xnPath.lineTo(p);
        }
    }
    //painting second half
    for(int i = points.size() - 1; i >= 0; i--)
    {
        xnPath.lineTo(-points.at(i).x(), points.at(i).y());
    }

    painter->setPen(QPen(Qt::transparent));
    painter->setBrush(QBrush(color()));
    qreal mainShift = (count() - 1) * (m_shiftAngle / 2);
    xnPath = QTransform().rotate(90 - mainShift).map(xnPath);

    for (int i = 0; i < count(); i++)
    {
        QPainterPath RotatedPath;
        QTransform shiftAngle;
        shiftAngle.rotate(m_shiftAngle * i);
        RotatedPath = shiftAngle.map(xnPath);
        painter->drawPath(RotatedPath);
    }
}
