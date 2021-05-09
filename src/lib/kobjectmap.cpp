#include "kobjectmap.h"

QMap<QObject *, QObject *> KObjectMap::data() const
{
    return m_data;
}

void KObjectMap::insert(QObject *key, QObject *value) {
    m_data[key] = value;
    connect(key, &QObject::destroyed, this, [key, this](){
        m_data.remove(key);
    });

    connect(value, &QObject::destroyed, this, [value, this](){
        for(auto it = m_data.begin(); it != m_data.end(); ++it) {
            if(it.value() == value) {
                m_data.remove(it.key());
            }
        }
    });
}

QObject *KObjectMap::value(QObject *key) {
    if(key == nullptr)
        return nullptr;

    return m_data[key];
}

KObjectMap::KObjectMap(QObject *parent) : QObject(parent) {

}
