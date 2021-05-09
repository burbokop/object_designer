#ifndef VESSEL_H
#define VESSEL_H

#include <QObject>

class Vessel : public QObject {
    Q_OBJECT
    bool m_readyRemove = false;
public:
    explicit Vessel(QObject *parent = nullptr);

    void remove() { m_readyRemove = true; };
    bool readyRemove() const;
signals:

};

#endif // VESSEL_H
