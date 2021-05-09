#ifndef BEAMTUBEEFFECT_H
#define BEAMTUBEEFFECT_H

#include <QQuickPaintedItem>
#include <QQuickItemGrabResult>
#include <klibcore/src/kmacro.h>

class BeamTubeEffect : public QQuickPaintedItem {
    Q_OBJECT
    K_QML_TYPE(BeamTubeEffect)
    K_AUTO_PROPERTY(QQuickItem *, source, source, setSource, sourceChanged, nullptr)
    QSharedPointer<QQuickItemGrabResult> grabResult = nullptr;
public:
    BeamTubeEffect(QQuickItem *parent = nullptr);

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter) override;
};

#endif // BEAMTUBEEFFECT_H
