#include "vessel.h"

bool Vessel::readyRemove() const {
    return m_readyRemove;
}

Vessel::Vessel(QObject *parent) : QObject(parent) {
    
}
