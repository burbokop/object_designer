#include "beamtubeeffect.h"

#include <QPainter>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QtDebug>
#include <QTimer>
//#include <private/qsh

BeamTubeEffect::BeamTubeEffect(QQuickItem *parent) : QQuickPaintedItem(parent) {
    //setFlag(ItemHasContents);
    connect(this, &BeamTubeEffect::sourceChanged, this, [this]() {
        update();
    });

    //QTimer::singleShot(5000, this, [this]{
    //    grabResult = source()->grabToImage();
    //});

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        if(source()->window()) {
            grabResult = source()->grabToImage();
            update();
        }
    });
    timer->start(100);



    QTimer *timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, [this](){
    });
    timer2->start(100);
}


void BeamTubeEffect::paint(QPainter *painter) {
    if(painter->isActive(), source() && grabResult) {
        auto sourceImage = grabResult->image();

        //int alpha = static_cast<int>(std::min(pressure * 255 * parent->brightness, 255.));
        //if (x >= 0 && y >= 0 && x < parent->image.width() && y < parent->image.height() && parent->mask.pixel(x, y) != 0) {
        //    pixels[(y * parent->image.width()) + x] = qRgba(parent->color().red(), parent->color().green(), parent->color().blue(), alpha);
        //}

        auto pixelCount = sourceImage.width() * sourceImage.height();
        uint32_t *pixels = reinterpret_cast<uint32_t*>(sourceImage.bits());
        for(int i = 0; i < pixelCount; ++i) {
            if(pixels[i] > 128) {
                pixels[i] = pixels[i] * 2;
            } else {
                pixels[i] = pixels[i] / 2;
            }
        }
        painter->drawImage(QPoint(), sourceImage);
    }
}
