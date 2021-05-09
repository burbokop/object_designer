#ifndef LINEMONITOR_H
#define LINEMONITOR_H

#include <QQuickItem>
#include <klibcore/src/kmacro.h>
#include <klibcore/src/graphics/kpainteditem.h>


//TODO: move this construction anywhare
Q_DECLARE_METATYPE(QVector<double>)
inline QDataStream& operator<<(QDataStream& out, const QVector<double>& v) {
    for(auto vv : v)
        out << vv;
    return out;
}
inline QDataStream& operator>>(QDataStream& in, QVector<double>& v) {
    for(auto vv : v)
        in >> vv;
    return in;
}
inline int qVectorDoubleStreamOperatorsRegistration = qRegisterMetaTypeStreamOperators<QVector<double>>();
//-------------------------------------


class LineMonitor : public KPaintedItem {
    Q_OBJECT
    K_QML_TYPE(LineMonitor)
    K_AUTO_PROPERTY(QVector<double>, sweep, sweep, setSweep, sweepChanged, {})
    K_AUTO_PROPERTY(double, distance, distance, setDistance, distanceChanged, 0)
    K_AUTO_PROPERTY(double, minDistance, minDistance, setMinDistance, minDistanceChanged, 0)
    K_AUTO_PROPERTY(double, maxDistance, maxDistance, setMaxDistance, maxDistanceChanged, 0)
    K_AUTO_PROPERTY(int, groupCount, groupCount, setGroupCount, groupCountChanged, 0)
    K_AUTO_PROPERTY(int, trackCount, trackCount, setTrackCount, trackCountChanged, 0)

    K_AUTO_PROPERTY(bool, fillBlank, fillBlank, setFillBlank, fillBlankChanged, true)
    K_AUTO_PROPERTY(double, tan, tan, setTan, tanChanged, 0)
    K_AUTO_PROPERTY(QColor, color, color, setColor, colorChanged, "#000000")

    K_AUTO_PROPERTY(double, sightRelativeX, sightRelativeX, setSightRelativeX, sightRelativeXChanged, 0)
    K_AUTO_PROPERTY(double, sightRelativeY, sightRelativeY, setSightRelativeY, sightRelativeYChanged, 0)
    K_AUTO_PROPERTY(int, sightGroup, sightGroup, setSightGroup, sightGroupChanged, 0)
    K_AUTO_PROPERTY(int, sightTrack, sightTrack, setSightTrack, sightTrackChanged, 0)
    K_AUTO_PROPERTY(int, sightRadius, sightRadius, setSightRadius, sightRadiusChanged, 1)
    K_AUTO_PROPERTY(double, sightOpacity, sightOpacity, setSightOpacity, sightOpacityChanged, 1)
    K_AUTO_PROPERTY(double, sightCount, sightCount, setSightCount, sightCountChanged, 1)

    int lastY = 0;
    bool hasLastY = false;

    int sightLastX = 0;
    int sightLastY = 0;
    bool sightHasLast = false;
public:
    static void paintSweepLine(QPainter *painter, const QVector<double> &sweep, int y, double width, int groupCount, int trackCount, double tan);
    static int paintGroup(QPainter *painter, const QVector<double> &sweep, int iterator, int x, int y, double groupWidth, int trackCount, double tan);
    static int paintTrack(QPainter *painter, const QVector<double> &sweep, int iterator, int x, int y, double trackWidth, double tan);
    static void paintSightTuple(QPainter *painter, int width, int sightCount, int trackCount, int lastX, int lastY, int x, int y);
    LineMonitor(QQuickItem *parent = nullptr);

signals:


    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;
};


#endif // LINEMONITOR_H
