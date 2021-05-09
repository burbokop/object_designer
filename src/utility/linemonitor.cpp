#include "linemonitor.h"

#include <QPainter>

#include <src/math/kmath.h>

LineMonitor::LineMonitor(QQuickItem *parent) : KPaintedItem(parent) {
    //connect(this, &LineMonitor::sweepChanged, this, [this](){ if(autoUpdateEnabled()) update(); });
    connect(this, &LineMonitor::distanceChanged, this, [this](){ if(autoUpdateEnabled()) { update(); } });
}

void LineMonitor::paint(QPainter *painter) {
    if(groupCount() > 0 && trackCount() > 0 && painter->isActive()) {
        painter->setPen(color());
        int y = KMath::instance()->dmap(distance(), minDistance(), maxDistance(), 0, height());

        if(qAbs(lastY - y) > height() * 0.5) {
            hasLastY = false;
        }
        if(hasLastY && fillBlank() && qAbs(lastY - y) > 0) {
            for(int i = 0; i < qAbs(lastY - y); ++i) {
                if(y > lastY) {
                    paintSweepLine(painter, sweep(), lastY + i, width(), groupCount(), trackCount(), tan());
                } else {
                    paintSweepLine(painter, sweep(), lastY - i, width(), groupCount(), trackCount(), tan());
                }
            }
        } else {
            paintSweepLine(painter, sweep(), y, width(), groupCount(), trackCount(), tan());
        }

        lastY = y;
        hasLastY = true;

        if(m_sightRadius > 0 && m_sightCount > 0) {
            int sightX = KMath::instance()->dmap(m_sightRelativeX, 0, 1, 0, width());
            int sightY = KMath::instance()->dmap(m_sightRelativeY, 0, 1, 0, height());
            sightX += (m_sightGroup * width() / m_groupCount) + (m_sightTrack * width() / m_trackCount);
            painter->setOpacity(m_sightOpacity);

            sightX %= static_cast<int>(width());
            sightY %= static_cast<int>(height());

            if((qAbs(sightLastY - sightY) > height() * 0.5) || (qAbs(sightLastX - sightX) > width() * 0.5)) {
                sightHasLast = false;
            }


            auto p = painter->pen();
            p.setWidth(m_sightRadius * 2);
            painter->setPen(p);

            auto modder = [](auto val1, auto val2){
                if(val1 == val2)
                    return 0;

                return (val1 - val2) / qAbs(val1 - val2);
            };

            if(sightHasLast && fillBlank() && (qAbs(sightLastX - sightX) > 0 || qAbs(sightLastY - sightY) > 0)) {
                //for(int iy = 0; iy < qAbs(sightLastY - sightY); ++iy) {
                //    for(int ix = 0; ix < qAbs(sightLastX - sightX); ++ix) {
                //        painter->drawEllipse(sightX - m_sightRadius + ix, sightY - m_sightRadius + iy, m_sightRadius * 2, m_sightRadius * 2);
                //    }
                //}


                for(int i = 0; i < m_sightCount; ++i) {
                    //painter->drawLine(sightLastX, sightLastY, sightX + m_sightRadius * modder(sightLastX, sightX) * 2, sightY + m_sightRadius * modder(sightLastY, sightY) * 2);
                    paintSightTuple(painter, width(), sightCount(), trackCount(), sightLastX -  + m_sightRadius * modder(sightLastX, sightX) * 2, sightLastY - m_sightRadius * modder(sightLastY, sightY) * 2, sightX, sightY);
                }

            } else {
                //for(int i = 0; i < m_sightCount * m_trackCount; ++i) {
                //    int gi = i / m_trackCount;
                //    int ti = i % m_trackCount * 2 + 1;
                //
                //    int gxo = gi * width() / m_sightCount;
                //    int txo = ti * width() / m_sightCount / (m_trackCount * 2 + 1);
                //
                //    painter->drawLine(sightX + gxo + txo, sightY, sightX + gxo + txo, sightY);
                //}
                paintSightTuple(painter, width(), sightCount(), trackCount(), sightX, sightY, sightX, sightY);
                //painter->drawEllipse(sightX - m_sightRadius, sightY - m_sightRadius, m_sightRadius * 2, m_sightRadius * 2);
            }

            sightLastX = sightX;
            sightLastY = sightY;
            sightHasLast = true;
        }
    }
}

void LineMonitor::paintSweepLine(QPainter *painter, const QVector<double> &sweep, int y, double width, int groupCount, int trackCount, double tan) {
    if(groupCount > 0 && trackCount > 0) {
        double groupWidth = width / groupCount;
        auto iterrator = 0;
        for(auto i = 0, size = groupCount; i < size; ++i) {
            iterrator = paintGroup(painter, sweep, iterrator, groupWidth * i, y, groupWidth, trackCount, tan);
        }
    }
}

int LineMonitor::paintGroup(QPainter *painter, const QVector<double> &sweep, int iterator, int x, int y, double groupWidth, int trackCount, double tan) {
    if(trackCount > 0) {
        double count = trackCount * 2 + 1;
        double w = groupWidth / count;
        bool fill = false;
        for(auto i = 0; i < count; ++i) {
            if(fill) {
                iterator = paintTrack(painter, sweep, iterator, x + w * i, y, w, tan);
            }
            fill = !fill;
        }
    }
    return iterator;
}

int LineMonitor::paintTrack(QPainter *painter, const QVector<double> &sweep, int iterator, int x, int y, double trackWidth, double tan) {
    if(iterator < sweep.size()) {
        painter->setOpacity(sweep[iterator]);
    } else {
        painter->setOpacity(0);
    }
    iterator++;

    for(auto i = 0; i < trackWidth; ++i) {
        painter->drawPoint(x + i, y + tan * (x + i));
    }
    return iterator;
}


void LineMonitor::paintSightTuple(QPainter *painter, int width, int sightCount, int trackCount, int lastX, int lastY, int x, int y) {
    for(int i = 0; i < sightCount * trackCount; ++i) {
        const int gi = i / trackCount;
        const int ti = i % trackCount * 2 + 1;

        const int gxo = gi * width / sightCount;
        const int txo = ti * width / sightCount / (trackCount * 2 + 1);

        painter->drawLine(lastX + gxo + txo, lastY, x + gxo + txo, y);
    }
}
